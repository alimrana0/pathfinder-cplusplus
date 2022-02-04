Pathfinding


## Overview

Implemented functionality of a grid
world, along with breadth-first-search (BFS) and A* algorithms for
finding paths through it, using standard library algorithms.

[Used this graph search introduction/overview](https://www.redblobgames.com/pathfinding/a-star/introduction.html).

# Implementation Notes
Worlds for pathfinding are initialized using an id

The file pathfinding_main.cpp implements a simple text command input system for using
the system.  A command reference is given below.

## Command reference

*print [worldId]*  
&nbsp; Print the world with *worldId*.

*neighbors [worldId]*  
&nbsp; Print the neighbors of the points along the diagonal of the world with *worldId*.

*bfs-print [worldId]*  
&nbsp; Print extended information about the path found using BFS for the world with *worldId*.

*bfs-summary [worldId]*  
&nbsp; Print a summary of the path found using BFS for the world with *worldId*.

*astar-print [worldId]*  
&nbsp; Print extended information about the path found using A* for the world with *worldId*.

*astar-summary [worldId]*  
&nbsp; Print a summary of the path found using A* for the world with *worldId*.
