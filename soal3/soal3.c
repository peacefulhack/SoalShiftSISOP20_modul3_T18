#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>


static void move_file(const char *filename);
static void mk_directory(const char *dirname);


int main(int argc, char *argv[])
{
   
	char *tok = NULL;
    char type[80] = {0};

    if(strcmp(argv[1], "-f")==0)
    {
        for(int i = 2;i<argc;i++)//start with first arg 
        {
            // categorise here
            move_file(argv[i]);
        }
    }

    // jika */

    else if(strcmp(argv[1], "/*")==0)
    {
        DIR *d;
        struct dirent *dir;
        d = opendir(".");
        if (d) 
        {

         while ((dir = readdir(d)) != NULL) 
         {
            move_file(dir->d_name);
         }

         closedir(d);
        }

     }

    return 0;

}



static void move_file(const char *filename)
{

    char *dot = strrchr(filename, '.');
    
    mk_directory(dot + 1);

    size_t namelen = strlen(dot + 1) + strlen(filename) + sizeof("/");

    char *buffer = malloc(namelen);

    sprintf(buffer, "%s/%s", dot + 1, filename);

    rename(filename, buffer);

    free(buffer);
}


static void mk_directory(const char *dirname)
{

	char *dot = strrchr(dirname, '.');

   	mkdir(dirname, 0755);
    
}

