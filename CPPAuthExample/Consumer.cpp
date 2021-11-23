///*|-----------------------------------------------------------------------------
// *|            This source code is provided under the Apache 2.0 license      --
// *|  and is provided AS IS with no warranty or guarantee of fit for purpose.  --
// *|                See the project's LICENSE.md for details.                  --
// *|           Copyright (C) 2021 Refinitiv. All rights reserved.            --
///*|-----------------------------------------------------------------------------

#include "Consumer.h"
#include "curl/curl.h"
#include "cjson/cJSON.h"
#include <stdlib.h>


using namespace refinitiv::ema::access;
using namespace refinitiv::ema::rdm;
using namespace refinitiv::ema::domain::login;
using namespace std;

const UInt32 maxLength = 256;
EmaString authurl;
EmaString username;
EmaString appId( "256" );
EmaString password;
EmaString service;
EmaString item("IBM.N");
EmaString authenticationToken;


size_t writefunc(void* ptr, size_t size, size_t nmemb, std::string* s)
{
	s->append(static_cast<char*>(ptr), size * nmemb);
	return size * nmemb;
}

void parseJson(std::string jsonStr) {
	cJSON* root = cJSON_Parse(jsonStr.c_str());
	cJSON* success = cJSON_GetObjectItem(root, "success");

	if (cJSON_IsTrue(success)) {
		cout << "True" << std::endl;
		cJSON* token = cJSON_GetObjectItem(root, "token");
		cout << token->valuestring << endl;
		authenticationToken.set(token->valuestring);

	}
	else {
		cout << "False" << std::endl;
		exit(-1);
	}
}
void getToken() 
{
	CURL* curl;
	CURLcode res;
	std::string jsonStr;
	EmaString payload;
	payload.clear();
	payload.append("username=").append(username.c_str()).append("&password=").append(password.c_str());
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
		curl_easy_setopt(curl, CURLOPT_URL, authurl.c_str());
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		//curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
		struct curl_slist* headers = NULL;
		headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
		//headers = curl_slist_append(headers, "Cookie: connect.sid=s%3AN8JQpBOXthPiIM7EehwBhlzT8RPYfli4.hHX0vlUA7%2FimpdoDb8uXp%2Fc%2FCnfMmXuHBmrYCx57shA");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &jsonStr);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);		
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
		res = curl_easy_perform(curl);
		if (res == CURLE_OK)
		{
			std::cout << jsonStr << std::endl;
			parseJson(jsonStr);
		}
		else {
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
			curl_easy_cleanup(curl);
			exit(-1);
		}
		
		
	}
	
}

void printUsage()
{
	cout << "\nOptions:\n"
		<< "  -?                            Shows this usage\n\n"
		<< "  -authurl <authurl>    Required: Authentication URL to get a token (e.g. http://<AuthServer>:8443/getToken) \n"
		<< "  -username <username>    Required: Username \n"
		<< "  -password <password>          Required: Password\n"
		<< "  -service <service name>    Required: Service name\n"
		<< "  -item <ric>    Optional: A RIC\n"
		<< "\n";
	exit( -1 );
}

void printActiveConfig()
{
	cout << "\nFollowing options are selected:" << endl;

	cout << "appId = " << appId << endl
		<< "authurl = " << authurl << endl
		<< "username = " << username << endl
		<< "password = *****" << endl
		<< "service = " << service << endl
		<< "item = " << item << endl;

}

