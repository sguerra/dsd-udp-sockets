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

struct registro{
 char celular[10];
 char CURP[18];
 char partido[3];
 char separador;
} regis;

char* toJSON(){
	char * super_string=NULL;

	super_string = (char*)malloc(64*sizeof(char));

	memcpy(&(super_string[0]),"{\"curp\":\"",9); 
	memcpy(&(super_string[9]),regis.CURP,18); 
	memcpy(&(super_string[27]),"\",\"phone\":\"",11); 
	memcpy(&(super_string[38]),regis.celular,10); 

	memcpy(&(super_string[48]),"\",\"party\":\"",11); 
	memcpy(&(super_string[59]),regis.partido,3); 
	memcpy(&(super_string[62]),"\"}",2);

	return super_string;
}

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

		string phone = "";
		for(int i = 0; i < 10;i++){
			phone.append(randChar());	
		}

		string curp = "AAAA";
		for(int i = 0; i < 6;i++){
			curp.append(randChar());	
		}
		curp.append("AAAAAA00");

		strcpy(regis.celular, phone.c_str());
		strcpy(regis.CURP, curp.c_str()); 
		strcpy(regis.partido, party);

		char* vote = toJSON();

		PackageDatagram request(vote, sizeof(char)*64, host, port);
		server.send(request);

		//PackageDatagram response(sizeof(char)*2);
		//server.receive(response);

		//char* data = response.getData();
		//printf("RESPONSE: %s\n", data);
	}
}