#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/bcm.h>

#define PROGNAME "demo"
#define VERSION  "0.0.1"

#define MSGID   (0x0C0)
#define MSGLEN  (3)
#define NFRAMES (4)

#define DELAY (10000)

static sig_atomic_t sigval;

static void onsig(int val)
{
    sigval = (sig_atomic_t)val;
}

static void usage(void)
{
    puts("Usage: " PROGNAME "[OPTIONS] IFACE\n"
         "Where:\n"
         "  IFACE    CAN network interface\n"
         "Options:\n"
         "  -h       Display this help then exit\n"
         "  -v       Display version info then exit\n");
}

static void version(void)
{
    puts(PROGNAME " " VERSION "\n");
}

int main(int argc, char **argv)
{
    unsigned int i;
    int opt;
    int s;
    char *iface;
    struct sockaddr_can addr;
    struct ifreq ifr;
    
    struct can_msg
    {
        struct bcm_msg_head msg_head;
        struct can_frame frame[NFRAMES];
    } msg;

    /* Check if at least one argument was specified */
    if (argc < 2)
    {
        fputs("Too few arguments!\n", stderr);
        usage();
        return EXIT_FAILURE;
    }

    /* Parse command line options */
    while ((opt = getopt(argc, argv, "hv")) != -1)
    {
        switch (opt)
        {
        case 'h':
            usage();
            return EXIT_SUCCESS;
        case 'v':
            version();
            return EXIT_SUCCESS;
        default:
            usage();
            return EXIT_FAILURE;
        }
    }

    /* Exactly one command line argument must remain; the interface to use */
    if (optind == (argc - 1))
    {
        iface = argv[optind];
    }
    else
    {
        fputs("Only one interface may be used!\n", stderr);
        usage();
        return EXIT_FAILURE;
    }

    /* Register signal handlers */
    if (signal(SIGINT, onsig)    == SIG_ERR ||
        signal(SIGTERM, onsig)   == SIG_ERR ||
        signal(SIGCHLD, SIG_IGN) == SIG_ERR)
    {
        perror(PROGNAME);
        return errno;
    }

    /* Open the CAN interface */
    s = socket(PF_CAN, SOCK_DGRAM, CAN_BCM);
    if (s < 0)
    {
        perror(PROGNAME ": socket");
        return errno;
    }

    strncpy(ifr.ifr_name, iface, IFNAMSIZ);
    if (ioctl(s, SIOCGIFINDEX, &ifr) < 0)
    {
        perror(PROGNAME ": ioctl");
        return errno;
    }

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    if (connect(s, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror(PROGNAME ": connect");
        return errno;
    }

    /* Setup code */
    sigval = 0;

    /* Set up cyclic messages. Note that both SETTIMER and STARTTIMER are
     * required as flags in order to continue transmitting.
     */
    msg.msg_head.opcode  = TX_SETUP;
    msg.msg_head.can_id  = 0;
    msg.msg_head.flags   = SETTIMER | STARTTIMER;
    msg.msg_head.nframes = NFRAMES;
    msg.msg_head.count   = 0;

    /* Set the time interval value to 1200 ms */
    msg.msg_head.ival2.tv_sec = 1;
    msg.msg_head.ival2.tv_usec = 200000;

    /* Create the example messages */
    for (i = 0; i < NFRAMES; ++i)
    {
        struct can_frame * const frame = msg.frame + i;
        frame->can_id = MSGID + i;
        frame->can_dlc = MSGLEN;
        memset(frame->data, i, MSGLEN);
    }

    /* Register the cyclic messages. Note that all of the messages in the msg
     * struct will be sent with the same periodicity because they share the
     * same bcm_msg_head setup data.
     */
    if (write(s, &msg, sizeof(msg)) < 0)
    {
        perror(PROGNAME ": write: TX_SETUP");
        return errno;
    }

    printf("Cyclic messages registed with SocketCAN!\n"
           "Use a tool such as \"candump %s\" to view the messages.\n"
           "These messages will continue to transmit so long as the socket\n"
           "used to communicate with SocketCAN remains open. In other words,\n"
           "close this program with SIGINT or SIGTERM in order to gracefully\n"
           "stop transmitting.\n",
           iface);

    /* Spin forever here */
    while (0 == sigval) usleep(DELAY);

    puts("\nGoodbye!");

    /* Close the CAN interface */
    if (close(s) < 0)
    {
        perror(PROGNAME ": close");
        return errno;
    }

    return EXIT_SUCCESS;
}
