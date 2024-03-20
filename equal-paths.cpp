#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <iostream>
#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
//helper function that returns like an array of heights?
//can't do my first idea bc you can't see parent from the node
//compare heights on l, f, if same do that for l and f nodes too
int pathHeight(Node * root) {
	if(root == NULL) {
		return -1;
	}
	if(root->left != NULL && root->right != NULL) {
		return max(pathHeight(root->left), pathHeight(root->right)) + 1;
	}
	else if(root->left == NULL && root->right == NULL) {
		return 1;
	}
	else if(root->left == NULL) {
		return pathHeight(root->right) + 1;
	}
	else {
		return pathHeight(root->left) + 1;
	}
}

bool equalPaths(Node * root)
{
    // Add your code below
	if(root == NULL) {
		return true;
	}
	if((pathHeight(root->left) == pathHeight(root->right)) || pathHeight(root->left) == -1 || pathHeight(root->right) == -1) {
		return equalPaths(root->left) && equalPaths(root->right);
	}
	else {
		return false;
	}
}

