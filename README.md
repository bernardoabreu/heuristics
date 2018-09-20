# Heuristics for TSP

##Construtive heuristic

A initial city must be selected (in this implementation the selected city is the first). Once the first city is defined, it is added to the solution, and the closest city to the current one is selected. This new city is the added to the solution and defined as the new current city. From that, the closest city to the new current city is selected from the remaining cities. This procedure is repeated until all cities are added to the solution.

##Local search heuristic
