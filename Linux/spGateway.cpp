#include "spGateway.h"
#include <unistd.h>
#include <ctype.h>
#include <time.h> 
#include <stdio.h>

ApiGateway::ApiGateway(void){
   	cout << "ApiGateway Object is being created" << endl;
}
ApiGateway::~ApiGateway(void){
	Unload();
	cout << "ApiGateway Object is being deleted" << endl;
}

void ApiGateway::LoadConfig(
	char* config_path
	)
{
	std::string line;
	int i = 0;
	// Read Config Detail
	std::ifstream config_file(config_path);
	while (std::getline(config_file, line))
	{
		if (i == 0)
			ioport = atoi(line.c_str());
		if (i == 1)
			pubport = atoi(line.c_str());
		i++;
	}
}

void ApiGateway::LoadLogin(
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

void ApiGateway::CheckPassword(
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
		int res = apiProxyWrapper.SPAPI_ChangePassword(userId, password, npassword);			
		cout << "old pw: " << password << " new pw: " << npassword << " Status: " << res << endl;
		strcpy(password, npassword);
	}
}

void ApiGateway::ReplyCommands(
	int fd,
	std::vector<char*> cmd
	)
{	
	char rc[IO_BUFFER_SIZE] = "-1";
	
	// char *rc;
	// rc = (char *) malloc( IO_BUFFER_SIZE );
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
	// free(rc);
}

void ApiGateway::InitAPI()
{
	unsigned int ui = 1;
	// Time	
	time(&thists);	
	prevts = thists;
	
	// Read Config Detail
	LoadConfig(CONFIGPATH);
	// Read Login Detail
	LoadLogin(LOGINPATH);

    printf("Login as %s\n", user_id);
	
	/*************************************************************/
	/* Create socket for IO
	/*************************************************************/
    iosock = socket(
		AF_INET, 
		SOCK_STREAM, 
		0
		);
    if (iosock < 0) {
        perror("socket() iosock failed");
        exit(1);
    }
	/*************************************************************/
	/* Allow socket descriptor to be reuseable
	/*************************************************************/   
	rc = setsockopt(
		iosock, 
		SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
		&ui, 
		sizeof(ui)
		);
	if (rc < 0)
	{
		perror("setsockopt() failed");
		close(iosock);
		exit(-1);
	}
	/*************************************************************/
	/* Set socket to be nonblocking. All of the sockets for      */
	/* the incoming connections will also be nonblocking since   */
	/* they will inherit that state from the listening socket.   */
	/*************************************************************/
   	rc = ioctl(
		iosock, 
		FIONBIO, 
		&ui
		);
	if (rc < 0)
	{
		perror("ioctl() failed");
		close(iosock);
		exit(-1);
	}
	/*************************************************************/
	/* Bind the socket                                           */
	/*************************************************************/
    ioserv.sin_family = AF_INET;
    ioserv.sin_addr.s_addr = INADDR_ANY;
    ioserv.sin_port = htons(ioport);
	rc = bind(
		iosock,
		(struct sockaddr *)&ioserv, 
		sizeof(ioserv)
		);
	if (rc < 0)
	{
		perror("bind() failed");
		close(iosock);
		exit(-1);
	}
    // /* Name socket using wildcards */
    // ioserv.sin_family = AF_INET;
    // ioserv.sin_addr.s_addr = INADDR_ANY;
    // ioserv.sin_port = htons(23456);
    // if (bind(iosock, (struct sockaddr *)&ioserv, 
    //          sizeof(ioserv))) {
    //     perror("binding stream socket");
    //     exit(1);
    // }
    // /* Find out assigned port number and print it out */
    // iolen = sizeof(ioserv);
    // if (getsockname(iosock, (struct sockaddr *)&ioserv, &iolen)) {
    //     perror("getting socket name");
    //     exit(1);
    // }
	/*************************************************************/
	/* Set the listen back log                                   */
	/*************************************************************/
	rc = listen(
		iosock, 
		32
		);
	if (rc < 0)
	{
		perror("listen() failed");
		close(iosock);
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

    printf("IO Port %d\n", ntohs(ioserv.sin_port));
    // /* Start accepting connections */
    // listen(iosock, 5);

	/*************************************************************/
	/* Create socket for Pub/Sub
	/*************************************************************/    
    pubsock = socket(
		AF_INET, 
		SOCK_DGRAM, 
		0
		);
    if (pubsock < 0) {
        perror("opening datagram socket");
        exit(1);
    }
	/*************************************************************/
	/* Allow socket descriptor to be reuseable and broadcast
	/*************************************************************/
	setsockopt(
		pubsock, 
		SOL_SOCKET, 
		SO_REUSEADDR | SO_REUSEPORT | SO_BROADCAST, 
		&ui, 
		sizeof(ui)
		);    
	/*************************************************************/
	/* Define descriptors for Pub/Sub socket
	/*************************************************************/
	memset(&pserv,0,sizeof(pserv));
    pserv.sin_family = AF_INET;
    pserv.sin_addr.s_addr = INADDR_ANY;
    pserv.sin_port=htons(pubport);
    printf("Callback Port %d\n", ntohs(pserv.sin_port));
}

void ApiGateway::IPCpub(
	char *msg
)
{
    if(
		sendto(
			pubsock, 
			msg, 
			strlen(msg), 
			0, 
			(struct sockaddr *) &pserv, 
			sizeof(pserv)
			) < 0
		)
		perror("sendto");
}

void ApiGateway::IPCClean(
)
{
    // Clean up and quit.
    wprintf(L"Exiting.\n");
    close(iosock);
    close(pubsock);
	exit(-1);
}

int ApiGateway::IPCrecv(
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
		apiProxyWrapper.SPAPI_Logout(userId);
		exit(-1);
	}	

	// Receive
	if (ioFD == -1) {
		// perror("accept");
		return EXIT_FAILURE;
	} else do {
	// } else {
		memset(ioBuffer, 0, sizeof(ioBuffer));
		if ((rval  = read(ioFD, ioBuffer,  IO_BUFFER_SIZE)) < 0)
			perror("reading stream message");
		else if (rval == 0){}
			// printf("Ending connection\n");
			// printf("\n");
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
	} while (rval > 0);
	close(ioFD);
	return 0;
}

