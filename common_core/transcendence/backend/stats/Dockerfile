FROM node:18-alpine

RUN apk add --no-cache curl

WORKDIR /app

COPY package*.json ./

RUN npm install --omit=dev && npm cache clean --force
COPY . .

RUN addgroup -g 10004 -S statsgroup && \
    adduser -S statsuser -u 10004 -G statsgroup

RUN chown -R statsuser:statsgroup /app
USER statsuser

EXPOSE 4004

CMD ["node", "index.js"]