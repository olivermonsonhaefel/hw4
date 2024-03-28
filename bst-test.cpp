#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    BinarySearchTree<char,int> bt;

		bt.insert(std::make_pair(0,0));
		bt.insert(std::make_pair(1,0));
		bt.insert(std::make_pair(5,0));
		bt.insert(std::make_pair(2,0));
		bt.insert(std::make_pair(6,0));
		bt.insert(std::make_pair(3,0));
		bt.insert(std::make_pair(4,0));
		
    // bt.insert(std::make_pair('a',5));
    // bt.insert(std::make_pair('b',8));
		// bt.insert(std::make_pair('f', 2));
		// bt.insert(std::make_pair('c', 7));
		// bt.insert(std::make_pair('d', 9));
		// bt.insert(std::make_pair('e', 1));
		// bt.insert(std::make_pair('g', 3));
		

		/*
		bt.insert(std::make_pair('a',5));
		bt.insert(std::make_pair('b',3));
		bt.insert(std::make_pair('c',8));
		bt.insert(std::make_pair('d',6));
		bt.insert(std::make_pair('e',9));
		*/
    
    // cout << "Binary Search Tree contents:" << endl;
    // for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
    //     cout << it->first << " " << it->second << endl;
    // }/*
    // if(bt.find('b') != bt.end()) {
    //     cout << "Found b" << endl;
    // }
    // else {
    //     cout << "Did not find b" << endl;
    // }
    // cout << "Erasing b" << endl;
    // bt.remove('b');
		// */
		/*
    // AVL Tree Tests
    AVLTree<char,int> at;
    at.insert(std::make_pair('a',1));
    at.insert(std::make_pair('b',2));

    cout << "\nAVLTree contents:" << endl;
    for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(at.find('b') != at.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    at.remove('b');
		*/
    return 0;
}
