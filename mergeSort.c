
#include <stdio.h>
#include <stdlib.h>

#define arraySize 200


int * merge(int * arr, int lo, int hi, int * tempArr){

	int mid = (lo + hi)/2;

	int left= lo; 

	int right=mid+1;

	int curr = lo;

	while(left <= mid && right <= hi){ //while within the bounds

		if(arr[left]<arr[right]){ // if left is smaller copy over left val into temp array
			tempArr[curr++] = arr[left++];
		}else{
			tempArr[curr++] = arr[right++]; //copy over right val right val into temp array
		}

	}

	while(left<=mid){ //copy over left half if it is left over
		tempArr[curr++] = arr[left++];
	}

	while(right<=hi){ //copy over right half if it is left over
		tempArr[curr++] = arr[right++];
	}
	
	for(int i=lo; i<=hi; i++){ // copy from temp array to actual array
		arr[i]= tempArr[i]; 
	}
}

void mergeSort(int * arr, int lo, int hi, int* tempArr){

	if(lo>=hi ){//base case
		return;
	}

	int mid = (lo + hi)/2; //mid

	mergeSort(arr,lo,mid,tempArr); //sort left half
	mergeSort(arr,mid+1,hi,tempArr); //sort right half

	merge(arr,lo,hi,tempArr); //merge both halfs


}

void mergeSort(int * arr, int arrSize){ // wrapper for mergeSort
	
	int tempArr[arrSize];
	mergeSort(arr, 0, arrSize-1, tempArr);


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