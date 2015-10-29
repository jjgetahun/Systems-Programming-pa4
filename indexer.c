#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include "tokenizer.h"

int main (int argc, char ** argv) {

    DIR * dir;
    //typedef struct dirent * dire;
    //dire entry;
    struct dirent * entry;
    extern int errno;

    if (argc < 2) {
        fprintf(stderr, "Must specify directory name on command line.\n");
        return 1;
    }
    dir = opendir(argv[1]);
    if (dir == NULL) {
        fprintf(stderr, "Could not open %s as directory: %s.\n", argv[1], strerror(errno));
        return 1;
    }
    else {
        printf("Begin directory info list.\n");
        entry = readdir(dir);
        while (entry != NULL) {
           // if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
	   // continue;
	   // }
	    printf("d_ino %d, d_off %d, d_reclen %d, d_name %s.\n", entry->d_ino, entry->d_off, entry->d_reclen, entry->d_name);
            printf("%s.\n", entry->d_name);
        }
        closedir(dir);
    }
    return 0;
}
