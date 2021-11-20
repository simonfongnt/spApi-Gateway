/*
Severity	Code	Description	Project	File	Line	Suppression State
Warning	C4996	'strcpy': This function or variable may be unsafe. Consider using strcpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
Warning	C4996	'sprintf': This function or variable may be unsafe. Consider using sprintf_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.

*/
#include "stdafx.h"
#include "spGateway.h"

void RegisterDLL()
{
	HINSTANCE hInst = LoadLibrary("spapidllm64.dll");

	if(hInst == NULL)
		exit(1);
	SPAPI_RegisterLoginReply = (p_SPAPI_RegisterLoginReply)GetProcAddress(hInst, "SPAPI_RegisterLoginReply");
	SPAPI_RegisterLoginReply(OnLoginReply);
	SPAPI_RegisterConnectingReply = (p_SPAPI_RegisterConnectingReply)GetProcAddress(hInst, "SPAPI_RegisterConnectingReply");
	SPAPI_RegisterConnectingReply(OnConnectedReply);
	SPAPI_RegisterOrderRequestFailed = (p_SPAPI_RegisterOrderRequestFailed)GetProcAddress(hInst, "SPAPI_RegisterOrderRequestFailed");
	SPAPI_RegisterOrderRequestFailed(OnApiOrderRequestFailed);
	SPAPI_RegisterOrderReport = (p_SPAPI_RegisterOrderReport)GetProcAddress(hInst, "SPAPI_RegisterOrderReport");
	SPAPI_RegisterOrderReport(OnApiOrderReport);
	SPAPI_RegisterOrderBeforeSendReport = (p_SPAPI_RegisterOrderBeforeSendReport)GetProcAddress(hInst, "SPAPI_RegisterOrderBeforeSendReport");
	SPAPI_RegisterOrderBeforeSendReport(OnApiOrderBeforeSendReport); 
	SPAPI_RegisterAccountLoginReply = (p_SPAPI_RegisterAccountLoginReply)GetProcAddress(hInst, "SPAPI_RegisterAccountLoginReply");
	SPAPI_RegisterAccountLoginReply(OnAccountLoginReply);
	SPAPI_RegisterAccountLogoutReply = (p_SPAPI_RegisterAccountLogoutReply)GetProcAddress(hInst, "SPAPI_RegisterAccountLogoutReply");
	SPAPI_RegisterAccountLogoutReply(OnAccountLogoutReply);
	SPAPI_RegisterAccountInfoPush = (p_SPAPI_RegisterAccountInfoPush)GetProcAddress(hInst, "SPAPI_RegisterAccountInfoPush");
	SPAPI_RegisterAccountInfoPush(OnAccountInfoPush);
	SPAPI_RegisterAccountPositionPush = (p_SPAPI_RegisterAccountPositionPush)GetProcAddress(hInst, "SPAPI_RegisterAccountPositionPush");
	SPAPI_RegisterAccountPositionPush(OnAccountPositionPush);
	SPAPI_RegisterUpdatedAccountPositionPush = (p_SPAPI_RegisterUpdatedAccountPositionPush)GetProcAddress(hInst, "SPAPI_RegisterUpdatedAccountPositionPush");
	SPAPI_RegisterUpdatedAccountPositionPush(OnUpdatedAccountPositionPush);
	SPAPI_RegisterUpdatedAccountBalancePush = (p_SPAPI_RegisterUpdatedAccountBalancePush)GetProcAddress(hInst, "SPAPI_RegisterUpdatedAccountBalancePush");
	SPAPI_RegisterUpdatedAccountBalancePush(OnUpdatedAccountBalancePush);
	SPAPI_RegisterTradeReport = (p_SPAPI_RegisterTradeReport)GetProcAddress(hInst, "SPAPI_RegisterTradeReport");
	SPAPI_RegisterTradeReport(OnApiTradeReport);
	SPAPI_RegisterApiPriceUpdate = (p_SPAPI_RegisterApiPriceUpdate)GetProcAddress(hInst, "SPAPI_RegisterApiPriceUpdate");
	SPAPI_RegisterApiPriceUpdate(OnApiPriceUpdate);
	SPAPI_RegisterTickerUpdate = (p_SPAPI_RegisterTickerUpdate)GetProcAddress(hInst, "SPAPI_RegisterTickerUpdate");
	SPAPI_RegisterTickerUpdate(OnApiTickerUpdate);
	SPAPI_RegisterPswChangeReply = (p_SPAPI_RegisterPswChangeReply)GetProcAddress(hInst, "SPAPI_RegisterPswChangeReply");
	SPAPI_RegisterPswChangeReply(OnPswChangeReply);
	SPAPI_RegisterProductListByCodeReply = (p_SPAPI_RegisterProductListByCodeReply)GetProcAddress(hInst, "SPAPI_RegisterProductListByCodeReply");
	SPAPI_RegisterProductListByCodeReply(OnProductListByCodeReply);
	SPAPI_RegisterInstrumentListReply = (p_SPAPI_RegisterInstrumentListReply)GetProcAddress(hInst, "SPAPI_RegisterInstrumentListReply");
	SPAPI_RegisterInstrumentListReply(OnInstrumentListReply);
	SPAPI_RegisterBusinessDateReply = (p_SPAPI_RegisterBusinessDateReply)GetProcAddress(hInst, "SPAPI_RegisterBusinessDateReply");
	SPAPI_RegisterBusinessDateReply(OnBusinessDateReply);
	SPAPI_RegisterMMOrderBeforeSendReport = (p_SPAPI_RegisterMMOrderBeforeSendReport)GetProcAddress(hInst, "SPAPI_RegisterMMOrderBeforeSendReport");
	SPAPI_RegisterMMOrderBeforeSendReport(OnApiMMOrderBeforeSendReport); 
	SPAPI_RegisterMMOrderRequestFailed = (p_SPAPI_RegisterMMOrderRequestFailed)GetProcAddress(hInst, "SPAPI_RegisterMMOrderRequestFailed");
	SPAPI_RegisterMMOrderRequestFailed(OnApiMMOrderRequestFailed); 
	SPAPI_RegisterQuoteRequestReceivedReport = (p_SPAPI_RegisterQuoteRequestReceivedReport)GetProcAddress(hInst, "SPAPI_RegisterQuoteRequestReceivedReport");
	SPAPI_RegisterQuoteRequestReceivedReport(OnApiQuoteRequestReceived); 
	SPAPI_RegisterAccountControlReply = (p_SPAPI_RegisterAccountControlReply)GetProcAddress(hInst, "SPAPI_RegisterAccountControlReply");
	SPAPI_RegisterAccountControlReply(OnApiAccountControlReply);
	SPAPI_RegisterLoadTradeReadyPush = (p_SPAPI_RegisterLoadTradeReadyPush)GetProcAddress(hInst, "SPAPI_RegisterLoadTradeReadyPush");
	SPAPI_RegisterLoadTradeReadyPush(OnApiLoadTradeReadyPush);

	SPAPI_SetLoginInfo = (p_SPAPI_SetLoginInfo)GetProcAddress(hInst, "SPAPI_SetLoginInfo");
	SPAPI_Login = (p_SPAPI_Login)GetProcAddress(hInst, "SPAPI_Login");
	SPAPI_Logout = (p_SPAPI_Logout)GetProcAddress(hInst, "SPAPI_Logout");

	SPAPI_AccountLogin  = (p_SPAPI_AccountLogin)GetProcAddress(hInst, "SPAPI_AccountLogin");
	SPAPI_AccountLogout = (p_SPAPI_AccountLogout)GetProcAddress(hInst, "SPAPI_AccountLogout");
	//Order start
	SPAPI_AddOrder = (p_SPAPI_AddOrder)GetProcAddress(hInst, "SPAPI_AddOrder");

	SPAPI_AddInactiveOrder = (p_SPAPI_AddInactiveOrder)GetProcAddress(hInst, "SPAPI_AddInactiveOrder");
	SPAPI_ChangeOrder = (p_SPAPI_ChangeOrder)GetProcAddress(hInst, "SPAPI_ChangeOrder");
	SPAPI_ChangeOrderBy = (p_SPAPI_ChangeOrderBy)GetProcAddress(hInst, "SPAPI_ChangeOrderBy");
	SPAPI_DeleteOrderBy = (p_SPAPI_DeleteOrderBy)GetProcAddress(hInst, "SPAPI_DeleteOrderBy");
	SPAPI_DeleteAllOrders = (p_SPAPI_DeleteAllOrders)GetProcAddress(hInst, "SPAPI_DeleteAllOrders");
	SPAPI_ActivateAllOrders = (p_SPAPI_ActivateAllOrders)GetProcAddress(hInst, "SPAPI_ActivateAllOrders");
	SPAPI_InactivateAllOrders = (p_SPAPI_InactivateAllOrders)GetProcAddress(hInst, "SPAPI_InactivateAllOrders");
	SPAPI_ActivateOrderBy = (p_SPAPI_ActivateOrderBy)GetProcAddress(hInst, "SPAPI_ActivateOrderBy");
	SPAPI_InactivateOrderBy = (p_SPAPI_InactivateOrderBy)GetProcAddress(hInst, "SPAPI_InactivateOrderBy");
	SPAPI_GetOrderCount = (p_SPAPI_GetOrderCount)GetProcAddress(hInst, "SPAPI_GetOrderCount");
	SPAPI_GetOrderByOrderNo = (p_SPAPI_GetOrderByOrderNo)GetProcAddress(hInst, "SPAPI_GetOrderByOrderNo");
	SPAPI_GetActiveOrders = (p_SPAPI_GetActiveOrders)GetProcAddress(hInst, "SPAPI_GetActiveOrders"); 
	SPAPI_SendMarketMakingOrder = (p_SPAPI_SendMarketMakingOrder)GetProcAddress(hInst, "SPAPI_SendMarketMakingOrder");

	SPAPI_GetPosCount = (p_SPAPI_GetPosCount)GetProcAddress(hInst, "SPAPI_GetPosCount"); 
	SPAPI_GetPosByProduct = (p_SPAPI_GetPosByProduct)GetProcAddress(hInst, "SPAPI_GetPosByProduct");
	SPAPI_GetAllPos = (p_SPAPI_GetAllPos)GetProcAddress(hInst, "SPAPI_GetAllPos");
	SPAPI_GetAllPosByArray = (p_SPAPI_GetAllPosByArray)GetProcAddress(hInst, "SPAPI_GetAllPosByArray");

	SPAPI_GetAccInfo = (p_SPAPI_GetAccInfo)GetProcAddress(hInst, "SPAPI_GetAccInfo");
	SPAPI_GetAccBalCount = (p_SPAPI_GetAccBalCount)GetProcAddress(hInst, "SPAPI_GetAccBalCount"); 
	SPAPI_GetAccBalByCurrency = (p_SPAPI_GetAccBalByCurrency)GetProcAddress(hInst, "SPAPI_GetAccBalByCurrency");
	SPAPI_GetAllAccBal = (p_SPAPI_GetAllAccBal)GetProcAddress(hInst, "SPAPI_GetAllAccBal");

	SPAPI_GetTradeCount = (p_SPAPI_GetTradeCount)GetProcAddress(hInst, "SPAPI_GetTradeCount"); 
	SPAPI_GetAllTrades  = (p_SPAPI_GetAllTrades)GetProcAddress(hInst, "SPAPI_GetAllTrades"); 
	SPAPI_SubscribePrice = (p_SPAPI_SubscribePrice)GetProcAddress(hInst, "SPAPI_SubscribePrice"); 
	SPAPI_SubscribeTicker = (p_SPAPI_SubscribeTicker)GetProcAddress(hInst, "SPAPI_SubscribeTicker"); 
	SPAPI_GetPriceByCode = (p_SPAPI_GetPriceByCode)GetProcAddress(hInst, "SPAPI_GetPriceByCode");
	SPAPI_SubscribeQuoteRequest = (p_SPAPI_SubscribeQuoteRequest)GetProcAddress(hInst, "SPAPI_SubscribeQuoteRequest");
	SPAPI_SubscribeAllQuoteRequest = (p_SPAPI_SubscribeAllQuoteRequest)GetProcAddress(hInst, "SPAPI_SubscribeAllQuoteRequest");

	SPAPI_ChangePassword = (p_SPAPI_ChangePassword)GetProcAddress(hInst, "SPAPI_ChangePassword"); 
	//Status start
	SPAPI_GetLoginStatus = (p_SPAPI_GetLoginStatus)GetProcAddress(hInst, "SPAPI_GetLoginStatus");
	SPAPI_GetCcyRateByCcy = (p_SPAPI_GetCcyRateByCcy)GetProcAddress(hInst, "SPAPI_GetCcyRateByCcy");

	SPAPI_SetApiLogPath = (p_SPAPI_SetApiLogPath)GetProcAddress(hInst, "SPAPI_SetApiLogPath");

	
	SPAPI_LoadProductInfoListByMarket = (p_SPAPI_LoadProductInfoListByMarket)GetProcAddress(hInst, "SPAPI_LoadProductInfoListByMarket");
	SPAPI_LoadProductInfoListByCode =(p_SPAPI_LoadProductInfoListByCode)GetProcAddress(hInst, "SPAPI_LoadProductInfoListByCode");
	SPAPI_GetProductCount  = (p_SPAPI_GetProductCount)GetProcAddress(hInst, "SPAPI_GetProductCount");
	SPAPI_GetProduct  = (p_SPAPI_GetProduct)GetProcAddress(hInst, "SPAPI_GetProduct");
	SPAPI_GetProductByCode  = (p_SPAPI_GetProductByCode)GetProcAddress(hInst, "SPAPI_GetProductByCode");

	SPAPI_LoadInstrumentList  = (p_SPAPI_LoadInstrumentList)GetProcAddress(hInst, "SPAPI_LoadInstrumentList");
	SPAPI_GetInstrumentCount = (p_SPAPI_GetInstrumentCount)GetProcAddress(hInst, "SPAPI_GetInstrumentCount");
	SPAPI_GetInstrument = (p_SPAPI_GetInstrument)GetProcAddress(hInst, "SPAPI_GetInstrument");
	SPAPI_GetInstrumentByCode = (p_SPAPI_GetInstrumentByCode)GetProcAddress(hInst, "SPAPI_GetInstrumentByCode");
	SPAPI_SetLanguageId = (p_SPAPI_SetLanguageId)GetProcAddress(hInst, "SPAPI_SetLanguageId");
	SPAPI_Initialize = (p_SPAPI_Initialize)GetProcAddress(hInst, "SPAPI_Initialize");
	SPAPI_Uninitialize = (p_SPAPI_Uninitialize)GetProcAddress(hInst, "SPAPI_Uninitialize");
	SPAPI_GetDllVersion = (p_SPAPI_GetDllVersion)GetProcAddress(hInst, "SPAPI_GetDllVersion");

	SPAPI_GetAllTradesByArray = (p_SPAPI_GetAllTradesByArray)GetProcAddress(hInst, "SPAPI_GetAllTradesByArray");
	SPAPI_GetOrdersByArray = (p_SPAPI_GetOrdersByArray)GetProcAddress(hInst, "SPAPI_GetOrdersByArray");
	SPAPI_GetAllAccBalByArray  = (p_SPAPI_GetAllAccBalByArray)GetProcAddress(hInst, "SPAPI_GetAllAccBalByArray");
	SPAPI_GetInstrumentByArray = (p_SPAPI_GetInstrumentByArray)GetProcAddress(hInst, "SPAPI_GetInstrumentByArray");
	SPAPI_GetProductByArray = (p_SPAPI_GetProductByArray)GetProcAddress(hInst, "SPAPI_GetProductByArray");
	SPAPI_SendAccControl = (p_SPAPI_SendAccControl)GetProcAddress(hInst, "SPAPI_SendAccControl");
}

