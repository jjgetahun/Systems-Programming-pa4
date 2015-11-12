#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>
#include "tokenizer.h"
#include "avl.h"

typedef struct dirent * dirent;
typedef struct stat stat_;

node * root = NULL;
//node * m = NULL;
//node * n;

int compareString(char* s1, char* s2) {
    return strcmp(s1, s2);
}

//node * n = NULL;

void findDirs(DIR * dir, dirent entry, char * str, node * n) {
    n = root;
    //node *n = NULL;
    stat_ sb;

    //m = n;

        while ((entry = readdir(dir)) != 0) {
            //n = root;
            char * name = entry->d_name;

            if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
                continue;

            char * s =(char *) malloc(strlen(str)+strlen(name)+2);

            strcpy(s, str);
            strcat(s, "/");
            strcat(s, name);

            stat(s, &sb);

            if (S_ISREG(sb.st_mode)) {
                //printf("FILE: %s\n", name);
                char * str = tokenize(s);
                char * token = strtok(str, " ");

                //node * n = NULL;
                
                while (token != NULL) {
                    n = insert(token,/* s,*/ n);
                    //printf("%s\n", n->name);
                    //printf("%s\n", token);
                    token = strtok(NULL, " ");
                }
                //print(n);
                free(str);
                //return n;
            }

            else if (S_ISDIR(sb.st_mode)) {
                DIR * newDir = opendir(s);
                dirent newEntry;
                //printf("DIR: %s\n", name);
                //n = root;
                findDirs(newDir, newEntry, s, n);
                closedir(newDir);
                //return n;
            }
            free(s);
            s = NULL;
            //return n;
        }
        if (n != NULL)
            root = n;
        //return n;
        //print(n);
}

int main (int argc, char ** argv) {
        DIR * dir;
        dirent entry;
        extern int errno;

        stat_ sb;
        node * n = NULL;

        if (argc != 2) { /*If there are not two arguments*/
            fprintf(stderr, "You must specify a single file or directory name on the command line.\n");
            return 1;
        }

        else { /*If there are two arguments*/
            //while ((entry = readdir(dir)) != 0) {
            stat(argv[1], &sb);

            if (!S_ISREG(sb.st_mode) && !S_ISDIR(sb.st_mode)) { /*If the argument is not a file nor a directory*/
                fprintf(stderr, "Could not open \"%s\" as a file or directory.\n", argv[1]);
                return 1;
            }

            else {

                if (S_ISREG(sb.st_mode)) { /*If the argument is a file*/
                    //printf("FILE: %s\n", argv[1]);
                    char * filename = argv[1];
                    char * str = tokenize(argv[1]);
                    char * token = strtok(str, " ");

                    //node * root = NULL; 
                    //root = insert(token, filename, root);

                    //node * n = NULL;

                    while (token != NULL) {
                        n = insert(token,/* filename,*/ n);
                        //printf("%s\n", n->name);
                        //printf("%s\n", token);
                        token = strtok(NULL, " ");
                    }
                    //print(root);
                    print(n);
                    free(str);
                    return 0;
                }

                if (S_ISDIR(sb.st_mode)) { /*If the argument is a directory*/
                    dir = opendir(argv[1]);
                    findDirs(dir, entry, argv[1], n);
                    //printf("DIR: %s\n", argv[1]);
                    //m = (node *)malloc(sizeof(n));
                    //m = findDirs(dir, entry, argv[1], n);
                    //node * p = (node *)malloc(sizeof(m));
                    closedir(dir);
                    //printf("%s\n", p->name);
                    //print(n);
                }
            }
        //}
        }
        //printf("%s\n", n->name);
        //printf("%d\n", n->height);
        //print(n);
        print(root);
        //printf("%s\n", root->name);
        return 0;
}
