/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){

    height = 1;
    address = -1;

    par = NULL;
    left = NULL;
    right = NULL;

}

SymNode::SymNode(string k){

    key = k;
    height = 1; 
    address = -1;

    par = NULL;
    left = NULL;
    right = NULL;

}

SymNode* SymNode::RightRightRotation(){

    SymNode *newRoot = right;
    SymNode *temp;  
    if (newRoot->left != NULL) {
        temp = newRoot->left;
    }
    else {
        temp = NULL;
    }
  
    newRoot->left = right->par;  
    right = temp;

    // update parent pointers

    if (right != NULL) {
        right->par = left->par;
    }
    par = newRoot;
  
    
    if ((left != NULL ? left->height : 0) > (right != NULL ? right->height : 0)) {
        height = (left != NULL ? left->height : 0) + 1;
    }
    else {
        height = (right != NULL ? right->height : 0) + 1;
    }

    if ((newRoot->left != NULL ? newRoot->left->height : 0) > (newRoot->right != NULL ? newRoot->right->height : 0)) {
        newRoot->height = (newRoot->left != NULL ? newRoot->left->height : 0) + 1;  
    }
    else {
        newRoot->height = (newRoot->right != NULL ? newRoot->right->height : 0) + 1;  
    }
  
    return newRoot;  

}

SymNode* SymNode::LeftLeftRotation(){

    // do a right rot

    SymNode *newRoot = left;
    SymNode *temp;  
    if (newRoot->right != NULL) {
        temp = newRoot->right;
    }
    else {
        temp = NULL;
    }
    
  
    newRoot->right = left->par;  
    left = temp;

    // update parent pointers

    if (left != NULL) {
        left->par = right->par;
    }
    par = newRoot;

    // update heights
  
    if ((left != NULL ? left->height : 0) > (right != NULL ? right->height : 0)) {
        height = (left != NULL ? left->height : 0) + 1;
    }
    else {
        height = (right != NULL ? right->height : 0) + 1;
    }

    if ((newRoot->left != NULL ? newRoot->left->height : 0) > (newRoot->right != NULL ? newRoot->right->height : 0)) {
        newRoot->height = (newRoot->left != NULL ? newRoot->left->height : 0) + 1;  
    }
    else {
        newRoot->height = (newRoot->right != NULL ? newRoot->right->height : 0) + 1;  
    }
  
    return newRoot;  

}

SymNode* SymNode::LeftRightRotation(){

    // not used: only implement simple LR and RR
    return NULL;

}

SymNode* SymNode::RightLeftRotation(){

    // not used: only implement simple LR and RR
    return NULL;

}

SymNode::~SymNode(){
    
        delete left;
        delete right;
        delete par;

}