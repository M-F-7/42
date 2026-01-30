### STAGE 1: Build ###

FROM node:18-alpine AS build

WORKDIR /app

COPY . .

RUN npm install && npm run build

### STAGE 2: Production ###
FROM node:18-alpine AS production

WORKDIR /app

COPY --from=build /app/dist ./dist
COPY --from=build /app/package*.json ./
COPY --from=build /app/node_modules ./node_modules

CMD ["node", "dist/index.js"]

