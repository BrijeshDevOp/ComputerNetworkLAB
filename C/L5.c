#include <stdio.h>
#include <conio.h>
#define infinity 999

void dij(int n, int v, int cost[10][10], int dist[100])
{
    int i, u, count, w, flag[10], min;

    // Initialize flags and distances
    for (i = 1; i <= n; i++)
    {
        flag[i] = 0;
        dist[i] = cost[v][i];
    }

    count = 2;
    while (count <= n)
    {
        min = 99;
        // Find the unvisited node with the smallest distance
        for (w = 1; w <= n; w++)
        {
            if (dist[w] < min && !flag[w])
            {
                min = dist[w];
                u = w;
            }
        }
        flag[u] = 1;
        count++;
        // Update distances to neighboring nodes
        for (w = 1; w <= n; w++)
        {
            if ((dist[u] + cost[u][w] < dist[w]) && !flag[w])
            {
                dist[w] = dist[u] + cost[u][w];
            }
        }
    }
}

void main()
{
    int n, v, i, j, cost[10][10], dist[10];

    // clrscr();
    printf("\n Enter the number of nodes:");
    scanf("%d", &n);
    printf("\n Enter the cost matrix:\n");

    // Input the cost matrix
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] == 0)
            {
                cost[i][j] = infinity;
            }
        }
    }

    printf("\n Enter the source matrix:");
    scanf("%d", &v);

    // Call Dijkstra's algorithm
    dij(n, v, cost, dist);

    printf("\n Shortest path:\n");
    // Print the shortest paths from the source
    for (i = 1; i <= n; i++)
    {
        if (i != v)
        {
            printf("%d->%d, cost=%d\n", v, i, dist[i]);
        }
    }

    getch();
}

/*
Variables in dij:
n: The total number of nodes in the graph.

v: The source node from which the shortest paths are calculated.

cost: A 2D array representing the cost matrix of the graph, where cost[i][j] is the weight of the edge from node i to node j.

dist: An array that will store the shortest distance from the source node v to each other node.

i: Loop variable used for initialization and traversing nodes.

u: The current node being processed, which has the smallest known distance from the source among unvisited nodes.

count: Counter to keep track of the number of nodes processed.

w: Loop variable used to iterate through all nodes, especially to find the minimum distance node and to update distances.

flag: An array to keep track of visited nodes; flag[i] is 1 if node i has been visited, otherwise 0.

min: Temporary variable to find the node with the smallest distance from the source among unvisited nodes.
*/

/*
Dijkstra's algorithm finds the shortest path from a single source node to all other nodes in a weighted graph. Here's a step-by-step explanation of the logic behind how the shortest path is found:

Key Concepts
Cost Matrix: A 2D array where cost[i][j] represents the weight of the edge from node i to node j. If there is no direct edge between i and j, the cost is set to a very high value (infinity).

Distance Array: An array dist where dist[i] holds the shortest known distance from the source node to node i.

Flag Array: A boolean array flag to keep track of which nodes have been visited. If flag[i] is 1, the node i has been visited.

Algorithm Steps
Initialization:

Set all nodes as unvisited (flag[i] = 0 for all i).
Initialize the distance array with the direct distances from the source node v (dist[i] = cost[v][i] for all i).
Start from the source node (v).
Main Loop:

Iterate n-1 times (where n is the number of nodes) because, in each iteration, we will mark one node as visited.
Select the Minimum Distance Node:

Find the unvisited node u with the smallest distance (min) from the source.
Mark this node as visited (flag[u] = 1).
Update Distances:

For each unvisited neighbor w of the current node u, check if the distance from the source to w can be minimized by going through u. This is done by comparing dist[u] + cost[u][w] with dist[w].
If a shorter path is found, update dist[w] to dist[u] + cost[u][w].
Detailed Walkthrough
Let's go through the process step-by-step:

Initialization:

Assume n = 4 and v = 1.
Cost matrix (example):
css
Copy code
cost = [    [0,  999, 999, 999, 999],
            [999, 0,   2,   999, 6  ],
            [999, 2,   0,   3,   8  ],
            [999, 999, 3,   0,   1  ],
            [999, 6,   8,   1,   0  ] ]
Initialize flag to [0, 0, 0, 0, 0] and dist to [999, 0, 2, 999, 6].
First Iteration:

Find the unvisited node with the smallest distance: Node 2 (dist[2] = 2).
Mark Node 2 as visited: flag = [0, 0, 1, 0, 0].
Update distances:
For Node 3: dist[3] = min(dist[3], dist[2] + cost[2][3]) = min(999, 2 + 3) = 5.
For Node 4: dist[4] = min(dist[4], dist[2] + cost[2][4]) = min(6, 2 + 8) = 6.
Updated dist = [999, 0, 2, 5, 6].
Second Iteration:

Find the unvisited node with the smallest distance: Node 3 (dist[3] = 5).
Mark Node 3 as visited: flag = [0, 0, 1, 1, 0].
Update distances:
For Node 4: dist[4] = min(dist[4], dist[3] + cost[3][4]) = min(6, 5 + 1) = 6.
dist remains [999, 0, 2, 5, 6].
Third Iteration:

Find the unvisited node with the smallest distance: Node 4 (dist[4] = 6).
Mark Node 4 as visited: flag = [0, 0, 1, 1, 1].
No distance updates needed since all remaining nodes are either visited or not reachable with a shorter path.
dist remains [999, 0, 2, 5, 6].
Result
The dist array now contains the shortest distances from the source node (Node 1) to all other nodes:

Distance from Node 1 to Node 2: 2
Distance from Node 1 to Node 3: 5
Distance from Node 1 to Node 4: 6
This completes Dijkstra's algorithm, ensuring that the shortest paths from the source node to all other nodes are correctly found and recorded in the dist array
*/