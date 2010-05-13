/*
		if (this->isDirectory = S_ISDIR(filestats.st_mode)){
			DIR * dir;
			if (!(dir = opendir(path))){
				cantopen(path);
			}
			struct dirent *dp;
			struct stat tempstat;
			this->size = 0;
			while(dp = readdir(dir)){
				stat(dp->d_name, &tempstat);
				if (strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")){
					this->size ++;
				}
			}
			closedir(dir);
		}
*/

#include "fsmodel.h"

#ifdef FSMODEL_DEBUG

#include <cstdlib>

int main(int argc, char **argv){
	FSModel mymodel;
	return EXIT_SUCCESS;
}
#endif
