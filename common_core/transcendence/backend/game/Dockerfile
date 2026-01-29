FROM node:18-alpine

RUN apk add --no-cache curl

WORKDIR /app

COPY package*.json ./

RUN npm install --omit=dev && npm cache clean --force
COPY . .

RUN addgroup -g 10002 -S gamegroup && \
    adduser -S gameuser -u 10002 -G gamegroup

RUN chown -R gameuser:gamegroup /app
USER gameuser

EXPOSE 4002

CMD ["node", "index.js"]