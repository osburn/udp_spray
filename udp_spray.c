/**
 * UDP packet sending
 * Tim Osburn
 * 210712
 *
 * gcc udp_spray.c -o udp_spray; strip udp_spray
 *
 * Listen:
 * tcpdump -Xvvvv -i eth0 udp and port 12345
 *
 */

#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(void)
{
	int sockfd = 0;
	struct sockaddr_in udp_packet;
	unsigned int count;
	unsigned int addressport;
	char string[1472];
	char address[20];

	puts("IP Address to send too: ");
	scanf("%s", address);
	puts("Port to send too: ");
	scanf("%u", &addressport);
	puts("How many times to send: ");
	scanf("%u", &count);
	printf("String to send: ");
	fflush(stdin);
	fgets(string, 1472, stdin);


	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0))< 0) {
		printf("\n Error : Could not create socket \n");
		return 1;
	}

	udp_packet.sin_family = AF_INET;
	udp_packet.sin_port = htons(addressport);
	udp_packet.sin_addr.s_addr = inet_addr(address);

	printf("Sending %i UDP packets of %lu byte size.\n", count, strlen(string)+1);

	for (int i = 1; i <= count; i++) {
		printf("!");
  		fflush(stdout);
		sendto(sockfd, string, (strlen(string)+1), 0, (struct sockaddr *)&udp_packet, sizeof(udp_packet));
		usleep(80000);
	}
	printf("\n");

	return 0;
}
