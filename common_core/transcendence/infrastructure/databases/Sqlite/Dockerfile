FROM node:18-alpine

RUN apk add --no-cache curl

WORKDIR /app


COPY package*.json ./

RUN npm install && npm cache clean --force


COPY . .


RUN npx tsc


RUN mkdir -p /app/data && \
    addgroup -g 10007 -S databasegroup && \
    adduser -S databaseuser -u 10007 -G databasegroup && \
    chown -R databaseuser:databasegroup /app

USER databaseuser

EXPOSE 4007


CMD ["node", "dist/index.js"]
