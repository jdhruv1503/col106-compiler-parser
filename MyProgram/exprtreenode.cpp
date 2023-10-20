/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){

    type = ":=";

    left = NULL;
    right = NULL;

}

ExprTreeNode::ExprTreeNode(string t,int v){

    type = "VAR";
    id = t;
    num = v;

    left = NULL;
    right = NULL;
  
}

ExprTreeNode::~ExprTreeNode(){

    delete left;
    delete right;

}

