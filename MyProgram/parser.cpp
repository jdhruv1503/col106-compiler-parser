/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your code below this line

Parser::Parser(){

    expr_trees = {};
    symtable = new SymbolTable();
    last_deleted = -1;

}

void Parser::parse(vector<string> expression){

    vector<ExprTreeNode*> parent_stk = {}; // store last visited nodes

    // eval first 2 elts

    ExprTreeNode *root = new ExprTreeNode();
    root->right = new ExprTreeNode();
    if (expression[0] == "del") {
        root->right->type = "DEL";
    }
    else if (expression[0] == "ret") {
        root->right->type = "RET";
    }
    else {
        root->right->type = "VAR";
        root->right->id = expression[0];
    }
    
    root->left = new ExprTreeNode();

    parent_stk.push_back(root); 
    parent_stk.push_back(root->left);
    root = root->left;

    // eval rest

    for (int i=2; i<expression.size(); i++) {

        if (expression[i] == "(") {
            // descend to left

            root->left = new ExprTreeNode();
            parent_stk.push_back(root->left);
            root = root->left;
        }
        else if (expression[i] == ")") {
            // ascend up

            parent_stk.pop_back();
            root = parent_stk.back();
        }
        else if (expression[i] == "+") {
            // set to operator, descend to right child

            root->type = "ADD";
            root->right = new ExprTreeNode();
            parent_stk.push_back(root->right);
            root = root->right;
        }
        else if (expression[i] == "-") {
            // set to operator, descend to right child

            root->type = "SUB";
            root->right = new ExprTreeNode();
            parent_stk.push_back(root->right);
            root = root->right;
        }
        else if (expression[i] == "*") {
            // set to operator, descend to right child

            root->type = "MUL";
            root->right = new ExprTreeNode();
            parent_stk.push_back(root->right);
            root = root->right;
        }
        else if (expression[i] == "/") {
            // set to operator, descend to right child

            root->type = "DIV";
            root->right = new ExprTreeNode();
            parent_stk.push_back(root->right);
            root = root->right;
        }

        // now, it's either a numerical string or a var
        else {

            bool isnum = true;

            for (int j=0; j<expression[i].length(); j++) {
                if (!isdigit(expression[i][j])) {
                    isnum = false;
                    break;
                }
            }
            
            if (isnum) {
                // set val, ascend

                root->type = "VAL";

                root->num = stoi(expression[i]);

                parent_stk.pop_back();
                root = parent_stk.back();
            }
            else {
                // set var, ascend

                root->type = "VAR";
                root->id = expression[i];

                parent_stk.pop_back();
                root = parent_stk.back();
            }

        }

    }

    parent_stk.clear();
    expr_trees.push_back(parent_stk.front());

}

Parser::~Parser(){

    for(int i=0; i<expr_trees.size(); i++) {
        delete expr_trees[i];
    }
    delete symtable;
  
}