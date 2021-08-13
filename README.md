# PathSearchingUsingAStar
### Dynamic Route planning with obstacles using the A* algorithm
#### About Code:
The requests are gathered from "crd.txt" file. After that, the coordinates are determined by choosing which request to be served.
The grid is read from the "grid.txt" file which has numbers from 0-4 (the Fire Brigade can only travel on path with 1) 
The "grid_size.txt" has grid size related info which is fetched from it

The source always start from 39 39 location that is from bottom-right, the destination varies.
The destination is filled with red color, indicating that there is a fire

After the grid display, the AStarSearch class comes into play which starts to run its searching algo given in search function in the class
The searching boxes are filled with light blue color. After searching completes and stores the optimal path in a pair, the tracing function by the use of stack gives the optimal path to destination.

Once the destination is reached, the red destination becomes greeen, indicating that the fire has been put of 
