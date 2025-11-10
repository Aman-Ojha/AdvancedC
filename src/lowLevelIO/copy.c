#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>

#define  O_BINARY O
int fdin=-1;
int fdout=-1;

/*Function to ensure the closure file descriptors after use*/
void closefds(void){
    if(fdin!=-1){
        close(fdin);
    }
    if(fdout!=-1){
        close(fdout);
    }
}

/*Function to print error messages*/
void error (int ret, char* fmt, ...){
    char buff[512];
    va_list list;
    va_start(list, fmt);
    vsprintf(buff, fmt, list);
    va_end(list);
    fprintf (stderr, "Error: %s: %s\n", buff, strerror(ret));
}


int main(int argc, char* argv[]){
    /*Check if the required number of arguments have been passed*/
    if(argc!=3){
        fprintf(stderr, "Usage: %s <source file> <destination file>\n", argv[0]);
        return 1;
    }
    atexit(closefds);

    fdin = open(argv[1], O_RDONLY);
    if(fdin==-1){
        error(2, "opening source file %s", argv[1]);
        return 1;
    }

    fdout=open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if(fdout==-1){
        error(3, "opening destination file %s", argv[2]);
        return 1;
    }

    char buffer[1024];
    ssize_t bytes_read;

    while ((bytes_read = read(fdin, buffer, sizeof(buffer))) > 0) {
        ssize_t bytes_written = write(fdout, buffer, bytes_read);  // use bytes_read!
        if (bytes_written != bytes_read) {  // check full write
            error(4, "writing to destination file %s", argv[2]);
            close(fdin);
            close(fdout);
            return 1;
        }
    }
    /*Error handling*/
    if(bytes_read<0){
        error(5, "reading from source file %s", argv[1]);
        return 1;
    }
    if(close(fdin)==-1){
        error(6, "closing source file %s", argv[1]);
        return 1;
    
    }
    if(close(fdout)==-1){
        error(7, "closing destination file %s", argv[2]);
        return 1;
    }
    return 0;
}

