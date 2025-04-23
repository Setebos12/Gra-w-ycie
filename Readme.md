# Game of Life - Documentation 1.0
---
Authors:
- **Piotr Pyrak**
- **Krzysztof Rutkowski**
- **Bartosz Paszkiewicz**

---

## Premises
<p>We will implement the Conway's Game of Life as descriped on [Wikipedia](https://en.wikipedia.org/wiki/Conway's_Game_of_Life).<br>
First the user will specify the starting conditions and start the simulation in a GUI. The simulation can be stopped, the alive population edited and then started again. While the simulation is stopped it can also be saved and loaded from file.<br>
During the runtime of the program log messages are written to file or terminal (which can be specified via input arguments). Some statisctics eg. generation count will also be visible in GUI.</p>

---

## Project Structure
The following files, each containing a singular class unless stated otherwise, are planned:

#### **Simulation**
- Gives control to Input, Logic, and Renderer in a main loop, passes neccessary data between them.
- Holds a vector of unique_ptr to gameobjects that are updated and rendered.
- Holds a uniqe_ptr to Logger
- Has a public run() method that starts the Simulation (currently supposed to be called from main directly).
- Has constructor that initalizes all objects according to input arguments from main

#### **Input**
- Has unique_ptr to ParserKeyboard.
- Has a CollectInput method that returns a CurrentInput object.

#### **CurrentInput**
- Has a collection of InputTokens (enums).
- Has methods for managing the Collection (adding pressed tokens and clearing).
- Created by Input passed to Logic.

#### **ParserKeyboard**
- Collects user input and creates a CurrentInput object.
- The object is supposed to be passed to Input.
- Has method KeyboardInput that creates CurrentInput collection and returns it.
- Interacts with the keyboard directly.
- Converts the pressed keys into tokens.
- Implements rule of 5 (as interacting directly (more directly than rest of the program) with keyboard)

#### **InputToken**
- An enum that has actions that can be emitted and acted upon by Logic

#### **Logic**
- Has Step method that taking a CurrentInput object and a vector of unique_ptr to gameobjects, updates the state.
- This method is supposed to be called from Simulation
- Has methods for pausing and starting the simulation

#### **GameObject**
- An abstract base class that all objects interacting with the main loop inherit.
- Has virtual draw (taking Drawer& as reference) and update methods called by Renderer and Logic, respectively. Both are required to be inherited.
- Has a name(std::string) and getter and setter for it.
- Overloads << and >> operators, used for log messages and saving loading simulation, both also must be implemented.

#### **HUD**
- Displays statistics in the GUI.
- Inherits GameObject.
- Stores values to be displayed.
- Has a method for updating those values, manually
- That method is called during update
- In constructor takes a reference to the Board
If one class won't be enough to display everything it can be easily split into several others.

#### **Board**
- Inherits GameObject.
- Has a unique_ptr to Container.
- Has getters for statistics concering generations (generation number and population count).
- Uses PointHandle for updates

#### **Container**
- Is a template class with a T type (allows for quickly changing the stored type)
- Has a vector<vector<T>> that is representing the board.
- Methods for managing the collection (set and get for a cell of coordiantes).
- Getters for width and height and private fields for them.
- Constructor that takes width and height as arguments.
- Has a method for generating neighbours.

#### **PointHandle**
- Stateless class that has a template method for deciding wheter a cell should be alive in the next generation, taking it and its neighbours as arguments.

#### **Renderer**
- Has a draw method that takes a vector of unique_ptr to GameObjects (from main loop).
- To draw uses methods from drawer.
- Has a unique_ptr to Drawer class.
- The Drawer is passed as a reference to draw methods.

#### **Drawer**
- Interacts with the display directly.
- Has methods for refreshing the screen.
- Has methods for drawing Shapes (Rectangles and Text) for GameObjects to use.
- Implements Rule of Five (To always close the window correctly)

#### **Main**
- Parses console arguments:
    - Wheter to log to terminal, console, both or none
    - What log messages to display
    - Wheter to load from file the starting state
    - The file to save to
- Creates Simulation object and calls run on it.

#### **Logger**
- Class for logging messages.
- Has enum for message types.
- Has enum for mode.
- Displays only log messages that are specified in a vector in constructor.
- Also in construtor has mode of output (terminal, file, both, none).

#### **FileIO**
- Stateless static class.
- Has methods to write and load to and from file, taking collection from main loop as argument.
- Has private template methods for writing and reading from stream, taking the type of object to be streamed as a template argument.

---

### Header and Implementation split
- **Piotr**: `Renderer`, `GameObject`, `HUD`, `Logic`, `FileIO`, `Main`.
- **Bartosz**: `Board`, `Container`, `PointHandle`, `GameState`.
- **Krzysztof**: `Simulation`, `Logger`, `Input`, `CurrentInput`.
