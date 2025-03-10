# Dijkstra's Algorithm Visualization

This project is a visualization tool for Dijkstra's algorithm, a popular graph algorithm for finding the shortest path between nodes.

## Overview

This application provides an interactive visualization of Dijkstra's algorithm, allowing users to better understand how the algorithm works by watching it execute step by step. The visualization demonstrates how the algorithm efficiently finds the shortest path between nodes in a graph.

## Features

- Visual representation of graphs and the algorithm's execution
- Step-by-step visualization of Dijkstra's algorithm
- Interactive console for command input and feedback
- Customizable display options

## Project Structure

```
.
├── CMakeLists.txt          # CMake build configuration
├── project.pro             # Qt project file
├── res/                    # Resource files (images, etc.)
└── src/                    # Source code for the visualization
```

## Prerequisites

- Qt 5.15.2 or later
- CMake 3.21 or later
- C++17 compatible compiler

## Building the Project

### Using CMake

```bash
mkdir build
cd build
cmake ..
make
```

### Using Qt Creator

1. Open the `project.pro` file in Qt Creator
2. Configure the project for your development environment
3. Click on the Build button or press Ctrl+B

## Running the Application

After building, run the executable:

```bash
./StarterProject
```

## Console Features

The application provides a graphical console with many customization options:

- `setConsoleFont()` - Changes the console font
- `setConsoleSize()` - Adjusts the console dimensions
- `setConsoleWindowTitle()` - Sets the title of the console window
- `setConsoleOutputColor()` - Changes the text color
- `clearConsole()` - Clears the console output

## Development Notes

This project uses the Qt framework to provide GUI components and console functionality. The graphical elements are built with Qt 5.

The main application code is located in the `src/` directory.

## License

This project is for educational purposes.

## Acknowledgements

- Built with Qt framework for cross-platform compatibility
