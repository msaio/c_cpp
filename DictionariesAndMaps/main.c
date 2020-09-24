#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include<math.h>

#define nameLM 50
#define phoneLM 8
#define max pow(10,5)

// define the dictionary struct
struct dict {
    char* name;
    char* phone;
};
typedef struct dict dict;


int main() {

    // Get number of entries in the phone book.
    int n;
    scanf("%d\n", &n);

    // Create a phonebook size n
    dict* phonebook = (dict*)malloc(n*sizeof(dict));
    

    char input[n][nameLM + phoneLM + 1];
    // Get raw input
    for(int i=0; i<n; i++){
        scanf("%[^\n]%*c", input[i]);
    }
    // From raw to phonebook
    for(int i=0; i<n; i++){
        char* temp1;
        char* temp2;

        temp1 = strtok(input[i], " ");
        temp2 = strtok(NULL, " ");
        
        phonebook[i].name = malloc((int)strlen(temp1)*sizeof(char));
        phonebook[i].phone = malloc((int)strlen(temp2)*sizeof(char));

        strcpy(phonebook[i].name, temp1);
        strcpy(phonebook[i].phone, temp2);
    }

    // Get queries
    char query[nameLM];
    int noQueries = 0;

    char** listOfQueries = malloc((noQueries+1) * sizeof(char*));

    fgets(query, sizeof query, stdin);
    while(query[0]!='\n' && noQueries < max)
    {
        listOfQueries[noQueries] = malloc((int)strlen(query) * sizeof(char));
        strcpy(listOfQueries[noQueries], query);
        noQueries++;
        listOfQueries = realloc(listOfQueries, (noQueries+1) * sizeof(char*));
        fgets(query, sizeof query, stdin);
    }
    // Remove '\n' from every query
    for(int i=0; i < noQueries; i++){
        strtok(listOfQueries[i], "\n");
        // printf("%s", listOfQueries[i]);
    }

    int* result = calloc(n, sizeof(int));
    // Search
    for(int i=0; i < noQueries; i++){
        for(int j=0; j < n; j++){
            if(strcmp(phonebook[j].name, listOfQueries[i]) == 0){           
                result[j]++; 
                break;
            }
        }
    }
    // for(int i=0; i<n; i++){
    //     printf("%d ", result[i]);
    // }

    for (int i = 0; i < n; i++)
    {
        if(result[i] != 0){
            printf("%s=%s\n", phonebook[i].name, phonebook[i].phone);
        }
        else {
            printf("Not found\n");
        }
    }
    
    return 0;
}
