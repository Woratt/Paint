# Graphics Editor

A modern graphics editor built with the **Qt Framework**, designed using professional software design patterns to ensure modularity, scalability, and maintainability.  
This project showcases advanced GUI development, low-level graphics handling, and clean architecture principles.

---

## Features

- **Drawing Tools** — Brush, Fill (Bucket), Rectangle, Circle, Line, Polyline, and Eraser  
- **Undo / Redo System** — Unlimited action history implemented using the Command pattern  
- **Advanced Color Palette** — Color selection via fixed grid (Common) or HSV gradient (All)  
- **Interactive UI** — Dynamic zooming, informative status bar (InfoBar), and full keyboard shortcut support  
- **Cross-Platform Support** — Platform-specific resource handling for macOS, Windows, and Linux  

---

## Project Architecture

The project is designed with a strong focus on **Separation of Concerns** and extensibility.

### 1. Command Pattern (Undo / Redo System)

Each drawing operation is encapsulated in a dedicated command object.  
This allows efficient undo/redo functionality while keeping memory usage under control.

- **`DrawingCommand`** — Abstract base class for all drawing commands  
- **`CommandManager`** — Manages command stacks and the current canvas state  

### 2. Strategy & Factory Patterns (Flexible Tools System)

The `IDrawingTool` interface allows the `Canvas` to interact with any drawing tool through a unified API.

- **`ToolFactory`** — Creates tool instances based on type, enabling easy extension without modifying core logic  
- **`IDrawingTool`** — Defines mouse event handling logic for each drawing tool  

---

## Technical Solutions & Algorithms

### Optimized Fill Algorithm (Scanline Flood Fill)

Instead of a recursive flood fill (which may cause stack overflow), the editor uses an optimized **Scanline Flood Fill** algorithm implemented with `QStack`.

- Processes the image line by line (scanlines)  
- Significantly improves performance on large areas  
- Ensures stability and predictable memory usage  

### Custom UI Components

- **`MenuPalette`** — Hybrid menu using `QWidgetAction` to embed complex color picker widgets directly into `QMenu`  
- **`NumberLine`** — Smart numeric input field with validation via `QRegularExpressionValidator` and automatic focus handling  
- **`ResourcePath`** — Automatic resolution of icon and style paths, including macOS bundle handling using `CFBundleRef`  

---

## Project Structure

- **/tools** — Drawing tool logic (Brush, Rectangle, Bucket, etc.)  
- **/toolsCommand** — Concrete command implementations for drawing actions  
- **/ui** — User interface components (ToolBar, MenuBar, InfoBar)  
- **`Canvas`** — Core widget responsible for drawing and pixel-level operations  
- **`PaintWindow`** — Central mediator connecting all system modules  

---

## Build & Run

### Requirements

- C++17 or newer  
- Qt 6.x (recommended) or Qt 5.15  
- CMake or qmake  

### Build Instructions (CMake)

Clone the repository:
   ```bash
   git clone https://github.com/yourusername/qt-paint-editor.git
   mkdir build && cd build
   cmake ..
   cmake --build .
   

