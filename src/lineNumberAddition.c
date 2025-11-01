#include <stdio.h>

void addLineNumbers(const char *inputFilePath, const char *outputFilePath) {
    FILE *inputFile = fopen(inputFilePath, "r");
    if(inputFile == NULL) {
        perror("Error opening input file");

        return;
    }

    FILE *outputFile = fopen(outputFilePath, "w");
    if(outputFile == NULL){
        perror("Error opening output file");
        return;

    }

    char buffer[1024];

    int lineNumber = 1;  
    while(fgets(buffer, sizeof(buffer), inputFile) != NULL) {
        fprintf(outputFile, "%4d: %s", lineNumber++, buffer);

    }

    fclose(inputFile);
    fclose(outputFile);

}

int main() {
    const char *inputFilePath = "/Users/amanojhaa/Documents/Projects/CAdvanced/Module2/src/lineNumberAddition.c";
    const char *outputFilePath = "/Users/amanojhaa/Documents/Projects/CAdvanced/Module2/output/styledLineNumberAddition.c";

    addLineNumbers(inputFilePath, outputFilePath);

    return 0;
}