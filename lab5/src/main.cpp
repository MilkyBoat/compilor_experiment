#include "common.h"
#include <fstream>

extern TreeNode *root;
extern FILE *yyin;
extern int yyparse();

using namespace std;
int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        FILE *fin = fopen(argv[1], "r");
        if (fin != nullptr)
        {
            yyin = fin;
        }
        else
        {
            cerr << "failed to open file: " << argv[1] << endl;
        }
    }
    yyparse();
    if(root != NULL) {
        root->genNodeId();
        root->printAST();
    }
    return 0;
}