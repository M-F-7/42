export type RouteHandler = () => Promise<void> | void;

export interface Route {
  path: string;
  handler: RouteHandler;
}

export class Router {
  private static instance: Router;
  private routes: Map<string, RouteHandler> = new Map();
  private currentRoute: string = 'home';

  private constructor() {
    window.addEventListener('popstate', () => {
      const route = this.getRouteFromLocation();
      this.go(route, { push: false });
    });
  }

  static getInstance(): Router {
    if (!Router.instance) {
      Router.instance = new Router();
    }
    return Router.instance;
  }

  register(path: string, handler: RouteHandler): void {
    this.routes.set(path, handler);
  }

  async navigate(path: string): Promise<void> {
    await this.go(path, { push: true });
  }

  async init(): Promise<void> {
    const initialRoute = this.getRouteFromLocation();
    await this.go(initialRoute, { push: false });
  }

  getCurrentRoute(): string {
    return this.currentRoute;
  }

  private async go(
    path: string,
    options: { push: boolean }
  ): Promise<void> {
    let handler = this.routes.get(path);

    if (!handler) {
      console.warn(`Route not found: ${path}, fallback to home`);
      handler = this.routes.get('home') || undefined;
      path = 'home';
      if (!handler) return;
    }

    this.currentRoute = path;

    if (options.push) {
      history.pushState({ route: path }, '', `#${path}`);
    }

    await handler();
  }
  private getRouteFromLocation(): string {
    const hash = window.location.hash.replace('#', '');

    if (hash && this.routes.has(hash)) {
      return hash;
    }

    return 'home';
  }
}
