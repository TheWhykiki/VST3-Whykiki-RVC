# VST3 Instrument with Integrated RVC Inference

This repository contains a VST3 instrument plugin that converts vocals in real time using Retrieval-based Voice Conversion (RVC).

## Repository Structure

```
project-root/
├── plugin/               # VST3 plugin source code
├── external/
│   ├── vst3sdk/          # Steinberg VST3 SDK (git submodule)
│   └── rvc-webui/        # RVC WebUI repository (git submodule)
├── tools/                # Build and installer scripts
├── assets/
│   └── models/           # Placeholder for RVC models
├── .gitignore
├── .gitattributes
└── README.md
```

## Getting Started

1. Clone the repository with submodules:

   ```bash
   git clone --recurse-submodules <repo-url>
   ```

2. Install Git LFS:

   ```bash
   git lfs install
   ```

3. Configure Development Environment (CMake, Compiler, Python):

   Siehe [docs/requirements.md](docs/requirements.md).

## Building the Plugin

Ensure ONNX Runtime C++ is installed and findable by CMake (e.g., via CMAKE_PREFIX_PATH or system package).

Place your RVC ONNX model file named `rvc_model.onnx` into `assets/models/`.

```bash
mkdir -p plugin/build && cd plugin/build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
``` 

After building, install or copy the plugin to your VST3 plugins folder:

```bash
cmake --install . --prefix <install-path>
``` 

## RVC Model Setup

The plugin expects the RVC model file at runtime under `assets/models/rvc_model.onnx` alongside the plugin binaries. Adjust the model path in `plugin/source/pluginprocessor.cpp` if needed.

## Usage Instructions

### Python API Server Setup
Install and activate a Python virtual environment for the FastAPI-based RVC server, alternativ über das Setup-Skript:
```bash
# Manuelles Setup
cd external/rvc-webui
python3 -m venv venv
source venv/bin/activate   # on Windows: venv\Scripts\activate
pip install --upgrade pip
pip install -r requirements.txt

# Automatisches Setup über Skript (empfohlen)
../tools/setup_rvc_server.sh
```

### DAW / Plugin Workflow
1. Baue und installiere das VST3-Plugin wie oben beschrieben.
2. Öffne deine DAW (z. B. Cubase, Reaper) und scanne den Plugin-Ordner.
3. Lade das VST3RVC-Plugin in eine Instrumenten- oder Audio-Spur:
   - Das Plugin startet automatisch den Python-API-Server.
   - Es sendet die Konfiguration und beginnt die Echtzeit-Konvertierung.
4. Schließe die Spur oder beende die DAW:
   - Das Plugin stoppt den API-Server automatisch.

### Hinweise
- Stelle sicher, dass der Python-Server auf Port 6242 erreichbar ist.
- Passe ggf. Firewall- oder Berechtigungseinstellungen an, damit `curl` und `python3` im Plugin-Context ausgeführt werden dürfen.
