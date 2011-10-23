#include<windows.h>
#include<Wininet.h>
#include"CURLController.h"

int main()
{
	/*CURLRequest request;
	request.SetURL("www.google.com");
	request.SetSubURL("/accounts/ClientLogin");
	request.SetPostData("accountType=HOSTED_OR_GOOGLE&"
					    "Email=sergey.sergeev.oneclick@gmail.com&"
						"Passwd=123455&"
						"service=cl&"
						"source=GreenFarm");
	request.SetProtocol(CURLRequest::E_PROTOCOL::HTTPS);
	request.SetMethod(CURLRequest::E_METHOD::POST);
	request.Connect();
	request.Send();
	char *_data = request.Recv();
	request.Disconnect();*/

	CURLController::Instance()->Send("one", "HTTPS", "POST", "www.google.com", "/accounts/ClientLogin", "accountType=HOSTED_OR_GOOGLE&"
																										"Email=sergey.sergeev.oneclick@gmail.com&"
																										"Passwd=123455&"
																										"service=cl&"
																										"source=GreenFarm");
	CURLController::Instance()->Send("two", "HTTPS", "POST", "www.google.com", "/accounts/ClientLogin", "accountType=HOSTED_OR_GOOGLE&"
																										"Email=sergey.sergeev.oneclick@gmail.com&"
																										"Passwd=12345&"
																										"service=cl&"
																										"source=GreenFarm");
	CURLController::Instance()->Send("three", "HTTP", "GET", "www.google.com", "", "");
	CURLController::Instance()->Update();
	
	return 0;						
}
