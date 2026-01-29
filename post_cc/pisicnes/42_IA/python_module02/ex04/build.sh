#!/bin/bash
set -e

export PATH=$PATH:$HOME/.local/bin

python3 -m pip install --upgrade pip setuptools wheel build

if [ -f requirements.txt ]; then
    python3 -m pip install -r requirements.txt
fi

python3 -m pip install pipenv

python3 -m pipenv install

python3 -m build

echo "✅ Build complet terminé !"