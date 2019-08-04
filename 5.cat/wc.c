#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void do_wc(const char *path);
static int do_count(const char *buf);
static void die(const char *s);

int
main(int argc, char *argv[])
{
    int i;
    if (argc < 2) {
        do_wc(NULL);
    }
    for (i = 1; i < argc; i++) {
        do_wc(argv[i]);
    }
    exit(0);
}

#define BUFFER_SIZE 2048

static void
do_wc(const char *path)
{
    int fd;
    unsigned char buf[BUFFER_SIZE];
    int n, count;

    if (path != NULL) {
        fd = open(path, O_RDONLY);
    } else {
        fd = STDIN_FILENO;
    }
    
    if (fd < 0) die(path);
    count = 0;
    for(;;) {
        n = read(fd, buf, sizeof buf);

        if (n < 0) die(path);
        if (n == 0) break;
        count += do_count(buf);
    }

    if (close(fd) < 0) die(path);
    printf("%d",  count);
}

static int
do_count(const char *buf)
{
    int count = 0;

    while (*buf != '\0') {
        if (*buf == '\n') count++;
        buf++;
    }
    return count;
}

static void
die(const char *s)
{
    perror(s);
    exit(1);
}