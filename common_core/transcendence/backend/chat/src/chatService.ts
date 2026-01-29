import { dbService } from '../../src/services/databaseService.js';
import { ChatMessage, User, ApiResponse } from '../../utils/interfaces.js';

export class ChatService {
  async sendMessage(senderId: string, content: string, channelId: string = 'general'): Promise<ApiResponse<ChatMessage>> {
    try {
      const sender = await dbService.getUserById(senderId);
      if (!sender) {
        return {
          success: false,
          error: 'Sender not found',
          timestamp: new Date()
        };
      }

      const message = await dbService.createChatMessage({
        senderId,
        content: content.trim(),
        channelId,
        isGlobal: channelId === 'general',
        type: 'normal'
      });

      return {
        success: true,
        data: message,
        message: 'Message sent successfully',
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to send message',
        timestamp: new Date()
      };
    }
  }

  async getChannelMessages(channelId: string, limit: number = 50, offset: number = 0): Promise<ApiResponse<ChatMessage[]>> {
    try {
      const messages = await dbService.getChatMessages(channelId, limit, offset);
      return {
        success: true,
        data: messages,
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to get messages',
        timestamp: new Date()
      };
    }
  }

  async getRecentMessages(limit: number = 20): Promise<ApiResponse<ChatMessage[]>> {
    try {
      const messages = await dbService.getRecentChatMessages(limit);
      return {
        success: true,
        data: messages,
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to get recent messages',
        timestamp: new Date()
      };
    }
  }

  async deleteMessage(messageId: string, userId: string): Promise<ApiResponse<boolean>> {
    try {
      const message = await dbService.getChatMessageById(messageId);
      if (!message) {
        return {
          success: false,
          error: 'Message not found',
          timestamp: new Date()
        };
      }

      // Only allow sender to delete their own message
      if (message.senderId !== userId) {
        return {
          success: false,
          error: 'Unauthorized to delete this message',
          timestamp: new Date()
        };
      }

      const deleted = await dbService.deleteChatMessage(messageId);
      if (!deleted) {
        return {
          success: false,
          error: 'Failed to delete message',
          timestamp: new Date()
        };
      }

      return {
        success: true,
        data: true,
        message: 'Message deleted successfully',
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to delete message',
        timestamp: new Date()
      };
    }
  }

  async moderateMessage(messageId: string, moderatorId: string, action: 'delete' | 'flag'): Promise<ApiResponse<boolean>> {
    try {
      const moderator = await dbService.getUserById(moderatorId);
      if (!moderator || moderator.role !== 'admin') {
        return {
          success: false,
          error: 'Unauthorized action',
          timestamp: new Date()
        };
      }

      const message = await dbService.getChatMessageById(messageId);
      if (!message) {
        return {
          success: false,
          error: 'Message not found',
          timestamp: new Date()
        };
      }

      if (action === 'delete') {
        const deleted = await dbService.deleteChatMessage(messageId);
        return {
          success: deleted,
          data: deleted,
          message: deleted ? 'Message moderated successfully' : 'Failed to moderate message',
          timestamp: new Date()
        };
      } else if (action === 'flag') {
        // Flag message for review (implementation depends on requirements)
        return {
          success: true,
          data: true,
          message: 'Message flagged for review',
          timestamp: new Date()
        };
      }

      return {
        success: false,
        error: 'Invalid moderation action',
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to moderate message',
        timestamp: new Date()
      };
    }
  }

  async getUserChatHistory(userId: string, limit: number = 100): Promise<ApiResponse<ChatMessage[]>> {
    try {
      const user = await dbService.getUserById(userId);
      if (!user) {
        return {
          success: false,
          error: 'User not found',
          timestamp: new Date()
        };
      }

      const messages = await dbService.getUserChatMessages(userId, limit);
      return {
        success: true,
        data: messages,
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to get user chat history',
        timestamp: new Date()
      };
    }
  }

  async createPrivateChannel(user1Id: string, user2Id: string): Promise<ApiResponse<string>> {
    try {
      const user1 = await dbService.getUserById(user1Id);
      const user2 = await dbService.getUserById(user2Id);

      if (!user1 || !user2) {
        return {
          success: false,
          error: 'One or both users not found',
          timestamp: new Date()
        };
      }

      // Create unique channel ID for private conversation
      const channelId = `private_${[user1Id, user2Id].sort().join('_')}`;

      return {
        success: true,
        data: channelId,
        message: 'Private channel created',
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to create private channel',
        timestamp: new Date()
      };
    }
  }

  async getOnlineUsers(): Promise<ApiResponse<User[]>> {
    try {
      const users = await dbService.getOnlineUsers();
      return {
        success: true,
        data: users,
        timestamp: new Date()
      };
    } catch (error) {
      return {
        success: false,
        error: 'Failed to get online users',
        timestamp: new Date()
      };
    }
  }
}

export const chatService = new ChatService();