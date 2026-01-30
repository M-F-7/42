### STAGE 1: Build ###

FROM node:18-alpine AS build

RUN apk add --no-cache curl

WORKDIR /app

COPY . .

RUN npm install && npm run build


### STAGE 2: Production ###

FROM node:18-alpine AS production

WORKDIR /app

COPY --from=build /app/dist ./dist
COPY --from=build /app/package.json ./package.json

RUN npm install --only=production

RUN addgroup -g 10005 -S tournamentsgroup && \
    adduser -S tournamentsuser -u 10005 -G tournamentsgroup

RUN chown -R tournamentsuser:tournamentsgroup /app
USER tournamentsuser

EXPOSE 4005

CMD ["node", "dist/index.js"]
