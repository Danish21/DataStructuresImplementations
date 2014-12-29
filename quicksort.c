#include <stdio.h>
#include <stdlib.h>

#define arraySize 200

int swap(int * arr, int a, int b){
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp; 
}

int partition(int * arr, int lo, int hi){ 

	int right=hi; 

	int left=lo;

	int pivotVal = arr[hi];

	while(left<right){

		while( (arr[left]<pivotVal) && (left < right) ){
			left++;
			
		}
		while( (arr[right] >= pivotVal) && (left < right) ){
			right--;
		}

		if(left<right){ //only swap if valid
			swap(arr,left, right);
		}

	}
	
	swap(arr,left,hi);
	return left;


}


void quicksort(int * arr, int lo, int hi){

	
	if(lo>=hi){return;}//base case

	int pivotIndex = partition(arr,lo,hi);

	quicksort(arr,lo,pivotIndex-1);

	quicksort(arr,pivotIndex+1, hi);


}



int main(){
      
   /* Intializes random number generator */
    //srand(time(NULL));

	int arr[arraySize];

	for(int i=0; i<arraySize;i++){
		arr[i]=rand()%arraySize;
	}

	quicksort(arr,0,arraySize-1);

	for(int i=0; i<arraySize; i++){
		printf("|%d", arr[i]);
	}

	printf("|\n");

}