void ApiGateway::GetAccNo(char *acc)
{
	strncpy(acc, user_id, 16);
}

void ApiGateway::GetUserId(char *user)
{
	strncpy(user, user_id, 16);
}

void ApiGateway::GetPassword(char *pwd)
{
	strncpy(pwd, password, 16);
}

void ApiGateway::RegisterReply()
{
	apiProxyWrapper.SPAPI_RegisterApiProxyWrapperReply(this);
}

void ApiGateway::Login(char* msg)
{

	int rc, result, langid;
	
	printf("\n:_______________________________________________");
	printf("\n|======           SP API Login            ======|");
	printf("\n|_______________________________________________|\n");

	//printf("\nSet API Language Id:[0:ENG, 1:Traditional Chinese, 2:Simplified Chinese]>>> ");scanf("%d", &langid);
	apiProxyWrapper.SPAPI_SetLanguageId(0);
	apiProxyWrapper.SPAPI_Initialize();
	//apiProxyWrapper.SPAPI_RegisterApiProxyWrapperReply(this);
	
	apiProxyWrapper.SPAPI_SetLoginInfo(host,port,license,app_id,user_id,password);

	rc = apiProxyWrapper.SPAPI_Login();
	isConnected = true;
	sprintf(msg, "%d", rc);
	// return rc;
}

void ApiGateway::Unload()
{
int rc;
char userId[16];

	GetUserId(userId);
	rc = apiProxyWrapper.SPAPI_Uninitialize(userId);

	if (rc == 0)printf("\nUninitialize DLL OK\n");
	else if (rc == -1)printf("\nUsers Not Logout\n");
	else printf("\nUninitialize DLL Catch\n");

}

