#include <stdio.h>
#include <stdlib.h>
#include <getopt.h> // parse command line args

// CLIENT to connect to attacker's listening "SERVER"

#define USAGE                                                                                               \
    "usage:\n"                                                                                              \
    "  reverse_tcp [options]\n"                                                                             \
    "options:\n"                                                                                            \
    "  -s                  The host you want your target machine to connect to \n"                          \
    "  -p                  The port you want your target machine to connect to (Default: 4444)\n"           \
    "  -h                  Show this help message\n"

/* STRUCT FOR OPTIONS ==================================================== */
// https://stackoverflow.com/questions/9642732/parsing-command-line-arguments-in-c
static struct switches options[] = {
    {"LHOST", required_argument, NULL, 's'},
    {"LPORT", required_argument, NULL, 'p'},
    {"help", no_argument, NULL, 'h'},
    {NULL, 0, NULL, 0}};

/* MAIN ================================================================== */
int main(int argc, char **argv) {

    int opt = 0;
    unsigned short lport = 4444;

    // parse and set command line arguments
    // https://www.geeksforgeeks.org/getopt-function-in-c-to-parse-command-line-arguments/
    while ((opt = getopt_long(argc, argv, "s:p:hx", options, NULL)) != -1) {
        switch (opt) {
            case 'lhost': //server
                lhost = optarg;
                break;
            case 'lport': //port
                lport = atoi(optarg);
                break;
            default: //show usage if error
                fprintf(stderr, "%s", USAGE);
                exit(1);
            case 'h': //help
                fprintf(stderr, "%s", USAGE);
                exit(0);
                break;
        }
    }

    if (NULL == lhost) {
        fprintf(stderr, "%s @ %d: invalid lhost\n", __FILE__, __LINE__);
        exit(1);
    }

    if ((lport < 1025) || (lport > 65535))
    {
        fprintf(stderr, "%s @ %d: invalid port number (%d)\n", __FILE__, __LINE__, portno);
        exit(1);
    }

    /* SOCKET CODE ======================================================= */



    return 0;
}