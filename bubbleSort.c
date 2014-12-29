#include <stdlib.h>
#include <stdio.h>
#define arraySize 9

void swap(int * arr, int a, int b){

	int temp = arr[a];
	arr[a] =arr[b];
	arr[b]=temp;
}

void doSwapping(int * arr, int arrSize, int * swapped){

	for(int i=0; i<arraySize-1; i++){
		if( arr[i+1]<arr[i] ){
			swap(arr,i,i+1);
			*swapped = 1;
		}
	}

}

void bubbleSort(int * arr, int arrSize){
	
	int swapped =1;

	while(swapped){

		swapped=0;
		doSwapping(arr, arrSize, &swapped);

	}

}



int main(){

	int arr[arraySize];

	for(int i=0; i<arraySize;i++){
		arr[i]=rand()%arraySize;
	}

	bubbleSort(arr,arraySize);

	for(int i=0; i<arraySize; i++){
		printf("|%d", arr[i]);
	}

	printf("|\n");


}