void ApiGateway::Logout(char* msg)
{
	int rc;
	char userId[16];
	
	GetUserId(userId);
	printf("\nLogout....\n");
	rc = apiProxyWrapper.SPAPI_Logout(userId);
	printf("\nLogout Req[userid:%s] return:%d\n",userId, rc);
	// rc = apiProxyWrapper.SPAPI_Uninitialize(userId);
	// if (rc == 0)printf("\nUninitialize DLL OK\n");
	// else if (rc == -1)printf("\nUsers Not Logout\n");
	// else printf("\nUninitialize DLL Catch\n");
	sprintf(msg, "%d", rc);
	exit(-1);
}

void  ApiGateway::AccountLogin(char* msg)
{
	char userId[16], accNo[16];
	GetUserId(userId);
	GetAccNo(accNo);
	int rc = apiProxyWrapper.SPAPI_AccountLogin(userId, accNo);
	sprintf(msg, "%d", rc);
}

void ApiGateway::AccountLogout(char* msg)
{
	char userId[16], accNo[16];	
	GetUserId(userId);
	GetAccNo(accNo);  
	int rc = apiProxyWrapper.SPAPI_AccountLogout(userId, accNo);
	sprintf(msg, "%d", rc);
}

void ApiGateway::AddOrder(std::vector<char*> cmd, char* msg)
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

	int rc = apiProxyWrapper.SPAPI_AddOrder(&ord);

// 	printf("\n Added Order.");
// 	if(rc != 0) printf("Added Order Error:%d", rc);

	sprintf(msg, "%d", rc);
}

void ApiGateway::AddInactiveOrder(std::vector<char*> cmd, char* msg)
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

	int rc = apiProxyWrapper.SPAPI_AddInactiveOrder(&ord);
	sprintf(msg, "%d", rc);
}

void ApiGateway::SendMMOrder()
{
	//TODO
}

// void ApiGateway::DeleteOrder(std::vector<char*> cmd, char* msg)
// {
void ApiGateway::DeleteOrderBy(std::vector<char*> cmd, char* msg)
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
	// rc = apiProxyWrapper.SPAPI_DeleteOrderBy(userId, accNo, int_order_no, prodcode, clOrderId);
	// if (rc != 0)printf("\n DeleteOrderBy, return : %d \n", rc);
	// }
	// else if (mode == 2) DeleteAllOrders();
	
    GetUserId(userId);
	GetAccNo(accNo);  
	rc = apiProxyWrapper.SPAPI_DeleteOrderBy(
			userId, 
			accNo, 
			atoi(cmd[3]),
			cmd[4], 
			cmd[5]
			);
	sprintf(msg, "%d", rc);
}

void ApiGateway::DeleteAllOrders(std::vector<char*> cmd, char* msg)
{
	char userId[16], accNo[16];
	int rc;

	GetUserId(userId);
	GetAccNo(accNo); 
	rc = apiProxyWrapper.SPAPI_DeleteAllOrders(userId, accNo);
	// if (rc != 0)printf("\n DeleteAllOrders, return : %d \n", rc);
	sprintf(msg, "%d", rc);
}

