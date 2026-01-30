import { ApiService } from './ApiService';

const api = ApiService.getInstance();

export const PresenceService = {
  online: () => api.post('/user/status/online', {}),
  offline: () => api.post('/user/status/offline', {}),
};
