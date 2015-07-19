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

char* randChar(){
	char* nums = "1234567890";

	char* result = (char*)malloc(sizeof(char));
	result[0] = nums[rand()%10];
	return result;
}

int main(int argc, char* argv[]){

	char* host = new char[15];
	int port = 0;

	char* party = new char[3];
	int votes = 0;

	if(argc == 5){
		memcpy(host, argv[1], 15);
		port = atoi(argv[2]);
		memcpy(party, argv[3], 3);
		votes = atoi(argv[4]);
	}
	else{
		printf("use format: %s [host] [port] [party] [votes]\n", argv[0]);
		return 0;
	}


	srand(time(0));

	SocketDatagram server(port, Interactive);

	for(int i = 0; i < votes; i++){

		string builder = "{\"curp\":\"AAAA";
		for(int i = 0; i < 6;i++){
			builder.append(randChar());	
		}
		builder.append("AAAAAA00\", \"phone\":\"");
		for(int i = 0; i < 10;i++){
			builder.append(randChar());	
		}
		builder.append("\", \"party\":\"");
		builder.append(party);
		builder.append("\"}");

		char* vote = (char*)builder.c_str();

		PackageDatagram request(vote, sizeof(char)*66, host, port);
		server.send(request);

		PackageDatagram response(sizeof(char)*3);
		server.receive(response);

		char* data = response.getData();
		printf("RESPONSE: %s\n", data);
	}


}