void ApiGateway::ChangeOrderBy(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 8)
		return;
	long int_order_no;
	double org_price, new_price;   
	int org_qty, new_qty, rc;
	char userId[16], accNo[16];
 
	GetUserId(userId);
	GetAccNo(accNo);  
	rc = apiProxyWrapper.SPAPI_ChangeOrderBy(
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

void ApiGateway::ActivateAllOrders(std::vector<char*> cmd, char* msg)
{
	
	char userId[16], accNo[16];
	GetUserId(userId);
	GetAccNo(accNo);
	
	int rc = apiProxyWrapper.SPAPI_ActivateAllOrders(userId, accNo);
	sprintf(msg, "%d", rc);

}
void ApiGateway::ActivateOrderBy(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 2)
		return;
	char userId[16], accNo[16];
	GetUserId(userId);
	GetAccNo(accNo);

	int rc = apiProxyWrapper.SPAPI_ActivateOrderBy(userId, accNo, atoi(cmd[1]));
	sprintf(msg, "%d", rc);	
}
void ApiGateway::InactivateAllOrders(std::vector<char*> cmd, char* msg)
{
	char userId[16], accNo[16];
	GetUserId(userId);
	GetAccNo(accNo);
	
	int rc = apiProxyWrapper.SPAPI_InactivateAllOrders(userId, accNo);
	sprintf(msg, "%d", rc);

	
}
void ApiGateway::InactivateOrderBy(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 2)
		return;
	char userId[16], accNo[16];
	GetUserId(userId);
	GetAccNo(accNo);
	int rc = apiProxyWrapper.SPAPI_InactivateOrderBy(userId, accNo, atoi(cmd[1]));
	sprintf(msg, "%d", rc);	
}

