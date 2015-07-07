#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <netdb.h>
#include <strings.h>
#include <sys/time.h>

#include "PackageDatagram.cpp"
#include "SocketDatagram.cpp"

using namespace std;

int main(int argc, char* argv[]){

	char* host = new char[15];
	int port = 0;

	if(argc == 3){
		memcpy(host, argv[1], 15);
		port = atoi(argv[2]);
	}
	else{
		printf("use format: %s [host] [port]\n", argv[0]);
		return 0;
	}

	SocketDatagram server(port, Interactive);

	int nums[2];
	nums[0] = 3;
	nums[1] = 5;

	PackageDatagram request((char*)nums, sizeof(int)*2, host, port);
	server.send(request);

	PackageDatagram response(sizeof(int));
	server.receive(response);

	char* data = response.getData();

	int result = data[0];
	printf("RESULT: %d + %d = %d\n", nums[0], nums[1], result);

}