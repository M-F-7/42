FROM node:18-alpine

RUN apk add --no-cache curl

WORKDIR /app

COPY package*.json ./

RUN npm install --omit=dev && npm cache clean --force
COPY . .

RUN addgroup -g 10080 -S gatewaygroup && \
    adduser -S gatewayuser -u 10080 -G gatewaygroup

RUN chown -R gatewayuser:gatewaygroup /app
USER gatewayuser

EXPOSE 8080

CMD ["node", "index.js"]