void ApiGateway::GetActiveOrders(std::vector<char*> cmd, char* msg)
{
	int rc;
	char userId[16], accNo[16];
	GetUserId(userId);
	GetAccNo(accNo);

	int lsize =  apiProxyWrapper.SPAPI_GetOrderCount(userId, accNo);
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
	rc = apiProxyWrapper.SPAPI_GetOrdersByArray(userId, accNo, apiOrderList);
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

void ApiGateway::GetOrderCount(char* msg)
{
int count;
char userId[16], accNo[16];

	GetUserId(userId);
	if (port == 8081)GetAccNo(accNo);
	else strcpy(accNo, user_id);
	count = apiProxyWrapper.SPAPI_GetOrderCount(userId, accNo);
	// printf("\n Acc: %s, Order Count:%d", accNo, count);
	sprintf(msg, "%d", count);
	
}

void ApiGateway::GetPosCount(char* msg)
{
int count;

	char user[16];
	GetUserId(user);
	// printf("\n|  User Id : ");		scanf("%s",user); 

	count = apiProxyWrapper.SPAPI_GetPosCount(user);
	// printf("\n Acc: %s,Pos Count:%d", acc_no,count);
	sprintf(msg, "%d", count);
}

void ApiGateway::GetPosByProduct(std::vector<char*> cmd, char* msg)
{
	int rc;
	SPApiPos pos;
	char prodcode[16];
	char user[16];

	if (cmd.size() != 3)
		return;

	GetUserId(user);
	memset(&pos, 0, sizeof(SPApiPos));
	rc = apiProxyWrapper.SPAPI_GetPosByProduct(user, cmd[2], &pos);
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

void ApiGateway::GetAllPos(char* msg)
{
	int rc;
	char userId[16];
	GetUserId(userId);

	int lsize =  apiProxyWrapper.SPAPI_GetPosCount(userId);
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
	rc = apiProxyWrapper.SPAPI_GetAllPosByArray(userId, apiPosList);
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

// void ApiGateway::GetAllPosByArray(std::vector<char*> cmd, char* msg)
// {
// 	// int rc, i;
// 	char userId[16], accNo[16];
// 	SPApiPos *apiPosList2;

// 	GetUserId(userId);
// 	int count =  apiProxyWrapper.SPAPI_GetPosCount(userId);
// 	if (count <= 0) {printf("\n No Pos \n"); return;}
// 	apiPosList2 = (SPApiPos *)malloc(count * sizeof(SPApiPos));
// 	int rc = apiProxyWrapper.SPAPI_GetAllPosByArray(userId, apiPosList2);
// 	for (int i = 0; i < count; i++) {
// 		SPApiPos& pos = apiPosList2[i];
// 		printf("\nAll Pos>> ProdCode=%s,Prev.=%d @ %f,DayLong=%d @ %f,DayShort=%d @ %f, Rate:%f", pos.ProdCode, (pos.LongShort == 'B')?pos.Qty:-1*pos.Qty, pos.TotalAmt, pos.LongQty, pos.LongTotalAmt, pos.ShortQty, pos.ShortTotalAmt, pos.ExchangeRate);
// 	}
// 	free(apiPosList2);
// }

void ApiGateway::GetTradeCount(char* msg)
{
	char userId[16], accNo[16];
	GetUserId(userId);
	GetAccNo(accNo);
	int count = apiProxyWrapper.SPAPI_GetTradeCount(userId, accNo);
	// printf("\n Acc: %s,Trade Count:%d", accNo,count);
	sprintf(msg, "%d", count);
}

// void ApiGateway::GetAllTrade(std::vector<char*> cmd, char* msg)
void ApiGateway::GetAllTrades(char* msg)
{
	int rc;
	char userId[16], accNo[16];
	GetUserId(userId);
	GetAccNo(accNo);

	int lsize =  apiProxyWrapper.SPAPI_GetTradeCount(userId, accNo);
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
	rc = apiProxyWrapper.SPAPI_GetAllTradesByArray(userId, accNo, apiTradeList);
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

// void ApiGateway::SubscribeUninitPrice(int idx)
void ApiGateway::SubscribePrice(std::vector<char*> cmd, char* msg)
{	
	if (cmd.size() != 3)
		return;
	char userId[16];
	GetUserId(userId); 
	int tc = atoi(cmd[2]);
	int rc = apiProxyWrapper.SPAPI_SubscribePrice(userId, cmd[1], tc);
	sprintf(msg, "%d", rc);
}

// void ApiGateway::SubscribeQuoteRequest()
void ApiGateway::SubscribeQuoteRequest(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 3)
		return;
	char userId[16];
	GetUserId(userId); 
	int tc = atoi(cmd[2]);
	int rc = apiProxyWrapper.SPAPI_SubscribeQuoteRequest(userId, cmd[1], tc);
	sprintf(msg, "%d", rc);
}

// void ApiGateway::SubscribeAllQuoteRequest()
void ApiGateway::SubscribeAllQuoteRequest(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 2)
		return;
	char userId[16];
	GetUserId(userId); 
	int tc = atoi(cmd[1]);
	int rc = apiProxyWrapper.SPAPI_SubscribeAllQuoteRequest(userId, tc);
	sprintf(msg, "%d", rc);
}

void ApiGateway::GetPriceByCode(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 2)
		return;

	SPApiPrice price;
	char user_id[16];
	GetUserId(user_id);
	int rc = apiProxyWrapper.SPAPI_GetPriceByCode(user_id, cmd[1], &price);

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
			"%d;%f;%f;%d;%s;%s;%d;%d;%d;%d;%d;%d;%d"
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

void ApiGateway::SubscribeTicker(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 3)
		return;
	char userId[16];
	GetUserId(userId); 
	int tc = atoi(cmd[2]);
	int rc = apiProxyWrapper.SPAPI_SubscribeTicker(userId, cmd[1], tc);
	sprintf(msg, "%d", rc);
}

// void ApiGateway::UninitTicker()
// {
// int rc;
// char prodcode[16], userId[16];

// 	GetUserId(userId);
// 	printf("\n>>>>>>>>Input Uninit Ticker ProdCode: ");	
// 	scanf("%s",&prodcode);
// 	printf("\n>>>>>>>>Uninit Ticker prodCode: %s", prodcode);
// 	rc = apiProxyWrapper.SPAPI_SubscribeTicker(userId, prodcode, 0);
// 	if (rc != 0)printf("\SubscribeTicker return:%d", rc);
// }


void ApiGateway::GetAccInfo(char* msg)
{
	SPApiAccInfo acc_info;
	int rc;
	char user[16];

	GetUserId(user);
	memset(&acc_info, 0, sizeof(SPApiAccInfo));
	rc = apiProxyWrapper.SPAPI_GetAccInfo(user, &acc_info);
	if (rc == 0)
	{
		// printf("\nAccInfo: acc_no: %s  AE:%s  BaseCcy:%s,  MarginClass:%s, NAV:%f, BuyingPower:%f, CashBal:%f, MarginCall:%f, CommodityPL:%f, LockupAmt:%f, Loan2MR:%f, Loan2MV:%f, AccName:%s", acc_info.ClientId, acc_info.AEId, acc_info.BaseCcy, acc_info.MarginClass,acc_info.NAV,acc_info.BuyingPower,acc_info.CashBal,acc_info.MarginCall,acc_info.CommodityPL,acc_info.LockupAmt, acc_info.LoanToMR, acc_info.LoanToMV, acc_info.AccName);
	    // //string str = Big2Gb(acc_info.AccName);
		// //printf("\nAccInfo: AccName>>>Chinese simplified: %s", str.c_str());
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

void ApiGateway::GetAccBalCount(char* msg)
{
	int count;
	char user[16];
	
	GetUserId(user);
	count = apiProxyWrapper.SPAPI_GetAccBalCount(user);
	sprintf(msg, "%d", count);
}

void ApiGateway::GetAllAccBal(std::vector<char*> cmd, char* msg)
{
	int rc;
	char userId[16], accNo[16];
	GetUserId(userId);
	GetAccNo(accNo);
	
	int lsize =  apiProxyWrapper.SPAPI_GetAccBalCount(userId);
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
	rc = apiProxyWrapper.SPAPI_GetAllAccBalByArray(accNo, apiAccBalList);
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

void ApiGateway::GetAccBalByCurrency(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 2)
		return;
	SPApiAccBal accBal;
	// int rc;
	char user[16];

	GetUserId(user);
	strcpy(accBal.Ccy, cmd[1]);
	int rc = apiProxyWrapper.SPAPI_GetAccBalByCurrency(user, accBal.Ccy, &accBal);
	
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

// void ApiGateway::GetConnectionStatus(std::vector<char*> cmd, char* msg)
void ApiGateway::GetLoginStatus(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 2)
		return;
	int status_Id = atoi(cmd[1]);
	int rc = apiProxyWrapper.SPAPI_GetLoginStatus(user_id, status_Id);
	sprintf(msg, "%d", rc);
}

void ApiGateway::GetCcyRateByCcy(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 2)
		return;
	double rate;
	char user[16];
	GetUserId(user);
	int rc = apiProxyWrapper.SPAPI_GetCcyRateByCcy(user, cmd[1], rate);
	if (rc == 0)
		sprintf(msg, "%f", rate);
	else
		sprintf(msg, "%d", rc);
}

// void ApiGateway::ChangePassword()
void  ApiGateway::ChangePassword(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 2)
		return;
	char userId[16];
	GetUserId(userId);
	
	char pwd[16];
	GetPassword(pwd);
	// int rc = apiProxyWrapper.SPAPI_ChangePassword(userId, cmd[1], cmd[1]);
	int rc = apiProxyWrapper.SPAPI_ChangePassword(userId, pwd, pwd);
	sprintf(msg, "%d", rc);
}

// void ApiGateway::SetApiLogPath()
// {
// int rc;
// char path[500];

// 	printf("\n Set Log Path : ");		scanf("%s",path);
// 	rc = apiProxyWrapper.SPAPI_SetApiLogPath(path);
// 	printf("\n[%s]Set Api Log Path Reply:%d ",acc_no,rc);
// }

// void ApiGateway::LoadProductList()
// {
// int idx;

//     // printf("\n>>>Input Type:(1: ByInstCode, 2:ByMarketCode ) ");	scanf("%d",&idx);
// 	// switch(idx)
// 	// {
// 	// 	case 1: LoadProductInfoListByCode();              break;
// 	// 	case 2: LoadProductInfoListByMarket();        break;
// 	// }
// }

void ApiGateway::LoadProductInfoListByMarket(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 2)
		return;
	int rc = apiProxyWrapper.SPAPI_LoadProductInfoListByMarket(cmd[1]);
	sprintf(msg, "%d", rc);
}

