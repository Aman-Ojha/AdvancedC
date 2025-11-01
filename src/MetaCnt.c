#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


int countLines(FILE *file) {
    int lineCount = 0;
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        lineCount++;
    }
    
    return lineCount;
}

FILE* readFile(const char *filePath) {
    if (filePath == NULL) {
        fprintf(stderr, "readFile: filePath is NULL\n");
        return NULL;
    }

    struct stat st;
    if (stat(filePath, &st) != 0) {
        fprintf(stderr, "readFile: cannot stat '%s': %s\n", filePath, strerror(errno));
        return NULL;
    }

    if (!S_ISREG(st.st_mode)) {
        fprintf(stderr, "readFile: '%s' is not a regular file\n", filePath);
        return NULL;
    }

    if (access(filePath, R_OK) != 0) {
        fprintf(stderr, "readFile: file '%s' is not readable: %s\n", filePath, strerror(errno));
        return NULL;
    }


    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        fprintf(stderr, "readFile: fopen('%s') failed: %s\n", filePath, strerror(errno));
        return NULL;
    }
    return file;
}

int countCharacters(FILE *file) {
    int charCount = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF) {
        charCount++;
    }

    return charCount;
}

int countWhitespace(FILE *file) {
    int whitespaceCount = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == 32 || ch == 9 || ch == 10|| ch == 13 || ch == 11 || ch == 12) {
            whitespaceCount++;
        }
    }
    return whitespaceCount;
}

int main(int argc, char *argv[]) {
    const char *filePath = "/Users/amanojhaa/Documents/Projects/CAdvanced/Module2/src/lineNumberAddition.c";
    FILE* file = readFile(filePath);

    int lines = countLines(file);
    if (lines >= 0) {
        printf("File '%s' has %d lines.\n", filePath, lines);
    }
    if (file != NULL) {
        rewind(file);
    } else {
        fprintf(stderr, "Cannot reset file position: file is NULL\n");
    }

    int characters = countCharacters(file);
    if(characters >= 0) {
        printf("File '%s' has %d characters.\n", filePath, characters);
    }

    if (file != NULL) {
        rewind(file);
    } else {
        fprintf(stderr, "Cannot reset file position: file is NULL\n");
    }

    int whitespace = countWhitespace(file);
    if(whitespace >= 0) {
        printf("File '%s' has %d whitespace characters.\n", filePath, whitespace);
    }
    
    return 0;
}