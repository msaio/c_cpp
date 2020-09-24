#include <stdio.h>
#include <stdlib.h>
#define MAX_STRING_LENGTH 6

struct package
{
    char* id;
    int weight;
};

typedef struct package package;

struct post_office
{
    int min_weight;
    int max_weight;
    package* packages;
    int packages_count;
};

typedef struct post_office post_office;

struct town
{
    char* name;
    post_office* offices;
    int offices_count;
};

typedef struct town town;



void print_all_packages(town t) {
    // town_name
    printf("%s:\n", t.name);    
    for(int i=0; i<t.offices_count; i++){
        // office_index
        printf("\t%d:\n", i);
        for(int j=0; j<t.offices[i].packages_count; j++){
            // package_name
            printf("\t\t%s\n", t.offices[i].packages[j].id);
        }
    }
}


int isItFit(package x, int min, int max){
    if(x.weight < min || x.weight > max) return 0;
    else return 1;
}
void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index) {
    int sizeOfSource = source->offices[source_office_index].packages_count;
    int sizeOfTarget = target->offices[target_office_index].packages_count;
    // create a truck for transfering packages
    int loadoutForTruck = 0; // first, come with 0 packages
    int truckLoad = loadoutForTruck+1; // the truck always has an empty space just in case
    package* theTruck = malloc(truckLoad*sizeof(package)); 

    int min = target->offices[target_office_index].min_weight;
    int max = target->offices[target_office_index].max_weight;
    // The strategy is:
    // Take all the packages to the truck then if some packages are not fit take them back to the stock
    int loadoutForReturn = 0;
    int backLoad = loadoutForReturn+1;
    package* backToStock = malloc(backLoad*sizeof(package));

    // go through all the packages in source
    for(int i=0; i<source->offices[source_office_index].packages_count; i++){
        // check if the package is fit then load it on the truck
        if( isItFit(source->offices[source_office_index].packages[i], min, max) == 1){
            theTruck[loadoutForTruck].id = source->offices[source_office_index].packages[i].id;
            theTruck[loadoutForTruck].weight = source->offices[source_office_index].packages[i].weight;
            loadoutForTruck++;
            truckLoad++;
            // increase the size of the truck
            theTruck = realloc(theTruck, truckLoad*sizeof(package));
            sizeOfSource--;
            sizeOfTarget++;
            
        }
        else{
            backToStock[loadoutForReturn].id = source->offices[source_office_index].packages[i].id;
            backToStock[loadoutForReturn].weight = source->offices[source_office_index].packages[i].weight;
            loadoutForReturn++;
            backLoad++;
            backToStock = realloc(backToStock, backLoad*sizeof(package));
        }
    }

    // Return the unfit packages to stock
    source->offices[source_office_index].packages = realloc(source->offices[source_office_index].packages, sizeOfSource*sizeof(package));
    for(int i=0; i<sizeOfSource; i++){
        source->offices[source_office_index].packages[i].id = backToStock[i].id;
        source->offices[source_office_index].packages[i].weight = backToStock[i].weight;
    }
    source->offices[source_office_index].packages_count = sizeOfSource;

    // The truck comes to target office
    /*printf("\n-------%d------\n", sizeOfTarget);*/
    int j=0;
    target->offices[target_office_index].packages = realloc(target->offices[target_office_index].packages, sizeOfTarget*sizeof(package));
    for(int i=target->offices[target_office_index].packages_count; i<sizeOfTarget; i++){
        target->offices[target_office_index].packages[i].id = theTruck[j].id;
        target->offices[target_office_index].packages[i].weight = theTruck[j].weight;
        j++;
    }
    target->offices[target_office_index].packages_count = sizeOfTarget;
    /*printf("\n-------%d------\n", target->offices[target_office_index].packages_count);*/
    /*for(int i=0; i<target->offices[target_office_index].packages_count; i++){*/
        /*printf("\n-------%s------\n", target->offices[target_office_index].packages[i].id);*/
    /*}*/
}

town town_with_most_packages(town* towns, int towns_count) {
    int max = 0;
    int p = 0;
    for(int i=0; i < towns_count; i++){
        int package_count = 0;
        for(int j=0; j < towns[i].offices_count; j++){
            package_count += towns[i].offices[j].packages_count;
        }
        if( package_count > max) {
            max = package_count;
            p = i;
        }
    }
    return towns[p];
}
int str_cmp(char* str1, char* str2){
    int i=0;
    while(str1[i] == str2[i]){
        if(str1[i] == '\0' || str2[2] == '\0') break;
        i++;
    }
    if(str1[i] == '\0' && str2[i] == '\0')
        return 1;
    else
        return 0;
}
town* find_town(town* towns, int towns_count, char* name) {
    for(int i=0; i<towns_count; i++){
        if(str_cmp(towns[i].name, name) == 1) return &towns[i];
    }
    return NULL;
}

int main()
{
    int towns_count;
    scanf("%d", &towns_count);
    town* towns = malloc(sizeof(town)*towns_count);
    for (int i = 0; i < towns_count; i++) {
        towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
        scanf("%s", towns[i].name);
        scanf("%d", &towns[i].offices_count);
        towns[i].offices = malloc(sizeof(post_office)*towns[i].offices_count);
        for (int j = 0; j < towns[i].offices_count; j++) {
            scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
            towns[i].offices[j].packages = malloc(sizeof(package)*towns[i].offices[j].packages_count);
            for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
                towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
                scanf("%s", towns[i].offices[j].packages[k].id);
                scanf("%d", &towns[i].offices[j].packages[k].weight);
            }
        }
    }
    int queries;
    scanf("%d", &queries);
    char town_name[MAX_STRING_LENGTH];
    while (queries--) {
        int type;
        scanf("%d", &type);
        switch (type) {
            case 1:
                scanf("%s", town_name);
                town* t = find_town(towns, towns_count, town_name);
                print_all_packages(*t);
                break;
            case 2:
                scanf("%s", town_name);
                town* source = find_town(towns, towns_count, town_name);
                int source_index;
                scanf("%d", &source_index);
                scanf("%s", town_name);
                town* target = find_town(towns, towns_count, town_name);
                int target_index;
                scanf("%d", &target_index);
                send_all_acceptable_packages(source, source_index, target, target_index);
                break;
            case 3:
                printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count).name);
                break;
        }
    }
    return 0;
}
