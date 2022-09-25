/*
 * Name: Jared Villanueva (A15821317)
 * Email: jtvillan@ucsd.edu
 *
 * This file contains the functionality of a BST
 *
 */
#include "BST.h"
#include <vector>
#include <iostream>

// initiliaze an empty BST
BST::BST() { 
    root = nullptr;
    numElements = 0;
}

// deallocate anything dynamic
BST::~BST() {
    clear();
}

// return the number of elements in the BST
unsigned int BST::size() const {
    return numElements;
}

// Deletes nodes in postorder 
void postorder(BST::Node *currNode) {
    if (currNode != nullptr) {
        postorder(currNode->leftChild);
        postorder(currNode->rightChild);
        currNode->leftChild = nullptr;
        currNode->rightChild = nullptr;
        currNode->parent = nullptr;
        delete currNode;
    }
}

// remove all elements from the BST
void BST::clear() {
    postorder(root);
    numElements = 0;
}

/**
 * Insert a new element to this BST
 *
 * @param element The new element to insert
 * @return true if the insertion was successful, otherwise false (e.g. duplicate)
 */
bool BST::insert(int element) {
    // case: duplicate element
    if (BST::find(element) == true) {
        return false;
    }

    // case: first element in the BST
    if (BST::size() == 0) {
        root = new Node(element);
        numElements++;
        return true;
    }

    // case: non-duplicate element & not first element
    Node *currNode = root;

    // iterate through the BST
    while (currNode != nullptr) {
        // traverse right
        if (element > currNode->data) {
            // location of insertion found
            if (currNode->rightChild == nullptr) {
                break;
            }
            currNode = currNode->rightChild;
        }
        // traverse left
        if (element < currNode->data) {
            //location of insertion found
            if (currNode->leftChild == nullptr) {
                break;
            }
            currNode = currNode->leftChild;
        }
    }
    Node *newNode = new Node(element);
    // insert right
    if (element > currNode->data && currNode->rightChild == nullptr) {
        newNode->parent = currNode;
        currNode->rightChild = newNode;
    }
    // insert left
    else if (element < currNode->data && currNode->leftChild == nullptr) {
        newNode->parent = currNode;
        currNode->leftChild = newNode;
    }
    numElements++;
    return true;
}

/**
 * Find a query element in this BST
 *
 * @param query The query element to find
 * @return true if query exists in this BST, otherwise false
 */
bool BST::find(const int & query) const {
    // case: BST empty
    if (BST::size() == 0) {
        return false;
    }
    // general case: BST not empty
    Node *currNode = root; // pointer to the root to begin iterating through the BST
    // iterate through the BST
    while (currNode != nullptr) {
        // found the query, done
        if (currNode->data == query) {
            return true;
        }
        // traverse right
        if (query > currNode->data) {
            // no right child, query doesn't exist
            if (currNode->rightChild == nullptr) {
                break;
            }
            // right child exists, traverse
            currNode = currNode->rightChild;
        }
        // traverse left
        else if (query < currNode->data) {
            // no left child, query doesn't exist
            if (currNode->leftChild == nullptr) {
                break;
            }
            // left child exists, traverse
            currNode = currNode->leftChild;
        }
    }
    // query not found
    return false;
}

/**
 * Return the left-most node in this BST, or nullptr if empty
 *
 * @return The left-most node in this BST, or nullptr if empty
 */
BST::Node* BST::getLeftMostNode() {
    // case: BST empty
    if (BST::size() == 0) {
        return nullptr;
    }

    // case: BST not empty
    Node *currNode = root;

    // case: BST of size 1
    if (BST::size() == 1) {
        return root;
    }

    // case: BST root has no left children
    if (root->leftChild == nullptr) {
        return root;
    }

    // general case: root has left children
    while (currNode != nullptr) {
        // leftmost child found
        if (currNode->leftChild == nullptr) {
            break;
        }
        // still has left children
        if (currNode->leftChild != nullptr) {
            currNode = currNode->leftChild;
        }
    }
    return currNode;
}

/**
 * Find the successor of this Node
 *
 * @return pointer to the successor of this Node, or nullptr if none exists
 */
BST::Node* BST::Node::successor() {

    //find the root
    Node *rootBST = this;
    while (rootBST != nullptr) {
        if (rootBST->parent == nullptr) {
            break;
        }
        rootBST = rootBST->parent;
    }

    // case: root node with no children
    if (this->leftChild == nullptr && this->rightChild == nullptr && this->parent == nullptr) {
        return nullptr;
    }

    Node *currNode = this;

    // case: node has right child
    if (this->rightChild != nullptr) {
        currNode = currNode->rightChild;
        while (currNode != nullptr) {
            // leftmost child found
            if (currNode->leftChild == nullptr) {
                break;
            }
            // still has left children
            else if (currNode->leftChild != nullptr) {
                currNode = currNode->leftChild;
            }
        }
        return currNode;
    }

    Node *parentNode = currNode->parent;

    // case: traverse when current node is a left child
    if (currNode == parentNode->leftChild) {
        return parentNode;
    }

    // case: traverse when current node is a right child
    // if (currNode == parentNode->rightChild) {
    //     cout << "current query node is a right leaf child " << endl;
    //     // case: traverse up the tree
    //     while (currNode != nullptr) {
    //         cout << "about to begin traversing up the tree " << endl;
    //         cout << "currNode: " << currNode->data << endl;
    //         cout << "parentNode: " << parentNode->data << endl;
    //         // first time node is it's parent's left child, the parent is our successor
    //         if (currNode == parentNode->leftChild) {
    //             break;
    //         }
    //         cout << "now traversing up the tree " << endl;
    //         if (currNode != parentNode->leftChild) {
    //             currNode = parentNode;
    //             cout << "currNode after traversal: " << currNode->data << endl;
    //             cout << "parentNode before traversal: " << parentNode->data << endl;
    //             cout << "root of bst:" << rootBST->data << endl;
    //             if (parentNode->parent == rootBST) {
    //                 return rootBST;
    //             }
    //             else if (currNode == rootBST) {
    //                 return nullptr;
    //             }
    //             parentNode = parentNode->parent;
    //             cout << "parentNode after traversal: " << parentNode->data << endl;
    //         }
    //     }
    // }

    // case: traverse up when query node is a right child
    while (currNode != nullptr) {
        cout << "here 1" << endl;
        // query node has no successor, and have traversed up to the root node
        if (currNode == rootBST) {
            cout << "here 2 " << endl;
            return nullptr;
        }
        // special case: successor is the root of the BST
        if (currNode == parentNode->leftChild && parentNode == rootBST) {
            cout << "here 3" << endl;
            return rootBST;
        }
        // successor found, most general case
        if (currNode == parentNode->leftChild) {
            cout << "here 4" << endl;
            break;
        }
        // traversing
        cout << "here 5" << endl;
        currNode = currNode->parent;
        parentNode = currNode->parent;
    }
    return parentNode;
}
