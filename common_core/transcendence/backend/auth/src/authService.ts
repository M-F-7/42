import bcrypt from 'bcryptjs';
import jwt from 'jsonwebtoken';
import { dbService } from '../../src/services/databaseService.js';
import { User, LoginRequest, RegisterRequest, ApiResponse } from '../../utils/interfaces.js';
import { config } from '../../gateway/src/config.js';

export class AuthService {
  async register(userData: RegisterRequest): Promise<ApiResponse<{ user: Omit<User, 'password'>; token: string }>> {
    try {
      const existingUser = await dbService.getUserByUsername(userData.username);
      if (existingUser) {
        return {
          success: false,
          error: 'Username already exists',
          timestamp: new Date()
        };
      }

      const existingEmail = await dbService.getUserByEmail(userData.email);
      if (existingEmail) {
        return {
          success: false,
          error: 'Email already exists',
          timestamp: new Date()
        };
      }

      const hashedPassword = await bcrypt.hash(userData.password, config.bcrypt.saltRounds); // hashing password

      // Create user
      const user = await dbService.createUser({
        username: userData.username,
        email: userData.email,
        password: hashedPassword,
        role: 'user'
      });

      // Generate token
      const token = this.generateToken(user.id);

      // Remove password from response
      const { password: _, ...userWithoutPassword } = user;

      return {
        success: true,
        data: {
          user: userWithoutPassword,
          token
        },
        message: 'User registered successfully',
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Registration failed',
        timestamp: new Date()
      };
    }
  }

  async login(loginData: LoginRequest): Promise<ApiResponse<{ user: Omit<User, 'password'>; token: string }>> {
    try {
      // Find user
      const user = await dbService.getUserByUsername(loginData.username);
      if (!user || !user.password) {
        return {
          success: false,
          error: 'Invalid credentials',
          timestamp: new Date()
        };
      }

      // Check password
      const isValidPassword = await bcrypt.compare(loginData.password, user.password);
      if (!isValidPassword) {
        return {
          success: false,
          error: 'Invalid credentials',
          timestamp: new Date()
        };
      }

      // Update user status
      await dbService.updateUser(user.id, {
        isOnline: true,
        lastActive: new Date()
      });

      // Generate token
      const token = this.generateToken(user.id);

      // Remove password from response
      const { password: _, ...userWithoutPassword } = user;

      return {
        success: true,
        data: {
          user: userWithoutPassword,
          token
        },
        message: 'Login successful',
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Login failed',
        timestamp: new Date()
      };
    }
  }

  async logout(userId: string): Promise<ApiResponse> {
    try {
      await dbService.updateUser(userId, {
        isOnline: false,
        lastActive: new Date()
      });

      return {
        success: true,
        message: 'Logout successful',
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Logout failed',
        timestamp: new Date()
      };
    }
  }

  async verifyToken(token: string): Promise<ApiResponse<User>> {
    try {
      const decoded = jwt.verify(token, config.jwt.secret) as { userId: string };
      const user = await dbService.getUserById(decoded.userId);
      
      if (!user) {
        return {
          success: false,
          error: 'User not found',
          timestamp: new Date()
        };
      }

      const { password: _, ...userWithoutPassword } = user;
      return {
        success: true,
        data: userWithoutPassword as User,
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Invalid token',
        timestamp: new Date()
      };
    }
  }

  private generateToken(userId: string): string {
    return jwt.sign(
      { userId },
      config.jwt.secret,
      { expiresIn: '24h' } // Fixed value to avoid type issues
    );
  }

  async getUserProfile(userId: string): Promise<ApiResponse<Omit<User, 'password'>>> {
    try {
      const user = await dbService.getUserById(userId);
      if (!user) {
        return {
          success: false,
          error: 'User not found',
          timestamp: new Date()
        };
      }

      const { password: _, ...userWithoutPassword } = user;

      return {
        success: true,
        data: userWithoutPassword,
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to get user profile',
        timestamp: new Date()
      };
    }
  }
}

export const authService = new AuthService();