void LoadConfig(
	char* config_path
	)
{
	// Read Config Detail
	std::ifstream config_file(config_path);	
	std::string line;
	int i = 0;
	while (std::getline(config_file, line))
	{
		if (i == 0)
			ioport = atoi(line.c_str());
		if (i == 1)
			pubport = atoi(line.c_str());
		i++;
	}
}

void LoadLogin(
	char* login_path
	)
{
	std::string line;
	int i = 0;
	// Read Login Detail
	std::ifstream login_file(login_path);
	i = 0;
	while (std::getline(login_file, line))
	{
		if (i == 0)
			strcpy(host, line.c_str());
		if (i == 1)
			port = atoi(line.c_str());
		if (i == 2)
			strcpy(user_id, line.c_str());
		if (i == 3)
			strcpy(password, line.c_str());
		if (i == 4)
			strcpy(license, line.c_str());
		if (i == 5)
			strcpy(app_id, line.c_str());
		i++;
	}
}

void CheckPassword(
	char* login_path
	)
{
	std::string line;
	int i = 0;
	// Read Login Detail
	std::ifstream login_file(login_path);
	i = 0;
	while (std::getline(login_file, line))
	{
		if (i == 3){
			strcpy(npassword, line.c_str());
			break;
		}	
		i++;
	}
	// update password?
	if (strcmp(password, npassword) != 0){
		char userId[16];
		GetUserId(userId);
		int res = SPAPI_ChangePassword(userId, password, npassword);			
		cout << "old pw: " << password << " new pw: " << npassword << " Status: " << res << endl;
		strcpy(password, npassword);
	}
}

void ReplyCommands(
	int fd,
	std::vector<char*> cmd
	)
{	
	char rc[IO_BUFFER_SIZE] = "-1";
	prevts = thists;
	// switch(stoi(ioBuffer))
	switch(atoi(cmd[0]))
	{
		case DatatypeLogin: 						Login(rc);
		break;
		case DatatypeLogout:						Logout(rc);
		break;
		case DatatypeAddOrder:						AddOrder(cmd, rc);
		break;
		case DatatypeAddInactiveOrder:				AddInactiveOrder(cmd, rc);
		break;
		case DatatypeActivateAllOrders:				ActivateAllOrders(cmd, rc);
		break;
		case DatatypeActivateOrderBy:				ActivateOrderBy(cmd, rc);
		break;
		case DatatypeInactivateAllOrders:			InactivateAllOrders(cmd, rc);
		break;
		case DatatypeInactivateOrderBy:				InactivateOrderBy(cmd, rc);
		break;

		case DatatypeSendMMOrder:					SendMMOrder();
		break;
		// case DatatypeDeleteOrder:					DeleteOrder(cmd, rc);
		// break;
		case DatatypeDeleteOrderBy:					DeleteOrderBy(cmd, rc);
		break;
		case DatatypeDeleteAllOrders:				DeleteAllOrders(cmd, rc);
		break;
		// case DatatypeChangeOrder:					ChangeOrder();
		// break;
		case DatatypeChangeOrderBy:					ChangeOrderBy(cmd, rc);
		break;
		case DatatypeGetActiveOrders:				GetActiveOrders(cmd, rc);
		// case DatatypeGetActiveOrders:				GetActiveOrders(cmd);
		break;
		// case DatatypeSetOrderInactive:				SetOrderInactive();
		// break;
		case DatatypeGetOrderCount:					GetOrderCount(rc);
		break;
		case DatatypeGetPosCount:					GetPosCount(rc);
		break;
		case DatatypeGetPosByProduct:				GetPosByProduct(cmd, rc);
		break;
		case DatatypeGetAllPos:						GetAllPos(rc);
		break;
		// case DatatypeGetAllPosByArray:				GetAllPosByArray();
		// break;
		// case DatatypeGetPos:						GetPos(rc);
		// break;
		case DatatypeGetTradeCount:					GetTradeCount(rc);
		break;
		// case DatatypeGetAllTrade:					GetAllTrade(cmd, rc);
		// break;
		case DatatypeGetAllTrades:					GetAllTrades(rc);
		break;
		// case DatatypeSubscribeUninitPrice:			SubscribeUninitPrice(1);
		case DatatypeSubscribePrice:				SubscribePrice(cmd, rc);				
		break;
		case DatatypeGetPriceByCode:				GetPriceByCode(cmd, rc);
		break;
		case DatatypeSubscribeTicker:				SubscribeTicker(cmd, rc);
		break;
		// case DatatypeUninitTicker:					UninitTicker();
		// break;
		case DatatypeSubscribeQuoteRequest:			SubscribeQuoteRequest(cmd, rc);
		break;
		case DatatypeSubscribeAllQuoteRequest:		SubscribeAllQuoteRequest(cmd, rc);
		break;
		case DatatypeGetAccInfo:					GetAccInfo(rc);
		break;
		case DatatypeGetAccBalCount:				GetAccBalCount(rc);
		break;
		case DatatypeGetAllAccBal:					GetAllAccBal(cmd, rc);
		break;
		case DatatypeGetAccBalByCurrency:			GetAccBalByCurrency(cmd, rc);
		break;
		// case DatatypeGetConnectionStatus:			GetConnectionStatus(cmd, rc);
		case DatatypeGetLoginStatus:				GetLoginStatus(cmd, rc);
		break;
		case DatatypeGetCcyRateByCcy:				GetCcyRateByCcy(cmd, rc);
		break;
		case DatatypeChangePassword:				ChangePassword(cmd, rc);
		break;
		// case DatatypeSetApiLogPath:					SetApiLogPath();
		// break;
		case DatatypeAccountLogin:					AccountLogin(rc);
		break;
		case DatatypeAccountLogout:					AccountLogout(rc);
		break;
		// case DatatypeLoadProductList:				LoadProductList();
		// break;
		case DatatypeLoadProductInfoListByMarket:	LoadProductInfoListByMarket(cmd, rc);
		break;
		case DatatypeLoadProductInfoListByCode:		LoadProductInfoListByCode(cmd, rc);
		break;
		case DatatypeGetProductCount:				GetProductCount(rc);
		break;
		// case DatatypeGetProduct:					GetProduct(rc);
		// break;
		case DatatypeGetProductByCode:				GetProductByCode(cmd, rc);
		break;
		case DatatypeLoadInstrumentList:			LoadInstrumentList(rc);
		break;
		case DatatypeGetInstrumentCount:			GetInstrumentCount(rc);
		break;
		// case DatatypeGetInstrument:					GetInstrument();
		// break;
		case DatatypeGetInstrumentByCode:			GetInstrumentByCode(cmd, rc);
		break;
		case DatatypeSendAccControl:				SendAccControl();
		break;
	}
	// format to socket reply
	size_t s = strlen(rc);
	send(fd, rc, s, 0);
}

