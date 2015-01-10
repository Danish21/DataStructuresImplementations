#include <stdio.h>
#include <stdlib.h>

////An edge and vertex list implementation of a graph
////////FOr simpliecity all vertex are ints < 100 and all edges are capital letters

#define doesNotExist 0

struct edge{ //an edge is an edge entry in the edgeList

	char name;
	int vertex1;
	int vertex2;
	int exists; 

}typedef edge;



struct Graph{ // is a list of vertexs and a list of edges

	int * vertexList;
	edge * edgeList;

}typedef Graph;


int min(int a, int b){

	if(a<b){return a;}

	return b;
}

int max(int a, int b){

	if(a>b){return a;}

	return b;

}
int edgeHash(char edge){
	return edge-65;
}
void graphInit(Graph * myGraph){ //intialize graph on the heap
	
	
	myGraph->vertexList = (int*) malloc(sizeof(int)*100);
	
	for(int i =0; i<100; i++){
		myGraph->vertexList[i]=0; //intialize all vertexes to not exist
	}

	myGraph->edgeList = (edge *) malloc(sizeof(edge)*26);
	for(int i =0; i<26; i++){
		myGraph->edgeList[i].exists=0; //intialize all edge to not exist
	}

}

void graphInsertVertex(Graph * myGraph, int vertex){ //simply mark a boolean to say it exists
//O(1) as simply changing a boolean
	if(vertex < 100){
		myGraph->vertexList[vertex] = 1;
	}else{
		printf("Invalid vertex entry\n");
	}

}

void graphInsertEdge(Graph * myGraph, char edge, int vertex1, int vertex2){ //Marks edge as existing and sets the name of edges and vertexs

//0(1) as changing 4 variables everytime
	if( (edge >= 'A') && (edge <= 'Z') ){

		int index = edgeHash(edge);
		//printf("Edge index %d\n",index );
		(myGraph->edgeList[index]).exists = 1;
		(myGraph->edgeList[index]).name = edge;
		(myGraph->edgeList[index]).vertex1 = min(vertex1,vertex2);
		(myGraph->edgeList[index]).vertex2 = max(vertex1,vertex2);

	}else{
		printf("Invalid edge entry\n");
	}


}


void removeEdge(Graph * myGraph, char edge){ //mark that the edge does not exist
//0(1) as simply changing a boolean

	if( (edge >= 'A') && (edge <= 'Z') ){ 

		int index = edgeHash(edge);

		(myGraph->edgeList[index]).exists = doesNotExist;

	}else{
		printf("Invalid edge entry\n");
	}
}



void removeVertex(Graph *  myGraph, int vertex){ //Marks

//O(M=size of edge list) as have to go through the whole edge list to remove the edges the vertex is an endpoint of

	if(vertex < 100){
		myGraph->vertexList[vertex] = doesNotExist;
	}else{
		printf("Invalid vertex entry\n");
	}


	for(int i=0; i < 26; i++){

		if(myGraph->edgeList[i].exists &&  ( (myGraph->edgeList[i].vertex1 == vertex) || (myGraph->edgeList[i].vertex2 == vertex) )  ){

			myGraph->edgeList[i].exists = doesNotExist;

		}

	}

}


int areAdjacent( Graph * myGraph, int v1, int v2){
//O(M=size of edge list) as have to go through all the edges to see if v1 or v2 share an edge

	int vertex1 = min(v1,v2);
	int vertex2 = max(v1,v2);

	for(int i=0; i < 26; i++){

		if(myGraph->edgeList[i].exists &&  ( (myGraph->edgeList[i].vertex1 == vertex1) && (myGraph->edgeList[i].vertex2 == vertex2) )  ){

			return 1;

		}

	}

	return 0;

}


char * incidentEdges(Graph * myGraph,int vertex){

	//O(M=size of edge list) as have to go through all the edges to see if which vertex share an edge with argument vertex

	char * listOfEdge = (char *) malloc(2); //String of characters of incident Edges
	int size = 0;
	int capacity = 2;

	for(int i=0; i < 26; i++){

		if(myGraph->edgeList[i].exists &&  ( (myGraph->edgeList[i].vertex1 == vertex) || (myGraph->edgeList[i].vertex2 == vertex) )  ){

				listOfEdge[size] = myGraph->edgeList[i].name;
				size ++;

				if(size == capacity ){ //make string bigger if there are more edges
					listOfEdge = (char *)realloc(listOfEdge, capacity * 2);
					capacity =capacity*2;
				}

		}

	}
	//printf("size: %d\n",size);
	listOfEdge[size]='\0';//Null terminated the string
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

