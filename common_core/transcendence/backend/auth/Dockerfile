FROM node:18-alpine

RUN apk add --no-cache curl

WORKDIR /app

COPY package*.json ./

RUN npm install --omit=dev && npm cache clean --force
COPY . .

RUN addgroup -g 10000 -S authgroup && \
    adduser -S authuser -u 10000 -G authgroup

RUN chown -R authuser:authgroup /app
USER authuser

EXPOSE 4000

CMD ["node", "index.js"]