#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <netdb.h>

#include <stdio.h>

class SocketStream
{

public:
	SocketStream(int port);
	~SocketStream();

	int receive(PackageDatagram &p);
	int send(PackageDatagram &p);

private:
	struct sockaddr_in localAddress; 
	struct sockaddr_in remoteAddress;

	int s; //socket id

};