void processCommandLineOptions( int argc, char* argv[] )
{
	int iargs = 1;
	authurl.clear();
	username.clear();
	password.clear();
	service.clear();

	while (iargs < argc)
	{
		if (0 == strcmp("-?", argv[iargs]))
		{
			printUsage();
		}
		else if (strcmp("-authurl", argv[iargs]) == 0)
		{
			++iargs; if (iargs == argc) printUsage();

			authurl.set(argv[iargs++]);
		}
		else if (strcmp("-username", argv[iargs]) == 0)
		{
			++iargs; if (iargs == argc) printUsage();

			username.set(argv[iargs++]);
		}
		else if (strcmp("-password", argv[iargs]) == 0)
		{
			++iargs; if (iargs == argc) printUsage();

			password.set(argv[iargs++]);
		}
		else if (strcmp("-service", argv[iargs]) == 0)
		{
			++iargs; if (iargs == argc) printUsage();

			service.set(argv[iargs++]);
		}
		else if (strcmp("-item", argv[iargs]) == 0)
		{
			++iargs; if (iargs == argc) printUsage();

			item.set(argv[iargs++]);
		}
		else
		{
			cout << "Invalid argument: " << argv[iargs] << endl;

			printUsage();
		}
	}
		if (authurl.empty())
		{
			cout << "Missing an authentication URL." << endl;

			printUsage();
		}

		if (username.empty())
		{
			cout << "Missing a username." << endl;

			printUsage();
		}

		if (password.empty())
		{
			cout << "Missing a password." << endl;

			printUsage();
		}

		if (service.empty())
		{
			cout << "Missing a service name." << endl;

			printUsage();
		}
}


void AppClient::onRefreshMsg( const RefreshMsg& refreshMsg, const OmmConsumerEvent& )
{
	cout << endl << "Received refresh" << endl;

	cout << endl << refreshMsg << endl;
}

void AppClient::onUpdateMsg( const UpdateMsg& updateMsg, const OmmConsumerEvent& )
{
	cout << endl << "Received update" << endl;
	cout << endl << updateMsg << endl;
}

void AppClient::onStatusMsg( const StatusMsg& statusMsg, const OmmConsumerEvent& )
{
	cout << endl << "Received status" << endl;

	cout << endl << statusMsg << endl;
}

AppLoginClient::AppLoginClient()
{
	_handle = 0;
	_TTReissue = 0;
}

void AppLoginClient::onRefreshMsg(const RefreshMsg& refreshMsg, const OmmConsumerEvent& event)
{
	Login::LoginRefresh tempRefresh;
	cout << endl << "Received login refresh message" << endl;
	
	_handle = event.getHandle();

	cout << endl << refreshMsg << endl;

	tempRefresh.message(refreshMsg);
	if (tempRefresh.hasAuthenticationTTReissue())
		_TTReissue = tempRefresh.getAuthenticationTTReissue();
	else
		_TTReissue = 0;

	
}

void AppLoginClient::onUpdateMsg(const UpdateMsg& updateMsg, const OmmConsumerEvent&)
{
	cout << endl << updateMsg << endl;
}

void AppLoginClient::onStatusMsg(const StatusMsg& statusMsg, const OmmConsumerEvent&)
{
	if (statusMsg.getDomainType() == MMT_LOGIN)
		cout << endl << "Received login status message" << endl;

	cout << endl << statusMsg << endl;
}


int main( int argc, char* argv[] )
{
	try {	
		authenticationToken.clear();
		processCommandLineOptions( argc, argv );
		printActiveConfig();
		getToken();
		AppLoginClient loginClient;

		EmaBuffer authnExtendedBuf;

		Login::LoginReq loginMsg;

		OmmConsumerConfig consumerConfig;

		loginMsg.name(authenticationToken).applicationId(appId).nameType(USER_AUTH_TOKEN);
			
		
		consumerConfig.addAdminMsg(loginMsg.getMessage());

		AppClient appClient;
		OmmConsumer consumer( consumerConfig, loginClient);
		
		
		consumer.registerClient( ReqMsg().serviceName( service ).name(item ), appClient );
		
		while(true)
		{						
			if (loginClient._TTReissue != 0 && getCurrentTime() >= loginClient._TTReissue)
			{
				getToken();
				loginMsg.clear().name(authenticationToken).applicationId(appId).nameType(USER_AUTH_TOKEN);			
				consumer.reissue(loginMsg.getMessage(), loginClient._handle);
			}
			
			sleep(1000);

		}

	}
	catch ( const OmmException& excp ) {
		cout << excp << endl;
	}
	return 0;
}
