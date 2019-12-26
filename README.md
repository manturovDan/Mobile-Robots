# Mobile Robots 
### Laboratory work on 3rd semester

### Task
Develop the application, describing the state of mobile robotics complex, which should include information about its components and functioning environment.
***Environment describer*** is a tiled 2-dimensional map, including *Obstacles*, components of robotics complex and points of interest.
Every component is a module platform, for which *coordinates*, the string of *description*, *level of the energy consumption*, *amount of slots* for *modules* connection, the cost are defined. For each *module* the *level of consumption*, *state* (on/off), *priority* and *cost* are defined.
There are some types of platforms: ***stationary*** (can't change location) and ***mobile*** (can move).
There are types of modules: ***managing***, ***power generator***, ***sensor***.
Managing modules may be stated on special type platforms - managing platforms only, that may be mobile (***robot-commander***) or stationary (***command center***). Managing module can command defined amount of robotics devices, if a component (***robot-scout*** or ***observation center***) isn't controlled by managing module, it is unworkable. Managing module works in defined radius.
Power generator is characterized by level of generation, that it provides. If the amount of energy is not enough, than some of the modules must be disabled by priority.
Sensors allow to get information about the environment (detect obstacles, nearby components and points of interest). For sensor radius of action, direction and angle are defined. All managing modules are connected with ***AI***. The task for it is to find all points of interest.

### Realization
AI is the totality of depth-first search, breadth-first search (wave trace - Lee algorithm). At first, stationary platforms detect everything, that they can, then pairs of commanders and scouts (if making of pairs is impossible, commander drives alone) research square areas, where AI sends (files ```robots/Ai_Deep.h```, ```robots/Ai_Deep.cpp```).

That is why motion is asynchronous: robot | coordinates | direction | arriving time (files ```robots/Moving_Desctiber.h```, ```robots/Moving_Desctiber.cpp```).

The analog of STL multimap was realized in this laboratory work.

The map stores in xml-files. Structure of these files describes in ```robots/interfacce.h```.

### GUI was realized on SFML:
![screen](https://i.imgur.com/hU2fcBD.png)

### Textures of objects
![textures](https://i.imgur.com/Xk6KlUP.png)

##### Compiler: gcc version 7.4.0
---
###### Manturov Danila - 2019 (NRNU Mephi)
