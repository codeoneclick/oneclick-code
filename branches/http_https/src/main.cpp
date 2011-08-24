#include<windows.h>
#include<Wininet.h>
#include"CURLRequest.h"

int main()
{
	CURLRequest request;
	request.SetURL("www.google.com");
	request.SetSubURL("/accounts/ClientLogin");
	request.SetPostData("accountType=HOSTED_OR_GOOGLE&"
					    "Email=sergey.sergeev.oneclick@gmail.com&"
						"Passwd=12345&"
						"service=cl&"
						"source=GreenFarm");
	request.SetProtocol(CURLRequest::E_PROTOCOL::HTTPS);
	request.SetMethod(CURLRequest::E_METHOD::POST);
	request.Connect();
	request.Send();
	char *_data = request.Recv();
	request.Disconnect();
	
	return 0;						
}