void InitAPI()
{
	char c = '1';
	unsigned long ul = 1;
	// // Time	
	time(&thists);	
	prevts = thists;
	
	// Read Config Detail
	LoadConfig(CONFIGPATH);
	// Read Login Detail
	LoadLogin(LOGINPATH);
	
    printf("Login as %s\n", user_id);
	/*************************************************************/
	/* Initialize Winsock
	/*************************************************************/
	WSADATA wsaData;
    rc = WSAStartup(
		MAKEWORD(2, 2), 
		&wsaData
		);
    if (rc != NO_ERROR) {
        wprintf(L"WSAStartup failed with error: %d\n", rc);
		exit(-1);
    }
	/*************************************************************/
	/* Define descriptors for IO socket
	/*************************************************************/
	struct addrinfo *result = NULL;
	struct addrinfo hints;
    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
	/*************************************************************/
	/* Resolve the server address and port
	/*************************************************************/        
	char ioportStr[6];
    sprintf(ioportStr, "%u",ioport);
    rc = getaddrinfo(NULL, ioportStr, &hints, &result);
    if ( rc != 0 ) {
        printf("getaddrinfo failed with error: %d\n", rc);
        freeaddrinfo(result);
        WSACleanup();
		exit(-1);
    }
	/*************************************************************/
	/* Create socket for IO
	/*************************************************************/
    iosock = socket(
		result->ai_family, 
		result->ai_socktype, 
		result->ai_protocol
		);
    if (iosock == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
		exit(-1);
    }
	/*************************************************************/
	/* Allow socket descriptor to be reuseable
	/*************************************************************/	
	rc = setsockopt(
		iosock, 
		SOL_SOCKET, 
		SO_REUSEADDR, 
		(char *) &c, 
		sizeof(c)
		);
	if (rc < 0)
	{
		perror("iosock setsockopt() failed");
        freeaddrinfo(result);
		closesocket(iosock);
        WSACleanup();
		exit(-1);
	}
	/*************************************************************/
	/* Set socket to be nonblocking. All of the sockets for      */
	/* the incoming connections will also be nonblocking since   */
	/* they will inherit that state from the listening socket.   */
	/*************************************************************/
    rc = ioctlsocket(
		iosock, 
		FIONBIO,
		(unsigned long *) &ul
		);
    if (rc == SOCKET_ERROR) {
        printf("Failed to put the socket into non-blocking mode: %d\n", WSAGetLastError());
        freeaddrinfo(result);
		closesocket(iosock);
        WSACleanup();
		exit(-1);
    }
	/*************************************************************/
	/* Bind the socket                                           */
	/*************************************************************/    
	rc = bind(
		iosock, 
		result->ai_addr, 
		(int)result->ai_addrlen
		);
    if (rc == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(iosock);
        WSACleanup();
		exit(-1);
    }
    freeaddrinfo(result);
	/*************************************************************/
	/* Set the listen back log                                   */
	/*************************************************************/
    rc = listen(
		iosock, 
		SOMAXCONN
		);
    if (rc == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(iosock);
        WSACleanup();
		exit(-1);
    }
	// /*************************************************************/
	// /* Initialize the master fd_set                              */
	// /*************************************************************/
	// FD_ZERO(&master_set);
	// max_sd = iosock;
	// FD_SET(iosock, &master_set);
	/*************************************************************/
	/* Initialize the timeval struct to 3 minutes.  If no        */
	/* activity after 3 minutes this program will end.           */
	/*************************************************************/
	timeout.tv_sec  = 3 * 60;
	timeout.tv_usec = 0;

    printf("IO Port %s\n", ioportStr);
    /*************************************************************/
	/* Create socket for Pub/Sub
	/*************************************************************/
    pubsock = socket(
		AF_INET, 
		SOCK_DGRAM, 
		// IPPROTO_UDP
		0
		);
    if (pubsock == INVALID_SOCKET) {
        wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
        closesocket(iosock);
        WSACleanup();
		exit(-1);
    }
	/*************************************************************/
	/* Allow socket descriptor to be reuseable and broadcast with timeout
	/*************************************************************/
	rc = setsockopt(
		pubsock, 
		SOL_SOCKET, 
		SO_BROADCAST, 
		(char *) &c, 
		sizeof(c)
		);
	// int nOpt = 1000;
	// rc = setsockopt(
	// 	pubsock, 
	// 	SOL_SOCKET, 
	// 	SO_RCVTIMEO, 
	// 	(char*)&nOpt, 
	// 	sizeof(int)
	// 	);
	if (rc < 0)
	{
		perror("pubsock setsockopt() failed");
        closesocket(iosock);
		closesocket(pubsock);
        WSACleanup();
		exit(-1);
	}
	/*************************************************************/
	/* Define descriptors for Pub/Sub socket
	/*************************************************************/
    pserv.sin_family = AF_INET;
    pserv.sin_port = htons(pubport);
    pserv.sin_addr.s_addr = INADDR_BROADCAST;
    printf("Callback Port %d\n", pubport);
}

void IPCpub(
	char *msg
)
{
    // wprintf(L"Sending a datagram to the receiver...\n");
    rc = sendto(
		pubsock,
		msg, 
		strlen(msg), 
		0, 
		(sockaddr *) & pserv, 
		sizeof (pserv)
		);
    if (rc == SOCKET_ERROR) {
        wprintf(L"sendto failed with error: %d\n", WSAGetLastError());
    }
}


void IPCClean(
)
{
    // Clean up and quit.
    wprintf(L"Exiting.\n");
    // WSACleanup();

    // No longer need server socket
    closesocket(iosock);
    closesocket(pubsock);
    // closesocket(ClientSocket);
    WSACleanup();
	exit(-1);
}

int IPCrecv(
)
{
    char ioBuffer[IO_BUFFER_SIZE];
	int ioFD = accept(iosock, 0, 0);
    int rval;

	// Exit Criteria
	time(&thists);	
	if (
			(
				thists >= prevts + tsConnectTimeout
			&&  isConnected
				)
		||	(
				thists >= prevts + tsPollingTimeout
			&&  isPolling
				)
		) {
		prevts = thists;
		char userId[16];
		GetUserId(userId);
		printf("\nLogout....");
		SPAPI_Logout(userId);
		exit(-1);
	}

	if (ioFD == -1) {
		// perror("accept");
		return EXIT_FAILURE;
	} else do {
		sockaddr_in from;
		int size = sizeof(from);
		memset(ioBuffer, 0, sizeof(ioBuffer));
		rval = recvfrom(ioFD, ioBuffer, IO_BUFFER_SIZE, 0, reinterpret_cast<SOCKADDR *>(&from), &size);
		// if(rval == SOCKET_ERROR){
		if(rval < 0){
			// perror("reading stream message");
			int err = WSAGetLastError();
			if (err == WSAEWOULDBLOCK)	// currently no data available
				continue;
			// Other errors
			break;
		}
		else if (rval == 0){
			break;
		}
			// printf("Ending connection\n");
		else {
			std::vector<char*> cmd;
			char* cmds = strtok(ioBuffer, ";");
			while(cmds)
			{
				cmd.push_back(cmds);
				cmds = strtok(NULL, ";");
			}
			// printf(
			// 	"%s %ld \n", 
			// 	ioBuffer,
			// 	cmd.size()
			// 	);
			ReplyCommands(
				ioFD,
				cmd
				);
			// Change password?
			CheckPassword(LOGINPATH);
			fflush(stdout);
		}
	} while (1);
	closesocket(ioFD);
	return 1;
}

void GetAccNo(char *acc)
{
	strncpy(acc, user_id, 16);
}

void GetUserId(char *user)
{
	strncpy(user, user_id, 16);
}

void GetPassword(char *pwd)
{
	strncpy(pwd, password, 16);
}

void Login(char* msg)
{

	int rc, result, langid;
	
	printf("\n:_______________________________________________");
	printf("\n|======           SP API Login            ======|");
	printf("\n|_______________________________________________|\n");

	//printf("\nSet API Language Id:[0:ENG, 1:Traditional Chinese, 2:Simplified Chinese]>>> ");scanf("%d", &langid);
	SPAPI_SetLanguageId(0);
	SPAPI_Initialize();
	//SPAPI_RegisterApiProxyWrapperReply(this);
	
	SPAPI_SetLoginInfo(host,port,license,app_id,user_id,password);

	rc = SPAPI_Login();
	isConnected = true;
	sprintf(msg, "%d", rc);
	// return rc;
}

void Unload()
{
int rc;
char userId[16];

	GetUserId(userId);
	rc = SPAPI_Uninitialize(userId);

	if (rc == 0)printf("\nUninitialize DLL OK\n");
	else if (rc == -1)printf("\nUsers Not Logout\n");
	else printf("\nUninitialize DLL Catch\n");

}

void Logout(char* msg)
{
	int rc;
	char userId[16];
	
	GetUserId(userId);
	printf("\nLogout....\n");
	rc = SPAPI_Logout(userId);
	printf("\nLogout Req[userid:%s] return:%d\n",userId, rc);
	// rc = SPAPI_Uninitialize(userId);
	// if (rc == 0)printf("\nUninitialize DLL OK\n");
	// else if (rc == -1)printf("\nUsers Not Logout\n");
	// else printf("\nUninitialize DLL Catch\n");
	sprintf(msg, "%d", rc);
	exit(-1);
}

void AccountLogin(char* msg)
{
	char userId[16], accNo[16];
	GetUserId(userId);
	GetAccNo(accNo);
	int rc = SPAPI_AccountLogin(userId, accNo);
	sprintf(msg, "%d", rc);
}

void AccountLogout(char* msg)
{
	char userId[16], accNo[16];	
	GetUserId(userId);
	GetAccNo(accNo);  
	int rc = SPAPI_AccountLogout(userId, accNo);
	sprintf(msg, "%d", rc);
}

void AddOrder(std::vector<char*> cmd, char* msg)
{
	
	if (cmd.size() != 34)
		return;
	// char userId[16], accNo[16];

	SPApiOrder ord;
	ord.Price 			= atof(cmd[ 1]);
	// ord.StopLevel 		= atof(cmd[ 2]);
	ord.StopLevel 		= 0;
	ord.UpLevel 		= atof(cmd[ 3]);
	ord.UpPrice 		= atof(cmd[ 4]);
	ord.DownLevel 		= atof(cmd[ 5]);
	ord.DownPrice 		= atof(cmd[ 6]);
	// ord.ExtOrderNo		= atoi(cmd[ 7]);
	// ord.IntOrderNo		= atoi(cmd[ 8]);
	ord.Qty				= atoi(cmd[ 9]);
	// ord.TradedQty		= atoi(cmd[10]);
	ord.TradedQty		= 0;
	// ord.TotalQty		= atoi(cmd[11]);
	ord.TotalQty		= 0;
	// ord.ValidTime		= atoi(cmd[12]);
	ord.ValidTime		= 0;
	// ord.SchedTime		= atoi(cmd[13]);
	// ord.TimeStamp		= atoi(cmd[14]);
	ord.OrderOptions	= atoi(cmd[15]);


	// strncpy(ord.AccNo, 			cmd[16], sizeof(ord.AccNo));
	GetAccNo(ord.AccNo);
	strncpy(ord.ProdCode, 		cmd[17], sizeof(ord.ProdCode));
	// strncpy(ord.Initiator, 		cmd[18], sizeof(ord.Initiator));
	GetUserId(ord.Initiator);


	strncpy(ord.Ref, 			cmd[19], sizeof(ord.Ref));
	strcpy(ord.Ref2,			"");
	strcpy(ord.GatewayCode,		"");
	strncpy(ord.ClOrderId, 		cmd[22], sizeof(ord.ClOrderId));

	strncpy(&ord.BuySell, 		&cmd[23][0], 1);
	// strncpy(&ord.StopType, 		&cmd[24][0], 1);
	ord.StopType 		= 0;
	// strncpy(&ord.OpenClose, 	&cmd[25][0], 1);
	ord.OpenClose 		= OC_DEFAULT;

	// ord.CondType		= atoi(cmd[26]);
	ord.CondType		= 0;
	// ord.OrderType		= atoi(cmd[27]);
	ord.OrderType		= 0;
	// ord.ValidType		= atoi(cmd[28]);
	ord.ValidType		= 0;
	// ord.Status			= atoi(cmd[29]);
	ord.DecInPrice		= atoi(cmd[30]);
	// ord.OrderAction		= atoi(cmd[31]);
	// ord.UpdateTime		= atoi(cmd[32]);
	// ord.UpdateSeqNo		= atoi(cmd[33]);

	int rc = SPAPI_AddOrder(&ord);

// 	printf("\n Added Order.");
// 	if(rc != 0) printf("Added Order Error:%d", rc);

	sprintf(msg, "%d", rc);
}

