#include <stdio.h>
#include <stdlib.h>
/////////Adjacency Lists Implementation 
//////For simplicity assumes all edges are uppercase letters and all vertexs are integers less than a 100





struct edge{
	//////////This entries makes up an edgelist which in this case is called an edgeArray
	int exists;//A boolean to tell us if an edge exists
	char name;//Name of the edge
	int vertex1;//points to one of the vertexes of the edge
	struct edgeNode * v1Pointer; //Pointer to the vertex in the list of edges of a vertex
	int vertex2;
	struct edgeNode * v2Pointer;

}typedef edge;


struct edgeNode{ //these are nodes in a linked linked which contain the edges of a vertex...I.E. 1 is vertex and it has an edge with vertex to 2 called A
				 //So there will be a VertexNode of 1 and it will contain a linked list with edgenodes containing 2 and 3

	int name; //the name of the vertex i.e 2 
	struct edgeNode * next; //a doubly linked list of all the vertex that share an edge in this example with 1
	struct edgeNode * prev;
	edge * edgePointer; //pointer to the actual edge so a pointer to edge A

}typedef edgeNode;


struct vertexNode{

	edgeNode * head; //Each vertex Node has a linked list of edgeNodes
	edgeNode * tail;
	int exists; //a boolean to check if the vertex exists
	int size; //the size of the linked list

}typedef vertexNode;

struct Graph{

	vertexNode * adjacencyList; //A graph is a hash table of vertex which contain a vertexNode called an adjecency list
	edge * edgeArray; //Also has an array of edges

}typedef Graph;

int min(int a, int b){ //helper function

	if(a<b){return a;}

	return b;
}

int max(int a, int b){ //helper function

	if(a>b){return a;}

	return b;

}

int edgeHash(char edge){ //Since an edge is an Upper case letter, the hash function is a simple shift in the int val to make A=0 and Z=25
	return edge-65; 
}


edgeNode * newEdgeNode(int vertex){ //creates a new edge node on the heap
	
	edgeNode * newNode = (edgeNode*) malloc(sizeof(edgeNode));
	newNode->name=vertex;
	newNode->next=NULL;
	newNode->prev=NULL;

	return newNode;
}	


void graphInit(Graph * myGraph){ //intializes the graph
	
	
	myGraph->adjacencyList = (vertexNode*) malloc(sizeof(vertexNode)*100); //creates space for an adjency list on the heap

	for(int i=0;i<100;i++){
		myGraph->adjacencyList[i].head = NULL; //zero and Null all the intial values
		myGraph->adjacencyList[i].tail = NULL;
		myGraph->adjacencyList[i].exists = 0;
		myGraph->adjacencyList[i].size = 0;
	}

	myGraph->edgeArray = (edge *) malloc(sizeof(edge)*26); //creates spaces for an edge array on the heap
	
	for(int i=0; i<26; i++){
		myGraph->edgeArray[i].exists = 0;
	}
		
}


void insertVertex(Graph * myGraph, int vertex){ //Inserts an edge in the edge list

	if(vertex<100){
		myGraph->adjacencyList[vertex].exists = 1;
	}else{
		printf("Invalid Vertex\n");
	}

}

