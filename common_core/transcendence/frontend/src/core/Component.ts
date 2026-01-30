export abstract class Component {
	protected container: HTMLElement;

	constructor(containerId: string = 'main-content') {
		const container = document.getElementById(containerId);
		if (!container) {
			throw new Error(`Container with id '${containerId}' not found`);
		}
		this.container = container;
	}

	abstract render(): string;

	mount(): void {
		this.container.innerHTML = `<div class="container mx-auto px-4 py-8">${this.render()}</div>`;
		this.afterMount();
	}

	protected afterMount(): void {

	}

	protected escapeHtml(text: string): string {
		const div = document.createElement('div');
		div.textContent = text;
		return div.innerHTML;
	}
}


