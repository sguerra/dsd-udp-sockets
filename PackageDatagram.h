
class PackageDatagram
{

public:

	PackageDatagram(char* data, unsigned int length, char* ip, int port); 
	PackageDatagram(unsigned int length);
	~PackageDatagram();

	char *getIp();
	unsigned int getLength(); 
	int getPort();
	char *getData();
	
	void setPort(int port); 
	void setIp(char* ip);
	void setData(char* data); 

private:
	char *data;
	char ip[16];
	unsigned int length; 
	int port;
	
};