void insertEdgeNode(Graph * myGraph, char edge, int origVertex, int connectingVertex, int first){ // inserts an edgeNode into the linked list

	if( !(myGraph->adjacencyList[origVertex].head) ){ // if head is null insert at beginning
		myGraph->adjacencyList[origVertex].head = newEdgeNode(connectingVertex); // the head equals a new edge node
		myGraph->adjacencyList[origVertex].tail = myGraph->adjacencyList[origVertex].head; //tail is pointing to the same thing as the head
		myGraph->adjacencyList[origVertex].head->edgePointer = & (myGraph->edgeArray[edgeHash(edge)]); //the edge node points to this edge
	}else{
		edgeNode *  temp = myGraph->adjacencyList[origVertex].tail; //get a pointer to the tail
		
		temp->next = newEdgeNode(connectingVertex); //tail's next is this new node

		temp->next->prev = temp; //The new Node's prev is the tail

		temp->next->edgePointer = & (myGraph->edgeArray[edgeHash(edge)]); //set its edgepointer
	
		myGraph->adjacencyList[origVertex].tail = temp->next; //its tail is the new tail
		 
	}


	if(first){ //sets pointer of edge to its two endpoints meaning vertexs that it connects
		myGraph->edgeArray[edgeHash(edge)].v2Pointer = myGraph->adjacencyList[origVertex].tail;
	}else{
		myGraph->edgeArray[edgeHash(edge)].v1Pointer = myGraph->adjacencyList[origVertex].tail;
	}


	myGraph->adjacencyList[origVertex].size++;//increment the size of the linked list


}
void insertEdge(Graph * myGraph, char edge, int v1, int v2){ //to insert an edge

	if( (!(myGraph->adjacencyList[v1].exists)) ||  (!(myGraph->adjacencyList[v2].exists))  ){
		printf("All parts do not exist\n");
		return;
	}
	if(  !((edge >= 'A') && (edge <= 'Z') && (v1<100) && (v2<100)) ){
		printf("Invalid edge entry\n");
		return;
	}

	
	int edgeIndex = edgeHash(edge);

	myGraph->edgeArray[edgeIndex].exists =1;
	myGraph->edgeArray[edgeIndex].name = edge;
	myGraph->edgeArray[edgeIndex].vertex1 = v1;
	myGraph->edgeArray[edgeIndex].vertex2 = v2;

	insertEdgeNode(myGraph,edge,v1,v2,1);
	insertEdgeNode(myGraph,edge,v2,v1,0);
}
void removeEdgeNode(Graph * myGraph, edgeNode * curr, int origVertex){ // helper function to remove an edgeNode from linked list

	if(curr->prev!=NULL){
		curr->prev->next = curr->next; 
	}else{ //if it is Null then need to set head pointer

		myGraph->adjacencyList[origVertex].head = curr->next;
	}

	if(curr->next!=NULL){
		curr->next->prev = curr->prev;
	}else{//if it is Null then need to set tail pointer
		myGraph->adjacencyList[origVertex].tail = curr->prev;
	}
	myGraph->adjacencyList[origVertex].size--; // decrement the size
	free(curr);


}
void removeEdge(Graph * myGraph, char edge){
	///o(1) as have pointer to everything we want to remove
	if(!myGraph->edgeArray[edgeHash(edge)].exists){
		printf("edge does not exist\n");
		return;
	}
	int vertex1 = myGraph->edgeArray[edgeHash(edge)].v1Pointer->name;
	int vertex2 = myGraph->edgeArray[edgeHash(edge)].v2Pointer->name; 
	removeEdgeNode( myGraph, myGraph->edgeArray[edgeHash(edge)].v1Pointer, vertex2 ); //remove both edge nodes

	removeEdgeNode( myGraph, myGraph->edgeArray[edgeHash(edge)].v2Pointer, vertex1);  
	myGraph->edgeArray[edgeHash(edge)].exists = 0; //set edge bollean to not exist

}

void removeVertex(Graph * myGraph, int vertex){
	//O(degree(vertex)) as have need to remove each edge which itself is an O(1) operation

	if( !myGraph->adjacencyList[vertex].exists ){
		printf("Vertex does not exist\n");
		return;
	 }
	edgeNode * curr = myGraph->adjacencyList[vertex].tail;
	
	while(curr!=NULL){// remove all the edges of the linked lists and in the edge array
		edgeNode * next = curr->prev;
		
		removeEdge(myGraph, curr->edgePointer->name);
		
		curr=next;
		
	}
	
	myGraph->adjacencyList[vertex].exists=0;
	myGraph->adjacencyList[vertex].size=0;

}
int searchForVetex(edgeNode * head, int query){

	edgeNode * curr = head;
	
	while(curr!=NULL){
		if(curr->name == query){return 1;}
		
		curr=curr->next;
		
	}

	return 0;
}
int areAdjacent(Graph * myGraph, int v1, int v2){

	//go through the smaller of the linked list and search if an edgenode exists
	//O(min(deg(v1),deg(v2)))

	if(  (!(myGraph->adjacencyList[v1].exists)) || (!(myGraph->adjacencyList[v2].exists))  ){return 0;}
	
	if(myGraph->adjacencyList[v1].size <= myGraph->adjacencyList[v2].size ){ //if v1 lists is smaller search it
	
		return searchForVetex(myGraph->adjacencyList[v1].head, v2);

	}

	return searchForVetex(myGraph->adjacencyList[v2].head, v1); // or else search v2's linked list

}