void AddInactiveOrder(std::vector<char*> cmd, char* msg)
{
	
	if (cmd.size() != 34)
		return;
	// char userId[16], accNo[16];

	SPApiOrder ord;
	ord.Price 			= atof(cmd[ 1]);
	// ord.StopLevel 		= atof(cmd[ 2]);
	ord.StopLevel 		= 0;
	ord.UpLevel 		= atof(cmd[ 3]);
	ord.UpPrice 		= atof(cmd[ 4]);
	ord.DownLevel 		= atof(cmd[ 5]);
	ord.DownPrice 		= atof(cmd[ 6]);
	// ord.ExtOrderNo		= atoi(cmd[ 7]);
	// ord.IntOrderNo		= atoi(cmd[ 8]);
	ord.Qty				= atoi(cmd[ 9]);
	// ord.TradedQty		= atoi(cmd[10]);
	ord.TradedQty		= 0;
	// ord.TotalQty		= atoi(cmd[11]);
	ord.TotalQty		= 0;
	// ord.ValidTime		= atoi(cmd[12]);
	ord.ValidTime		= 0;
	// ord.SchedTime		= atoi(cmd[13]);
	// ord.TimeStamp		= atoi(cmd[14]);
	ord.OrderOptions	= atoi(cmd[15]);


	// strncpy(ord.AccNo, 			cmd[16], sizeof(ord.AccNo));
	GetAccNo(ord.AccNo);
	strncpy(ord.ProdCode, 		cmd[17], sizeof(ord.ProdCode));
	// strncpy(ord.Initiator, 		cmd[18], sizeof(ord.Initiator));
	GetUserId(ord.Initiator);


	strncpy(ord.Ref, 			cmd[19], sizeof(ord.Ref));
	strcpy(ord.Ref2,			"");
	strcpy(ord.GatewayCode,		"");
	strncpy(ord.ClOrderId, 		cmd[22], sizeof(ord.ClOrderId));

	strncpy(&ord.BuySell, 		&cmd[23][0], 1);
	// strncpy(&ord.StopType, 		&cmd[24][0], 1);
	ord.StopType 		= 0;
	// strncpy(&ord.OpenClose, 	&cmd[25][0], 1);
	ord.OpenClose 		= OC_DEFAULT;

	// ord.CondType		= atoi(cmd[26]);
	ord.CondType		= 0;
	// ord.OrderType		= atoi(cmd[27]);
	ord.OrderType		= 0;
	// ord.ValidType		= atoi(cmd[28]);
	ord.ValidType		= 0;
	// ord.Status			= atoi(cmd[29]);
	// ord.DecInPrice		= atoi(cmd[30]);
	// ord.OrderAction		= atoi(cmd[31]);
	// ord.UpdateTime		= atoi(cmd[32]);
	// ord.UpdateSeqNo		= atoi(cmd[33]);

	int rc = SPAPI_AddInactiveOrder(&ord);
	sprintf(msg, "%d", rc);
}

void SendMMOrder()
{
	//TODO
}

// void DeleteOrder(std::vector<char*> cmd, char* msg)
// {
void DeleteOrderBy(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 6)
		return;
	char prodcode[16], clOrderId[40];
	long int_order_no;
	int mode, rc;
	char userId[16], accNo[16];

    // // printf("\n>>>>>>>>[1:DeleteOrderBy, 2:DeleteAllOrders]: ");scanf("%d",&mode);
	// // if(mode == 1)
	// // {
    // // GetUserId(userId);
	// // GetAccNo(accNo);  
	// // printf("\n>>>>>>>>Input Int Order No: ");	scanf("%ld",&int_order_no);
	// // printf("\n>>>>>>>>Input Order prodCode: ");scanf("%s",&prodcode);
	// // printf("\n>>>>>>>>Input ClOrderId: "); scanf("%s",&clOrderId);
	// rc = SPAPI_DeleteOrderBy(userId, accNo, int_order_no, prodcode, clOrderId);
	// if (rc != 0)printf("\n DeleteOrderBy, return : %d \n", rc);
	// }
	// else if (mode == 2) DeleteAllOrders();
	
    GetUserId(userId);
	GetAccNo(accNo);  
	rc = SPAPI_DeleteOrderBy(
			userId, 
			accNo, 
			atoi(cmd[3]),
			cmd[4], 
			cmd[5]
			);
	sprintf(msg, "%d", rc);
}

void DeleteAllOrders(std::vector<char*> cmd, char* msg)
{
	char userId[16], accNo[16];
	int rc;

	GetUserId(userId);
	GetAccNo(accNo); 
	rc = SPAPI_DeleteAllOrders(userId, accNo);
	// if (rc != 0)printf("\n DeleteAllOrders, return : %d \n", rc);
	sprintf(msg, "%d", rc);
}

void ChangeOrderBy(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 8)
		return;
	long int_order_no;
	double org_price, new_price;   
	int org_qty, new_qty, rc;
	char userId[16], accNo[16];
 
	GetUserId(userId);
	GetAccNo(accNo);  
	rc = SPAPI_ChangeOrderBy(
		userId, 
		accNo, 
		atoi(cmd[3]),
		atof(cmd[4]),
		atoi(cmd[5]),
		atof(cmd[6]),
		atoi(cmd[7])
		);
	sprintf(msg, "%d", rc);

}

void ActivateAllOrders(std::vector<char*> cmd, char* msg)
{
	
	char userId[16], accNo[16];
	GetUserId(userId);
	GetAccNo(accNo);
	
	int rc = SPAPI_ActivateAllOrders(userId, accNo);
	sprintf(msg, "%d", rc);

}
void ActivateOrderBy(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 2)
		return;
	char userId[16], accNo[16];
	GetUserId(userId);
	GetAccNo(accNo);

	int rc = SPAPI_ActivateOrderBy(userId, accNo, atoi(cmd[1]));
	sprintf(msg, "%d", rc);	
}
void InactivateAllOrders(std::vector<char*> cmd, char* msg)
{
	char userId[16], accNo[16];
	GetUserId(userId);
	GetAccNo(accNo);
	
	int rc = SPAPI_InactivateAllOrders(userId, accNo);
	sprintf(msg, "%d", rc);

	
}
void InactivateOrderBy(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 2)
		return;
	char userId[16], accNo[16];
	GetUserId(userId);
	GetAccNo(accNo);
	int rc = SPAPI_InactivateOrderBy(userId, accNo, atoi(cmd[1]));
	sprintf(msg, "%d", rc);	
}

void GetActiveOrders(std::vector<char*> cmd, char* msg)
{
	char userId[16], accNo[16];
	int rc;
	GetUserId(userId);
	GetAccNo(accNo);

	int lsize =  SPAPI_GetOrderCount(userId, accNo);
	if (lsize <= 0) {
		// printf("\n Empty Order Lists, return : %d \n", rc);
		sprintf(msg, "%d", rc);
		return;
	}
	char *MSGFORMAT;
	MSGFORMAT = (char *) malloc( 256 );
	char *MSGFORMAT1;
	MSGFORMAT1 = (char *) malloc( 256 );
	sprintf(
		MSGFORMAT1, 
		"%s",
		"%f;%f;%f;%f;%f;%f;%lld;%d;%d;%d;%d;%d;%d;%d;%d;%s;%s;%s;%s;%s;%s;%s;%c;%u;%u;%d;%d;%d;%d;%d;%d;%d;%d"
		);
	sprintf(msg, "%s", "");
	
	SPApiOrder *apiOrderList;
	apiOrderList = (SPApiOrder *)malloc(lsize * sizeof(SPApiOrder));
	rc = SPAPI_GetOrdersByArray(userId, accNo, apiOrderList);
	if (rc != 0){
		// printf("\n GetActiveOrders, return : %d \n", rc);
		sprintf(msg, "%d", rc);
		return;
	}
	for (int i = 0; i < lsize; i++) {
		SPApiOrder& order = apiOrderList[i];
		if 		(i == lsize - 1)sprintf(MSGFORMAT, "%s",	MSGFORMAT1);
		else 					sprintf(MSGFORMAT, "%s;",	MSGFORMAT1);
		// Put into Buffer
		sprintf(
			msg + strlen(msg),
			MSGFORMAT,
			order.Price,
			order.StopLevel,
			order.UpLevel,
			order.UpPrice,
			order.DownLevel,
			order.DownPrice,
			order.ExtOrderNo,
			order.IntOrderNo,
			order.Qty,
			order.TradedQty,
			order.TotalQty,
			order.ValidTime,
			order.SchedTime,
			order.TimeStamp,
			order.OrderOptions,
			order.AccNo,
			order.ProdCode,
			order.Initiator,
			order.Ref,
			order.Ref2,
			order.GatewayCode,
			order.ClOrderId,
			order.BuySell,
			order.StopType,
			order.OpenClose,
			order.CondType,
			order.OrderType,
			order.ValidType,
			order.Status,
			order.DecInPrice,
			order.OrderAction,
			order.UpdateTime,
			order.UpdateSeqNo
			);	
	}
	free(apiOrderList);
	free(MSGFORMAT);
	free(MSGFORMAT1);
}

void GetOrderCount(char* msg)
{
int count;
char userId[16], accNo[16];

	GetUserId(userId);
	if (port == 8081)GetAccNo(accNo);
	else strcpy(accNo, user_id);
	count = SPAPI_GetOrderCount(userId, accNo);
	// printf("\n Acc: %s, Order Count:%d", accNo, count);
	sprintf(msg, "%d", count);
	
}

void GetPosCount(char* msg)
{
int count;

	char user[16];
	GetUserId(user);
	// printf("\n|  User Id : ");		scanf("%s",user); 

	count = SPAPI_GetPosCount(user);
	// printf("\n Acc: %s,Pos Count:%d", acc_no,count);
	sprintf(msg, "%d", count);
}

