#include <stdlib.h>
#include <stdio.h>
#define arraySize 10

int swap(int * arr, int a, int b){ //swaps two indexs 

	int temp = arr[a];
	arr[a] =arr[b];
	arr[b]=temp;

}

int findMinIndex(int * arr, int start, int arrSize ){ //find the minimum index

	int minIndex= start;

	for(int i=start+1; i<arrSize; i++){
		if(arr[i]<arr[minIndex]){
			minIndex= i;
		}
	}

	return minIndex;

}
int selectionSort(int * arr, int arrSize){ //find the smallest put it at the beginning
										   //find the second smallest number and put it 
										   //at the second spot in the array and so on


	for(int i=0; i<arrSize; i++){

		int minIndex = findMinIndex(arr,i,arrSize);
		swap(arr,i,minIndex);
		
	}


}

int main(){

	int arr[arraySize];

	for(int i=0; i<arraySize;i++){
		arr[i]=rand()%arraySize;
	}

	selectionSort(arr,arraySize);

	for(int i=0; i<arraySize; i++){
		printf("|%d", arr[i]);
	}

	printf("|\n");


}