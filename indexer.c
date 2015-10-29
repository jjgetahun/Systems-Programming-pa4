#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>
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
    FILE * file;
    DIR * dir;
    dirent entry;
    extern int errno;
struct stat sb;

    if (argc != 2) { /*If there are not two arguments*/
        fprintf(stderr, "You must specify a single file or directory name on the command line.\n");
        return 1;
    }
else {
stat(argv[1], &sb);
    if (/*(file = fopen(argv[1], "r")) == NULL && (dir = opendir(argv[1])) == 0*/!S_ISREG(sb.st_mode) && !S_ISDIR(sb.st_mode)) { /*If the argument is not a file nor a directory*/
    	fprintf(stderr, "Could not open \"%s\" as a file or directory.\n", argv[1]);
        return 1;
    }
    else {
    	if (/*(file = fopen(argv[1], "r")) != NULL*/S_ISREG(sb.st_mode)) { /*If the argument is a file*/
printf("%d\n", errno);
file = fopen(argv[1], "r");
            tokenize(file);
	    fclose(file);
        }
        if (/*(dir = opendir(argv[1])) != 0*/S_ISDIR(sb.st_mode)) { /*If the argument is a directory*/
dir = opendir(argv[1]);
            findDirs(dir, entry);
            closedir(dir);
        }
    }
}
    return 0;
}
