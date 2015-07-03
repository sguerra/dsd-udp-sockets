#include "SocketDatagram.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

// Constructors

SocketDatagram::SocketDatagram(int port)
{
	silent = false;

	s = socket(AF_INET, SOCK_DGRAM, 0);
	bzero((char *)&localAddress, sizeof(localAddress));
	bzero((char *)&remoteAddress, sizeof(remoteAddress));

	localAddress.sin_family = AF_INET;
	localAddress.sin_addr.s_addr = INADDR_ANY;
	localAddress.sin_port = htons(port);

	bind(s, (struct sockaddr *)&localAddress, sizeof(localAddress));

	char* local_ip = inet_ntoa(localAddress.sin_addr);
	int local_port = ntohs(localAddress.sin_port);

	const char* real_local_ip = this->localIP();
	printf("READY AT %s, PORT: %d\n\n", real_local_ip, local_port);
}
	
SocketDatagram::SocketDatagram(int port, SocketType type): SocketDatagram(port)
{
	int yes;
	yes = 1;


	switch(type){
		case Interactive:

			struct timeval time_out;
			time_out.tv_sec = 5;

			setsockopt(s, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(int));
			setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char*)&time_out, sizeof(time_out));

			break;
		case Concurrent:
		
			setsockopt(s, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(int));

			break;
		default:
			break;

	}
}

SocketDatagram::~SocketDatagram()
{
	//close(s);
}

//Public Methods

int SocketDatagram::receive(PackageDatagram &p)
{
	socklen_t clilen = sizeof(remoteAddress);
	recvfrom(s, (char*)p.getData(), p.getLength(), 0, (struct sockaddr *)&remoteAddress, &clilen);

	char* sender_ip = inet_ntoa(remoteAddress.sin_addr);
	int sender_port = ntohs(localAddress.sin_port);

	if(!silent){
		printf("RECEIVED FROM IP: %s, PORT: %d\n", sender_ip, sender_port);	
	}

	p.setPort(sender_port); 
	p.setIp(sender_ip);

	return 0;
}

int SocketDatagram::send(PackageDatagram &p)
{
	remoteAddress.sin_family = AF_INET;
	remoteAddress.sin_addr.s_addr = inet_addr(p.getIp());
	remoteAddress.sin_port = htons(p.getPort());

	char* sender_ip = inet_ntoa(remoteAddress.sin_addr);
	
	if(!silent){
		printf("SENT TO IP: %s, PORT: %d\n", sender_ip, ntohs(remoteAddress.sin_port));
	}

	socklen_t clilen = sizeof(remoteAddress);
	sendto(s, p.getData(), p.getLength(), 0, (struct sockaddr *)&remoteAddress, clilen);

	return 0;
}

string cli(string command)
{
	string result = "";

	string cli_file = "cli.txt";
	string cmd = command + ">" + cli_file;
	system(cmd.c_str());

	string line;
	ifstream file(cli_file);

	if (file.is_open()){

		while ( getline (file,line) ){
			result += line;
		}

		file.close();
	}

    return result;
}

const char* SocketDatagram::localIP()
{
	string ipconfig = cli("ifconfig");

	string s1(ipconfig);
	regex e1("en0:((.*)en1:)");
	
	smatch m1, m2;
	regex_search (s1, m1, e1);

	string s2(m1.str());
	regex e2("inet ((.){7,16}) netmask");
	regex_search (s2, m2, e2);

	string s3(m2.str());

	string ip = s3.replace(s3.begin(), s3.begin() + 5, "");
	ip = ip.replace(ip.end()-8, ip.begin(), "");


	return ip.c_str();
}

void SocketDatagram::setSilent(){
	this->silent= true;
}