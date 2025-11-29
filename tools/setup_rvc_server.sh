#!/usr/bin/env bash
# Einrichtungsskript für den Python RVC API-Server
set -e

# Wechsel ins RVC-WebUI-Verzeichnis
SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
cd "$SCRIPT_DIR/external/rvc-webui"

# Virtuelle Python-Umgebung anlegen, falls nicht vorhanden
if [ ! -d venv ]; then
    echo "==> Erstelle Python venv..."
    python3 -m venv venv
fi
source venv/bin/activate

echo "==> Aktualisiere pip und installiere Abhängigkeiten..."
pip install --upgrade pip
pip install -r requirements.txt

echo "==> RVC-WebUI Python-Server-Umgebung bereit."
