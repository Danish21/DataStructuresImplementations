#include <stdio.h>
#include <stdlib.h>

////////////////////An implementation of a Graph
//////Has a vertex and edge list but also has an adjacency matrix which is a 2d array of pointers to edges
/////For simplicity an edge is always an uppercase letter and a vertex is an int < 100


#define doesNotExist 0

struct edge{ ///Represents an edge which is an uppercase Letter

	int exists;
	char name;
	int vertex1;
	int vertex2; 

}typedef edge;



struct Graph{//A List of vertexes and 

	int * vertexList;
	edge * edgeList;
	edge *** adjacenyMatrix;

}typedef Graph;


int min(int a, int b){ //Helper function

	if(a<b){return a;}

	return b;
}

int max(int a, int b){//Helper Function

	if(a>b){return a;}

	return b;

}


int edgeHash(char edge){ //SImple hash for an edge A=65-65=0 and Z=90-65=25
	return edge-65;
}

void graphInit(Graph * myGraph){
	
	
	myGraph->vertexList = (int*) malloc(sizeof(int)*100); //Create space for graph on the heap
	myGraph->edgeList = (edge *) malloc(sizeof(edge)*26);
	myGraph->adjacenyMatrix = (edge***)malloc(sizeof(edge**)*100);
	
	for(int i =0; i<100; i++){
		myGraph->adjacenyMatrix[i] = (edge**)malloc(sizeof(edge*)*100);
		myGraph->vertexList[i]=0; //intialize all vertexs to not exist
	}

	for(int i =0; i<26; i++){
		myGraph->edgeList[i].exists=0; //intialize all edges to not exist
	}

	for(int i =0; i<100; i++){
		for(int j=0; j<100; j++){
			myGraph->adjacenyMatrix[i][j] = NULL; // Null out the adjacency matrix
		}
		
	}


}

void graphInsertVertex(Graph * myGraph, int vertex){
 
 //O(n) to null out all the entries of the inseted vertex


	if(vertex < 100){
		
		myGraph->vertexList[vertex] = 1; //mark vertex as existing

		for(int i=0; i <100; i++){
			myGraph->adjacenyMatrix[vertex][i]=NULL; //NUll out its row of enteries
		}

	}else{
		printf("Invalid vertex entry\n");
	}

}

void graphInsertEdge(Graph * myGraph, char edge, int vertex1, int vertex2){

//0(1) as a constant amount of entries everytime
	if( (edge >= 'A') && (edge <= 'Z') && myGraph->vertexList[vertex1]  && myGraph->vertexList[vertex2]){

		int index = edgeHash(edge);
		
		(myGraph->edgeList[index]).exists = 1; //Intial values of edge
		(myGraph->edgeList[index]).name = edge;
		(myGraph->edgeList[index]).vertex1 = min(vertex1,vertex2);
		(myGraph->edgeList[index]).vertex2 = max(vertex1,vertex2);

		myGraph->adjacenyMatrix[vertex1][vertex2] = &(myGraph->edgeList[index]); //set pointers to edge in adjacency matrix
		myGraph->adjacenyMatrix[vertex2][vertex1] = &(myGraph->edgeList[index]);

	}else{
		printf("Invalid edge entry\n");
	}


}


void removeEdge(Graph * myGraph, char edge){

//O(1) as a constant amount of work everytime
	if( (edge >= 'A') && (edge <= 'Z') ){

		int index = edgeHash(edge);
		int vertex1 = (myGraph->edgeList[index]).vertex1; //get vertexs of the edge
		int vertex2 = (myGraph->edgeList[index]).vertex2;

		(myGraph->edgeList[index]).exists = doesNotExist;//mark edge as not existing

		myGraph->adjacenyMatrix[vertex1][vertex2] = NULL; //NULL out edge in the amatrix
		myGraph->adjacenyMatrix[vertex2][vertex1] = NULL;

	}else{
		printf("Invalid edge entry\n");
	}
}



void removeVertex(Graph *  myGraph, int vertex){
//O(n) as have to walk through all possible edge combinations with this vertex

	if(vertex < 100){
		
		for(int i=0; i < 100; i++){

			if(myGraph->adjacenyMatrix[vertex][i]){ //if edge exists
				removeEdge( myGraph,myGraph->adjacenyMatrix[vertex][i]->name); //remove edge
			}
			
		}

		myGraph->vertexList[vertex] = doesNotExist; //mark vertex as not existing

	}else{
		printf("Invalid vertex entry\n");
	}
}


int areAdjacent( Graph * myGraph, int v1, int v2){

//0(1) as a simple array look up
	
	if(myGraph->adjacenyMatrix[v1][v2]){//if edge exists between the two vertexs
		return 1;
	}

	return 0;

}


char * incidentEdges(Graph * myGraph,int vertex){
//0(N) as have to walk through the whole row

	char * listOfEdge = (char *) malloc(2); //String of characters of adjacent Edges
	int size = 0;
	int capacity = 2;

	for(int i=0; i < 100; i++){

		if(myGraph->adjacenyMatrix[vertex][i]){ // if edge exists

				listOfEdge[size] = (*(myGraph->adjacenyMatrix[vertex][i])).name; //store name in the String
				size ++;

				if(size == capacity ){ //of String is full double it
					listOfEdge = (char *)realloc(listOfEdge, capacity * 2);
					capacity =capacity*2;
				}

		}

	}
	//printf("size: %d\n",size);
	listOfEdge[size]='\0'; //Null terminate the String
	return listOfEdge;

}


int main(){

	Graph *  newGraph = (Graph* )malloc(sizeof(Graph));

	graphInit(newGraph);
	printf("Graph created\n");
	graphInsertVertex(newGraph,0);
	graphInsertVertex(newGraph,1);
	graphInsertVertex(newGraph,2);

	graphInsertEdge(newGraph,'A',0,1);
	graphInsertEdge(newGraph,'B',1,2);
	graphInsertEdge(newGraph,'C',0,2);

	if(areAdjacent(newGraph,0,1)){
		printf("0 and 1 are are Adjacent\n");
	}

	if(areAdjacent(newGraph,1,2)){
		printf("1 and 2 are are Adjacent\n");
	}

	if(areAdjacent(newGraph,0,2)){
		printf("0 and 2 are are Adjacent\n");
	}

	char * neighbors = incidentEdges(newGraph,0);
	printf("%s\n",neighbors);

	neighbors = incidentEdges(newGraph,1);
	printf("%s\n",neighbors);

	neighbors = incidentEdges(newGraph,2);
	printf("%s\n",neighbors);

	removeEdge(newGraph,'B');
	if(!areAdjacent(newGraph,1,2)){
		printf("1 and 2 are no longer Adjacent\n");
	}

	removeVertex(newGraph,0);
	if(!areAdjacent(newGraph,0,1)){
		printf("0 and 1 are no longer Adjacent\n");
	}
}

