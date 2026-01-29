FROM node:18-alpine

RUN apk add --no-cache curl

WORKDIR /app

COPY package*.json ./

RUN npm install --omit=dev && npm cache clean --force
COPY . .

RUN addgroup -g 10003 -S settingsgroup && \
    adduser -S settingsuser -u 10003 -G settingsgroup

RUN chown -R settingsuser:settingsgroup /app
USER settingsuser

EXPOSE 4003

CMD ["node", "index.js"]