#include "common.h"
#include <fstream>

extern TreeNode *root;
extern FILE *yyin;
extern int yyparse();
bool parserError = false;
bool typeError = false;

using namespace std;
int main(int argc, char *argv[]) {
    if (argc >= 2) {
        FILE *fin = fopen(argv[1], "r");
        if (fin != nullptr) {
            yyin = fin;
        }
        else {
            cerr << "failed to open file: " << argv[1] << endl;
        }
    }

    InitIOFunctionNode();
    yyparse();

    if (parserError)
        return 0;
        
    root->genNodeId();
#ifdef AST
    cout << "# -------------------------" << endl;
    root->printAST();
    cout << "# -------------------------" << endl;
#endif
    root->typeCheck();

    if (typeError)
        return 0;

    root->genCode();

    return 0;
}
