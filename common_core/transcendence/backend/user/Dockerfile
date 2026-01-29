FROM node:18-alpine

RUN apk add --no-cache curl

WORKDIR /app

COPY package*.json ./

RUN npm install --omit=dev && npm cache clean --force
COPY . .

RUN addgroup -g 10006 -S usergroup && \
    adduser -S useruser -u 10006 -G usergroup

RUN chown -R useruser:usergroup /app
USER useruser

EXPOSE 4006


CMD ["node", "index.js"]