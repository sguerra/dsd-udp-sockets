#include "SocketStream.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

// Constructors

SocketStream::SocketStream(int port)
{
	s = socket(AF_INET, SOCK_DGRAM, 0);
	bzero((char *)&localAddress, sizeof(localAddress));
	bzero((char *)&remoteAddress, sizeof(remoteAddress));

	localAddress.sin_family = AF_INET;
	localAddress.sin_addr.s_addr = INADDR_ANY;
	localAddress.sin_port = htons(port);

	bind(s, (struct sockaddr *)&localAddress, sizeof(localAddress));

	char* local_ip = inet_ntoa(localAddress.sin_addr);
	int local_port = ntohs(localAddress.sin_port);

	printf("READY AT %s, PORT: %d\n\n", local_ip, local_port);
}

SocketStream::~SocketStream()
{
	//close(s);
}

//Public Methods

int SocketStream::receive(PackageDatagram &p)
{
	socklen_t clilen = sizeof(remoteAddress);

	char* data = (char*)malloc(sizeof(char)*p.getLength());
	recvfrom(s, (char*)data, p.getLength(), 0, (struct sockaddr *)&remoteAddress, &clilen);
	p.setData(data);

	char* sender_ip = inet_ntoa(remoteAddress.sin_addr);
	int sender_port = ntohs(localAddress.sin_port);

	printf("RECEIVED FROM IP: %s, PORT: %d\n", sender_ip, sender_port);

	p.setPort(sender_port); 
	p.setIp(sender_ip);

	return 0;
}

int SocketStream::send(PackageDatagram &p)
{
	remoteAddress.sin_family = AF_INET;
	remoteAddress.sin_addr.s_addr = inet_addr(p.getIp());
	remoteAddress.sin_port = htons(p.getPort());

	char* sender_ip = inet_ntoa(remoteAddress.sin_addr);
	
	printf("SENT TO IP: %s, PORT: %d\n", sender_ip, ntohs(remoteAddress.sin_port));

	socklen_t clilen = sizeof(remoteAddress);
	sendto(s, p.getData(), p.getLength(), 0, (struct sockaddr *)&remoteAddress, clilen);

	return 0;
}