void GetPosByProduct(std::vector<char*> cmd, char* msg)
{
	int rc;
	SPApiPos pos;
	char prodcode[16];
	char user[16];

	if (cmd.size() != 3)
		return;

	GetUserId(user);
	memset(&pos, 0, sizeof(SPApiPos));
	rc = SPAPI_GetPosByProduct(user, cmd[2], &pos);
	printf(
		"%d",
		rc
	);

	// if (rc != 0)
	// 	return;
	// if (rc == 0)
	// 	printf("\n ProdCode=%s,Prev.=%d @ %f,DayLong=%d @ %f,DayShort=%d @ %f, Rate:%f", pos.ProdCode, (pos.LongShort == 'B')?pos.Qty:-1*pos.Qty, pos.TotalAmt, pos.LongQty, pos.LongTotalAmt, pos.ShortQty, pos.ShortTotalAmt, pos.ExchangeRate);
	// else
	// 	printf("\n No Product");

	// Put into Buffer
	sprintf(
		msg,
		"%d;%d;%d;%d;%f;%f;%f;%f;%f;%f;%f;%s;%s;%c;%d",
		pos.Qty,
		pos.DepQty,
		pos.LongQty,
		pos.ShortQty,

		pos.TotalAmt,
		pos.DepTotalAmt,
		pos.LongTotalAmt,
		pos.ShortTotalAmt,
		pos.PLBaseCcy,
		pos.PL,
		pos.ExchangeRate,

		pos.AccNo,
		pos.ProdCode,

		pos.LongShort,
		pos.DecInPrice
		);
}

void GetAllPos(char* msg)
{
	int rc;
	char userId[16];
	GetUserId(userId);

	int lsize =  SPAPI_GetPosCount(userId);
	if (lsize <= 0) {		
		// printf("\n Empty Pos Lists, return : %d \n", rc);
		sprintf(msg, "%d", rc);
		return;
	}
	char *MSGFORMAT;
	MSGFORMAT = (char *) malloc( 256 );
	char *MSGFORMAT1;
	MSGFORMAT1 = (char *) malloc( 256 );
	sprintf(
		MSGFORMAT1, 
		"%s",
		"%d;%d;%d;%d;%f;%f;%f;%f;%f;%f;%f;%s;%s;%c;%d"
		);
	sprintf(msg, "%s", "");

	SPApiPos *apiPosList;
	apiPosList = (SPApiPos *)malloc(lsize * sizeof(SPApiPos));
	rc = SPAPI_GetAllPosByArray(userId, apiPosList);
	if (rc != 0){
		// printf("\n GetAllPos, return : %d \n", rc);
		sprintf(msg, "%d", rc);
		return;
	}
	for (int i = 0; i < lsize; i++) {
		SPApiPos& pos = apiPosList[i];
		if 		(i == lsize - 1)sprintf(MSGFORMAT, "%s",	MSGFORMAT1);
		else 					sprintf(MSGFORMAT, "%s;",	MSGFORMAT1);
		// Put into Buffer
		sprintf(
			msg + strlen(msg),
			MSGFORMAT,
			pos.Qty,
			pos.DepQty,
			pos.LongQty,
			pos.ShortQty,

			pos.TotalAmt,
			pos.DepTotalAmt,
			pos.LongTotalAmt,
			pos.ShortTotalAmt,
			pos.PLBaseCcy,
			pos.PL,
			pos.ExchangeRate,

			pos.AccNo,
			pos.ProdCode,

			pos.LongShort,
			pos.DecInPrice
			);
	}
	isPolling = true;	
	free(apiPosList);
	free(MSGFORMAT);
	free(MSGFORMAT1);
}

// void GetAllPosByArray(std::vector<char*> cmd, char* msg)
// {
// 	// int rc, i;
// 	char userId[16], accNo[16];
// 	SPApiPos *apiPosList2;

// 	GetUserId(userId);
// 	int count =  SPAPI_GetPosCount(userId);
// 	if (count <= 0) {printf("\n No Pos \n"); return;}
// 	apiPosList2 = (SPApiPos *)malloc(count * sizeof(SPApiPos));
// 	int rc = SPAPI_GetAllPosByArray(userId, apiPosList2);
// 	for (int i = 0; i < count; i++) {
// 		SPApiPos& pos = apiPosList2[i];
// 		printf("\nAll Pos>> ProdCode=%s,Prev.=%d @ %f,DayLong=%d @ %f,DayShort=%d @ %f, Rate:%f", pos.ProdCode, (pos.LongShort == 'B')?pos.Qty:-1*pos.Qty, pos.TotalAmt, pos.LongQty, pos.LongTotalAmt, pos.ShortQty, pos.ShortTotalAmt, pos.ExchangeRate);
// 	}
// 	free(apiPosList2);
// }

void GetTradeCount(char* msg)
{
	char userId[16], accNo[16];
	GetUserId(userId);
	GetAccNo(accNo);
	int count = SPAPI_GetTradeCount(userId, accNo);
	// printf("\n Acc: %s,Trade Count:%d", accNo,count);
	sprintf(msg, "%d", count);
}

// void GetAllTrade(std::vector<char*> cmd, char* msg)
void GetAllTrades(char* msg)
{
	int rc;
	char userId[16], accNo[16];
	GetUserId(userId);
	GetAccNo(accNo);

	int lsize =  SPAPI_GetTradeCount(userId, accNo);
	if (lsize <= 0) {		
		// printf("\n Empty Trade Lists, return : %d \n", rc);
		sprintf(msg, "%d", rc);
		return;
	}
	char *MSGFORMAT;
	MSGFORMAT = (char *) malloc( 256 );
	char *MSGFORMAT1;
	MSGFORMAT1 = (char *) malloc( 256 );
	sprintf(
		MSGFORMAT1, 
		"%s",
		"%d;%f;%lld;%lld;%d;%d;%d;%d;%s;%s;%s;%s;%s;%s;%s;%c;%u;%d;%d;%f;%s;%d;%d;%d;%f"
		);
	sprintf(msg, "%s", "");

	SPApiTrade *apiTradeList;
	apiTradeList = (SPApiTrade *)malloc(lsize * sizeof(SPApiTrade));
	rc = SPAPI_GetAllTradesByArray(userId, accNo, apiTradeList);
	if (rc != 0){
		// printf("\n GetAllTrades, return : %d \n", rc);
		sprintf(msg, "%d", rc);
		return;
	}
	for (int i = 0; i < lsize; i++) {
		SPApiTrade& trade = apiTradeList[i];
		if 		(i == lsize - 1)sprintf(MSGFORMAT, "%s",	MSGFORMAT1);
		else 					sprintf(MSGFORMAT, "%s;",	MSGFORMAT1);
		// Put into Buffer
		sprintf(
			msg + strlen(msg),
			MSGFORMAT,
			trade.RecNo,

			trade.Price,

			trade.TradeNo,
			trade.ExtOrderNo,
			trade.IntOrderNo,
			trade.Qty,
			trade.TradeDate,
			trade.TradeTime,

			trade.AccNo,
			trade.ProdCode,
			trade.Initiator,
			trade.Ref,
			trade.Ref2,
			trade.GatewayCode,
			trade.ClOrderId,

			trade.BuySell,
			trade.OpenClose,

			trade.Status,
			trade.DecInPrice,

			trade.OrderPrice,

			trade.TradeRef,

			trade.TotalQty,
			trade.RemainingQty,
			trade.TradedQty,

			trade.AvgTradedPrice
			);
	}
	free(apiTradeList);
	free(MSGFORMAT);
	free(MSGFORMAT1);
}

// void SubscribeUninitPrice(int idx)
void SubscribePrice(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 3)
		return;
	char userId[16];
	GetUserId(userId); 
	int tc = atoi(cmd[2]);
	int rc = SPAPI_SubscribePrice(userId, cmd[1], tc);
	sprintf(msg, "%d", rc);
}

// void SubscribeQuoteRequest()
void SubscribeQuoteRequest(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 3)
		return;
	char userId[16];
	GetUserId(userId); 
	int tc = atoi(cmd[2]);
	int rc = SPAPI_SubscribeQuoteRequest(userId, cmd[1], tc);
	sprintf(msg, "%d", rc);
}

// void SubscribeAllQuoteRequest()
void SubscribeAllQuoteRequest(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 2)
		return;
	char userId[16];
	GetUserId(userId); 
	int tc = atoi(cmd[1]);
	int rc = SPAPI_SubscribeAllQuoteRequest(userId, tc);
	sprintf(msg, "%d", rc);
}

void GetPriceByCode(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 2)
		return;

	SPApiPrice price;
	char user_id[16];
	GetUserId(user_id);
	int rc = SPAPI_GetPriceByCode(user_id, cmd[1], &price);

	if (rc == 0)
	{
		char DPFORMAT1[8];
		char DPFORMAT2[8];
		char DPFORMAT[256];
		sprintf(
			DPFORMAT1, 
			"%s%df", 
			"%.",
			price.DecInPrice
			);
		sprintf(
			DPFORMAT2, 
			",%s%df",
			"%.",
			price.DecInPrice
			);
		sprintf(
			DPFORMAT, 
			"%s;%s;%s;%s;%s;%s;%s",
			"[%s];[%s];[%s];[%s];[%s];[%s];[%s];[%s];[%s]",
			DPFORMAT1, 
			DPFORMAT1, 
			DPFORMAT1, 
			DPFORMAT1, 
			DPFORMAT1, 
			"%d;%f;%f;%d;%s;%s;%u;%d;%d;%d;%d;%d;%d"
			);
		char Bid[256];
		char BidQty[256];
		char BidTicket[256];
		char Ask[256];
		char AskQty[256];
		char AskTicket[256];
		sprintf(Bid, 		DPFORMAT1, 	price.Bid[0]);
		sprintf(BidQty, 	"%d", 		price.BidQty[0]);
		sprintf(BidTicket, 	"%d", 		price.BidTicket[0]);
		sprintf(Ask, 		DPFORMAT1, 	price.Ask[0]);
		sprintf(AskQty, 	"%d", 		price.AskQty[0]);
		sprintf(AskTicket, 	"%d", 		price.AskTicket[0]);
		for (int i = 1; i < SP_MAX_DEPTH; i++){
			sprintf(Bid + strlen(Bid), 				DPFORMAT2, 	price.Bid[i]);
			sprintf(BidQty + strlen(BidQty), 		",%d", 		price.BidQty[i]);
			sprintf(BidTicket + strlen(BidTicket), 	",%d", 		price.BidTicket[i]);
			sprintf(Ask + strlen(Ask), 				DPFORMAT2, 	price.Ask[i]);
			sprintf(AskQty + strlen(AskQty), 		",%d", 		price.AskQty[i]);
			sprintf(AskTicket + strlen(AskTicket), 	",%d", 		price.AskTicket[i]);
		}
		char Last[256];
		char LastQty[256];
		char LastTime[256];
		sprintf(Last, 		DPFORMAT1, 	price.Last[0]);
		sprintf(LastQty, 	"%d", 		price.LastQty[0]);
		sprintf(LastTime, 	"%d", 		price.LastTime[0]);
		for (int i = 1; i < SP_MAX_LAST; i++){
			sprintf(Last + strlen(Last), 			DPFORMAT2, 	price.Last[i]);
			sprintf(LastQty + strlen(LastQty), 		",%d", 		price.LastQty[i]);
			sprintf(LastTime + strlen(LastTime), 	",%d", 		price.LastTime[i]);
		}
		// Put into Buffer
		sprintf(
			msg, 
			DPFORMAT,
			Bid,
			BidQty,
			BidTicket,
			Ask,
			AskQty,
			AskTicket,
			Last,
			LastQty,
			LastTime,
			price.Equil,
			price.Open,
			price.High,
			price.Low,
			price.Close,
			price.CloseDate,
			price.TurnoverVol,
			price.TurnoverAmt,
			price.OpenInt,
			price.ProdCode,
			price.ProdName,
			price.DecInPrice,
			price.ExStateNo,
			price.TradeStateNo,
			price.Suspend,
			price.ExpiryYMD,
			price.ContractYMD,
			price.Timestamp
			);
	}
	else
		sprintf(msg, "%d", rc);
		
}

