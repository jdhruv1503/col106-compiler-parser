/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"

//Write your code below this line

MinHeap::MinHeap(){

    root = new HeapNode();
    size = 0;

}

void MinHeap::push_heap(int num){

    if (size == 0) {
        root->val = num;
        size = 1;
        return;
    }

    int newPos = size + 1;

    int* stk = new int[size];
    int ctr = 0;

    while(newPos>=2) {
        stk[ctr] = newPos%2;
        newPos /= 2;
        ctr++;
    }

    HeapNode* curr = root;
    int i = ctr - 1;

    while(i>0) {

        if (stk[i] == 0) {
            curr = curr->left;
        }

        else {
            curr = curr->right;
        }

        i--;

    }

    // insert left
    if (stk[0] == 0) {
        curr->left = new HeapNode();
        curr->left->par = curr;
        curr->left->val = num;
        curr = curr->left;
    }
    else {
        curr->right = new HeapNode();
        curr->right->par = curr;
        curr->right->val = num;
        curr = curr->right;
    }

    size++;
    delete[] stk;

    // insertion done; now we need to heapify UP

    while(curr->par != NULL) {

        if (curr->par->val > curr->val) {
            // swap
            int temp = curr->val;
            curr->val = curr->par->val;
            curr->par->val = temp;
            curr = curr->par;

        }
        else {
            //done
            break;
        }

    }

}

int MinHeap::get_min(){

    return root->val;

}

void MinHeap::pop(){

    // go get the latest node

    if (size == 1) {
        root->left = NULL;
        root->right = NULL;
        root->val = -1;
        size = 0;
        return;
    }

    int newPos = size;

    int* stk = new int[size];
    int ctr = 0;

    while(newPos>=2) {
        stk[ctr] = newPos%2;
        newPos /= 2;
        ctr++;
    }

    HeapNode* curr = root;
    int i = ctr - 1;

    while(i>=0) {

        if (stk[i] == 0) {
            curr = curr->left;
        }

        else {
            curr = curr->right;
        }

        i--;

    }

    delete[] stk;

    // curr is now the last node
    root->val = curr->val;

    // delete curr
    if (curr->par->right != NULL) {
        curr->par->right = NULL;
    }
    else {
        curr->par->left = NULL;
    }
    curr->par = NULL;
    delete curr;
    size--;

    // heapify down from root node
    curr = root;

    while (curr->left != NULL || curr->right != NULL) {
        
        if (curr->val < curr->left->val) {

            if (curr->right != NULL) {

                if (curr->val < curr->right->val) {
                    // heap satisfied
                    break;
                }
                else {
                    // swap w right child
                    int temp = curr->val;
                    curr->val = curr->right->val;
                    curr->right->val = temp;
                    curr = curr->right;
                }

            }
            else {
                // only left child, heap satisfied
                break;
            }

        }
        
        else {
            // swap w left or right child whichever is smaller

            if (curr->right != NULL) {

                if (curr->right->val < curr->left->val) {
                    // swap w right child
                    int temp = curr->val;
                    curr->val = curr->right->val;
                    curr->right->val = temp;
                    curr = curr->right;
                }
                else {
                    // swap w left
                    int temp = curr->val;
                    curr->val = curr->left->val;
                    curr->left->val = temp;
                    curr = curr->left;
                }

            }

            else {

                // swap w left
                int temp = curr->val;
                curr->val = curr->left->val;
                curr->left->val = temp;
                curr = curr->left;

            }


        }
    }

}

MinHeap::~MinHeap(){

    delete root;

}