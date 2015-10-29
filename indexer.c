#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include "tokenizer.h"

typedef struct dirent * dirent;

void findDirs(DIR * dir, dirent entry) {

    while ((entry = readdir(dir)) != 0) {
	if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
	    continue;
	}
	printf("d_ino %d, d_off %d, d_reclen %d, d_name %s\n", entry->d_ino, entry->d_off, entry->d_reclen, entry->d_name);
	printf("%s\n", entry->d_name);
    }

}

int main (int argc, char ** argv) {
    
    DIR * dir;
    dirent entry;
    extern int errno;
    FILE * file;

    if (argc != 2) {
        fprintf(stderr, "You must specify a single file or directory name on the command line.\n");
        return 1;
    }
    if ((file = fopen(argv[1], "r")) == NULL && (dir = opendir(argv[1])) == 0) {
    	fprintf(stderr, "Could not open %s as file or directory: %s.\n", argv[1], strerror(errno));
	return 1;
    }
    else {
    	if ((file = fopen(argv[1], "r")) != NULL) {
	tokenize(file);
	}
	if ((dir = opendir(argv[1])) != 0) {
	findDirs(dir, entry);
	closedir(dir);
	}
    }
    return 0;
}
