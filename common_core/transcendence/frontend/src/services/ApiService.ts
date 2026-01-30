import type { ApiResponse } from '../types';
import { StorageService } from './StorageService';

export class ApiService {
	private static instance: ApiService;
	private baseUrl: string;
	private storage: StorageService;

	private constructor() {
		this.baseUrl = 'https://localhost:3001';
		this.storage = StorageService.getInstance();
	}

	static getInstance(): ApiService {
		if (!ApiService.instance) {
			ApiService.instance = new ApiService();
		}
		return ApiService.instance;
	}

	getBaseUrl(): string {
		return this.baseUrl;
	}

	private getHeaders(): HeadersInit {
		const headers: HeadersInit = {
			'Content-Type': 'application/json',
		};

		const token = this.storage.get<string>('authToken');
		if (token) {
			headers['Authorization'] = `Bearer ${token}`;
		}

		return headers;
	}

	private handleUnauthorized(): void {
		try {
			this.storage.set('authToken', null as any);
			this.storage.set('pongUser', null as any);
		} catch (_) {
		}

		try {
			localStorage.removeItem('authToken');
			localStorage.removeItem('pongUser');
		} catch (_) { }

		try {
			document.cookie.split(';').forEach((cookie) => {
				document.cookie = cookie
					.replace(/^ +/, '')
					.replace(/=.*/, '=;expires=' + new Date(0).toUTCString() + ';path=/');
			});
		} catch (_) { }

		window.location.href = '/';
	}

	private async handleResponse<T>(response: Response): Promise<ApiResponse<T>> {
		let data: any = null;
		try {
			data = await response.json();
		} catch (_) {

		}

		const isUnauthorized =
			response.status === 401 ||
			(data &&
				data.success === false &&
				(data.message === 'User not found' ||
					data.message === 'Invalid token'));

		if (isUnauthorized) {
			this.handleUnauthorized();
		}

		if (response.ok) {
			return data ?? { success: true } as ApiResponse<T>;
		}


		return (
			data ?? {
				success: false,
				message: `HTTP error! status: ${response.status}`,
			}
		);
	}

	async get<T>(endpoint: string): Promise<ApiResponse<T>> {
		try {
			const response = await fetch(`${this.baseUrl}${endpoint}`, {
				method: 'GET',
				credentials: 'include',
				headers: this.getHeaders(),
			});

			return await this.handleResponse<T>(response);
		} catch (error) {
			console.error('GET request failed:', error);
			return {
				success: false,
				message: error instanceof Error ? error.message : 'Request failed',
			};
		}
	}

	async post<T>(
		endpoint: string,
		data?: any,
		options?: { keepalive?: boolean }
	): Promise<ApiResponse<T>> {
		const hasBody = data !== undefined && data !== null;
		const headers = this.getHeaders();

		if (!hasBody) {
			delete (headers as any)['Content-Type'];
		}

		const response = await fetch(`${this.baseUrl}${endpoint}`, {
			method: 'POST',
			headers,
			credentials: 'include',
			body: hasBody ? JSON.stringify(data) : undefined,
			keepalive: Boolean(options?.keepalive),
		});

		return this.handleResponse<T>(response);
	}


	async put<T>(endpoint: string, data?: any): Promise<ApiResponse<T>> {
		try {
			const response = await fetch(`${this.baseUrl}${endpoint}`, {
				method: 'PUT',
				headers: this.getHeaders(),
				credentials: 'include',
				body: data ? JSON.stringify(data) : undefined,
			});

			return await this.handleResponse<T>(response);
		} catch (error) {
			console.error('PUT request failed:', error);
			return {
				success: false,
				message: error instanceof Error ? error.message : 'Request failed',
			};
		}
	}

	async delete<T>(endpoint: string): Promise<ApiResponse<T>> {
		try {
			const response = await fetch(`${this.baseUrl}${endpoint}`, {
				method: 'DELETE',
				credentials: 'include',
				headers: this.getHeaders(),
			});

			return await this.handleResponse<T>(response);
		} catch (error) {
			console.error('DELETE request failed:', error);
			return {
				success: false,
				message: error instanceof Error ? error.message : 'Request failed',
			};
		}
	}

	async postForm<T>(url: string, formData: FormData): Promise<T> {
		const token = this.storage.get<string>('authToken');
		const res = await fetch(this.baseUrl + url, {
			method: 'POST',
			credentials: 'include',
			headers: {
				...(token ? { Authorization: `Bearer ${token}` } : {}),
			},
			body: formData,
		});

		if (res.status === 401) {
			this.handleUnauthorized();
		}
		return res.json();
	}

}
