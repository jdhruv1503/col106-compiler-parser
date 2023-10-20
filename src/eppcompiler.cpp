/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

//Write your code below this line

EPPCompiler::EPPCompiler(){

    memory_size = 100;

    for(int i=0; i<memory_size; i++) {
        least_mem_loc.push_heap(i);
    }

}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){

    output_file = out_file;
    memory_size = mem_limit;

    for(int i=0; i<memory_size; i++) {
        least_mem_loc.push_heap(i);
    }

}

void EPPCompiler::compile(vector<vector<string>> code){

    vector<string> finalout = {};

    for(int i=0; i<code.size(); i++) {
        targ.parse(code[i]);
        vector<string> out = generate_targ_commands();
        string thisout = "";

        for (int j=0; j<out.size(); j++) {
            thisout += out[j] + "\n";
        }

        finalout.push_back(thisout);
    }

    write_to_file(finalout);

}

vector<string> EPPCompiler::generate_targ_commands(){

    vector<string> outp = {};

    ExprTreeNode *currenttree = targ.expr_trees.back();

    // do a postorder
    vector<ExprTreeNode*> stak = {};
    vector<ExprTreeNode*> out = {};
    stak.push_back(currenttree);
    while(stak.size() != 0) {
        ExprTreeNode *curr = stak.back();
        stak.pop_back();
        out.push_back(curr);
        if (curr->right != nullptr) {
            stak.push_back(curr->right);
        }
        if (curr->left != nullptr) {
            stak.push_back(curr->left);
        }
        
    }

    out.pop_back();

    while (out.size() != 0) {
        string outst = "";
        // process out.back()
        ExprTreeNode *root = out.back();
        if (root->type == "VAL") {
            outst = "PUSH "+to_string(root->num);
        }
        else if (root->type == "VAR") {
            outst = "PUSH mem["+to_string(targ.symtable->search(root->id))+"]";
        }
        else if (root->type == "ADD") {
            outst = "ADD";
        }
        else if (root->type == "SUB") {
            outst = "SUB";
        }
        else if (root->type == "MUL") {
            outst = "MUL";
        }
        else if (root->type == "DIV") {
            outst = "DIV";
        }
        else if (root->type == ":=") {
            if (root->left->type == "DEL") {
                outst = "DEL = mem["+to_string(targ.symtable->search(root->left->id))+"]";
                least_mem_loc.push_heap(targ.symtable->search(root->left->id));
                targ.symtable->remove(root->left->id);
            }
            else if (root->right->type == "RET") {
                outst = "RET = POP";
            }
            else {
                // it's a value assignment
                targ.symtable->insert(root->right->id);
                targ.symtable->assign_address(root->right->id, least_mem_loc.get_min());
                least_mem_loc.pop();
                outst = "mem["+to_string(targ.symtable->search(root->right->id))+"] = POP";
            }
        }
        // pop from out
        out.pop_back();
        outp.push_back(outst+"\n");
    }

    return outp;

}    

void EPPCompiler::write_to_file(vector<string> commands){

    ofstream ofout(output_file);

    for(int i=0; i<commands.size(); i++) {
        ofout << commands[i];
    }

    ofout.close();

}

EPPCompiler::~EPPCompiler(){

    mem_loc.clear();
  
}

/* -------------------------------------
using namespace std;
#include<iostream>

int main() {

    EPPCompiler *me = new EPPCompiler("out.txt", 100);

    me->compile({{"myname", ":=", "(", "2", "+", "5", ")"},
    {"myname2", ":=", "(", "4", "*", "522", ")"},
    {"myname3", ":=", "(", "5", "/", "523", ")"},
    {"mynam4", ":=", "(", "myname2", "+", "myname3", ")"},
    {"del", ":=", "myname"},
    {"del", ":=", "myname2"},
    {"del", ":=", "myname3"},
    {"myname32", ":=", "(", "5", "/", "523", ")"},
    {"del", ":=", "mynam4"},
    {"rawr", ":=", "(", "(", "(", "myname32", "-", "1000", ")", "*", "224", ")", "/", "2324", ")"},
    {"rawr", ":=", "(", "myname32", "-", "1000", ")"},
    {"ret", ":=", "myname32"}});

    return 0;
}
 */