#include <stdio.h>
#include <stdlib.h>
struct node{

	int key;
	int val;
	struct node * left;
	struct node * right;

}typedef node;


struct BST{
	node * root; 
}typedef BST;

node * newNode(int key, int value){

	node * mNode = (node *)malloc(sizeof(node));
	mNode->key= key;
	mNode->val = value;
	mNode->left = NULL;
	mNode->right = NULL;

	return mNode;
}
void add(node * root, int key, int value){
	
	if( (root->key == key) || (root==NULL)){
		return;
	}

	if(key < root->key){
		if( root->left == NULL){
			root->left = newNode(key,value);
		}else{
			add(root->left, key, value);
		}
	}

	else{
		if(root->right == NULL){
			root->right = newNode(key,value);
		}else{
			add(root->right, key, value);
		}
	}


}
void bstInsert(node ** rootPointer, int key, int value){
	//printf("In insert\n");
	if(*rootPointer == NULL){
		//printf("Inserting at top\n");
		*rootPointer =  newNode(key, value);
	}else{
		add(*rootPointer, key, value);
	}

}
node * find(node * root, int key){
	if(root == NULL){
		return NULL;
	}

	if(root->key==key){
		return root;
	}

	if(key < root->key){
		return find(root->left, key);
	}

	else{
		return find(root->right, key);
	}
}

node ** findIOP(node ** rootPointer){
	
	node ** iopPointer = rootPointer;

	while( (*iopPointer)->left != NULL ){
		iopPointer = &((*iopPointer)->left); 
	}

	return iopPointer;
}
void bstRemove(node ** rootPointer, int key){

	node * root = *rootPointer;

	if(root == NULL){
		return;
	}



	if(key < root->key){
		bstRemove(& (root->left) , key);
	}

	else if(key > root->key){
		bstRemove(& (root->right) , key);
	}

	else if( (root->left == NULL) &&  (root->right == NULL) ){ //0 children
		free(*rootPointer);
		*rootPointer = NULL;
	}

	else if( (root->left == NULL) ){ //1 children
		node * temp = root;
		*rootPointer = root->right;
		free(temp);
	}
	else if( (root->right == NULL) ){ //1 children
		node * temp = root;
		*rootPointer = root->left;
		free(temp);
	}
	else{ //2 children

		node ** iopPointer = findIOP(rootPointer);
		
		root->key = (*iopPointer)->key;
		root->val = (*iopPointer)->val;

		bstRemove(iopPointer,root->key);
	}

}
void printInOrder(node * root){
	if(root==NULL){
		//printf("Root is NULL\n");
		return;
	}
	printInOrder(root->left);
	printf("key: %d value: %d\n",root->key,root->val);
	printInOrder(root->right);
}

void bstDestroy(node ** rootPointer){
	if( (*rootPointer)==NULL){return;}
	
	bstDestroy( &( (*rootPointer)->left ) );
	bstDestroy( &( (*rootPointer)->right ) );
	
	free(*rootPointer);
	(*rootPointer) = NULL;

}
int main(){
	

	node * treeRoot = NULL;

	bstInsert(&treeRoot, 5, 5);
	bstInsert(&treeRoot, 2, 5);
	bstInsert(&treeRoot, 3, 5);
	bstInsert(&treeRoot, 4, 5);
	bstInsert(&treeRoot, 1, 5);
	bstRemove(&treeRoot, 1);
	bstRemove(&treeRoot, 4);
	bstRemove(&treeRoot, 5);
	bstRemove(&treeRoot, 3);
	bstRemove(&treeRoot, 2);
	bstInsert(&treeRoot, 6,13);
	bstInsert(&treeRoot, 8,15);

	node * found = find(treeRoot, 8);
	printf("found key: %d value: %d\n",found->key,found->val );
	printInOrder(treeRoot);
	bstDestroy(&treeRoot);
	found = find(treeRoot, 8);
	if(!found){
		printf("Nothing Found\n");
	}
	printInOrder(treeRoot);

}