
#include <stdio.h>
#include <strings.h>
#include <sys/time.h>

#include "PackageDatagram.cpp"
#include "SocketStream.cpp"

using namespace std;

const int BUFFER_SIZE = 255;

int main(int argc, char* argv[]){

	int port = 0;

	if(argc == 2){
		port = atoi(argv[1]);
	}
	else{
		printf("use format: %s [port]\n", argv[0]);
		return 0;
	}

	SocketStream server(port);

	while(1){

		PackageDatagram request(sizeof(char)*255);
		server.receive(request);

		char* data = request.getData();
		printf("CLIENT: %s\n", data);

		char* rdata = (char*)malloc(sizeof(char)*255);
		memcpy(rdata, "Message received!", sizeof(char)*255);

		PackageDatagram response(rdata, sizeof(char)*255, request.getIp(), request.getPort()+1);
		response.setData(rdata);
		server.send(response);

		break;
	}

}