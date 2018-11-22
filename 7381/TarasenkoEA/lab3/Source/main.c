#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define N 1000

typedef struct Stack_El{
    	int data;
    	struct Stack_El* son;
} Stack_El;

int min(int x, int y) {
	if(x <= y)
        	return x;
    	else
        	return y;
}

int max(int x, int y) {
    	if(x >= y)
        	return x;
    	else
    		return y;
}

void push(int data, Stack_El* head, Stack_El* element) {
    	element->data = data;
    	element->son = NULL;
    	Stack_El* tmp = head;
    	while(tmp->son)
        	tmp = tmp->son;
    	if(tmp != element) tmp->son = element;
    	printf("\x1b[33mpush: %d\x1b[0m\n", data);
}

int pop(Stack_El* head) {
    	Stack_El* tmp = head;
    	Stack_El* tmp1 = NULL;
    	while(tmp->son){
        	tmp1 = tmp;
        	tmp = tmp->son;
    	}
    	int element = tmp->data;
    	if(tmp1)
        	tmp1->son = NULL;
    	printf("\x1b[33mpop: %d\x1b[0m\n", element);
    	return element;
}

int main() {
    	// initialization stuff;
    	int stack_size = -1;
    	Stack_El* stack = (Stack_El*)malloc(sizeof(Stack_El));
    	char str[N];
	printf("Please, enter the data line:\n");
    	fgets(str, N, stdin);
    	if(str[0] == '\n'){ // empty line;
        	fprintf(stderr, "\x1b[31mERROR: You entered an empty line!\x1b[0m\n");
        	free(stack);
        	return 0;
    	}
    	int i = strlen(str);
    	int count_of_brackets = 0;
    	printf("\n");
    
    	// working with the stack;
    	while(i >= 1){
        	i--;
        	if(str[i] == '('){
            	count_of_brackets++; // looking for an available error (operation name);
            	if(((i - 1) < 0) || (((i - 1) < 0) && ((str[i - 1] != 'm') || (str[i - 1] != 'M')))){
                		fprintf(stderr, "\x1b[31mERROR: Expected a name of operation before '('!\x1b[0m\n");
                		free(stack);
                		return 0;
            	}
            	continue;
        	}
        	if(str[i] == ')'){
            	count_of_brackets--;
            	continue;
        	}
        	if((str[i] == ' ') || (str[i] == ',') || (str[i] == '\t') || (str[i] == '\n') || (str[i] == '\0'))
            	continue;
        
        	if(isdigit(str[i])){ // pushing an element to the stack;
            	stack = (Stack_El*)realloc(stack, (stack_size + 2) * sizeof(Stack_El));
            	push((int)(str[i] - '0'), stack, &stack[++stack_size]);
            	continue;
        	}
        	if((str[i] == 'm') || (str[i] == 'M')){ // calling a min or max function;
		    	if(stack_size < 1){ // looking for an available error (the count of args);
				fprintf(stderr, "\x1b[31mERROR: There are 2 args should be in a function!\x1b[0m\n");
        			free(stack);
        			return 0;
			}
			
            	int x = pop(stack);
                	stack_size--;
            	int y = pop(stack);
                	stack_size--;
            
            	if(str[i] == 'm'){
                		stack = (Stack_El*)realloc(stack, (stack_size + 2) * sizeof(Stack_El));
				push(min(x, y), stack, &stack[++stack_size]);
            	}
			if(str[i] == 'M'){
			    	stack = (Stack_El*)realloc(stack, (stack_size + 2) * sizeof(Stack_El));
				push(max(x, y), stack, &stack[++stack_size]);
			}
            	continue;
        	}
        
        	fprintf(stderr, "\x1b[31mERROR: Unexpected symbol %c!\x1b[0m\n", str[i]);
        	free(stack);
        	return 0;
    	}
    
    	// construction error;
    	if(count_of_brackets != 0){
        	fprintf(stderr, "\x1b[31mERROR: Counts of symbols '(' and ')' aren't equal!\x1b[0m\n");
        	free(stack);
        	return 0;
    	}
 	if(stack_size != 0){ // looking for an available error (the count of args);
		fprintf(stderr, "\x1b[31mERROR: There are 2 args should be in a function!\x1b[0m\n");
        	free(stack);
        	return 0;
	}
    
    	// print a result;
    	printf("\n\x1b[32mResult: %d\x1b[0m\n", pop(stack));
    	free(stack);
    	return 0;
}