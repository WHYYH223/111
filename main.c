#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int countWords(const char *text);
int countChars(const char *text);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s -c|-w input_file_name\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[2], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *text = (char *)malloc(fileSize + 1);
    fread(text, 1, fileSize, file);
    text[fileSize] = '\0'; 

    if (strcmp(argv[1], "-c") == 0) {
        printf("字符数：%d\n", countChars(text));
    } else if (strcmp(argv[1], "-w") == 0) {
        printf("单词数：%d\n", countWords(text));
    } else {
        printf("无效的参数\n");
        free(text);
        fclose(file);
        return 1;
    }
    free(text);
    fclose(file);
    return 0;
}
int countWords(const char *text) {
    int count = 0;
    int inWord = 0;
    while (*text) {
        if (isspace(*text) || *text == ',' || *text == '\n') {
            inWord = 0;
        } else if (!inWord) {
            inWord = 1;
            count++;
        }
        text++;
    }
    return count;
}
int countChars(const char *text) {
    int count = 0;
    while (*text) {
        count++;
        text++;
    }
    return count;
}
