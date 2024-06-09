# IdharUdhar Car Racing Game
This is the final project of data structures for Semester 3 with my lovely friend Affan Hameed!


## Semester Project Statement: Design and Implement a Race Car Game

## Project Description:

In this semester project, you will have the opportunity to apply your knowledge of
data structures practically and excitingly by designing and implementing a race
car game in C++. The goal of the project is to create an engaging and interactive
game that incorporates various data structures, such as graphs, linked lists, or
queues, to manage game elements efficiently.

**Project Objectives:**

1. Develop a 2D console-based race car game using C++ without utilizing any
    external graphics library. Implement a text-based user interface within the
    console (A text-based user interface (TUI) relies on characters and text to
    convey information to the user instead of graphical elements. In a console-
    based game, a TUI might involve using ASCII characters and text to represent
    various game elements). The game must also feature player-controlled race
    cars, obstacles, tracks, and a scoring system. Here's a simple example of what
    a text-based user interface for a race car game might look like:


**2. Data Structures Integration:**

```
a. Graphs for Map and Navigation:
```
- Map Representation: Create a graph to represent the game map. Nodes
in the graph represent locations or waypoints in the game world, while edges
represent paths between them. This graph can be used for player navigation.
- Navigation and Pathfinding: Implement algorithms like Dijkstra's algorithm
or any other shortest path finding algorithms on the graph to find optimal
paths for player-controlled race cars. The graph can help ensure that
characters navigate the race track efficiently and avoiding obstacles

```
b. Queues for Obstacle:
```
- Obstacle : Utilize a queue data structure to manage the generation of
obstacles. New obstacles can be added to the queue as they are generated,
and the game loop can process the queue to introduce these elements at
appropriate times.
- Example: If your game features randomly appearing obstacles on the race
track, you can enqueue obstacle objects with information about their type
and location. During each game update, you can dequeue these objects and
add them to the game world at the specified positions.

```
c. Linked Lists for Collected Coins and Game Trophies:
```
- Collected Items: Maintain a linked list to keep track of items collected by
players during the game, such as coins or trophies. Each node in the linked
list represents an item collected, with relevant information (e.g., item type,
score value).
- Example: As players collect coins or achieve milestones, you can add nodes
to the linked list. The linked list allows easy tracking of collected items and
can be used to update the player's score or display their achievements.
**3. Game Logic** :


Develop the game logic, including player controls, collision detection, scoring, and
win/lose conditions. Implement gameplay features that challenge players and make
the game enjoyable.

**4. User Interface** :
Design and create a user-friendly interface (text-based user interface TUI) for the
game, including menus, scoreboards, and any additional features that enhance the
player experience.
**5. Documentation:**
Provide clear and comprehensive documentation for your code, including
comments, code organization, and explanations of data structure usage.
**6. Testing and Optimization:**
Thoroughly test the game to ensure it runs smoothly and without bugs. Optimize
the code and data structure implementations for performance and efficiency.


