#define MAX_ID 1024

typedef struct TAG_SYMBOL_ENTRY
{
	string name;
	int token;
	int type;
} symbol_entry;

class symbol_table
{
private:
	symbol_entry table[MAX_ID];
	int size;

public:
	int lookup(string name);
	int insert(string name, int token);
	int gettoken(string name);
	string &getname(int pos);
	int set_type(int pos, int type);
	int get_type(int pos);
};
