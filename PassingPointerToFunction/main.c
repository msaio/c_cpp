#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// INT
void create(int **x, int size){
	*x = (int*)malloc(size * sizeof(int));
	for(int i=0; i<size; i++){
		*(*x+i) = i;
	}
}
void show(int *x, int size){
	for(int i=0; i<size; i++){
		printf("%d ", x[i]);
	}
}
/*Using void => Using pointer to pointer*/
void expand(int **x, int new_size){
	*x = (int*)realloc(*x, new_size * sizeof(int));
	for(int i=0; i<new_size; i++){
		*(*x+i) = i;
	}
}
/*If not using pointer to pointer*/
/*MUST return a pointer*/
int* expand_5(int *x, int *size){
	(*size) += 5;
	x = realloc(x, (*size)*sizeof(int));

	for(int i=0; i<(*size); i++){
		x[i] = i;
	}
	return x;
}

// CHAR
void char_create(char** c, int size){
	*c = (char*)malloc(size*sizeof(char));
	for(int i=0; i<size; i++){
		*(*c+i) = i+65;
	}
}

void char_show(char *c){
	for(int i=0; i<strlen(c); i++){
		printf("%c ", c[i]);
	}
	printf("\n");
}

void char_expand(char** c, int new_size){
	*c = (char*)realloc(*c, new_size * sizeof(char));
	for(int i=0; i<new_size; i++){
		*(*c+i) = i+65;
	}
}

void add_char(char** w, char c){
	int len = strlen(*w);
	*w = (char*)realloc(*w, (len+1)*sizeof(char));
	*(*w+len) = c;
}
int main()
{
	// INT
	int *x;
	create(&x, 10);
	show(x, 10);
	printf("\n");
	expand(&x, 15);
	show(x, 15);
	printf("\n");
	int size = 10;
	x = expand_5(x, &size);
	show(x, size);

	// CHAR
	char *c;
	char_create(&c, 10);
	char_show(c);
	char_expand(&c, 15);
	char_show(c);
	add_char(&c, 'Z');
	char_show(c);

	return 0;
}
