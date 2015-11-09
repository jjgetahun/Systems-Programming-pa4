#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>
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
            char * str = tokenize(s);
            if (str == NULL) {
                free(s);
                s = NULL;
                continue;
            }
            char * token = strtok(str, " ");
            while (token != NULL) {
                SLInsertWord(root,token,s);
                token = strtok(NULL, " ");
            }
            free(str);
            token = NULL;
        }
        else if (S_ISDIR(sb.st_mode)) {
            DIR * newDir = opendir(s);
            dirent newEntry;
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

    FILE * file;

    SortedListPtr root = SLCreate(compareString);

    if (argc != 3) { /*If there are not three arguments*/
        fprintf(stderr, "You must give a file to be written to, and specify a single file or directory name on the command line.\n");
        return 1;
    }
    else { /*If there are three arguments*/

        file = fopen(argv[1], "w");
        stat(argv[1], &sb);
        if (!S_ISREG(sb.st_mode)) { /*If the second argument is not a file*/
            fprintf(stderr, "\"%s\"is not a file.\n", argv[1]);
            fclose(file);
            return 1;
        }
        int check = stat(argv[2], &sb);
        if ((!S_ISREG(sb.st_mode) && !S_ISDIR(sb.st_mode)) || check == -1) { /*If the argument is not a file nor a directory*/
            fprintf(stderr, "Could not open \"%s\" as a file or directory.\n", argv[2]);
            fclose(file);
            return 1;
        }
        else {
            if (S_ISREG(sb.st_mode)) { /*If the argument is a file*/
                fprintf(file, "{\"list\" : [\n");
                char * str = tokenize(argv[2]);
                char * token = strtok(str, " ");
                while (token != NULL) {
                    SLInsertWord(root,token,argv[1]);
                    token = strtok(NULL, " ");
                }
                free(str);
                printList(root, file);
                cleanList(root);
                fprintf(file, "]}\n");
                fclose(file);
                return 0;
            }
            if (S_ISDIR(sb.st_mode)) { /*If the argument is a directory*/
                fprintf(file, "{\"list\" : [\n");
                dir = opendir(argv[2]);
                findDirs(dir, entry, argv[2], root);
                closedir(dir);
            }
        }
    }
    printList(root, file);
    cleanList(root);
    fprintf(file, "]}\n");
    fclose(file);
    return 0;
}
