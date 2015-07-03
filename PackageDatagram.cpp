#include "PackageDatagram.h"

// Constructors

PackageDatagram::PackageDatagram(char* data, unsigned int length, char* ip, int port)
{
	this->data = new char[length];
	memcpy(this->data, data, length);

	this->length = length;
	memcpy(this->ip, ip, sizeof this->ip);
	this->port = port; 
}

PackageDatagram::PackageDatagram(unsigned int length)
{
	this->length = length;
}

PackageDatagram::~PackageDatagram(){

}

// Public Methods

char* PackageDatagram::getIp(){
	return ip;
}
unsigned int PackageDatagram::getLength(){
	return length;
}
int PackageDatagram::getPort(){
	return port;
}
char* PackageDatagram::getData(){
	return data;
}

void PackageDatagram::setPort(int port)
{
	this->port = port; 
}
void PackageDatagram::setIp(char* ip)
{
	for(int i=0; i < 16; i++){
		this->ip[i] = ip[i];
	}
}
void PackageDatagram::setData(char* data){

	this->data = data;
}