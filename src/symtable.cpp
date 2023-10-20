/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line

SymbolTable::SymbolTable(){

    size = 0;
    root = new SymNode();

}

void SymbolTable::insert(string k){

    if ( size == 0 ) {

        root->key = k;
        size = 1;

    }

    else {

        SymNode *current = root;

        while (true) {

            if (current->key < k) {

                if (current->right == NULL) {

                    current->right = new SymNode();
                    current->right->key = k;
                    current->right->par = current;
                    size += 1;
                    current = current->right;
                    break;

                }
                else {
                    current = current->right;
                }

            }

            else if (current->key > k) {

                if (current->left == NULL) {

                    current->left = new SymNode();
                    current->left->key = k;
                    current->left->par = current;
                    size += 1;
                    current = current->left;
                    break;

                }
                else {
                    current = current->left;
                }

            }
        
            else {
                // it already exists
                return;
            }

        }

        // Now current contains the newly inserted node! Update heights going up, and calculate balance factor

        while(current->par != NULL) {

            // update height

            current = current->par;

            int lefth, righth, bf;

            if(current->left != NULL) {
                lefth = current->left->height;
            }
            else {
                lefth = 0;
            }
            if(current->right != NULL) {
                righth = current->right->height;
            }
            else {
                righth = 0;
            }

            // check if height change
            int oldh = current->height;

            if (lefth > righth) {
                current->height = lefth + 1;
            }
            else {
                current->height = righth + 1;
            }
            /*
            if (current->height == oldh) {
                break; // terminate rebalance
            }
            */

            // find balance factor

            bf = righth - lefth;

            if (bf == 2) {

                // find right's balance factor
                int rightrighth, rightlefth, rightbf;

                if (current->right->right != NULL) {
                    rightrighth = current->right->right->height;
                }
                else {
                    rightrighth = 0;
                }

                if (current->right->left != NULL) {
                    rightlefth = current->right->left->height;
                }
                else {
                    rightlefth = 0;
                }

                rightbf = rightrighth - rightlefth;

                if (rightbf == 1) {

                    // RR

                    if (current->par != NULL){
                        if (current->par->right != NULL) {
                            if (current->par->right->key == current->key) {
                                SymNode *parent = current->par;
                                parent->right = current->RightRightRotation();
                                parent->right->par = parent;
                            }
                            else {
                                SymNode *parent = current->par;
                                parent->left = current->RightRightRotation();
                                parent->left->par = parent;
                            }
                        }
                        else {
                            SymNode *parent = current->par;
                            parent->left = current->RightRightRotation();
                            parent->left->par = parent;
                        }
                    }

                    else {
                        root = current->RightRightRotation();
                        root->par = NULL;
                    }
                    break;

                }
                else {

                    // RL

                    // right rotate at current's right

                    current->right = current->right->LeftLeftRotation();
                    current->right->par = current;

                    // left rotate at current
                    
                    if (current->par != NULL){
                        if (current->par->right != NULL) {
                            if (current->par->right->key == current->key) {
                                SymNode *parent = current->par;
                                parent->right = current->RightRightRotation();
                                parent->right->par = parent;
                            }
                            else {
                                SymNode *parent = current->par;
                                parent->left = current->RightRightRotation();
                                parent->left->par = parent;
                            }
                        }
                        else {
                            SymNode *parent = current->par;
                            parent->left = current->RightRightRotation();
                            parent->left->par = parent;
                        }
                    }

                    else {
                        root = current->RightRightRotation();
                        root->par = NULL;
                    }
                    break;


                }
            }
            else if (bf == -2) {

                // find left's balance factor
                int leftrighth, leftlefth, leftbf;

                if (current->left->right != NULL) {
                    leftrighth = current->left->right->height;
                }
                else {
                    leftrighth = 0;
                }

                if (current->left->left != NULL) {
                    leftlefth = current->left->left->height;
                }
                else {
                    leftlefth = 0;
                }

                leftbf =leftrighth -leftlefth;

                if (leftbf == 1) {

                    // LR

                    // left rotate at current's left

                    current->left = current->left->RightRightRotation();
                    current->left->par = current;

                    // right rotate at current

                    if (current->par != NULL){
                        if (current->par->right != NULL) {
                            if (current->par->right->key == current->key) {
                                SymNode *parent = current->par;
                                parent->right = current->LeftLeftRotation();
                                parent->right->par = parent;
                            }
                            else {
                                SymNode *parent = current->par;
                                parent->left = current->LeftLeftRotation();
                                parent->left->par = parent;
                            }
                        }
                        else {
                            SymNode *parent = current->par;
                            parent->left = current->LeftLeftRotation();
                            parent->left->par = parent;
                        }
                    }

                    else {
                        root = current->LeftLeftRotation();
                        root->par = NULL;
                    }
                    break;

                }
                else {

                    // LL

                    if (current->par != NULL){
                        if (current->par->right != NULL) {
                            if (current->par->right->key == current->key) {
                                SymNode *parent = current->par;
                                parent->right = current->LeftLeftRotation();
                                parent->right->par = parent;
                            }
                            else {
                                SymNode *parent = current->par;
                                parent->left = current->LeftLeftRotation();
                                parent->left->par = parent;
                            }
                        }
                        else {
                            SymNode *parent = current->par;
                            parent->left = current->LeftLeftRotation();
                            parent->left->par = parent;
                        }
                    }

                    else {
                        root = current->LeftLeftRotation();
                        root->par = NULL;
                    }
                    break;

                }
            }

        }

    }

}