void ApiGateway::LoadProductInfoListByCode(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 2)
		return;
	int rc = apiProxyWrapper.SPAPI_LoadProductInfoListByCode(cmd[1]);
	sprintf(msg, "%d", rc);
}

void ApiGateway::GetProductCount(char* msg)
{
	int count = apiProxyWrapper.SPAPI_GetProductCount();
	sprintf(msg, "%d", count);
}

// void ApiGateway::GetProduct(char* msg)		
// {
// 	int rc;
	
// 	int lsize =  apiProxyWrapper.SPAPI_GetProductCount();
// 	if (lsize <= 0) {		
// 		printf("\n Empty Product Lists, return : %d \n", rc);
// 		sprintf(msg, "%d", rc);
// 		return;
// 	}
// 	char *MSGFORMAT;
// 	MSGFORMAT = (char *) malloc( IO_BUFFER_SIZE );
// 	char *MSGFORMAT1;
// 	MSGFORMAT1 = (char *) malloc( IO_BUFFER_SIZE );
// 	sprintf(
// 		MSGFORMAT1, 
// 		"%s",
// 		// "%s;%d;%s;%s;%s;%d;%d;%d;%d;%s;%s;%d;%d"
// 		"%s"
// 		);
// 	sprintf(msg, "%s", "");
	
