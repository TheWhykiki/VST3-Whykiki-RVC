# Dokumentation der Entwicklungs­schritte

Im Folgenden sind die wesentlichen Schritte dokumentiert, die zur Implementierung des VST3‑RVC‑Plugins durchgeführt wurden.

## 1. Codebasis erkunden
- Plugin-Ordner (`plugin/`) und CMake-Setup analysiert
- RVC-WebUI-Submodul (`external/rvc-webui`) und Modelle-Verzeichnis (`assets/models/`) identifiziert

## 2. Projektstruktur und CMake-Konfiguration anpassen
- Neue Datei `modelmanager.h/.cpp` für RVC-Inferenz-Engine hinzugefügt
- `plugin/CMakeLists.txt` erweitert um:
  - Kompilierung der ModelManager-Quellen
  - Automatisches Kopieren des `assets/models/`-Verzeichnisses in das Plugin-Binärverzeichnis
  - Optionale Integration von ONNX Runtime und curl CLI

## 3. Stub für RVC-Inferenz im PluginProcessor implementiert
- Ring-Buffer und Puffer für verarbeitete Blöcke (`processedBuffer`) in `pluginprocessor.h` hinzugefügt
- `handleBlock()` führt stubmäßiges Pass-through über `RvcModel::process()` aus
- `process()`-Loop ergänzt um Block-Erkennung und Ausspielung der verarbeiteten Samples

## 4. ONNX Runtime-Kontext in ModelManager integriert
- `Ort::Env`, `Ort::SessionOptions` und `Ort::Session` in `modelmanager.h` definiert
- `loadModel()` lädt das ONNX-Modell via ONNX Runtime C++ API

## 5. HTTP-basierte API-Steuerung eingebunden
- Im `initialize()` des Processors automatisch FastAPI-/uvicorn-Server gestartet
- Anschließend per `curl`-Aufrufen (`/config`, `/start`) initialisiert
- Im `terminate()` wird `/stop` aufgerufen und der Server via `pkill` beendet

## 6. README.md erweitert
- Abschnitte "Building the Plugin", "RVC Model Setup" und "Usage Instructions" hinzugefügt
- Python API Server Setup und DAW-/Plugin-Workflow dokumentiert

## 7. Zusammenfassende Dokumentation
- Diese Datei `docs/development_steps.md` beschreibt den Gesamtworkflow

---
_Ende der Dokumentation_
