#!/bin/bash


COUNTRY="FR"
STATE="Ile-de-France"
LOCALITY="Paris"
ORGANIZATION="COKE_MONKEYS"
ORGANIZATIONAL_UNIT="IT"
COMMON_NAME="localhost"
EMAIL="admin@localhost"

CERT_DIR="./ssl/certs"
mkdir -p $CERT_DIR

openssl req -x509 -nodes -newkey rsa:2048 -days 365 \
  -keyout "$CERT_DIR/server.key" \
  -out "$CERT_DIR/server.crt" \
  -subj "/C=$COUNTRY/ST=$STATE/L=$LOCALITY/O=$ORGANIZATION/OU=$ORGANIZATIONAL_UNIT/CN=$COMMON_NAME/emailAddress=$EMAIL" \
  -addext "subjectAltName=DNS:localhost"

chmod 644 "$CERT_DIR/server.key"
chmod 644 "$CERT_DIR/server.crt"

echo "Self-signed SSL certificates (with SAN) generated at $CERT_DIR"
