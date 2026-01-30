
export class StorageService {
	private static instance: StorageService;

	private constructor() { }

	static getInstance(): StorageService {
		if (!StorageService.instance) {
			StorageService.instance = new StorageService();
		}
		return StorageService.instance;
	}

	set<T>(key: string, value: T): void {
		try {
			localStorage.setItem(key, JSON.stringify(value));
		} catch (error) {
			console.error(`Error saving to localStorage: ${key}`, error);
		}
	}

	get<T>(key: string): T | null {
		try {
			const item = localStorage.getItem(key);
			return item ? JSON.parse(item) : null;
		} catch (error) {
			console.error(`Error reading from localStorage: ${key}`, error);
			return null;
		}
	}

	remove(key: string): void {
		try {
			localStorage.removeItem(key);
		} catch (error) {
			console.error(`Error removing from localStorage: ${key}`, error);
		}
	}

	clear(): void {
		try {
			localStorage.clear();
		} catch (error) {
			console.error('Error clearing localStorage', error);
		}
	}
}


