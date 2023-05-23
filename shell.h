#ifndef SHELL_H
#define SHELL_H

/* --Libraries-- */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>


/* --Read & Write Buffers--*/
#define READ_SIZE 1024
#define BUFSIZE 1024