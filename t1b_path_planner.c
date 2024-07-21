/*
* AstroTinker Bot (AB): Task 1B Path Planner
*
* This program computes the valid path from the start point to the end point.
* Make sure you don't change anything outside the "Add your code here" section.
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef linux // for host pc

    #include <stdio.h>

    void _put_byte(char c) { putchar(c); }

    void _put_str(char *str) {
        while (*str) {
            _put_byte(*str++);
        }
    }

    void print_output(uint8_t num) {
        if (num == 0) {
            putchar('0'); // if the number is 0, directly print '0'
            _put_byte('\n');
            return;
        }

        if (num < 0) {
            putchar('-'); // print the negative sign for negative numbers
            num = -num;   // make the number positive for easier processing
        }

        // convert the integer to a string
        char buffer[20]; // assuming a 32-bit integer, the maximum number of digits is 10 (plus sign and null terminator)
        uint8_t index = 0;

        while (num > 0) {
            buffer[index++] = '0' + num % 10; // convert the last digit to its character representation
            num /= 10;                        // move to the next digit
        }

        // print the characters in reverse order (from right to left)
        while (index > 0) { putchar(buffer[--index]); }
        _put_byte('\n');
    }

    void _put_value(uint8_t val) { print_output(val); }

#else  // for the test device

    void _put_value(uint8_t val) { }
    void _put_str(char *str) { }

#endif


// main function
int main(int argc, char const *argv[]) {

    #ifdef linux

        const uint8_t START_POINT   = atoi(argv[1]);
        const uint8_t END_POINT     = atoi(argv[2]);
        uint8_t CPU_DONE            = 0;

    #else

        #define START_POINT         (* (volatile uint8_t * ) 0x20000000)
        #define END_POINT           (* (volatile uint8_t * ) 0x20000001)
        #define CPU_DONE            (* (volatile uint8_t * ) 0x20000003)

    #endif

    // array to store the planned path
    uint8_t path_planned[32];

    // index to keep track of the path_planned array
    uint8_t idx = 0;

    // instead of using printf() function for debugging,
    // use the below function calls to print a number, string or a newline

    // for newline: _put_byte('\n');
    // for string:  _put_str("your string here");
    // for number:  _put_value(your_number_here);

    // Examples:
    // _put_value(START_POINT);
    // _put_value(END_POINT);
    // _put_str("Hello World!");
    // _put_byte('\n');

    // ############# Add your code here #############
#define INFINITY 9999
#define MAX 30
int G[MAX][MAX]={{0,2,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999},//0
{2,0,2,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,2},//1
{999,2,0,3,999,999,999,999,3,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999},//2
{999,999,3,0,3,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,10,999},//3
{999,999,999,3,0,2,4,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999},//4
{999,999,999,999,2,0,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999},//5
{999,999,999,999,4,999,0,4,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999},//6
{999,999,999,999,999,999,4,0,2,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999},//7
{999,999,3,999,999,999,999,2,0,2,999,999,3,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999},//8
{999,999,999,999,999,999,999,999,2,0,2,2,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999},//9
{999,999,999,999,999,999,999,999,999,2,0,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999},//10
{999,999,999,999,999,999,999,999,999,2,999,0,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999},//11
{999,999,999,999,999,999,999,999,3,999,999,999,0,5,999,999,999,999,999,10,999,999,999,999,999,999,999,999,999,999},//12
{999,999,999,999,999,999,999,999,999,999,999,999,5,0,5,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999},//13
{999,999,999,999,999,999,999,999,999,999,999,999,999,5,0,2,999,999,999,999,999,999,999,999,999,999,999,999,999,999},//14
{999,999,999,999,999,999,999,999,999,999,999,999,999,999,2,0,999,999,999,999,999,999,999,999,999,999,999,999,999,999},//15
{999,999,999,999,999,999,999,999,999,999,999,999,999,999,3,999,0,2,5,999,999,999,999,999,999,999,999,999,999,999},//16
{999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,2,0,999,999,999,999,999,999,999,999,999,999,999,999},//17
{999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,5,999,0,5,999,999,999,999,999,999,999,999,999,999},//18
{999,999,999,999,999,999,999,999,999,999,999,999,999,10,999,999,999,999,5,0,3,999,999,999,999,999,999,999,999,999},//19
{999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,3,0,2,999,999,2,999,999,999,999,999},//20
{999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,2,0,2,2,999,999,999,999,999,999},//21
{999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,2,0,999,999,999,999,999,999,999},//22
{999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,2,999,0,999,999,999,999,999,999},//23
{999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,2,999,999,999,0,4,999,999,999,999},//24
{999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,4,0,4,999,999,999},//25
{999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,4,0,2,3,999},//26
{999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,2,0,999,999},//27
{999,999,999,10,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,3,999,0,3},//28
{999,2,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,3,999,999,999,999,999,999,999,3,0}};//29

int cost[MAX][MAX],distance[MAX],pred[MAX],n=30,start=START_POINT,end=END_POINT,path[32];
int visited[MAX],count,mindistance,nextnode,i,j,k;
//pred[] stores the predecessor of each node
//count gives the number of nodes seen so far
//create the cost matrix
for(i=0;i<n;i++)
for(j=0;j<n;j++)
if(G[i][j]==999)
cost[i][j]=INFINITY;
else
cost[i][j]=G[i][j];
for(i=0;i<n;i++)
{
distance[i]=cost[start][i];
pred[i]=start;
visited[i]=0;
}
distance[start]=0;
visited[start]=1;
count=1;
while(count<n-1)
{
mindistance=INFINITY;
//nextnode gives the node at minimum distance
for(i=0;i<n;i++)
if(distance[i]<mindistance&&!visited[i])
{
mindistance=distance[i];
nextnode=i;
}
//check if a better path exists through nextnode
visited[nextnode]=1;
for(i=0;i<n;i++)
if(!visited[i])
if(mindistance+cost[nextnode][i]<distance[i])
{
distance[i]=mindistance+cost[nextnode][i];
pred[i]=nextnode;
}
count++;
}
for (i = 0; i < n; i++) {
    if (i == end) {
        j = i;
        int x=0;
        do {
            j = pred[j];
            path_planned[x] = j;
            path[x]=j;
			x++; // Storing the value of j in path_planned
        } while (j != start);
    }
}

// Define the graph representing connections between nodes
#define MAX_NODES 10 // Maximum number of nodes in the graph
#define INF 255      // Represents infinity for our path planning

// Function to find the minimum distance vertex
uint8_t minDistance(uint8_t dist[], bool sptSet[], uint8_t numNodes) {
    uint8_t minDist = INF; // Represents infinity
    uint8_t minIndex = 0;

    for (uint8_t v = 0; v < numNodes; v++) {
        if (!sptSet[v] && dist[v] <= minDist) {
            minDist = dist[v];
            minIndex = v;
        }
    }

    return minIndex;
}

// Function to calculate and store the path from start to end using Dijkstra's algorithm
void dijkstra(uint8_t graph[MAX_NODES][MAX_NODES], uint8_t start, uint8_t end, uint8_t path_planned[], uint8_t *idx) {
    uint8_t numNodes = MAX_NODES;
    uint8_t dist[MAX_NODES];
    bool sptSet[MAX_NODES];

    // Initialize dist[] and sptSet[]
    for (uint8_t i = 0; i < numNodes; i++) {
        dist[i] = INF; // Represents infinity
        sptSet[i] = false;
    }

    dist[start] = 0; // Distance from the start node to itself is always 0

    for (uint8_t count = 0; count < numNodes - 1; count++) {
        uint8_t u = minDistance(dist, sptSet, numNodes);
        sptSet[u] = true;

        for (uint8_t v = 0; v < numNodes; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Backtrack to find the path
    uint8_t currentNode = end;
    *idx = 0;

    while (currentNode != start) {
        path_planned[*idx] = currentNode;
        (*idx)++;
        currentNode = start; // Assuming the path_planned array is reversed
    }

    path_planned[*idx] = start; // Add the start node to the path
    (*idx)++;
}

// Define the graph representing connections between nodes
uint8_t graph[MAX_NODES][MAX_NODES] = {
    {0, 1, 1, 0, 0}, // Node 0
    {1, 0, 0, 1, 0}, // Node 1
    {1, 0, 0, 1, 1}, // Node 2
    {0, 1, 1, 0, 1}, // Node 3
    {0, 0, 1, 1, 0}  // Node 4
};

// Call Dijkstra's algorithm to compute the path
dijkstra(graph, START_POINT, END_POINT, path_planned, &idx);

// ##############################################


    #ifdef linux    // for host pc

        _put_str("######### Planned Path #########\n");
        _put_value(END_POINT);
        for (int i = 0; i < idx; ++i) {
            _put_value(path[i]);
        }
        _put_value(START_POINT);
        _put_str("################################\n");

    #endif

    return 0;
}
