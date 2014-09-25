#include <stdio.h>
#include <stdlib.h>

#define UNSEEN 0 
#define FRINGE 1
#define INTREE 2

void initializeMatrix(int v, float adjacencyMatrix[][v]);
void printMatrix(int v, float adjacencyMatrix[][v]);
void printStatusArrays(int v, int *status, int *dad, float *dist);
int fringeCount(int v, int *status);
int findClosestFringeVertex(int v, int *status, float *dist);

int main()
{
	//Reads the vertices, edges and edge weights from the text file and stores the edges in an adjacency matrix.
	FILE *ifp;
	char *mode = "r";	
	int v, e, v1, v2;
	float weight;
	ifp = fopen("DijkstraInput3.txt", mode);

	if (ifp == NULL) 
	{
		printf("Can't open input file in.list!\n");
		exit(1);
	}
	
	fscanf(ifp, "%d", &v);
	printf("%d\n", v);
	fscanf(ifp, "%d", &e);
	printf("%d\n", e);
	float adjacencyMatrix[v][v];
	initializeMatrix(v, adjacencyMatrix);
	printMatrix(v, adjacencyMatrix);
	
	while (fscanf(ifp, "%d %d %f", &v1, &v2, &weight) != EOF) 
	{
		printf( "%d %d %f\n", v1, v2, weight);
		adjacencyMatrix[v1][v2] = weight;
	}	
	fclose(ifp);
	
	printMatrix(v, adjacencyMatrix);
	
	/*Dijkstra's Algorithm begins*/
	//Holds the status of vertex, whether SEEN/UNSEEN	
	int source = 0, dest = v-1;
	int status[v], index, dad[v];
	float dist[v];
	for(index=0; index<v; index++)
	{
		status[index] = UNSEEN;
		dad[index] = -1;
		dist[index] = 99999.00;
	}
	status[source] = INTREE;
	dad[source] = 0;
	dist[source] = 0.00;
	int i;
	for(i=0; i<v; i++)
	{
		if(i!=source)
		{
			if(adjacencyMatrix[source][i] != 0.00)
			{
				status[i] = FRINGE;
				dad[i] = source;
				dist[i] = adjacencyMatrix[source][i];
			}
		}
	}
	printStatusArrays(v, status, dad, dist);
	
	while(fringeCount(v, status) > 0)
	{
		int closestVertex = findClosestFringeVertex(v, status, dist);
		printf("\nNext closest vertex: %d\n", closestVertex);
		status[closestVertex] = INTREE;		
		for(i=0; i<v; i++)
		{
			if(adjacencyMatrix[closestVertex][i] != 0.00 && status[i] == UNSEEN)
			{
				status[i] = FRINGE;
				dad[i] = closestVertex;
				dist[i] = dist[closestVertex] + adjacencyMatrix[closestVertex][i];
			}
			else if(adjacencyMatrix[closestVertex][i] != 0.00 && status[i] == FRINGE)
			{
				if((dist[closestVertex] + adjacencyMatrix[closestVertex][i]) < dist[i])
				{
					dist[i] = dist[closestVertex] + adjacencyMatrix[closestVertex][i];
					dad[i] = closestVertex;
				}
			}
		}
		printStatusArrays(v, status, dad, dist);		
	}			
	
	printf("\nShortest path from source to destination is %f\n", dist[dest]);
}

int findClosestFringeVertex(int v, int *status, float *dist)
{
	int i, vertex=-1;
	float minDist = 9999.99;
	for(i=0; i<v; i++)
	{
		//printf("%d\n", status[i]);
		//printf("If check: %d\n", status[i] == FRINGE);
		if(status[i] == FRINGE)
		{	
			//printf("Fringe vertex: %d\n", i);
			if(dist[i] < minDist)
			{
				minDist = dist[i];
				vertex = i;
			}
		}
	}
	return vertex;
}

int fringeCount(int v, int *status)
{
	int i, count=0;
	for(i=0; i<v; i++)
	{
		if(status[i] == FRINGE)
		{
			count++;
		}
	}
	printf("Fringe Count: %d\n", count);
	return count;
}

void printStatusArrays(int v, int *status, int *dad, float *dist)
{
	int i;
	for(i=0; i<v; i++)
	{
		printf("%d  ", status[i]);		
	}
	printf("\n");
	for(i=0; i<v; i++)
	{
		printf("%d  ", dad[i]);		
	}		
	printf("\n");
	for(i=0; i<v; i++)
	{
		printf("%f  ", dist[i]);
	}
	printf("\n");
}

void initializeMatrix(int v, float adjacencyMatrix[][v])
{
	int i=0, j=0;
	for(i=0; i<v; i++)
	{
		for(j=0; j<v; j++)
		{
			adjacencyMatrix[i][j] = 0.00;
		}		
	}
}
void printMatrix(int v, float adjacencyMatrix[][v])
{
	int i=0, j=0;
	for(i=0; i<v; i++)
	{
		for(j=0; j<v; j++)
		{
			printf("%f\t", adjacencyMatrix[i][j]);
		}
		printf("\n");
	}
}