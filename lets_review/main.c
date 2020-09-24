#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define MAX_LIMIT 10000
int main() {
	// Enter number of words
	int n;
	scanf("%d", &n);
	// Allocate memory
	char* words[n];
	for (int i = 0; i < n; ++i) {
		words[i] = malloc(0);
	}
	// Get the input
	char* temp = malloc(MAX_LIMIT);
	for(int i=0; i<n; i++){
		scanf("%s", temp);
		strcpy(words[i], temp);
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

