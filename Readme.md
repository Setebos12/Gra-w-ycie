# Game of Life

This project is an implementation of Conway's Game of Life, a cellular automaton devised by mathematician John Conway. The simulation evolves based on simple rules applied to a grid of cells, creating complex and fascinating patterns.

## Initial Documentation 1.0

### Project Overview
The project is divided into several modules, each responsible for a specific aspect of the simulation:
- **Simulation**: Manages the main loop and coordinates the flow between `Input`, `Logic`, and `Render`.
- **Input**: Handles user input, converting it into tokens and managing the current state of pressed keys.
- **Logic**: Updates the game state (board) based on Conway's rules and processes user commands.
- **Render**: Draws the game board and UI elements on the screen.
- **GameObject**: Abstract class representing drawable and updatable objects in the game.

---

### Features
- **Start/Stop Simulation**: Control the simulation's execution.
- **Dynamic Updates**: The board updates based on Conway's rules.
- **UI Elements**: Display generation count and other statistics.
- **Keyboard Interaction**: Allows drawing on the board and controlling the simulation.

---

### Project Structure
The project is organized into the following classes and modules:

#### **Simulation**
- Manages the main loop.
- Delegates control to `Input`, `Logic`, and `Render` in sequence.
- Coordinates the flow of data between modules.

#### **Input**
- Collects user input and converts it into tokens using `ParserKeyboard`.
- Maintains a set of tokens representing the current state of pressed keys.
- Handles commands like:
  - Start/Stop simulation.
  - Exit the application.
  - Drawing on the board (only when paused).

#### **Logic**
- Manages the game board (`Board`) and updates its state.
- Uses `PointHandle` to determine the next state of each cell.
- Implements the `step` function to process input and update the board.
- Stores the game state in `GameState` (or directly in `Board`).
- Updates the `HUD` object with statistics like the number of generations.

#### **Render**
- Renders all drawable objects, including the board and UI elements.
- Calls the `draw` method on each object in the render list.

#### **GameObject**
- Abstract base class for all game objects.
- Defines the interface for `draw` and `update` methods.
- Implemented by classes like `Board` and `HUD`.

#### **Board**
- Stores the game state in a `Container` (a `vector<vector<bool>>`).
- Updates the board state based on the logic provided by `PointHandle`.

#### **HUD**
- Displays information such as the number of generations and simulation status.
- Updated in the main simulation loop.

#### **PointHandle**
- Stateless class that determines whether a cell should live or die based on its neighbors.
- Optimized for performance by processing rows in batches.

#### **Logger**
- Static class for logging messages.
- Centralized control for enabling/disabling logs.

### Authors
- **Piotr Pyrak**
- **Krzysztof Rutkowski**
- **Bartosz Paszkiewicz**

### Contribution
Each team member works on their assigned modules in separate branches:
- **Piotr**: `Renderer`, `GameObject`, `HUD`, `Logic`.
- **Bartosz**: `Board`, `Container`, `PointHandle`, `GameState`.
- **Krzysztof**: `Simulation`, `Logger`, `Input`.