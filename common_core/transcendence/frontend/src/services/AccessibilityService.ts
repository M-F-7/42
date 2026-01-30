export class AccessibilityService {
	private static instance: AccessibilityService;

	private highContrast = false;
	private fontScale = 1;
	private readonly STORAGE_KEY = 'gpoat_accessibility';

	private constructor() { }

	public static getInstance(): AccessibilityService {
		if (!AccessibilityService.instance) {
			AccessibilityService.instance = new AccessibilityService();
		}
		return AccessibilityService.instance;
	}

	public init(): void {
		try {
			const raw = localStorage.getItem(this.STORAGE_KEY);
			if (raw) {
				const data = JSON.parse(raw);
				this.highContrast = !!data.highContrast;
				this.fontScale = typeof data.fontScale === 'number' ? data.fontScale : 1;
			}
		} catch {

		}
		this.apply();
	}

	private persist(): void {
		localStorage.setItem(
			this.STORAGE_KEY,
			JSON.stringify({
				highContrast: this.highContrast,
				fontScale: this.fontScale,
			})
		);
	}

	private apply(): void {
		const root = document.documentElement;

		root.classList.toggle('high-contrast', this.highContrast);

		root.style.fontSize = `${this.fontScale * 100}%`;
	}

	public toggleHighContrast(): void {
		this.highContrast = !this.highContrast;
		this.persist();
		this.apply();
	}

	public increaseFont(): void {
		this.fontScale = Math.min(1.4, this.fontScale + 0.1);
		this.persist();
		this.apply();
	}

	public decreaseFont(): void {
		this.fontScale = Math.max(0.8, this.fontScale - 0.1);
		this.persist();
		this.apply();
	}
}