char * incidentEdges(Graph * myGraph, int vertex){
	
	//goes through the linked list and returns all the edge names
	//o(deg(vertex))

	if(myGraph->adjacencyList[vertex].exists){
		
		char * listOfEdge = (char *) malloc(2);
		int size = 0;
		int capacity = 2;
		edgeNode * curr = myGraph->adjacencyList[vertex].head;

		while(curr!=NULL){

			// printf("1\n");
			if(!curr->edgePointer){printf("Is NULL\n");}
			listOfEdge[size] = curr->edgePointer->name;
			size ++;
			// printf("2\n");
			if(size == capacity ){
				listOfEdge = (char *)realloc(listOfEdge, capacity * 2);
				capacity =capacity*2;
			}
			// printf("3\n");
			
			curr=curr->next;
		}
		// printf("4\n");
		listOfEdge[size]='\0';
		return listOfEdge;
	}

	return NULL;

}

void printLinks(Graph * myGraph, int vertex){
	printf("%d ",vertex );
	edgeNode * curr =  myGraph->adjacencyList[vertex].head;
	while(curr!=NULL){
		printf("%d w/edge: %c ", curr->name, curr->edgePointer->name);

		curr=curr->next;
	}
	printf("\n");
}

void printLinksReverse(Graph * myGraph, int vertex){
	printf("%d ",vertex );
	edgeNode * curr =  myGraph->adjacencyList[vertex].tail;
	while(curr!=NULL){
		printf("%d w/edge: %c ", curr->name, curr->edgePointer->name);

		curr=curr->prev;
	}
	printf("\n");
}

void printEdge(Graph * myGraph, char edge){

	int edgeIndex = edgeHash(edge);


	printf("%c exists: %d name: %c vertex1: %i vertex2: %i vertex1Pointer: %i vertex2Pointer: %i \n",edge, myGraph->edgeArray[edgeIndex].exists, myGraph->edgeArray[edgeIndex].name, myGraph->edgeArray[edgeIndex].vertex1,
	myGraph->edgeArray[edgeIndex].vertex2, myGraph->edgeArray[edgeIndex].v1Pointer->name, myGraph->edgeArray[edgeIndex].v2Pointer->name   );

	int exists;
	char name;
	int vertex1;
	struct edgeNode * v1Pointer;
	int vertex2; 
	struct edgeNode * v2Pointer;

}
int main(){




Graph *  newGraph = (Graph* )malloc(sizeof(Graph));

	graphInit(newGraph);
	//printf("Graph created\n");
	insertVertex(newGraph,0);
	insertVertex(newGraph,1);
	insertVertex(newGraph,2);

	insertEdge(newGraph,'A',0,1);
	insertEdge(newGraph,'B',1,2);
	insertEdge(newGraph,'C',0,2);
	// printLinks(newGraph, 0);
	// printLinks(newGraph, 1);
	// printLinks(newGraph, 2);

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
	removeVertex(newGraph,0);
	if(!areAdjacent(newGraph,1,2)){
		printf("1 and 2 are no longer Adjacent\n");
	}

	// removeEdge(newGraph,'A');
	if(!areAdjacent(newGraph,0,1)){
		printf("0 and 1 are no longer Adjacent\n");
	}

	// //removeEdge(newGraph,'C');
	if(!areAdjacent(newGraph,0,2)){
		printf("0 and 2 are no longer Adjacent\n");
	}




}

