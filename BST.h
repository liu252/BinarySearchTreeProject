#ifndef BST_h
#define BST_h

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

//treeNode
template<typename T> class TreeNode{
public:
		TreeNode(T d);
		virtual ~TreeNode();

		TreeNode<T>* left; 	//pointer to left child
		TreeNode<T>* right; //pointer to right child

		T key; 				//value at node
};

template<typename T> TreeNode<T>::TreeNode(T d){
		left = 0;		
		right = 0;
		key = d;
}

template<typename T> TreeNode<T>::~TreeNode(){
}

//BST woo
template<typename T> class BST{
public:
		BST(){
				size = 0;
				root = 0;
		}
		virtual ~BST(){
		}

		void addNode(T d); //add an element to the tree
		bool deleteNode(T d); // delete an element from the tree
		void printTree();  //print the tree in order
		void displayNode(T d); //print selected node
		void serialize(ostream &out); //serialize tree to txt

		T returnKey(T d); //return selected node

		bool contains(T d);	//check to see if your tree contains a value
		bool isEmpty() {return(size == 0);}	//check to see if tree is empty
		int getSize() {return size;}		//return the number of elements in the tree
        void deleteTree();

private:
		TreeNode<T>* root;
		int size;
        void deleteHelper(TreeNode<T> *n);
		void printHelper(TreeNode<T>* n);
		void serializeHelper(ostream &out, TreeNode<T>* n);
};

template<typename T> void BST<T>::serialize(ostream &out){
		serializeHelper(out, root);
}

template<typename T> void BST<T>::serializeHelper(ostream &out, TreeNode<T>* n){
	if(n == NULL){
		return;
	}
	else{
		out <<  n->key << endl;		// POTENTIAL ERROR

		serializeHelper(out, n->left);
		serializeHelper(out, n->right);
	}
}

template<typename T> void BST<T>::printTree(){
		printHelper(root);
}

template<typename T> void BST<T>::printHelper(TreeNode<T>* n){
	if(n!= 0){
			printHelper(n->left);
			cout << n->key << endl;
			printHelper(n->right);
	}
}

//add to BST if doesnt exist create new node
template<typename T> void BST<T>::addNode(T d){
		if(isEmpty()){		//if the tree is empty, set to root
				root = new TreeNode<T>(d);
		}
		
		else{
				TreeNode<T>* current = root;
				TreeNode<T>* parent = 0;

				while(current != 0){   //
						parent = current;
						
						if(d < current->key){	//if smaller go left
								current = current->left;
						}
						else{					//if larger go right
								current = current->right;
						}
				}
				TreeNode<T>* newNode = new TreeNode<T>(d);
					
				if(d > parent->key){
						parent->right = newNode;
				}
				else{
						parent->left = newNode;
				}
			}
			++size;
}

//check to see if val in BST
template<typename T> bool BST<T>::contains(T d){
		bool found = false;

		TreeNode<T>* current = root; 

		while((current != 0) && !(found)){
				if(d == current->key){
						found = true;
						continue;
				}
				if(d < current->key){
						current = current->left;
				}
				else{
						current = current->right;
				}
		}

		return found;
}

/*Method to dsiplay a selected node */
template<typename T> void BST<T>::displayNode(T d){
		bool found = false;

		TreeNode<T>* current = root; 

		while((current != 0) && !(found)){
				if(d == current->key){
						found = true;
						cout << current->key << endl;
						continue;
				}
				if(d < current->key){
						current = current->left;
				}
				else{
						current = current->right;
				}
		}
}


template<typename T> T BST<T>::returnKey(T d){
		bool found = false;

		TreeNode<T>* current = root; 

		while((current != 0) && !(found)){
				if(d == current->key){
						found = true;
						return current->key;
				}
				if(d < current->key){
						current = current->left;
				}
				else{
						current = current->right;
				}
		}
    return false;
}

//delete entire tree
template<typename T> void BST<T>::deleteTree(){
    deleteHelper(root);
}

//delete helper
template<typename T> void BST<T>::deleteHelper(TreeNode<T> *n){
    if(n !=0){
        deleteHelper(n->right);
        deleteHelper(n->left);
        delete n;
    }
}

//delete value from BST
template<typename T> bool BST<T>::deleteNode(T d){
    if(root == NULL){
            return false;
    }
		TreeNode<T>* current = root;
		TreeNode<T>* parent = root;

		bool isLeft = true;

		//Standard Node Search Algorithm ********************************
		while(current->key != d){					
				parent = current;
				if(d < current->key){				
						isLeft = true;	
						current = current->left;
				}
				else{								
						isLeft = false;
						current = current->right;
				}
				if(current == NULL) return false;	
		}

		//Case 1: No children ********************************************
		if((current->left == NULL) && (current->right == NULL)){
				if(current == root){	
						root = NULL;
				}		
				else if(isLeft){
						parent->left = NULL;
				}
				else{
					parent->right = NULL;
				}
		}

		//Case 2: One Child (LEFT)******************************************
		else if(current->right == NULL){
				if(current == root){
						root = current->left;
				}
				else if(isLeft){
						parent->left = current->left;
				}
				else{
						parent->right = current->left;
				}
		}

		//Case 2: One Child (RIGHT)******************************************
		else if(current->left == NULL){
				if(current == root){
						root = current->right;
				}
				else if(isLeft){
						parent->left = current->right;
				}
				else{
						parent->right = current->right;
				}
		}

		//Case 3: Two Childtren *********************************************
		else{
				TreeNode<T>* successor = getSuccessor(current);

				if(current == root){
						root = successor;

				}
				else if(isLeft){
						parent->left = successor; 
				}
				else{
						parent->right = successor;
				}

				successor->left = current->left;
		}
		return true;
}


template<typename T> TreeNode<T>* getSuccessor(TreeNode<T>*k){
		TreeNode<T>* sp = k;
		TreeNode<T>* successor = k;
		TreeNode<T>* current = k->right;

		while(current != NULL){
				sp = successor;
				successor = current;
				current = current->left;

		}

		if(successor != k->right){
				sp->left = successor->right;
				successor->right = k->right;
		}

		return successor;
}
#endif
