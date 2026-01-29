FROM node:18-alpine

RUN apk add --no-cache curl

WORKDIR /app

COPY package*.json ./

RUN npm install --omit=dev && npm cache clean --force
COPY . .

RUN addgroup -g 10001 -S chatgroup && \
    adduser -S chatuser -u 10001 -G chatgroup

RUN chown -R chatuser:chatgroup /app
USER chatuser

EXPOSE 4001

CMD ["node", "index.js"]