void SubscribeTicker(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 3)
		return;
	char userId[16];
	GetUserId(userId); 
	int tc = atoi(cmd[2]);
	int rc = SPAPI_SubscribeTicker(userId, cmd[1], tc);
	sprintf(msg, "%d", rc);
}

// void UninitTicker()
// {
// int rc;
// char prodcode[16], userId[16];

// 	GetUserId(userId);
// 	printf("\n>>>>>>>>Input Uninit Ticker ProdCode: ");	
// 	scanf("%s",&prodcode);
// 	printf("\n>>>>>>>>Uninit Ticker prodCode: %s", prodcode);
// 	rc = SPAPI_SubscribeTicker(userId, prodcode, 0);
// 	if (rc != 0)printf("\SubscribeTicker return:%d", rc);
// }


void GetAccInfo(char* msg)
{
	SPApiAccInfo acc_info;
	int rc;
	char user[16];

	GetUserId(user);
	memset(&acc_info, 0, sizeof(SPApiAccInfo));
	rc = SPAPI_GetAccInfo(user, &acc_info);
	if (rc == 0)
	{
		// Put into Buffer
		sprintf(
			msg,
			"%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%s;%s;%s;%s;%s;%s;%u;%u;%u;%u",
			acc_info.NAV,
			acc_info.BuyingPower,
			acc_info.CashBal,
			acc_info.MarginCall,
			acc_info.CommodityPL,
			acc_info.LockupAmt,
			acc_info.CreditLimit,
			acc_info.MaxMargin,
			acc_info.MaxLoanLimit,
			acc_info.TradingLimit,
			acc_info.RawMargin,
			acc_info.IMargin,
			acc_info.MMargin,
			acc_info.TodayTrans,
			acc_info.LoanLimit,
			acc_info.TotalFee,
			acc_info.LoanToMR,
			acc_info.LoanToMV,

			acc_info.AccName,
			acc_info.BaseCcy,
			acc_info.MarginClass,
			acc_info.TradeClass,
			acc_info.ClientId,
			acc_info.AEId,

			acc_info.AccType,
			acc_info.CtrlLevel,
			acc_info.Active,
			acc_info.MarginPeriod
			);
	}

}

void GetAccBalCount(char* msg)
{
	int count;
	char user[16];
	
	GetUserId(user);
	count = SPAPI_GetAccBalCount(user);
	sprintf(msg, "%d", count);
}

void GetAllAccBal(std::vector<char*> cmd, char* msg)
{
	int rc;
	char userId[16], accNo[16];
	GetUserId(userId);
	GetAccNo(accNo);
	
	int lsize =  SPAPI_GetAccBalCount(userId);
	if (lsize <= 0) {		
		// printf("\n Empty Account Lists, return : %d \n", rc);
		sprintf(msg, "%d", rc);
		return;
	}
	char *MSGFORMAT;
	MSGFORMAT = (char *) malloc( 256 );
	char *MSGFORMAT1;
	MSGFORMAT1 = (char *) malloc( 256 );
	sprintf(
		MSGFORMAT1, 
		"%s",
		"%f;%f;%f;%f;%f;%s"
		);
	sprintf(msg, "%s", "");
	
	SPApiAccBal *apiAccBalList;
	apiAccBalList = (SPApiAccBal *)malloc(lsize * sizeof(SPApiAccBal));
	rc = SPAPI_GetAllAccBalByArray(accNo, apiAccBalList);
	if (rc != 0){
		// printf("\n GetAllAccBal, return : %d \n", rc);
		sprintf(msg, "%d", rc);
		return;
	}
	for (int i = 0; i < lsize; i++) {
		SPApiAccBal& accBal = apiAccBalList[i];
		if 		(i == lsize - 1)sprintf(MSGFORMAT, "%s",	MSGFORMAT1);
		else 					sprintf(MSGFORMAT, "%s;",	MSGFORMAT1);
		// Put into Buffer
		sprintf(
			msg + strlen(msg), 
			MSGFORMAT,
			accBal.CashBf,
			accBal.TodayCash,
			accBal.NotYetValue,
			accBal.Unpresented,
			accBal.TodayOut,
			accBal.Ccy
			);
	}
	free(apiAccBalList);
	free(MSGFORMAT);
	free(MSGFORMAT1);
}

void GetAccBalByCurrency(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 2)
		return;
	SPApiAccBal accBal;
	// int rc;
	char user[16];

	GetUserId(user);
	strcpy(accBal.Ccy, cmd[1]);
	int rc = SPAPI_GetAccBalByCurrency(user, accBal.Ccy, &accBal);
	
	if (rc == 0)
	{
		sprintf(
			msg, 
			"%f;%f;%f;%f;%f;%s", 
			accBal.CashBf,
			accBal.TodayCash,
			accBal.NotYetValue,
			accBal.Unpresented,
			accBal.TodayOut,
			accBal.Ccy
			);
	}
	else
		sprintf(msg, "%d", rc);
}

// void GetConnectionStatus(std::vector<char*> cmd, char* msg)
void GetLoginStatus(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 2)
		return;
	int status_Id = atoi(cmd[1]);
	int rc = SPAPI_GetLoginStatus(user_id, status_Id);
	sprintf(msg, "%d", rc);
}

void GetCcyRateByCcy(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 2)
		return;
	double rate;
	char user[16];
	GetUserId(user);
	int rc = SPAPI_GetCcyRateByCcy(user, cmd[1], rate);
	if (rc == 0)
		sprintf(msg, "%f", rate);
	else
		sprintf(msg, "%d", rc);
}

// void ChangePassword()
void  ChangePassword(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 2)
		return;
	char userId[16];
	GetUserId(userId);
	
	char pwd[16];
	GetPassword(pwd);
	// int rc = SPAPI_ChangePassword(userId, cmd[1], cmd[1]);
	int rc = SPAPI_ChangePassword(userId, pwd, pwd);
	sprintf(msg, "%d", rc);
}

// void SetApiLogPath()
// {
// int rc;
// char path[500];

// 	printf("\n Set Log Path : ");		scanf("%s",path);
// 	rc = SPAPI_SetApiLogPath(path);
// 	printf("\n[%s]Set Api Log Path Reply:%d ",acc_no,rc);
// }

// void LoadProductList()
// {
// int idx;

//     // printf("\n>>>Input Type:(1: ByInstCode, 2:ByMarketCode ) ");	scanf("%d",&idx);
// 	// switch(idx)
// 	// {
// 	// 	case 1: LoadProductInfoListByCode();              break;
// 	// 	case 2: LoadProductInfoListByMarket();        break;
// 	// }
// }

void LoadProductInfoListByMarket(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 2)
		return;
	int rc = SPAPI_LoadProductInfoListByMarket(cmd[1]);
	sprintf(msg, "%d", rc);
}

void LoadProductInfoListByCode(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 2)
		return;
	int rc = SPAPI_LoadProductInfoListByCode(cmd[1]);
	sprintf(msg, "%d", rc);
}

void GetProductCount(char* msg)
{
	int count = SPAPI_GetProductCount();
	sprintf(msg, "%d", count);
}

void GetProduct(char* msg)		
{
	int rc;
	
	int lsize =  SPAPI_GetProductCount();
	if (lsize <= 0) {		
		// printf("\n Empty Order Lists, return : %d \n", rc);
		sprintf(msg, "%d", rc);
		return;
	}
	char *MSGFORMAT;
	MSGFORMAT = (char *) malloc( 256 );
	char *MSGFORMAT1;
	MSGFORMAT1 = (char *) malloc( 256 );
	sprintf(
		MSGFORMAT1, 
		"%s",
		"%s;%d;%s;%s;%s;%d;%d;%d;%d;%s;%s;%d;%d"
		);
	sprintf(msg, "%s", "");
	
	SPApiProduct *apiProdList;
	apiProdList = (SPApiProduct *)malloc(lsize * sizeof(SPApiProduct));
	rc = SPAPI_GetProductByArray(apiProdList);
	if (rc != 0){
		// printf("\n GetProduct, return : %d \n", rc);
		sprintf(msg, "%d", rc);
		return;
	}
	for (int i = 0; i < lsize; i++) {
		SPApiProduct& prod = apiProdList[i];
		if 		(i == lsize - 1)sprintf(MSGFORMAT, "%s",	MSGFORMAT1);
		else 					sprintf(MSGFORMAT, "%s;",	MSGFORMAT1);
		// Put into Buffer
		sprintf(
			msg + strlen(msg),
			MSGFORMAT,
			prod.ProdCode,
			prod.ProdType,
			prod.ProdName,
			prod.Underlying,
			prod.InstCode,
			prod.ExpiryDate,
			prod.CallPut,
			prod.Strike,
			prod.LotSize,
			prod.ProdName1,
			prod.ProdName2,
			prod.OptStyle,
			prod.TickSize
			);	
	}
	free(apiProdList);
	free(MSGFORMAT);
	free(MSGFORMAT1);
}
					
void GetProductByCode(std::vector<char*> cmd, char* msg)	
{
	if (cmd.size() != 2)
		return;
	SPApiProduct prod;
	int rc = SPAPI_GetProductByCode(cmd[1], &prod);
	if (rc == 0)
		// printf("\n ProdCode=%s , ProdName=%s , InstCode=%s ", prod.ProdCode, prod.ProdName, prod.InstCode);		
		// Put into Buffer
		sprintf(
			msg,
			"%s;%c;%s;%s;%s;%d;%c;%d;%d;%s;%s;%c;%d",
			prod.ProdCode,
			prod.ProdType,
			prod.ProdName,
			prod.Underlying,
			prod.InstCode,
			prod.ExpiryDate,
			prod.CallPut,
			prod.Strike,
			prod.LotSize,
			prod.ProdName1,
			prod.ProdName2,
			prod.OptStyle,
			prod.TickSize
			);
	else
		sprintf(msg, "%d", rc);
}

void LoadInstrumentList(char* msg)
{
	int rc = SPAPI_LoadInstrumentList();
	sprintf(msg, "%d", rc);
}

void GetInstrumentCount(char* msg)	
{
	int count = SPAPI_GetInstrumentCount();
	sprintf(msg, "%d", count);
}	
				
// void GetInstrument()	
// {
// int rc;
// vector<SPApiInstrument> apiInstList;

// 	rc = SPAPI_GetInstrument(apiInstList);
// 	if (rc != 0)printf("\n Get Instrument, return : %d ,Count:%d \n", rc, apiInstList.size());
// 	for (int i = 0; i < apiInstList.size(); i++) {
// 		SPApiInstrument& instrument = apiInstList[i];
// 		printf("\n Number:%d, InstCode=%s, InstName=%s, Ccy=%s, Margin=%f",i+1, instrument.InstCode, instrument.InstName, instrument.Ccy, instrument.Margin);
// 	}	
// 	if (apiInstList.size() == 0) printf("\n No Instrument \n");    
// }
							
