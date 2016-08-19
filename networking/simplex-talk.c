// Example Application 1.4.2 from Peterson and Davie (2012)

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define SERVER_PORT 5432
#define MAX_LINE 256

int main(int argc, char *argv[])
{
	struct hostent *hp;	// represent an entry in the hosts database
	struct sockaddr_in sin; // handling internet addresses
	char *host, buf[MAX_LINE];
	int s, len;

	if (argc !=2 ) {
		fprintf(stderr, "usage: simplex-talk host\n");
		exit(1);
	}

	host = argv[1];

	// translate host name into peer's IP address: obsolete
	hp = gethostbyname(host);

	if (!hp) {
		fprintf(stderr, "simplex-talk: unknown host: %s\n", host);
		exit(1);
	}

	// build address data structure
	bzero((char *) &sin, sizeof(sin));	// zeros out bytes
	sin.sin_family = AF_INET; // address family (IPv4)
	bcopy(hp->h_addr, (char *) &sin.sin_addr, hp->h_length); // byte copy
	sin.sin_port = htons(SERVER_PORT); // host to network endianness short int

	/* active open */
	if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("simplex-talk: socket");
		exit(1);
	}

	if (connect(s, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
		perror("simplex-talk: connect");
		close(s); // no shutdown(s, SHUT_RDWR) needed
		exit(1);
	}

	/* main loop: get and send lines of text */
	while (fgets(buf, sizeof(buf), stdin)) {
		buf[MAX_LINE-1] = '\0';
		len = strlen(buf) + 1; // strnlen(buf, MAX_LINE);
		send(s, buf, len, 0);
	}
}
