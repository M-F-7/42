FROM node:18-alpine

WORKDIR /app

COPY package*.json ./

RUN npm install --omit=dev && npm cache clean --force

COPY . .
RUN mkdir -p /app/data && \
    addgroup -g 10007 -S databasegroup && \
    adduser -S databaseuser -u 10007 -G databasegroup

RUN chown -R databaseuser:databasegroup /app
USER databaseuser

EXPOSE 4007

CMD ["node", "index.js"]