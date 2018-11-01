#include <stdio.h>
#include <stdlib.h>
#define YES 1
#define NO 0

typedef struct Atom {
    	char value;
    	int level;
    	struct Atom* son;
    	struct Atom* brother;
} Atom;

void create_atom(Atom* atom, char value, int level){
	atom->value = value;
	atom->level = level;
	atom->son = NULL;
	atom->brother = NULL;
}

void print_list(Atom* list, int is_son){
	if(is_son == YES) printf("\x1b[32m(\x1b[0m");
	if(list->value)
		printf("\x1b[32m%c\x1b[0m", list->value);
	// recursive printing;
	if(list->son)
		print_list(list->son, YES);
	if(list->brother)
		print_list(list->brother, NO);

	if(is_son == YES) printf("\x1b[32m)\x1b[0m");
}

void change_atom(Atom* list, char x, char y){
    	// change the atom;
    	if(list->value == x) list->value = y;
    	// recursion;
    	if(list->son)
        	change_atom(list->son, x, y);
    	if(list->brother)
        	change_atom(list->brother, x, y);
}

void push(Atom* list, int level, char value, int i){
    	Atom* tmp = list;
	create_atom(&list[i - 1], value, level);
	Atom* element = &list[i - 1];

	while(((tmp->son) && (tmp->level != level)) || (tmp->brother)){
		if(tmp->brother){
        		tmp = tmp->brother;
			continue;
    		}
    		if((tmp->son) && (tmp->level != level)){
        		tmp = tmp->son;
			continue;
    		}
	}
    	if(i != 1){
        	if((tmp->level) != (element->level)){
			tmp->son = element;
			printf("\x1b[33m'%c' is a son of '%c';\x1b[0m\n", value, tmp->value);
		}
        	else{
			tmp->brother = element;
			printf("\x1b[33m'%c' is a brother of '%c';\x1b[0m\n", value, tmp->value);
		}
    	}
	else
		printf("\x1b[33m'%c' is a head of the list;\x1b[0m\n", value);
}

int main(){
    	//initialization;
    	printf("Please, enter list members. Ex.: (a(bc)d).\n");
    	char c, x, y;
    	int level = 0, i = 1;
    	Atom* list = (Atom*)malloc(i * sizeof(Atom));
    
    	// create a head of the list;
	create_atom(&list[0], 0, 1);
    
    	// entering the data;
    	while((c = getchar()) != '\n'){
		if(c == ' ')
			continue;
        	if(c == '('){
            		level++;
            		continue;
        	}
        	if(c == ')'){
            		level--;
            		continue;
        	}
		list = (Atom*)realloc(list, i * sizeof(Atom));
		if(level > 0){
        		push(list, level, c, i);
        		i++;
		}
		else{
			fprintf(stderr, "\x1b[31mThe symbol '(' was expected!\x1b[0m\n"); 
			free(list);
			return 0;
		}
    	}

	// list errors;
	if(level != 0){
		fprintf(stderr, "\x1b[31mCounts of characters '(' and ')' is not equal!\x1b[0m\n"); 
		free(list);
		return 0; 
	}
	if(list[0].value == 0){
		fprintf(stderr, "\x1b[31mThe list is empty!\x1b[0m\n");
		free(list);
		return 0;
	}

    	// a problem solution;
    	printf("Enter an element, which we should change: ");
    	scanf("%c", &x);
	getchar();
    	printf("Enter a new element: ");
    	scanf("%c", &y);
    	if(list->value)
		change_atom(list, x, y);
	printf("\x1b[32mResult: \x1b[0m");
	print_list(list, YES);
	printf("\n\x1b[32mFinish!\x1b[0m\n");
    
    	//free memory;
    	free(list);
    	return 0;
}