// 	SPApiProduct *apiProdList;
// 	apiProdList = (SPApiProduct *)malloc(lsize * sizeof(SPApiProduct));
// 	rc = apiProxyWrapper.SPAPI_GetProductByArray(apiProdList);
// 	if (rc != 0){
// 		printf("\n GetProduct, return : %d \n", rc);
// 		sprintf(msg, "%d", rc);
// 		return;
// 	}
	
// 	for (int i = 0; i < lsize; i++) {
// 		SPApiProduct& prod = apiProdList[i];
// 		cout << prod.ProdCode << endl;
// 		if 		(i == lsize - 1)sprintf(MSGFORMAT, "%s",	MSGFORMAT1);
// 		else 					sprintf(MSGFORMAT, "%s;",	MSGFORMAT1);
// 		// Put into Buffer
// 		sprintf(
// 			msg + strlen(msg),
// 			MSGFORMAT,
// 			prod.ProdCode
// 			// prod.ProdType,
// 			// prod.ProdName,
// 			// prod.Underlying,
// 			// prod.InstCode,
// 			// prod.ExpiryDate,
// 			// prod.CallPut,
// 			// prod.Strike,
// 			// prod.LotSize,
// 			// prod.ProdName1,
// 			// prod.ProdName2,
// 			// prod.OptStyle,
// 			// prod.TickSize
// 			);	
// 	}
// 	free(apiProdList);
// 	free(MSGFORMAT);
// 	free(MSGFORMAT1);
// }
					