void SymbolTable::remove(string k) {
    // Find the node to be deleted and its parent
    SymNode *current = root, *parent = NULL;

    while (current != NULL && current->key != k) {
        parent = current;
        if (k < current->key) {
            current = current->left;
        } else if (k > current->key) {
            current = current->right;
        }
    }

    // If the key isn't found in the tree
    if (current == NULL) {
        return;
    }

    // Case 1: The node to be deleted has no children
    if (current->left == NULL && current->right == NULL) {
        if (current != root) {
            if (parent->left == current) {
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
        } else {
            root = NULL;
        }
        free(current);
        current = parent;
        size--;
    }
    // Case 2: The node to be deleted has two children
    else if (current->left && current->right) {
        // Find its in-order successor node
        SymNode *successor = current->right;

        while (successor->left != NULL) {
            successor = successor->left;
        }

        // Store successor value
        string val = successor->key;
        int add = successor->address;

        // Recursively delete the successor. Note that the successor
        // will have at most one child (right child)
        remove(successor->key);

        // Copy value of the successor to the current node
        current->key = val;
        current->address = add;
    }
    // Case 3: The node to be deleted has only one child
    else {
        SymNode *child = (current->left) ? current->left : current->right;

        // If the node to be deleted is not a root node, then set its parent
        // to its child
        if (current != root) {
            if (current == parent->left) {
                parent->left = child;
            } else {
                parent->right = child;
            }
        }
        // If the node to be deleted is a root node, then set the root to the child
        else {
            root = child;
        }

        // Set the parent of the child to the parent of the deleted node
        child->par = parent;
        free(current);
        current = child;
        size--;
    }

    if (current != NULL) {

    // Find height of current
    int righth, lefth;
    
    if (current->right) {
        righth = current->right->height;
    }
    else {
        righth = 0;
    }

    if (current->left) {
        lefth = current->left->height;
    }
    else {
        lefth = 0;
    }

    if (righth > lefth) {
        current->height = righth + 1;
    }
    else {
        current->height = lefth + 1;
    }

    // Rebalance the tree
    while(current->par != NULL) {

            // update height

            current = current->par;

            int lefth, righth, bf;

            if(current->left != NULL) {
                lefth = current->left->height;
            }
            else {
                lefth = 0;
            }
            if(current->right != NULL) {
                righth = current->right->height;
            }
            else {
                righth = 0;
            }

            // check if height change
            int oldh = current->height;

            if (lefth > righth) {
                current->height = lefth + 1;
            }
            else {
                current->height = righth + 1;
            }

            /*
            if (current->height == oldh) {
                break; // terminate rebalance
            }
            */

            // find balance factor

            bf = righth - lefth;

            if (bf == 2) {

                // find right's balance factor
                int rightrighth, rightlefth, rightbf;

                if (current->right->right != NULL) {
                    rightrighth = current->right->right->height;
                }
                else {
                    rightrighth = 0;
                }

                if (current->right->left != NULL) {
                    rightlefth = current->right->left->height;
                }
                else {
                    rightlefth = 0;
                }

                rightbf = rightrighth - rightlefth;

                if (rightbf == 1) {

                    // RR

                    if (current->par != NULL){
                        if (current->par->right != NULL) {
                            if (current->par->right->key == current->key) {
                                SymNode *parent = current->par;
                                parent->right = current->RightRightRotation();
                                parent->right->par = parent;
                            }
                            else {
                                SymNode *parent = current->par;
                                parent->left = current->RightRightRotation();
                                parent->left->par = parent;
                            }
                        }
                        else {
                            SymNode *parent = current->par;
                            parent->left = current->RightRightRotation();
                            parent->left->par = parent;
                        }
                    }

                    else {
                        root = current->RightRightRotation();
                        root->par = NULL;
                    }
                    break;

                }
                else {

                    // RL

                    // right rotate at current's right

                    current->right = current->right->LeftLeftRotation();
                    current->right->par = current;

                    // left rotate at current
                    
                    if (current->par != NULL){
                        if (current->par->right != NULL) {
                            if (current->par->right->key == current->key) {
                                SymNode *parent = current->par;
                                parent->right = current->RightRightRotation();
                                parent->right->par = parent;
                            }
                            else {
                                SymNode *parent = current->par;
                                parent->left = current->RightRightRotation();
                                parent->left->par = parent;
                            }
                        }
                        else {
                            SymNode *parent = current->par;
                            parent->left = current->RightRightRotation();
                            parent->left->par = parent;
                        }
                    }

                    else {
                        root = current->RightRightRotation();
                        root->par = NULL;
                    }
                    break;


                }
            }
            else if (bf == -2) {

                // find left's balance factor
                int leftrighth, leftlefth, leftbf;

                if (current->left->right != NULL) {
                    leftrighth = current->left->right->height;
                }
                else {
                    leftrighth = 0;
                }

                if (current->left->left != NULL) {
                    leftlefth = current->left->left->height;
                }
                else {
                    leftlefth = 0;
                }

                leftbf =leftrighth -leftlefth;

                if (leftbf == 1) {

                    // LR

                    // left rotate at current's left

                    current->left = current->left->RightRightRotation();
                    current->left->par = current;

                    // right rotate at current

                    if (current->par != NULL){
                        if (current->par->right != NULL) {
                            if (current->par->right->key == current->key) {
                                SymNode *parent = current->par;
                                parent->right = current->LeftLeftRotation();
                                parent->right->par = parent;
                            }
                            else {
                                SymNode *parent = current->par;
                                parent->left = current->LeftLeftRotation();
                                parent->left->par = parent;
                            }
                        }
                        else {
                            SymNode *parent = current->par;
                            parent->left = current->LeftLeftRotation();
                            parent->left->par = parent;
                        }
                    }

                    else {
                        root = current->LeftLeftRotation();
                        root->par = NULL;
                    }
                    break;

                }
                else {

                    // LL

                    if (current->par != NULL){
                        if (current->par->right != NULL) {
                            if (current->par->right->key == current->key) {
                                SymNode *parent = current->par;
                                parent->right = current->LeftLeftRotation();
                                parent->right->par = parent;
                            }
                            else {
                                SymNode *parent = current->par;
                                parent->left = current->LeftLeftRotation();
                                parent->left->par = parent;
                            }
                        }
                        else {
                            SymNode *parent = current->par;
                            parent->left = current->LeftLeftRotation();
                            parent->left->par = parent;
                        }
                    }

                    else {
                        root = current->LeftLeftRotation();
                        root->par = NULL;
                    }
                    break;

                }
            }
        }
    }

    if(current == root && size != 0) {
        // check it once

        // update height

            int lefth, righth, bf;

            if(current->left != NULL) {
                lefth = current->left->height;
            }
            else {
                lefth = 0;
            }
            if(current->right != NULL) {
                righth = current->right->height;
            }
            else {
                righth = 0;
            }

            // check if height change
            int oldh = current->height;

            if (lefth > righth) {
                current->height = lefth + 1;
            }
            else {
                current->height = righth + 1;
            }

            /*
            if (current->height == oldh) {
                break; // terminate rebalance
            }
            */

            // find balance factor

            bf = righth - lefth;

            if (bf == 2) {

                // find right's balance factor
                int rightrighth, rightlefth, rightbf;

                if (current->right->right != NULL) {
                    rightrighth = current->right->right->height;
                }
                else {
                    rightrighth = 0;
                }

                if (current->right->left != NULL) {
                    rightlefth = current->right->left->height;
                }
                else {
                    rightlefth = 0;
                }

                rightbf = rightrighth - rightlefth;

                if (rightbf == 1) {

                    // RR

                    if (current->par != NULL){
                        if (current->par->right != NULL) {
                            if (current->par->right->key == current->key) {
                                SymNode *parent = current->par;
                                parent->right = current->RightRightRotation();
                                parent->right->par = parent;
                            }
                            else {
                                SymNode *parent = current->par;
                                parent->left = current->RightRightRotation();
                                parent->left->par = parent;
                            }
                        }
                        else {
                            SymNode *parent = current->par;
                            parent->left = current->RightRightRotation();
                            parent->left->par = parent;
                        }
                    }

                    else {
                        root = current->RightRightRotation();
                        root->par = NULL;
                    }

                }
                else {

                    // RL

                    // right rotate at current's right

                    current->right = current->right->LeftLeftRotation();
                    current->right->par = current;

                    // left rotate at current
                    
                    if (current->par != NULL){
                        if (current->par->right != NULL) {
                            if (current->par->right->key == current->key) {
                                SymNode *parent = current->par;
                                parent->right = current->RightRightRotation();
                                parent->right->par = parent;
                            }
                            else {
                                SymNode *parent = current->par;
                                parent->left = current->RightRightRotation();
                                parent->left->par = parent;
                            }
                        }
                        else {
                            SymNode *parent = current->par;
                            parent->left = current->RightRightRotation();
                            parent->left->par = parent;
                        }
                    }

                    else {
                        root = current->RightRightRotation();
                        root->par = NULL;
                    }

                }
            }
            else if (bf == -2) {

                // find left's balance factor
                int leftrighth, leftlefth, leftbf;

                if (current->left->right != NULL) {
                    leftrighth = current->left->right->height;
                }
                else {
                    leftrighth = 0;
                }

                if (current->left->left != NULL) {
                    leftlefth = current->left->left->height;
                }
                else {
                    leftlefth = 0;
                }

                leftbf =leftrighth -leftlefth;

                if (leftbf == 1) {

                    // LR

                    // left rotate at current's left

                    current->left = current->left->RightRightRotation();
                    current->left->par = current;

                    // right rotate at current

                    if (current->par != NULL){
                        if (current->par->right != NULL) {
                            if (current->par->right->key == current->key) {
                                SymNode *parent = current->par;
                                parent->right = current->LeftLeftRotation();
                                parent->right->par = parent;
                            }
                            else {
                                SymNode *parent = current->par;
                                parent->left = current->LeftLeftRotation();
                                parent->left->par = parent;
                            }
                        }
                        else {
                            SymNode *parent = current->par;
                            parent->left = current->LeftLeftRotation();
                            parent->left->par = parent;
                        }
                    }

                    else {
                        root = current->LeftLeftRotation();
                        root->par = NULL;
                    }

                }
                else {

                    // LL

                    if (current->par != NULL){
                        if (current->par->right != NULL) {
                            if (current->par->right->key == current->key) {
                                SymNode *parent = current->par;
                                parent->right = current->LeftLeftRotation();
                                parent->right->par = parent;
                            }
                            else {
                                SymNode *parent = current->par;
                                parent->left = current->LeftLeftRotation();
                                parent->left->par = parent;
                            }
                        }
                        else {
                            SymNode *parent = current->par;
                            parent->left = current->LeftLeftRotation();
                            parent->left->par = parent;
                        }
                    }

                    else {
                        root = current->LeftLeftRotation();
                        root->par = NULL;
                    }

                }
            }
        }

}


int SymbolTable::search(string k){

    if ( size == 0 ) {

        // not found
        return -2;

    }

    else {

        SymNode *current = root;

        while(true) {

            if (current->key < k) {

                if (current->right == NULL) {

                    // not found
                    return -2;

                }
                else {
                    current = current->right;
                }

            }
            else if (current->key > k) {

                if (current->left == NULL) {

                    // not found
                    return -2;

                }
                else {
                    current = current->left;
                }

            }
            else {
                // equality
                // found
                return current->address;
            }
        }

    }

    return -2;

}

void SymbolTable::assign_address(string k,int idx){

    if ( size == 0 ) {

        // not found
        return;

    }

    else {

        SymNode *current = root;

        while(true) {

            if (current->key < k) {

                if (current->right == NULL) {

                    // not found
                    return;

                }
                else {
                    current = current->right;
                }

            }
            else if (current->key > k) {

                if (current->left == NULL) {

                    // not found
                    return;

                }
                else {
                    current = current->left;
                }

            }
            else {
                // equality
                // found
                current->address = idx;
                return;
            }
        }

    }

    return;

}

int SymbolTable::get_size(){

    return size;

}

SymNode* SymbolTable::get_root(){

    return root;

}

SymbolTable::~SymbolTable(){

    delete root;

}