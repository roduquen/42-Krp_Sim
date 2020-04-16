#include <cstdlib>
#include <fstream>
#include <vector>
#include <iostream>
#include <string.h>
using namespace std;

#define OBJ_NAME	0 // Name of object
#define OBJ_POSD	1 // Number of object possesed
#define	OBJ_COST	2 // Cost of an object

#define START		0
#define NUMBER		1
#define LETTER		2
#define SPACE		3
#define ENDLINE		4
#define HASHTAG		5
#define	DOUBLE_PT	6
#define SEMI_COL	7
#define ENTRANCE	8
#define OUTRANCE	9

typedef struct		Obj {
	char	*name;
	int		code;
	long	quantity;
}					Obj;

typedef struct		Process {
	char		*name;
	int			code;
	vector<Obj>	cost;
	vector<Obj>	gain;
}					Process;

typedef struct		NameIndex {
	char		*name;
	int			code;
}					NameIndex;

class Lexer {
	public:
		char	*buffer = nullptr;
		int		length;
		bool	err;
		vector<int> *lexem = new vector<int>;

		// Constructor
		Lexer(string path) {
			ifstream file(path, ifstream::binary);
			if (!file) {
				cout << "File cannot be loaded" << endl;
			}
			else {
				file.seekg(0, file.end);
				length = file.tellg();
				file.seekg(0, file.beg);
				buffer = new char [length];
				file.read(buffer, length);
				if (!file) {
					err = true;
				}
				else {
					err = create_lexem();
				}
				file.close();
			}
		}

		// Destructor
		~Lexer() {
			delete lexem;
			if (buffer) {
				delete buffer;
			}
		}

	private:
		bool create_lexem() {
			int state = START;
			int	inside = false;
			for (int i = 0; i < length; ++i) {
				if (state == HASHTAG) {
					if (buffer[i] == '\n') {
						lexem->push_back(ENDLINE);
						state = ENDLINE;
					}
					else {
						lexem->push_back(HASHTAG);
					}
				}
				else {
					if (buffer[i] == '#') {
						lexem->push_back(HASHTAG);
						state = HASHTAG;
					}
					else if (isdigit(buffer[i])) {
						lexem->push_back(NUMBER);
						state = NUMBER;
					}
					else if (buffer[i] == '\n') {
						lexem->push_back(ENDLINE);
						state = ENDLINE;
					}
					else if (isspace(buffer[i])) {
						return (true);
					}
					else if (buffer[i] == ':') {
						lexem->push_back(DOUBLE_PT);
						state = DOUBLE_PT;
					}
					else if (buffer[i] == ';') {
						if (inside == false || state == DOUBLE_PT)
							return (true);
						lexem->push_back(SEMI_COL);
						state = SEMI_COL;
					}
					else if (buffer[i] == '(') {
						if (inside == true || state != DOUBLE_PT) {
							return (true);
						}
						lexem->push_back(ENTRANCE);
						state = ENTRANCE;
						inside = true;
					}
					else if (buffer[i] == ')') {
						if (inside == false || state == DOUBLE_PT || state == SEMI_COL) {
							return (true);
						}
						lexem->push_back(OUTRANCE);
						state = OUTRANCE;
						inside = false;
					}
					else if (isalpha(buffer[i])) {
						lexem->push_back(LETTER);
						state = LETTER;
					}
					else {
						return (true);
					}
				}
			}
			return (inside);
		}

		bool parse_file(Lexer *lexer) {
			char	*test;
			int		characters;
			int		i = 0;
			int		col;
			int		row;
			int		max;
			vector<NameIndex> *names = new vector<NameIndex>;
			vector<Process> *process = new vector<Process>;
			vector<Obj> *objects = new vector<Obj>;

			while (i < lexer->length) {
			}
		}
};
