#include "stdafx.h"
#include "spGateway.h"

int main(void)
{
	RegisterDLL();
	InitAPI();
	while(IPCrecv() >= 0){}
	IPCClean();
	// Sleep(3000);  

	return 0;
}