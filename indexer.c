#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include "tokenizer.h"

int main (int argc, char ** argv) {

    DIR * dir;
    typedef struct dirent * dirent;
    dirent entry;
    extern int errno;
    dir = opendir(argv[1]);

    if (argc < 2) {
        fprintf(stderr, "Must specify directory name on command line.\n");
        return 1;
    }
    else if (dir == 0) {
        fprintf(stderr, "Could not open %s as directory: %s.\n", argv[1], strerror(errno));
        return 1;
    }
    else {
        printf("Begin directory info list.\n");
        entry = readdir(dir);
        while (entry != 0) {
            printf("d_ino %d, d_off %d, d_reclen %d, d_name %s.\n", entry->d_ino, entry->d_off, entry->d_reclen, entry->d_name);
            printf("%s.\n", entry->d_name);
        }
        closedir(dir);
    }
    return 0;
}
