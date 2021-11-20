#include "spGateway.h"

using namespace std;

int main( int argc, const char* argv[] )
{
	ApiGateway apiGateway;
	apiGateway.RegisterReply();
	apiGateway.InitAPI();
	while(apiGateway.IPCrecv() >= 0){}
	apiGateway.IPCClean();
	return 0;
}
