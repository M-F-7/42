#!/bin/bash
docker network inspect app-net >/dev/null 2>&1 || \
docker network create app-net
echo "✅ Docker network 'app-net' ready."
