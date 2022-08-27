/**
 * Description: This module counts for all the names in
 * two files(one per line) how many times each name appears.
 * Author names: Shu Sian (Jessie) Lyu
 * Author email: shusian.lyu@sjsu.edu
 * Last modified date:
 * Creation date: Aug 26, 2022
 */
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    char buffer[50];              // variable to hold string in the file
    char nameArr[100][50];        // distinct name Array
    int nameCount[100];           // distinct name count array

    // open file
    FILE *fp = fopen(argv[1], "r");
    if(fp == NULL){
        perror("cannot open file.gg\n");
        return(-1);
    }

    int countLines = 0;              // variable to count lines in the file
    int countDistinctNames = 0;      // variable to count the number of distinct names
    const int NAMES = 1;             // constant starting value of distinct name count

    fgets(buffer, 50, fp);           // read first line in the file
    if(strlen(buffer) != 1){
        // check if the first line was empty
        strcpy(nameArr[countDistinctNames],buffer);   // copy first line into name array
        nameCount[countDistinctNames] = NAMES;            // assign the occurrence of name to 1
        countLines += 1;                              // count the lines in the file
        countDistinctNames += 1;                      // count the distinct names
    }else{
        // if the line was empty, print the warning message to stderr
        fprintf(stderr, "Warning - Line %d is empty.\n", countLines);
    }

    int found;   // variable to check if the name was found in the nameArr

    // while loop to read through the file
    while(fgets(buffer, 50, fp) != NULL){
        countLines += 1;
        found = 0;
        if(strlen(buffer) == 1){
            // check if the line was empty
            fprintf(stderr, "Warning - Line %d is empty.\n", countLines);
        }else{
            for(int i = countDistinctNames - 1; i >= 0; i--){
                // for loop to check if the name was found in the nameArr
                if(strcmp(buffer, nameArr[i]) == 0){
                    nameCount[i] += 1;      // increment the count of the name
                    found = 1;              // assign the found to 1
                    break;                  // break the for loop once the name was found
                }
            }
            if(found != 1){
                // if the name was not found in the nameArr,
                // copy the name to the nameArr, and increment the distinct name counts
                strcpy(nameArr[countDistinctNames],buffer);
                nameCount[countDistinctNames] = NAMES;
                countDistinctNames += 1;
            }
        }
    }

    int lengthOfString;      // variable to hold length of each line
    for(int i = 0; i < countDistinctNames; i++){
        lengthOfString = strlen(nameArr[i]);
        nameArr[i][lengthOfString-1] = '\0';      // replace the newline
        printf("%s: %d\n", nameArr[i], nameCount[i]);
    }

    fclose(fp);

    return 0;
}