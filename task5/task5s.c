#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>

#define MAXPATH 256


void print_permissions(mode_t mode) {
    printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

int list_dir(char * dir, int rec)
{
	DIR * dirp;
	char path[MAXPATH];
	struct dirent * direntp;
	struct stat st;
	

	if ((dirp = opendir(dir)) == NULL) {
		perror(dir);
		return -1;
	}
	printf("Directory: %s\n", dir);

	while ((direntp = readdir(dirp)) != NULL) {
	
		if (strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0) {
			continue;
		}

		if (snprintf(path, MAXPATH, "%s/%s", dir, direntp->d_name) >= MAXPATH) {
            fprintf(stderr, "Path length exceeds maximum allowed length: %s/%s\n", dir, direntp->d_name);
            continue;
        }
		if (stat(path, &st) == -1) {
            perror(path);
            continue;
        }

		// Print the file information
		printf("%*s%s\n", rec * 2, "", direntp->d_name);
		printf("  Links: %ld\n", st.st_nlink);
		printf("  Size: %ld bytes\n", st.st_size);
		printf("  Permissions: ");
		print_permissions(st.st_mode);
		printf("\n  Last modified: %s\n", ctime(&st.st_mtime)); 

		// Recursively list subdirectories if rec > 0
		if (rec > 0 && S_ISDIR(st.st_mode)) {
			list_dir(path, rec - 1);
		}
    
	}

	if (closedir(dirp) == -1) {
		perror(dir);
		return -1;
	}
	
	return 0;
}

int main(int argc, char * * argv)
{
	int i = 1, rec = 0;

    if (argc > 1) {
        if (argc > 2 && strcmp(argv[1], "-r") == 0) {
            rec = atoi(argv[2]);
            i = 3;
        }

        while (i < argc) {
            if (list_dir(argv[i], rec) == -1) exit(1);
            i++;
        }
    } else {
        printf("Usage: %s [-r rec] <dir1> <dir2> ... <dirN>\n", argv[0]);
    }

    return 0;
}
