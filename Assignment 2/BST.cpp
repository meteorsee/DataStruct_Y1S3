#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {

	if (cur == NULL) return;

	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}

// edit start from here
int BST::height(BTNode* cur) {
	if (cur == NULL) {
		return 0;
	}
	else{
		int left = height(cur->left);
		int right = height(cur->right);

		if (left > right) { // if left's height is larger than right's then need to add 1 to left's height
		return left + 1;
		}
		else {
			return right + 1;
		}
	}
}

bool BST::deepestNodes() {
	int x = 0;
	if (root == NULL) {
		return false;
	}
	else {
		x = height(root);
		cout << "The height is :" << x << endl;
		deepestNodeSecond(root, 0, x-1); // from height 0 of tree
		return true;
	}
}

void BST::deepestNodeSecond(BTNode* cur, int curHeight, int targetHeight) {
	if (cur == NULL) {
		return;
	}
	if (curHeight == targetHeight) {
		cout << "The Deepest Node = " << cur->item.id << " \n";
		return;
	}
	deepestNodeSecond(cur->left, curHeight + 1, targetHeight);
	deepestNodeSecond(cur->right, curHeight + 1, targetHeight);
}

bool BST::display(int order, int source){
	ofstream outputFile;
		outputFile.open("student-info.txt");
	if (root == NULL) {
		cout << "There is no data in the tree. \nPlease input some data into the system"<<endl;
		return false;
	}
	else{
		
		displaySecond(root, order, source, outputFile);
		if(source ==2){
			system("cls");
			cout<<"The file has successfully created"<<endl;
		} 
	}
}
void BST::displaySecond(BTNode *cur, int order, int source, ofstream& outputFile){
	BST *student1 = new BST ;
	Student student;
	if (cur == NULL){
		return;
	}
	if (order == 1) {				//if the user choose assecending order
		if (source == 1) {			//if the user choose print to on screem
				displaySecond(cur->left, order, source, outputFile);
				cur->item.print(cout);
				displaySecond(cur->right, order, source, outputFile);
		}
		else if (source == 2) {			//if the user choose to print in file
				displaySecond(cur->left, order, source, outputFile);
				cur->item.print(outputFile);
				displaySecond(cur->right, order, source, outputFile);
		}
	}
	else if (order == 2) {			//if the user choose desecending order
		if (source == 1) {			//if the user choose to print on screem
				displaySecond(cur->right, order, source, outputFile);
				cur->item.print(cout);
				displaySecond(cur->left, order, source, outputFile);
		}
		else if (source == 2) {			//if the user choose to print in file
				displaySecond(cur->right, order, source, outputFile);
				cur->item.print(outputFile);
				displaySecond(cur->left, order, source, outputFile);
		}
	}
}
//Clone SubTree
bool BST::CloneSubTree(BST t1, type item) {

	BTNode* cur = root;
	if (t1.root == NULL) {
		cout << "There is no data in the tree. \nPlease input some data into the system" << endl;
		return false;
	}

	if (root != NULL) {
		return false;
	}

	int key = item.id;
	CloneSubTree2(cur, t1.root, key);
	cout<<"<----------------------------- Cloned SubTree t2 ----------------------------->"<<endl;
	preOrderPrint(); //print the cloned tree
	cout << "<----------------------------- Cloned SubTree t2 ----------------------------->" << endl;
	cout<<"<----------------------------- Tree t1 ----------------------------->"<<endl;
	t1.preOrderPrint(); //print the original tree t1
	cout << "<----------------------------- Tree t1 ----------------------------->" << endl;
	return true;
}


bool BST::CloneSubTree2(BTNode* t1, BTNode* cur, int key) {
	if (cur == NULL){
		return false;
	}
		
	if (cur->item.id == key) {
		root = cur;
		return true;
	}
	CloneSubTree2(t1, cur->left, key);
	CloneSubTree2(t1, cur->right, key);

	return true;
}

bool BST::printLevelNodes() {
	Queue queue;
	BTNode* cur;
	int head = 1, tail = 0, x = 1;

	queue.enqueue(root);
	if (root == NULL) {
		cout << "There is no data in the tree. \nPlease input some data into the system" << endl;
		return false;
	}
	else {
		while (!queue.empty()) {
			tail = 0;
			cout << "Level " << x++ << " nodes: ";
			while (head != 0) {
				queue.dequeue(cur);
				cout << cur->item.id << " ";
				head--;
				if (cur->left != NULL) {
					queue.enqueue(cur->left);
					tail++;
				}
				if (cur->right != NULL) {
					queue.enqueue(cur->right);
					tail++;
				}
			}
			head = tail;
			cout << "\n";
		}
	}

	return true;
}

/* UTILITY FUNCTIONS */
/* Utility that prints out an array on a line. */
bool BST::printDataArray(int ints[], int length)
{
    
    if(length==0){
        return false;
    }
    
	for (int i = 0; i < length; i++)
	{
		cout << ints[i] << " ";
	}
	cout<<endl;
	return true;
}
/* Recursive helper function -- given a node,
and an array containing the path from the root
node up to but not including this node,
print out all the root-leaf paths.*/
bool BST::printPathsRecur(BTNode *cur, int path[], int pathLength)
{
	if (cur == NULL)
		return false;
	
	/* append this node to the path array */
	path[pathLength] = cur->item.id;
	pathLength++;
	
	/* it's a leaf, so print the path that lead to here */
	if (cur->left == NULL && cur->right == NULL)
	{
		printDataArray(path, pathLength);
	}
	else
	{
		/* otherwise try both subtrees */
		printPathsRecur(cur->left, path, pathLength);
		printPathsRecur(cur->right, path, pathLength);
	}
}

/*Given a binary tree, print out all of its root-to-leaf
paths, one per line. Uses a recursive helper to do the work.*/
bool BST:: printPath(){
	BTNode* cur = root;
    if (root == NULL){
		cout << "There is no data in the tree. \nPlease input some data into the system" << endl;
		return false;
	}
	else{
		int path[3000]; // the size of the path can be change
		cout << "Below are all the external paths for the tree: " << endl;
		cout << endl;
		printPathsRecur(cur, path, 0);
	}
}



