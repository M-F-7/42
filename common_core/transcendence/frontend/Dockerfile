FROM node:18-alpine AS build
WORKDIR /app

COPY package.json package-lock.json* ./
COPY tsconfig.json vite.config.js postcss.config.js tailwind.config.js ./
COPY index.html ./
COPY src ./src
COPY src/components ./src/components

RUN npm install --silent --no-audit --progress=false && npm run build


FROM nginx:alpine
RUN apk add --no-cache openssl


RUN rm -rf /etc/nginx/templates

COPY --from=build /app/dist /usr/share/nginx/html
COPY nginx.conf /etc/nginx/conf.d/default.conf

EXPOSE 80 4443

CMD ["nginx", "-g", "daemon off;"]
