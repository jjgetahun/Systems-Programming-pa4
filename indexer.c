#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include "tokenizer.h"
#include "sorted-list.h"

typedef struct dirent * dirent;
typedef struct stat stat_;

int compareString(char* s1, char* s2) {
    return strcmp(s1, s2);
}

void findDirs(DIR * dir, dirent entry, char * str, SortedListPtr root) {

    stat_ sb;

    while ((entry = readdir(dir)) != 0) {
        char * name = entry->d_name;
        if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
            continue;
        char * s =(char *) malloc(strlen(str)+strlen(name)+2);
        strcpy(s, str);
        strcat(s, "/");
        strcat(s, name);
        stat(s, &sb);

        if (S_ISREG(sb.st_mode)) {
            printf("FILE: %s\n", name);
            char * str = tokenize(s);
            if (str == NULL) {
                continue;
            }
            char * token = strtok(str, " ");
            if (strcmp(token,"hello") == 0)
                printf(" ");
            while (token != NULL) {
                //printf("%s\n", token);
                SLInsertWord(root,token,s);
                token = strtok(NULL, " ");
            }
            free(str);
            token = NULL;
        }
        else if (S_ISDIR(sb.st_mode)) {
            DIR * newDir = opendir(s);
            dirent newEntry;
            printf("DIR: %s\n", name);
            findDirs(newDir, newEntry, s, root);
            closedir(newDir);
        }
        free(s);
        s = NULL;
    }
}

int main (int argc, char ** argv) {
    DIR * dir;
    dirent entry;
    extern int errno;
    stat_ sb;

    SortedListPtr root = SLCreate(compareString);

    if (argc != 2) { /*If there are not two arguments*/
        fprintf(stderr, "You must specify a single file or directory name on the command line.\n");
        return 1;
    }
    else { /*If there are two arguments*/
        stat(argv[1], &sb);
        if (!S_ISREG(sb.st_mode) && !S_ISDIR(sb.st_mode)) { /*If the argument is not a file nor a directory*/
            fprintf(stderr, "Could not open \"%s\" as a file or directory.\n", argv[1]);
            return 1;
        }
        else {
            if (S_ISREG(sb.st_mode)) { /*If the argument is a file*/
                printf("FILE: %s\n", argv[1]);
                char * str = tokenize(argv[1]);
                char * token = strtok(str, " ");
                while (token != NULL) {
                    //printf("%s\n", token);
                    SLInsertWord(root,token,argv[1]);
                    token = strtok(NULL, " ");
                }
                free(str);
                printList(root);
                cleanList(root);
                return 0;
            }
            if (S_ISDIR(sb.st_mode)) { /*If the argument is a directory*/
                dir = opendir(argv[1]);
                printf("DIR: %s\n", argv[1]);
                findDirs(dir, entry, argv[1], root);
                closedir(dir);
            }
        }
    }
    printList(root);
    cleanList(root);
    return 0;
}
