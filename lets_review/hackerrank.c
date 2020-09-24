#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define MAX_LIMIT 10000
int main() {
	// Enter number of words
	int n;
	scanf("%d", &n);
	char* words[n];
	// Get the input
	for(int i=0; i<n; i++){
		words[i] = malloc(MAX_LIMIT);
		scanf("%s", words[i]);
	}
	// Show to screen
	for(int i=0; i<n; i++){
		for(int j=0; j<strlen(words[i]); j+=2){
			printf("%c", words[i][j]);
		}
		printf(" ");
		for(int j=1; j<strlen(words[i]); j+=2){
			printf("%c", words[i][j]);
		}
		printf("\n");
	}
	return 0;
}

