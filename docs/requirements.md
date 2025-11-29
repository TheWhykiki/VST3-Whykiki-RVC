# Development Requirements and Environment

Dieses Dokument beschreibt die Systemvoraussetzungen und Abhängigkeiten für das Building und die lokale Entwicklung des VST3-RVC-Instruments.

### Unterstützte Plattformen & DAWs
- Windows 10/11, macOS 10.15+ (Intel/Apple Silicon), Linux (weitere Distributionen ggf. mit Anpassungen)
- DAWs: Cubase 11+, Reaper, andere VST3-kompatible Hosts

### CMake & Compiler
- CMake ≥ 3.16
- Windows: Visual Studio 2019/2022
- macOS: Xcode 12+ (Xcode Command Line Tools erforderlich)
- Linux: GCC ≥ 9 oder Clang ≥ 11

### Python & RVC
- Python ≥ 3.9 (virtuelle Umgebung empfohlen)
- Abhängigkeiten siehe `external/rvc-webui/requirements.txt`. Auf macOS kann das Bauen von Abhängigkeiten (z. B. aria2) eine Umgebungsvariable `WHL_PLATFORM` erfordern oder den Einsatz von Poetry/Conda empfehlen (siehe RVC-Repo-README).
- optional: GPU‑Support (CUDA Toolkit ≥ 11.x) für ONNX- und Torch-Beschleunigung
- Python ≥ 3.9 (virtuelle Umgebung empfohlen)
- Abhängigkeiten siehe `external/rvc-webui/requirements.txt`. Auf macOS kann das Bauen von Abhängigkeiten (z. B. aria2) eine Umgebungsvariable `WHL_PLATFORM` erfordern oder den Einsatz von Poetry/Conda empfehlen (siehe RVC-Repo-README).
- **Hinweis zur Inferenz-Testumgebung:**
- Da RVC-WebUI `setup.py` Python ≥3.7,<3.11 voraussetzt und auf bestehenden Systemen (z.B. Python 3.12) zu Fehlern führt, empfiehlt sich für einen Quick-Test die Nutzung der mitgelieferten Dockerfile:
-
- ```bash
- cd external/rvc-webui
- docker build -t rvc-webui:local .
- docker run --rm rvc-webui:local python infer-web.py --help
- ```
### Git & LFS
- Git ≥ 2.25
- Git LFS für große Modell-/Audio-Dateien (z. B. .onnx, .pth, .pt, .wav)

## CMake-Presets (IDE-Integration)
Siehe `CMakePresets.json` im Projekt-Root für Debug/Release‑Presets bzw. Ninja-Generator.
