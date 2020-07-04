#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define DEFAULT_DELAY 1 /* msec */
#define MSEC 1000000

int tty_unready(int fd) {
    struct winsize ws;

    if (ioctl(fd, TIOCGWINSZ, &ws) == -1) {
        perror("couldn't get window size");
        exit(EXIT_FAILURE);
    }
#ifdef DEBUG
    printf("ws_col=%d ws_row=%d\n", ws.ws_col, ws.ws_row);
#endif
    return ws.ws_row == 0 && ws.ws_col == 0;
}

int main(int argc, char **argv) {
    struct timespec delay;
    int i;

    for (i = 1; tty_unready(0); i++) {
        delay.tv_sec = 0;
        delay.tv_nsec = (i < argc ? atoi(argv[i]) : DEFAULT_DELAY) * MSEC;
        nanosleep(&delay, NULL);
    }

    return i == 1 ? EXIT_SUCCESS : EXIT_FAILURE;
}
