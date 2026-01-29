FROM nginx:alpine

RUN apk add --no-cache openssl

COPY index.html /usr/share/nginx/html/
COPY app-unified.js /usr/share/nginx/html/
COPY components/ /usr/share/nginx/html/components/


COPY nginx.conf /etc/nginx/conf.d/default.conf

RUN mkdir -p /etc/nginx/ssl && \
    openssl genrsa -out /etc/nginx/ssl/nginx.key 2048 && \
    openssl req -new -x509 -key /etc/nginx/ssl/nginx.key -out /etc/nginx/ssl/nginx.crt -days 365 \
    -subj "/C=FR/ST=France/L=Paris/O=Dev/CN=localhost"

EXPOSE 80 443

CMD ["nginx", "-g", "daemon off;"]