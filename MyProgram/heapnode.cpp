/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "heapnode.h"

//Write your code below this line

HeapNode::HeapNode(){

    par = NULL;
    left = NULL;
    right = NULL;

}

HeapNode::HeapNode(int _val){

    val = _val;
    par = NULL;
    left = NULL;
    right = NULL;

}

HeapNode::~HeapNode(){

    delete left;
    delete right;
    delete par;
  
}