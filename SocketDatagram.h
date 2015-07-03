#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <netdb.h>

enum SocketType{
	Interactive,
	Concurrent,
	None
};

class SocketDatagram
{

public:
	SocketDatagram(int port);
	SocketDatagram(int port, SocketType type);
	~SocketDatagram();

	int receive(PackageDatagram &p);
	int send(PackageDatagram &p);

	// disables printf messages
	void setSilent();
	// gets local ip address (Tested in Mac OS)
	const char* localIP();

private:
	struct sockaddr_in localAddress; 
	struct sockaddr_in remoteAddress;

	int s; //socket id
	bool silent;

};