void ApiGateway::GetProductByCode(std::vector<char*> cmd, char* msg)	
{
	if (cmd.size() != 2)
		return;
	SPApiProduct prod;
	int rc = apiProxyWrapper.SPAPI_GetProductByCode(cmd[1], &prod);
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

void ApiGateway::LoadInstrumentList(char* msg)
{
	int rc = apiProxyWrapper.SPAPI_LoadInstrumentList();
	sprintf(msg, "%d", rc);
}

void ApiGateway::GetInstrumentCount(char* msg)	
{
	int count = apiProxyWrapper.SPAPI_GetInstrumentCount();
	sprintf(msg, "%d", count);
}	
				
// void ApiGateway::GetInstrument()	
// {
// int rc;
// vector<SPApiInstrument> apiInstList;

// 	rc = apiProxyWrapper.SPAPI_GetInstrument(apiInstList);
// 	if (rc != 0)printf("\n Get Instrument, return : %d ,Count:%d \n", rc, apiInstList.size());
// 	for (int i = 0; i < apiInstList.size(); i++) {
// 		SPApiInstrument& instrument = apiInstList[i];
// 		printf("\n Number:%d, InstCode=%s, InstName=%s, Ccy=%s, Margin=%f",i+1, instrument.InstCode, instrument.InstName, instrument.Ccy, instrument.Margin);
// 	}	
// 	if (apiInstList.size() == 0) printf("\n No Instrument \n");    
// }
							
void ApiGateway::GetInstrumentByCode(std::vector<char*> cmd, char* msg)
{
	if (cmd.size() != 2)
		return;
	SPApiInstrument instrument;
	int rc = apiProxyWrapper.SPAPI_GetInstrumentByCode(cmd[1], &instrument);
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

void ApiGateway::SendAccControl()
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
	// 	rc = apiProxyWrapper.SPAPI_SendAccControl(userId, accNo, CTRLMASK_CTRL_LEVEL, ctrl_level);
	// }
	// else if (ctrl_mask == CTRLMASK_KICKOUT)
	// {
	// 	rc = apiProxyWrapper.SPAPI_SendAccControl(userId, accNo, CTRLMASK_KICKOUT, 0);
	// }
	// printf("\nSend Acc Control Report Reply:%d ",rc);  
}
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ApiGateway::OnLoginReply(char *user_id, long ret_code,char *ret_msg)
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

void ApiGateway::OnConnectedReply(long host_type, long con_status)
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

void ApiGateway::OnApiOrderRequestFailed(tinyint action, const SPApiOrder *order, long err_code, char *err_msg)
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
void ApiGateway::OnApiOrderReport(long rec_no, const SPApiOrder *order)
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

void ApiGateway::OnApiOrderBeforeSendReport(const SPApiOrder *order)
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

void ApiGateway::OnAccountLoginReply(char *accNo, long ret_code, char* ret_msg)
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


void ApiGateway::OnAccountLogoutReply(char *accNo, long ret_code, char* ret_msg)
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

void ApiGateway::OnAccountInfoPush(const SPApiAccInfo *acc_info)
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

void ApiGateway::OnAccountPositionPush(const SPApiPos *pos)
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

void ApiGateway::OnUpdatedAccountPositionPush(const SPApiPos *pos)
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

void ApiGateway::OnUpdatedAccountBalancePush(const SPApiAccBal *acc_bal)
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

void ApiGateway::OnApiTradeReport(long rec_no, const SPApiTrade *trade)
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

// void ApiGateway::rstpcount()
// {
// 	pcount = 0;
// }

void ApiGateway::OnApiPriceUpdate(const SPApiPrice *price)
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
		"%d;%f;%f;%d;%s;%s;%u;%d;%d;%d;%d;%d;%d"
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

void ApiGateway::OnApiTickerUpdate(const SPApiTicker *ticker)
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

void ApiGateway::OnPswChangeReply(long ret_code, char *ret_msg)
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

void ApiGateway::OnProductListByCodeReply(long req_id, char *inst_code, bool is_ready, char *ret_msg)
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

void ApiGateway::OnInstrumentListReply(long req_id, bool is_ready, char *ret_msg)
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

void ApiGateway::OnBusinessDateReply(long business_date)
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

void ApiGateway::OnApiAccountControlReply(long ret_code, char *ret_msg)
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

void ApiGateway::OnApiLoadTradeReadyPush(long rec_no, const SPApiTrade *trade)
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


void ApiGateway::OnApiMMOrderBeforeSendReport(SPApiMMOrder *mm_order)
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

void ApiGateway::OnApiMMOrderRequestFailed(SPApiMMOrder *mm_order, long err_code, char *err_msg)
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

void ApiGateway::OnApiQuoteRequestReceived(char *product_code, char buy_sell, long qty)
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