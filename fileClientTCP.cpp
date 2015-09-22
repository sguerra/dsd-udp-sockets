#include <sys/types.h>
#include <stdio.h>
#include <strings.h>
#include <sys/time.h>

#include "PackageDatagram.cpp"
#include "SocketStream.cpp"

using namespace std;

const int BUFFER_SIZE = 255;

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

	SocketStream server(port + 1);

	char* data  = (char*)malloc(sizeof(char)*255);
	memcpy(data, "Hello there! :)", sizeof(char)*255);

	PackageDatagram request(data, sizeof(char)*255, host, port);
	server.send(request);

	PackageDatagram response(sizeof(char)*255);
	server.receive(response);

	char* rdata = response.getData();


	printf("SERVER: %s\n", rdata);
}