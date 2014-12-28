
#include <stdio.h>
#include <stdlib.h>

#define arraySize 200


int * merge(int * arr, int lo, int hi, int * sortedArr){

	int mid = (lo + hi)/2;

	int left= lo; 

	int right=mid+1;

	int curr = lo;
	while(left <= mid && right <= hi){

		if(arr[left]<arr[right]){
			sortedArr[curr++] = arr[left++];
		}else{
			sortedArr[curr++] = arr[right++];
		}

	}

	while(left<=mid){
		sortedArr[curr++] = arr[left++];
	}

	while(right<=hi){
		sortedArr[curr++] = arr[right++];
	}
	for(int i=lo; i<=hi; i++){
		arr[i]= sortedArr[i]; 
	}
}

void mergeSort(int * arr, int lo, int hi, int* sortedArr){

	if(lo>=hi ){
		return;
	}

	//printf("lo: %d hi: %d\n",lo,hi);
	int mid = (lo + hi)/2;

	mergeSort(arr,lo,mid,sortedArr);
	mergeSort(arr,mid+1,hi,sortedArr);

	merge(arr,lo,hi,sortedArr);


}

void mergeSort(int * arr, int arrSize){
	
	int sortedArr[arrSize];
	mergeSort(arr, 0, arrSize-1, sortedArr);


}


int main(int agc, char ** argv){

	int arr[arraySize];

	for(int i=0; i<arraySize;i++){
		arr[i]=arraySize-i;
	}

	mergeSort(arr, arraySize);

	for(int i=0; i<arraySize; i++){
		printf("|%d", arr[i]);
	}
	printf("|\n");
}