void GetInstrumentByCode(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 2)
		return;
	SPApiInstrument instrument;
	int rc = SPAPI_GetInstrumentByCode(cmd[1], &instrument);
	if (rc == 0)
		// Put into Buffer
		sprintf(
			msg,
			"%f;%f;%s;%s;%s;%s;%s;%s;%c",
			instrument.Margin,
			instrument.ContractSize,
			instrument.MarketCode,
			instrument.InstCode,
			instrument.InstName,
			instrument.InstName1,
			instrument.InstName2,
			instrument.Ccy,
			// instrument.DecInPrice
			instrument.InstType
			);
	else
		sprintf(msg, "%d", rc);
}

void SendAccControl()
{
	// int rc;
	// int ctrl_level;
	// int ctrl_mask;
	// char userId[16], accNo[16];

	// GetUserId(userId);
	// GetAccNo(accNo);

	// printf("\n>>>>>>>>Input Ctrl Mask:(1:Access Control)(2:Login Control) ");  scanf("%d",&ctrl_mask);

	// if (ctrl_mask == CTRLMASK_CTRL_LEVEL)
	// {
	// 	printf("\n>>>>>>>>Input Ctrl Level: \n");	   
	// 	printf("\n[0: Level 0 - Normal Client Access] \n");
	// 	printf("\n[1: Level 1 - Disable Client Trading] \n");
	// 	printf("\n[2: Level 2 - Suspend Client Login and Trading] \n");
	// 	printf("\n[3: Level 3 - Freeze Account] \n");
	// 	printf("\n[4: Level 4 - Client Trade Only] \n Input:");
	// 	getchar(); 
	// 	scanf("%d", &ctrl_level);
	// 	rc = SPAPI_SendAccControl(userId, accNo, CTRLMASK_CTRL_LEVEL, ctrl_level);
	// }
	// else if (ctrl_mask == CTRLMASK_KICKOUT)
	// {
	// 	rc = SPAPI_SendAccControl(userId, accNo, CTRLMASK_KICKOUT, 0);
	// }
	// printf("\nSend Acc Control Report Reply:%d ",rc);  
}
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void SPDLLCALL OnLoginReply(char *user_id, long ret_code,char *ret_msg)
{
   	char buffer[PUBLISH_BUFFER_SIZE];
	sprintf(
		buffer, 
		"%d;%s;%ld;%s", 
		DatatypeOnLoginReply, 
		user_id, 
		ret_code, 
		ret_msg
		);
	IPCpub(buffer);
}

void SPDLLCALL OnConnectedReply(long host_type, long con_status)
{
   	char buffer[PUBLISH_BUFFER_SIZE];
	sprintf(
		buffer, 
		"%d;%ld;%ld", 
		DatatypeOnConnectedReply, 
		host_type, 
		con_status
		);
	IPCpub(buffer);

}

void SPDLLCALL OnApiOrderRequestFailed(tinyint action, SPApiOrder *order, long err_code, char *err_msg)
{
   	char buffer[PUBLISH_BUFFER_SIZE];
	sprintf(
		buffer, 
		"%d;%d;%ld;%s;%f;%f;%f;%f;%f;%f;%lld;%d;%d;%d;%d;%d;%d;%d;%d;%s;%s;%s;%s;%s;%s;%s;%c;%u;%u;%d;%d;%d;%d;%d;%d;%d;%d", 
		DatatypeOnApiOrderRequestFailed, 
		action,
		err_code, 
		err_msg,
		order->Price,
		order->StopLevel,
		order->UpLevel,
		order->UpPrice,
		order->DownLevel,
		order->DownPrice,
		order->ExtOrderNo,
		order->IntOrderNo,
		order->Qty,
		order->TradedQty,
		order->TotalQty,
		order->ValidTime,
		order->SchedTime,
		order->TimeStamp,
		order->OrderOptions,
		order->AccNo,
		order->ProdCode,
		order->Initiator,
		order->Ref,
		order->Ref2,
		order->GatewayCode,
		order->ClOrderId,
		order->BuySell,
		order->StopType,
		order->OpenClose,
		order->CondType,
		order->OrderType,
		order->ValidType,
		order->Status,
		order->DecInPrice,
		order->OrderAction,
		order->UpdateTime,
		order->UpdateSeqNo
		);
	IPCpub(buffer);
}

// NOTE: UpdateTime & UpdateSeqNo disappeared after restarted
void SPDLLCALL OnApiOrderReport(long rec_no, SPApiOrder *order)
{
	
   	char buffer[PUBLISH_BUFFER_SIZE];
	sprintf(
		buffer, 
		"%d;%ld;%f;%f;%f;%f;%f;%f;%lld;%d;%d;%d;%d;%d;%d;%d;%d;%s;%s;%s;%s;%s;%s;%s;%c;%u;%u;%d;%d;%d;%d;%d;%d;%d;%d",
		DatatypeOnApiOrderReport, 
		rec_no,
		order->Price,
		order->StopLevel,
		order->UpLevel,
		order->UpPrice,
		order->DownLevel,
		order->DownPrice,
		order->ExtOrderNo,
		order->IntOrderNo,
		order->Qty,
		order->TradedQty,
		order->TotalQty,
		order->ValidTime,
		order->SchedTime,
		order->TimeStamp,
		order->OrderOptions,
		order->AccNo,
		order->ProdCode,
		order->Initiator,
		order->Ref,
		order->Ref2,
		order->GatewayCode,
		order->ClOrderId,
		order->BuySell,
		order->StopType,
		order->OpenClose,
		order->CondType,
		order->OrderType,
		order->ValidType,
		order->Status,
		order->DecInPrice,
		order->OrderAction,
		order->UpdateTime,
		order->UpdateSeqNo
		);
	IPCpub(buffer);
}

void SPDLLCALL OnApiOrderBeforeSendReport(SPApiOrder *order)
{
   	char buffer[PUBLISH_BUFFER_SIZE];
	sprintf(
		buffer, 
		"%d;%f;%f;%f;%f;%f;%f;%lld;%d;%d;%d;%d;%d;%d;%d;%d;%s;%s;%s;%s;%s;%s;%s;%c;%u;%u;%d;%d;%d;%d;%d;%d;%d;%d",
		DatatypeOnApiOrderBeforeSendReport, 
		order->Price,
		order->StopLevel,
		order->UpLevel,
		order->UpPrice,
		order->DownLevel,
		order->DownPrice,
		order->ExtOrderNo,
		order->IntOrderNo,
		order->Qty,
		order->TradedQty,
		order->TotalQty,
		order->ValidTime,
		order->SchedTime,
		order->TimeStamp,
		order->OrderOptions,
		order->AccNo,
		order->ProdCode,
		order->Initiator,
		order->Ref,
		order->Ref2,
		order->GatewayCode,
		order->ClOrderId,
		order->BuySell,
		order->StopType,
		order->OpenClose,
		order->CondType,
		order->OrderType,
		order->ValidType,
		order->Status,
		order->DecInPrice,
		order->OrderAction,
		order->UpdateTime,
		order->UpdateSeqNo
		);
	IPCpub(buffer);
	OnApiOrderReport(0, order);
}

void SPDLLCALL OnAccountLoginReply(char *accNo, long ret_code, char* ret_msg)
{
   	char buffer[PUBLISH_BUFFER_SIZE];
	sprintf(
		buffer, 
		"%d;%s;%ld;%s",
		DatatypeOnAccountLoginReply, 
		accNo,
		ret_code,
		ret_msg
		);
	IPCpub(buffer);
}


void SPDLLCALL OnAccountLogoutReply(char *accNo, long ret_code, char* ret_msg)
{
   	char buffer[PUBLISH_BUFFER_SIZE];
	sprintf(
		buffer, 
		"%d;%s;%ld;%s",
		DatatypeOnAccountLogoutReply, 
		accNo,
		ret_code,
		ret_msg
		);
	IPCpub(buffer);
}

void SPDLLCALL OnAccountInfoPush(SPApiAccInfo *acc_info)
{
   	char buffer[PUBLISH_BUFFER_SIZE];
	sprintf(
		buffer, 
		"%d;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%s;%s;%s;%s;%s;%s;%u;%u;%u;%u",
		DatatypeOnAccountInfoPush, 
		acc_info->NAV,
		acc_info->BuyingPower,
		acc_info->CashBal,
		acc_info->MarginCall,
		acc_info->CommodityPL,
		acc_info->LockupAmt,
		acc_info->CreditLimit,
		acc_info->MaxMargin,
		acc_info->MaxLoanLimit,
		acc_info->TradingLimit,
		acc_info->RawMargin,
		acc_info->IMargin,
		acc_info->MMargin,
		acc_info->TodayTrans,
		acc_info->LoanLimit,
		acc_info->TotalFee,
		acc_info->LoanToMR,
		acc_info->LoanToMV,
		acc_info->AccName,
		acc_info->BaseCcy,
		acc_info->MarginClass,
		acc_info->TradeClass,
		acc_info->ClientId,
		acc_info->AEId,
		acc_info->AccType,
		acc_info->CtrlLevel,
		acc_info->Active,
		acc_info->MarginPeriod
		);
	IPCpub(buffer);
}

void SPDLLCALL OnAccountPositionPush(SPApiPos *pos)
{
   	char buffer[PUBLISH_BUFFER_SIZE];
	sprintf(
		buffer, 
		"%d;%d;%d;%d;%d;%f;%f;%f;%f;%f;%f;%f;%s;%s;%c;%d",
		DatatypeOnAccountPositionPush, 
		pos->Qty,
		pos->DepQty,
		pos->LongQty,
		pos->ShortQty,
		pos->TotalAmt,
		pos->DepTotalAmt,
		pos->LongTotalAmt,
		pos->ShortTotalAmt,
		pos->PLBaseCcy,
		pos->PL,
		pos->ExchangeRate,
		pos->AccNo,
		pos->ProdCode,
		pos->LongShort,
		pos->DecInPrice
		);
	IPCpub(buffer);
}

void SPDLLCALL OnUpdatedAccountPositionPush(SPApiPos *pos)
{
   	char buffer[PUBLISH_BUFFER_SIZE];
	sprintf(
		buffer, 
		"%d;%d;%d;%d;%d;%f;%f;%f;%f;%f;%f;%f;%s;%s;%c;%d",
		DatatypeOnUpdatedAccountPositionPush, 
		pos->Qty,
		pos->DepQty,
		pos->LongQty,
		pos->ShortQty,
		pos->TotalAmt,
		pos->DepTotalAmt,
		pos->LongTotalAmt,
		pos->ShortTotalAmt,
		pos->PLBaseCcy,
		pos->PL,
		pos->ExchangeRate,
		pos->AccNo,
		pos->ProdCode,
		pos->LongShort,
		pos->DecInPrice
		);
	IPCpub(buffer);
}

