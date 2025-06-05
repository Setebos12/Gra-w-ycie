# Game of Life - Documentation 2.0
---
Authors:
- **Piotr Pyrak**
- **Krzysztof Rutkowski**
- **Bartosz Paszkiewicz**

---

## Premises
<p>We will implement the Conway's Game of Life as descriped on [Wikipedia](https://en.wikipedia.org/wiki/Conway's_Game_of_Life). We use SFML to interact with hardware.<br>
First the user will specify the starting conditions and start the simulation in a GUI. The simulation can be stopped, the alive population edited and then started again. While the simulation is stopped it can also be saved and loaded from file.<br>
During the runtime of the program log messages are written to terminal. Generation count will also be visible in GUI.</p>

---

## Tutorial
###### InputArguments
--level Level           Possible Levels are: error, info, debug. Specifies the level of log messages.
--read filename         Read button will read from this
--write filename        Write button will write to this
###### Simulation
Enable draw button allows for drawing on the board. Clicking and draging there will turn cells alive.
If an alive cell is clicked it will be killed.

---

## STL used
vectors as containers for gameobjects (and listeners in events)
queue for taking input arguments and proccessing them
std::remove_if for unsubscribing from events
Iterator loops (for example for event to call methods on listeners)

We use a lot of smart pointers for the entire project mainly:
- unique_ptr for holding long lived classes that are mostly self-contained
- shared_ptr for gameobjects and other things that need logging, as weak_ptr needs to be created for events
- weak_ptr in events

---

## Exceptions

FileIO is a class that throws exceptions if it fails to read or write to fail in any way. Those are intercepted in simulation (as this class uses FilIO), to log.
Other non-standard situations are handled without exceptions as other situations are recoverable in the class that produced those situations.

---

## Testing

Board, Container, Event, Parser, PointHandle are tested. This way we test main simulation logic, along with util helper functions.
We test those classes without accessing private members, so black box testing.
We don't test classess interacting with SFML as it would require a lot of mocking and may not be even possible.

---

## Project Structure
The following files, each containing a singular class unless stated otherwise, are implemented:

### **Util**

#### **Parser**
- Takes argc and argv in constructor
- Able to parse out flags with and without arguments

#### **Event**
- Generic implementation of observer pattern
- An event can be subscribed to with a method on an object (unsubscribed also)
- Can be invoked with arguments to call the method
- Holds objects as weak pointers so no memory leaks are created

#### **Logger**
- Class for logging messages.
- Has enum for message levels.
- Displays only log messages that are specified in constructor as enum.
- Also in construtor has mode of output (terminal, file, both, none).

#### **FileIO**
- Static strings of paths from input arguments
- Has methods to write and load to and from file an object (template functions).
- A single object opens streams only once
- Implements rule of five to close the stream

---

### **Core**

#### **GameObject**
- An abstract base class that all objects interacting with the main loop inherit.
- Has virtual draw (taking Drawer& as reference) and update methods called by Renderer and Logic, respectively. Both are required to be inherited.
- Has virtual input (taking InputToken& as reference) to proccess input tokens
- Has a name(std::string) and getter and setter for it.
- Overloads << and >> operators, used for saving and loading simulation, both also must be implemented.

---

### **Simulation**

#### **Simulation**
- Gives control to Input, Logic, and Renderer in a main loop, passes neccessary data between them.
- Holds a vector of shared_ptr (not unique for logs) to gameobjects that are updated and rendered.
- Holds a uniqe_ptr to Logger
- Has a public run() method that starts the Simulation.
- Has constructor that initalizes all objects according to input arguments from main
- Methods to save and load state

---

### **Render**

#### **Drawer**
- Interacts with the display directly.
- Has methods for refreshing the screen.
- Has methods for drawing Shapes (Rectangles and Text) for GameObjects to use.
- Holds shared_ptr to window.

#### **IRenderObject**
- Virtual Pure class requiring methods that are used by Render (draw method)

#### **Renderer**
- Has a draw method that takes a vector of shared_ptr to GameObjects (from main loop).
- To draw uses methods from drawer.
- Has a unique_ptr to Drawer class.
- The Drawer is passed as a reference to draw methods.

---

### **Ui**

#### **HUD**
- Its method for updating generation count listens to event in board
- Draws the generation count

#### **UiPanel**
- Inherits GameObject.
- Container class that passess control of input, draw and logic to its components
- In constructor takes a references to create events and pass to buttons

#### **InputButton**
- Holds an Event to invoke when clicked
- Implements input to deduce from the input token if it is clicked

---

### **Logic**

#### **Board**
- Inherits GameObject.
- Has a unique_ptr to Container.
- Uses PointHandle for updates
- Implements input to draw cells
- Counts generations

#### **Container**
- Has a vector<vector> that is representing the board.
- Methods for managing the collection (set and get for a cell of coordiantes).
- Getters for width and height and private fields for them.
- Constructor that takes width and height as arguments.

#### **Logic**
- Has Step method that taking a CurrentInput object and a vector of shared_ptr to gameobjects, updates the state.
- This method is supposed to be called from simulation
- Has methods for pausing, starting, speeding up and down the simulation

#### **PointHandle**
- Stateless class that has a method for deciding wheter a cell should be alive in the next generation, taking it and its neighbours as arguments.

---

### **Input**

#### **Input**
- Calls input methods on gameobjects passing input tokens
- Those input tokens are taken from a queue which is previously constructed from polling events from InputPoller

#### **InputPoller**
- Has shared_ptr to window
- Method to proccess clicks
- Creates lambdas to emplace token on actions and passess it to SFML window.handleEvents()
- Checks at the end of polling if mouse is still pressed, if so it emits a token of mouse held down

#### **InputToken**
- An object holding an enum with action type and mouse position

---

### **Main**
- Parses console arguments:
    - What log messages to display
    - The file to save to and load from
- Creates Simulation object and calls run on it.
- Inits FileIO

---