FROM node:18-alpine

RUN apk add --no-cache curl

WORKDIR /app

COPY package*.json ./

RUN npm install --omit=dev && npm cache clean --force
COPY . .

RUN addgroup -g 10005 -S tournamentsgroup && \
    adduser -S tournamentsuser -u 10005 -G tournamentsgroup

RUN chown -R tournamentsuser:tournamentsgroup /app
USER tournamentsuser

EXPOSE 4005

CMD ["node", "index.js"]