void SPDLLCALL OnUpdatedAccountBalancePush(SPApiAccBal *acc_bal)
{
   	char buffer[PUBLISH_BUFFER_SIZE];
	sprintf(
		buffer, 
		"%d;%f;%f;%f;%f;%f;%s",
		DatatypeOnUpdatedAccountBalancePush, 
		acc_bal->CashBf,
		acc_bal->TodayCash,
		acc_bal->NotYetValue,
		acc_bal->Unpresented,
		acc_bal->TodayOut,
		acc_bal->Ccy
		);
	IPCpub(buffer);
}

void SPDLLCALL OnApiTradeReport(long rec_no, SPApiTrade *trade)
{
   	char buffer[PUBLISH_BUFFER_SIZE];
	sprintf(
		buffer, 
		"%d;%ld;%d;%f;%lld;%lld;%d;%d;%d;%d;%s;%s;%s;%s;%s;%s;%s;%c;%u;%d;%d;%f;%s;%d;%d;%d;%f",
		DatatypeOnApiTradeReport, 
		rec_no,
		trade->RecNo,
		trade->Price,
		trade->TradeNo,
		trade->ExtOrderNo,
		trade->IntOrderNo,
		trade->Qty,
		trade->TradeDate,
		trade->TradeTime,
		trade->AccNo,
		trade->ProdCode,
		trade->Initiator,
		trade->Ref,
		trade->Ref2,
		trade->GatewayCode,
		trade->ClOrderId,
		trade->BuySell,
		trade->OpenClose,
		trade->Status,
		trade->DecInPrice,
		trade->OrderPrice,
		trade->TradeRef,
		trade->TotalQty,
		trade->RemainingQty,
		trade->TradedQty,
		trade->AvgTradedPrice
		);
	IPCpub(buffer);
}

void SPDLLCALL OnApiPriceUpdate(SPApiPrice *price)
{
	if (price == NULL) 
		return;
	
   	char buffer[PUBLISH_BUFFER_SIZE];

	char DPFORMAT1[8];
	char DPFORMAT2[8];
	char DPFORMAT[256];

	sprintf(
		DPFORMAT1, 
		"%s%df", 
		"%.",
		price->DecInPrice
		);
	sprintf(
		DPFORMAT2, 
		",%s%df",
		"%.",
		price->DecInPrice
		);
	sprintf(
		DPFORMAT, 
		"%s;%s;%s;%s;%s;%s;%s",
		"%d;[%s];[%s];[%s];[%s];[%s];[%s];[%s];[%s];[%s]",
		DPFORMAT1, 
		DPFORMAT1, 
		DPFORMAT1, 
		DPFORMAT1, 
		DPFORMAT1, 
		"%d;%f;%f;%d;%s;%s;%d;%d;%d;%d;%d;%d;%d"
		);
	char Bid[256];
	char BidQty[256];
	char BidTicket[256];
	char Ask[256];
	char AskQty[256];
	char AskTicket[256];
	sprintf(Bid, 		DPFORMAT1, 	price->Bid[0]);
	sprintf(BidQty, 	"%d", 		price->BidQty[0]);
	sprintf(BidTicket, 	"%d", 		price->BidTicket[0]);
	sprintf(Ask, 		DPFORMAT1, 	price->Ask[0]);
	sprintf(AskQty, 	"%d", 		price->AskQty[0]);
	sprintf(AskTicket, 	"%d", 		price->AskTicket[0]);
	for (int i = 1; i < SP_MAX_DEPTH; i++){
		sprintf(Bid + strlen(Bid), 				DPFORMAT2, 	price->Bid[i]);
		sprintf(BidQty + strlen(BidQty), 		",%d", 		price->BidQty[i]);
		sprintf(BidTicket + strlen(BidTicket), 	",%d", 		price->BidTicket[i]);
		sprintf(Ask + strlen(Ask), 				DPFORMAT2, 	price->Ask[i]);
		sprintf(AskQty + strlen(AskQty), 		",%d", 		price->AskQty[i]);
		sprintf(AskTicket + strlen(AskTicket), 	",%d", 		price->AskTicket[i]);
	}
	char Last[256];
	char LastQty[256];
	char LastTime[256];
	sprintf(Last, 		DPFORMAT1, 	price->Last[0]);
	sprintf(LastQty, 	"%d", 		price->LastQty[0]);
	sprintf(LastTime, 	"%d", 		price->LastTime[0]);
	for (int i = 1; i < SP_MAX_LAST; i++){
		sprintf(Last + strlen(Last), 			DPFORMAT2, 	price->Last[i]);
		sprintf(LastQty + strlen(LastQty), 		",%d", 		price->LastQty[i]);
		sprintf(LastTime + strlen(LastTime), 	",%d", 		price->LastTime[i]);
	}
	// Put into Buffer
	sprintf(
		buffer, 
		DPFORMAT,
		DatatypeOnApiPriceUpdate,
		Bid,
		BidQty,
		BidTicket,
		Ask,
		AskQty,
		AskTicket,
		Last,
		LastQty,
		LastTime,

		price->Equil,
		price->Open,
		price->High,
		price->Low,		
		price->Close,

		price->CloseDate,
		price->TurnoverVol,
		price->TurnoverAmt,
		price->OpenInt,
		price->ProdCode,
		price->ProdName,
		price->DecInPrice,
		price->ExStateNo,
		price->TradeStateNo,
		price->Suspend,
		price->ExpiryYMD,
		price->ContractYMD,
		price->Timestamp
		);
	IPCpub(buffer);
}

void SPDLLCALL OnApiTickerUpdate(SPApiTicker *ticker)
{
   	char buffer[PUBLISH_BUFFER_SIZE];
	sprintf(
		buffer, 
		"%d;%f;%d;%d;%d;%s;%d",
		DatatypeOnApiTickerUpdate, 
		ticker->Price,
		ticker->Qty,
		ticker->TickerTime,
		ticker->DealSrc,
		ticker->ProdCode,
		ticker->DecInPrice
		);
	IPCpub(buffer);
}

void SPDLLCALL OnPswChangeReply(long ret_code, char *ret_msg)
{
   	char buffer[PUBLISH_BUFFER_SIZE];
	sprintf(
		buffer, 
		"%d;%ld;%s",
		DatatypeOnPswChangeReply, 
		ret_code,
		ret_msg
		);
	IPCpub(buffer);
}

void SPDLLCALL OnProductListByCodeReply(long req_id, char *inst_code, bool is_ready, char *ret_msg)
{
   	char buffer[PUBLISH_BUFFER_SIZE];
	sprintf(
		buffer, 
		"%d;%ld;%s;%d;%s",
		DatatypeOnProductListByCodeReply, 
		req_id,
		inst_code,
		is_ready,
		ret_msg
		);
	IPCpub(buffer);
}

void SPDLLCALL OnInstrumentListReply(long req_id, bool is_ready, char *ret_msg)
{
   	char buffer[PUBLISH_BUFFER_SIZE];
	sprintf(
		buffer, 
		"%d;%ld;%d;%s",
		DatatypeOnInstrumentListReply, 
		req_id,
		is_ready,
		ret_msg
		);
	IPCpub(buffer);
}

void SPDLLCALL OnBusinessDateReply(long business_date)
{
   	char buffer[PUBLISH_BUFFER_SIZE];
	sprintf(
		buffer, 
		"%d;%ld",
		DatatypeOnBusinessDateReply, 
		business_date
		);
	IPCpub(buffer);
}

void SPDLLCALL OnApiAccountControlReply(long ret_code, char *ret_msg)
{
   	char buffer[PUBLISH_BUFFER_SIZE];
	sprintf(
		buffer, 
		"%d;%ld;%s",
		DatatypeOnApiAccountControlReply, 
		ret_code,
		ret_msg
		);
	IPCpub(buffer);
}

void SPDLLCALL OnApiLoadTradeReadyPush(long rec_no, SPApiTrade *trade)
{
   	char buffer[PUBLISH_BUFFER_SIZE];
	sprintf(
		buffer, 
		"%d;%ld;%d;%f;%lld;%lld;%d;%d;%d;%d;%s;%s;%s;%s;%s;%s;%s;%c;%u;%d;%d;%f;%s;%d;%d;%d;%f",
		DatatypeOnApiLoadTradeReadyPush, 
		rec_no,
		trade->RecNo,
		trade->Price,
		trade->TradeNo,
		trade->ExtOrderNo,
		trade->IntOrderNo,
		trade->Qty,
		trade->TradeDate,
		trade->TradeTime,
		trade->AccNo,
		trade->ProdCode,
		trade->Initiator,
		trade->Ref,
		trade->Ref2,
		trade->GatewayCode,
		trade->ClOrderId,
		trade->BuySell,
		trade->OpenClose,
		trade->Status,
		trade->DecInPrice,
		trade->OrderPrice,
		trade->TradeRef,
		trade->TotalQty,
		trade->RemainingQty,
		trade->TradedQty,
		trade->AvgTradedPrice
		);
	IPCpub(buffer);
}


void SPDLLCALL OnApiMMOrderBeforeSendReport(SPApiMMOrder *mm_order)
{
   	char buffer[PUBLISH_BUFFER_SIZE];
	sprintf(
		buffer, 
		"%d;%lld;%lld;%ld;%ld;%f;%f;%ld;%ld;%ld;%ld;%s;%s;%s;%s;%d;%d;%d",
		DatatypeOnApiMMOrderBeforeSendReport, 
		mm_order->BidExtOrderNo,
		mm_order->AskExtOrderNo,
		mm_order->BidAccOrderNo,
		mm_order->AskAccOrderNo,
		mm_order->BidPrice,
		mm_order->AskPrice,
		mm_order->BidQty,
		mm_order->AskQty,
		mm_order->SpecTime,
		mm_order->OrderOptions,
		mm_order->ProdCode,
		mm_order->AccNo,
		mm_order->ClOrderId,
		mm_order->OrigClOrdId,
		mm_order->OrderType,
		mm_order->ValidType,
		mm_order->DecInPrice
		);
	IPCpub(buffer);
}

void SPDLLCALL OnApiMMOrderRequestFailed(SPApiMMOrder *mm_order, long err_code, char *err_msg)
{
   	char buffer[PUBLISH_BUFFER_SIZE];
	sprintf(
		buffer, 
		"%d;%ld;%s;%lld;%lld;%ld;%ld;%f;%f;%ld;%ld;%ld;%ld;%s;%s;%s;%s;%d;%d;%d",
		DatatypeOnApiMMOrderRequestFailed,
		err_code,
		err_msg, 
		mm_order->BidExtOrderNo,
		mm_order->AskExtOrderNo,
		mm_order->BidAccOrderNo,
		mm_order->AskAccOrderNo,
		mm_order->BidPrice,
		mm_order->AskPrice,
		mm_order->BidQty,
		mm_order->AskQty,
		mm_order->SpecTime,
		mm_order->OrderOptions,
		mm_order->ProdCode,
		mm_order->AccNo,
		mm_order->ClOrderId,
		mm_order->OrigClOrdId,
		mm_order->OrderType,
		mm_order->ValidType,
		mm_order->DecInPrice
		);
	IPCpub(buffer);
}

void SPDLLCALL OnApiQuoteRequestReceived(char *product_code, char buy_sell, long qty)
{
   	char buffer[PUBLISH_BUFFER_SIZE];
	sprintf(
		buffer, 
		"%d;%s;%d;%ld",
		DatatypeOnApiMMOrderBeforeSendReport, 
		product_code,
		buy_sell,
		qty
		);
	IPCpub(buffer);
}