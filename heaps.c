#include <stdio.h>
#include <stdlib.h>

struct heap{

	int * data;
	int capacity;
	int size;

}typedef heap;


/////////////////////////////////////Helper functions
int min(int a, int b){
	if(a<b){
		return a;
	}

	return b;
}


int leftChildIndex(int parentIndex){
	
	return 2*parentIndex+1;
}

int rightChildIndex(int parentIndex){
	return (2*parentIndex)+2;
}

int parentIndex(int childIndex){

	return (childIndex-1)/2;

}

int swap(heap * myHeap, int index1, int index2){
	int temp = myHeap->data[index1];

	myHeap->data[index1] = myHeap->data[index2];
	myHeap->data[index2] = temp; 

}

int hasLeftChild(heap * myHeap, int pIndex){

	int lChild = leftChildIndex(pIndex);

	if(lChild > myHeap->size){
		return 0;
	}

	return 1;
}

int hasRightChild(heap * myHeap, int pIndex){

	int rChild = rightChildIndex(pIndex);

	if(rChild > myHeap->size){
		return 0;
	}

	return 1;
}

//////////////////////////////////////////////Helper Functions

/////////////////////////////////////////////Classic Heap functions

void heapInit(heap * myHeap, int size){
	
	myHeap->data = (int *)malloc(size * sizeof(int)); // heap has an array of ints
	myHeap->capacity = size; //a capacity
	myHeap->size=0; //and the current size

}

void heapifyDown(heap * myHeap, int index){
	if(index>myHeap->size){ //if index is bigger then size then return
		return;
	}
	
	if(hasLeftChild(myHeap, index)){ // if curr index has a left child
		
		int lIndex = leftChildIndex(index); // get left index

		int rIndex = rightChildIndex(index); //get right index

		int swapIndex= lIndex; //by default it is the left child index since we know it exists

		if( hasRightChild(myHeap,index) && (myHeap->data[rIndex] < myHeap->data[lIndex]) ){ //if right child is smaller
			swapIndex = rIndex; 
		}

		if(myHeap->data[index] > myHeap->data[swapIndex] ){ //if currIndex's data is greater then it can move down the heap
			swap(myHeap,index, swapIndex);
			heapifyDown(myHeap,swapIndex);
		}

	}



}

void heapifyUp(heap * myHeap, int index){

	if(index==0){return;} // if at root then no more up

	int pIndex = parentIndex(index); // get parent index

	if(myHeap->data[pIndex] > myHeap->data[index] ){ // if parent is bigger than child
		swap(myHeap, index, pIndex); //then swap data
		heapifyUp(myHeap,pIndex); //check if can go more up
	}

}

void heapInsert(heap * myHeap, int num){

	if(myHeap->capacity==myHeap->size){ // if heap is full
		
		myHeap->data = (int *)realloc(myHeap->data, myHeap->capacity * 2 * sizeof(int)); //double the size
		myHeap->capacity= 2 * myHeap->capacity;

	}

	myHeap->data[myHeap->size]= num; //insert the element at the end of the heap

	heapifyUp(myHeap,myHeap->size); //and restore the heap structure

	myHeap->size++; //update the size
}


int heapRemoveMin(heap * myHeap){
	
	if(myHeap->size > 0){
		int ret = myHeap->data[0]; //get root data
		
		myHeap->data[0] = myHeap->data[myHeap->size-1]; //take last element and put in place of the root
		//printf("my\n");
		myHeap->size--; // decrease the size

		heapifyDown(myHeap,0); //restore the heap structure

		return ret;
	}
		
	return 0;
}

void buildHeap(heap * myHeap, int * inputArray, int arraySize){ // transfrom an an array of inputs into a heap

	for(int i=0; i<arraySize; i++){
		heapInsert(myHeap, inputArray[i]);
	}

}

///////////////////////////////////////////Classic heap functions



void heapDestroy(heap * myHeap){ //free the heap
	free(myHeap->data);
	free(myHeap);
}

void printHeap(heap * myHeap){ //print the heap array
	

	for(int i=0; i<myHeap->size; i++){
		printf("|%d",myHeap->data[i]);
	}
	printf("|\n");
}

int* heapSort(heap * myHeap){

	int * outputArray = (int *) malloc( myHeap->size * sizeof(int));
	int size = myHeap->size;
	
	for(int i=0; i<size; i++){
		outputArray[i]=heapRemoveMin(myHeap);
	}

	return outputArray;
}

int main(){

	heap * newHeap = (heap *) malloc(sizeof(heap));

	heapInit(newHeap,1);
	

	heapInsert(newHeap,10);
	heapInsert(newHeap,9);
	heapInsert(newHeap,23);
	heapInsert(newHeap,25);
	heapInsert(newHeap,1);
	heapInsert(newHeap,2);
	heapInsert(newHeap,78);
	heapInsert(newHeap,5);
	
	printHeap(newHeap);


	int size = newHeap->size;
	int * outputArray = heapSort(newHeap);
	for(int i=0; i< size; i++){
		printf("|%d",outputArray[i]);
	}

	printf("|\n");


	////Do stuff

	heapDestroy(newHeap);




}