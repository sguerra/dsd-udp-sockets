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

	int port = 0;

	if(argc == 2){
		port = atoi(argv[1]);
	}
	else{
		printf("use format: %s [port]\n", argv[0]);
		return 0;
	}

	SocketDatagram server(port, Interactive);

	while(1){

		PackageDatagram request(sizeof(int));
		server.receive(request);

		char* data = request.getData();

		int nums[2];
		memcpy(nums, data, sizeof(int)*2);

		int sum = nums[0] + nums[1];

		char* rdata = (char*)malloc(sizeof(int));
		memcpy(rdata, nums, sizeof(int));

		PackageDatagram response(sizeof(int));
		response.setData((char*)rdata);
		server.send(response);

		printf("RESULT: %d + %d = %d\n", nums[0], nums[1], sum);

	}

}