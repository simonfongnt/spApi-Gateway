#ifndef spGatewayH
#define spGatewayH

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include "spapidll.h"

#include "stdafx.h"
#include <windows.h>
// #include <winsock.h>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <time.h> 
#include <thread>

#include <string>
// #include <iostream>
#include <fstream>
#include <assert.h>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>

#pragma comment(lib, "ws2_32.lib")

#define CONFIGPATH "const.txt"
#define LOGINPATH "login.txt"

#define DatatypeInitialize						128
#define DatatypeSetLoginInfo					129
#define DatatypeLogin							130
#define DatatypeGetLoginStatus					131
#define DatatypeAddOrder						132
#define DatatypeAddInactiveOrder				133
#define DatatypeChangeOrder						144
#define DatatypeChangeOrderBy					145
#define DatatypeDeleteOrderBy					146
#define DatatypeDeleteAllOrders					147
#define DatatypeActivateAllOrders				148
#define DatatypeInactivateAllOrders				149
#define DatatypeActivateOrderBy					150
#define DatatypeInactivateOrderBy				151
#define DatatypeGetOrderCount					152
#define DatatypeGetOrderByOrderNo				153
#define DatatypeGetActiveOrders					154
#define DatatypeGetPosCount						155
#define DatatypeGetPosByProduct					156
#define DatatypeUninitialize					157
#define DatatypeLogout							158
#define DatatypeAccountLogin					159
#define DatatypeAccountLogout					160
#define DatatypeGetTradeCount					161
#define DatatypeGetAllTrades					162
#define DatatypeSubscribePrice					163
#define DatatypeSubscribeTicker					164
#define DatatypeChangePassword					165
#define DatatypeGetDllVersion					166
#define DatatypeGetAccBalCount					167
#define DatatypeGetAccBalByCurrency				168
#define DatatypeGetAllAccBal					169
#define DatatypeGetCcyRateByCcy					170
#define DatatypeGetAccInfo						171
#define DatatypeGetPriceByCode					172
#define DatatypeSetApiLogPath					173
#define DatatypeLoadProductInfoListByCode		174
#define DatatypeLoadProductInfoListByMarket		175
#define DatatypeGetProductCount					176
#define DatatypeGetProduct						177
#define DatatypeGetProductByCode				178
#define DatatypeLoadInstrumentList				179
#define DatatypeGetInstrumentCount				180
#define DatatypeGetInstrument					181
#define DatatypeGetInstrumentByCode				182
#define DatatypeSetLanguageId					183
#define DatatypeSendMarketMakingOrder			184
#define DatatypeSubscribeQuoteRequest			185
#define DatatypeSubscribeAllQuoteRequest		186
#define DatatypeGetAllAccBalByArray				187
#define DatatypeGetOrdersByArray				188
#define DatatypeGetAllTradesByArray				189
#define DatatypeGetInstrumentByArray			190
#define DatatypeGetProductByArray				191
#define DatatypeGetAllPos						192
#define DatatypeGetAllPosByArray				193
#define DatatypeSendAccControl					194

// #define DatatypeGetAccNo 						16
// #define DatatypeGetUserId 						17
// #define DatatypeHelpInfo 						18
// #define DatatypeLogin 							19
// #define DatatypeLogout 							20

// #define DatatypeAddOrder 						21
#define DatatypeSendMMOrder 					22
#define DatatypeDeleteOrder 					23
// #define DatatypeDeleteAllOrders 				24
// #define DatatypeChangeOrder 					25
// #define DatatypeChangeOrderBy 					26
// #define DatatypeGetActiveOrders 				27
#define DatatypeSetOrderInactive 				28
// #define DatatypeGetOrderCount 					29

#define DatatypePosCount 						30
// #define DatatypeGetPosByProduct 				31
// #define DatatypeGetAllPos 						32
// #define DatatypeGetAllPosByArray 				33
#define DatatypeGetPos 							34

#define DatatypeTradeCount 						35
// #define DatatypeGetAllTrade 					36

// #define DatatypeSubscribeUninitPrice 			37
// #define DatatypeSubscribePrice				37
// #define DatatypeGetPriceByCode 					38
// #define DatatypeSubscribeTicker 				39
#define DatatypeUninitTicker 					40
// #define DatatypeSubscribeQuoteRequest 			41
// #define DatatypeSubscribeAllQuoteRequest		42

// #define DatatypeGetAccInfo 						43
// #define DatatypeGetAccBalCount 					44
// #define DatatypeGetAllAccBal 					45
// #define DatatypeGetAccBalByCurrency 			46
// #define DatatypeGetConnectionStatus 			47
// #define DatatypeGetLoginStatus 					47
// #define DatatypeGetCcyRateByCcy 				48

// #define DatatypeChangePassword 					49
// #define DatatypeSetApiLogPath 					50
// #define DatatypeAccountLogin 					51
// #define DatatypeAccountLogout 					52

#define DatatypeLoadProductList 				53
// #define DatatypeLoadProductInfoListByMarket		54
// #define DatatypeLoadProductInfoListByCode 		55
// #define DatatypeGetProductCount 				56
// #define DatatypeGetProduct 						57
// #define DatatypeGetProductByCode 				58

// #define DatatypeLoadInstrumentList 				59
// #define DatatypeGetInstrumentCount 				60
// #define DatatypeGetInstrument 					61
// #define DatatypeGetInstrumentByCode 			62
// #define DatatypeSendAccControl 					63

#define DatatypeOnLoginReply 					64
#define DatatypeOnConnectedReply 				65
#define DatatypeOnApiOrderRequestFailed 		66
#define DatatypeOnApiOrderReport 				67
#define DatatypeOnApiOrderBeforeSendReport 		68
#define DatatypeOnAccountLoginReply 			69
#define DatatypeOnAccountLogoutReply 			70
#define DatatypeOnAccountInfoPush 				71
#define DatatypeOnAccountPositionPush 			72
#define DatatypeOnUpdatedAccountPositionPush 	73
#define DatatypeOnUpdatedAccountBalancePush 	74
#define DatatypeOnApiTradeReport 				75
#define DatatypeOnApiPriceUpdate 				76
#define DatatypeOnApiTickerUpdate 				77
#define DatatypeOnPswChangeReply 				78
#define DatatypeOnProductListByCodeReply 		79
#define DatatypeOnInstrumentListReply 			80
#define DatatypeOnBusinessDateReply 			81
#define DatatypeOnApiMMOrderBeforeSendReport 	82
#define DatatypeOnApiMMOrderRequestFailed 		83
#define DatatypeOnApiQuoteRequestReceived 		84
#define DatatypeOnApiAccountControlReply 		85
#define DatatypeOnApiLoadTradeReadyPush 		86

#define PUBLISH_BUFFER_SIZE		8192
#define IO_BUFFER_SIZE			16384

#define TRUE             1
#define FALSE            0

void SPDLLCALL OnLoginReply(char *user_id, long ret_code, char *ret_msg);	
void SPDLLCALL OnConnectedReply(long host_type,  long con_status);
void SPDLLCALL OnApiOrderRequestFailed(tinyint action, SPApiOrder *order, long err_code, char *err_msg);   
void SPDLLCALL OnApiOrderReport(long rec_no, SPApiOrder *order);								  
void SPDLLCALL OnApiOrderBeforeSendReport(SPApiOrder *order);	
void SPDLLCALL OnAccountLoginReply(char *accNo, long ret_code, char* ret_msg);
void SPDLLCALL OnAccountLogoutReply(char *accNo, long ret_code, char* ret_msg);
void SPDLLCALL OnAccountInfoPush(SPApiAccInfo *acc_info);
void SPDLLCALL OnAccountPositionPush(SPApiPos *pos);
void SPDLLCALL OnUpdatedAccountPositionPush(SPApiPos *pos);
void SPDLLCALL OnUpdatedAccountBalancePush(SPApiAccBal *acc_bal);
void SPDLLCALL OnApiTradeReport(long rec_no, SPApiTrade *trade);
void SPDLLCALL OnApiPriceUpdate(SPApiPrice *price);
void SPDLLCALL OnApiTickerUpdate(SPApiTicker *ticker);
void SPDLLCALL OnPswChangeReply(long ret_code, char *ret_msg);
void SPDLLCALL OnProductListByCodeReply(long req_id, char *inst_code, bool is_ready, char *ret_msg);
void SPDLLCALL OnInstrumentListReply(long req_id, bool is_ready, char *ret_msg);							
void SPDLLCALL OnBusinessDateReply(long business_date);
void SPDLLCALL OnApiMMOrderBeforeSendReport(SPApiMMOrder *mm_order);
void SPDLLCALL OnApiMMOrderRequestFailed(SPApiMMOrder *mm_order, long err_code, char *err_msg);
void SPDLLCALL OnApiQuoteRequestReceived(char *product_code, char buy_sell, long qty);
void SPDLLCALL OnApiAccountControlReply(long ret_code, char *ret_msg);
void SPDLLCALL OnApiLoadTradeReadyPush(long rec_no, SPApiTrade *trade);

static p_SPAPI_RegisterLoginReply				 	SPAPI_RegisterLoginReply;
static p_SPAPI_RegisterConnectingReply          	SPAPI_RegisterConnectingReply;
static p_SPAPI_RegisterOrderReport              	SPAPI_RegisterOrderReport;
static p_SPAPI_RegisterOrderRequestFailed       	SPAPI_RegisterOrderRequestFailed;
static p_SPAPI_RegisterOrderBeforeSendReport    	SPAPI_RegisterOrderBeforeSendReport;
static p_SPAPI_RegisterAccountLoginReply        	SPAPI_RegisterAccountLoginReply;
static p_SPAPI_RegisterAccountLogoutReply       	SPAPI_RegisterAccountLogoutReply;
static p_SPAPI_RegisterAccountInfoPush          	SPAPI_RegisterAccountInfoPush;
static p_SPAPI_RegisterAccountPositionPush      	SPAPI_RegisterAccountPositionPush;
static p_SPAPI_RegisterUpdatedAccountPositionPush   SPAPI_RegisterUpdatedAccountPositionPush;
static p_SPAPI_RegisterUpdatedAccountBalancePush    SPAPI_RegisterUpdatedAccountBalancePush;
static p_SPAPI_RegisterTradeReport              	SPAPI_RegisterTradeReport;
static p_SPAPI_RegisterApiPriceUpdate           	SPAPI_RegisterApiPriceUpdate;
static p_SPAPI_RegisterTickerUpdate             	SPAPI_RegisterTickerUpdate;
static p_SPAPI_RegisterPswChangeReply           	SPAPI_RegisterPswChangeReply;
static p_SPAPI_RegisterProductListByCodeReply   	SPAPI_RegisterProductListByCodeReply;
static p_SPAPI_RegisterInstrumentListReply      	SPAPI_RegisterInstrumentListReply;
static p_SPAPI_RegisterBusinessDateReply        	SPAPI_RegisterBusinessDateReply;
static p_SPAPI_RegisterMMOrderRequestFailed         SPAPI_RegisterMMOrderRequestFailed;
static p_SPAPI_RegisterMMOrderBeforeSendReport      SPAPI_RegisterMMOrderBeforeSendReport;
static p_SPAPI_RegisterQuoteRequestReceivedReport   SPAPI_RegisterQuoteRequestReceivedReport;
static p_SPAPI_RegisterAccountControlReply          SPAPI_RegisterAccountControlReply;
static p_SPAPI_RegisterLoadTradeReadyPush       	SPAPI_RegisterLoadTradeReadyPush;


static p_SPAPI_GetDllVersion      			SPAPI_GetDllVersion;		
static p_SPAPI_Initialize		   			SPAPI_Initialize;			
static p_SPAPI_SetLoginInfo	   				SPAPI_SetLoginInfo;			
static p_SPAPI_Login			   			SPAPI_Login;	
static p_SPAPI_Logout             			SPAPI_Logout;
static p_SPAPI_AccountLogin        			SPAPI_AccountLogin;        
static p_SPAPI_AccountLogout       			SPAPI_AccountLogout;       
static p_SPAPI_Uninitialize        			SPAPI_Uninitialize;

static p_SPAPI_AddOrder		   				SPAPI_AddOrder;				
static p_SPAPI_AddInactiveOrder   			SPAPI_AddInactiveOrder;
static p_SPAPI_ChangeOrder        			SPAPI_ChangeOrder;
static p_SPAPI_ChangeOrderBy      			SPAPI_ChangeOrderBy;
static p_SPAPI_DeleteOrderBy      			SPAPI_DeleteOrderBy;
static p_SPAPI_DeleteAllOrders    			SPAPI_DeleteAllOrders;
static p_SPAPI_ActivateAllOrders  			SPAPI_ActivateAllOrders;
static p_SPAPI_InactivateAllOrders  		SPAPI_InactivateAllOrders;
static p_SPAPI_ActivateOrderBy      		SPAPI_ActivateOrderBy;
static p_SPAPI_InactivateOrderBy    		SPAPI_InactivateOrderBy;
static p_SPAPI_GetOrderCount        		SPAPI_GetOrderCount;
static p_SPAPI_GetOrderByOrderNo    		SPAPI_GetOrderByOrderNo;
static p_SPAPI_GetActiveOrders      		SPAPI_GetActiveOrders;
static p_SPAPI_SendMarketMakingOrder  		SPAPI_SendMarketMakingOrder;

static p_SPAPI_GetPosCount        			SPAPI_GetPosCount;
static p_SPAPI_GetPosByProduct    			SPAPI_GetPosByProduct;		
static p_SPAPI_GetAllPos          			SPAPI_GetAllPos;
static p_SPAPI_GetAllPosByArray   			SPAPI_GetAllPosByArray; 

static p_SPAPI_GetTradeCount 				SPAPI_GetTradeCount;
static p_SPAPI_GetAllTrades  				SPAPI_GetAllTrades;

static p_SPAPI_SubscribePrice           	SPAPI_SubscribePrice;
static p_SPAPI_SubscribeTicker          	SPAPI_SubscribeTicker;
static p_SPAPI_GetPriceByCode	        	SPAPI_GetPriceByCode;		
static p_SPAPI_SubscribeQuoteRequest    	SPAPI_SubscribeQuoteRequest;
static p_SPAPI_SubscribeAllQuoteRequest 	SPAPI_SubscribeAllQuoteRequest;


static p_SPAPI_ChangePassword       		SPAPI_ChangePassword;

static p_SPAPI_GetAccInfo           		SPAPI_GetAccInfo;		
static p_SPAPI_GetAccBalCount       		SPAPI_GetAccBalCount;
static p_SPAPI_GetAccBalByCurrency  		SPAPI_GetAccBalByCurrency; 
static p_SPAPI_GetAllAccBal         		SPAPI_GetAllAccBal;

static p_SPAPI_GetLoginStatus      			SPAPI_GetLoginStatus;
static p_SPAPI_GetCcyRateByCcy     			SPAPI_GetCcyRateByCcy;
static p_SPAPI_SetApiLogPath       			SPAPI_SetApiLogPath;

static p_SPAPI_GetProductCount           	SPAPI_GetProductCount;		
static p_SPAPI_GetProduct                	SPAPI_GetProduct;			
static p_SPAPI_GetProductByCode          	SPAPI_GetProductByCode;	
static p_SPAPI_LoadProductInfoListByCode 	SPAPI_LoadProductInfoListByCode;
static p_SPAPI_LoadProductInfoListByMarket 	SPAPI_LoadProductInfoListByMarket;

static p_SPAPI_LoadInstrumentList   		SPAPI_LoadInstrumentList;	
static p_SPAPI_GetInstrumentCount   		SPAPI_GetInstrumentCount;   
static p_SPAPI_GetInstrument        		SPAPI_GetInstrument;			
static p_SPAPI_GetInstrumentByCode  		SPAPI_GetInstrumentByCode; 

static p_SPAPI_SetLanguageId        		SPAPI_SetLanguageId;

static p_SPAPI_GetAllTradesByArray  		SPAPI_GetAllTradesByArray;
static p_SPAPI_GetOrdersByArray     		SPAPI_GetOrdersByArray;
static p_SPAPI_GetAllAccBalByArray  		SPAPI_GetAllAccBalByArray;
static p_SPAPI_GetInstrumentByArray 		SPAPI_GetInstrumentByArray;
static p_SPAPI_GetProductByArray    		SPAPI_GetProductByArray;
static p_SPAPI_SendAccControl       		SPAPI_SendAccControl;


void InitAPI();
void Unload();
void RegisterDLL();

void GetAccNo(char *acc);
void GetUserId(char *user);
void GetPassword(char *pwd);
void Login(char* msg);
void Logout(char* msg);

void AddOrder(std::vector<char*> cmd, char* msg);
void AddInactiveOrder(std::vector<char*> cmd, char* msg);

void ActivateAllOrders(std::vector<char*> cmd, char* msg);
void ActivateOrderBy(std::vector<char*> cmd, char* msg);

void InactivateAllOrders(std::vector<char*> cmd, char* msg);
void InactivateOrderBy(std::vector<char*> cmd, char* msg);

void SendMMOrder();

// void ChangeOrder();
void ChangeOrderBy(std::vector<char*> cmd, char* msg);
void GetActiveOrders(std::vector<char*> cmd, char* msg);
// void GetActiveOrders(std::vector<char*> cmd);

void DeleteOrderBy(std::vector<char*> cmd, char* msg);
void DeleteAllOrders(std::vector<char*> cmd, char* msg);

void SetOrderInactive();
void GetOrderCount();
void GetActiveOrders();
void GetOrderByOrderNo();
// void GetOrder();


void GetOrderCount(char* msg);

void GetPosCount(char* msg);
void GetPosByProduct(std::vector<char*> cmd, char* msg);
void GetAllPos(char* msg);
// void GetAllPosByArray(std::vector<char*> cmd, char* msg);
// void GetPos(char* msg);

void GetTradeCount(char* msg);
// void GetAllTrade(std::vector<char*> cmd, char* msg);
void GetAllTrades(char* msg);

// void SubscribeUninitPrice(int idx);
void SubscribePrice(std::vector<char*> cmd, char* msg);
void GetPriceByCode(std::vector<char*> cmd, char* msg);
void SubscribeTicker(std::vector<char*> cmd, char* msg);
// void UninitTicker();
void SubscribeQuoteRequest(std::vector<char*> cmd, char* msg);
void SubscribeAllQuoteRequest(std::vector<char*> cmd, char* msg);

void GetAccInfo(char* msg);
void GetAccBalCount(char* msg);
void GetAllAccBal(std::vector<char*> cmd, char* msg);
void GetAccBalByCurrency(std::vector<char*> cmd, char* msg);
// void GetConnectionStatus(std::vector<char*> cmd, char* msg);
void GetLoginStatus(std::vector<char*> cmd, char* msg);
void GetCcyRateByCcy(std::vector<char*> cmd, char* msg);

void ChangePassword(std::vector<char*> cmd, char* msg);
// void SetApiLogPath();
void AccountLogin(char* msg);
void AccountLogout(char* msg);
    
// void LoadProductList();
void LoadProductInfoListByMarket(std::vector<char*> cmd, char* msg);
void LoadProductInfoListByCode(std::vector<char*> cmd, char* msg);
void GetProductCount(char* msg);
void GetProduct(char* msg);
void GetProductByCode(std::vector<char*> cmd, char* msg);

void LoadInstrumentList(char* msg);
void GetInstrumentCount(char* msg);
// void GetInstrument();
void GetInstrumentByCode(std::vector<char*> cmd, char* msg);
void SendAccControl();

// static char *UserStatus(long status_id);
// static char *OutputOrderStatus(char status);
// static char *OutputErrorData(int idx);
// static void CheckAO(double price, char *new_price);
// static char *ConnectionStatus(int status);
// static string Big2Gb(char* sBig);

static const int nBufSize = 256;
static char host[256],user_id[256],password[256],acc_no[16], license[256], app_id[16];
static char npassword[256];
// static bool login_status = false;			
static int  port;							
// static TCHAR T1[nBufSize];
// static TCHAR T2[nBufSize];
// static int s1, ms1;
// static int s2, ms2;
// static int ATotal=0;
// static int ACount=1;
// static int AUpated=0;
// static int LoginCount=0;

// Exit Criteria
static time_t thists, prevts;
static const int tsConnectTimeout 	= 30;
static const int tsPollingTimeout 	= 6;
static bool isConnected 			= false;
static bool isPolling 				= false;

static int rc;

static int ioport;
static int iosock;
// static socklen_t iolen;
static int iolen;
static struct sockaddr_in ioserv;
// static fd_set master_set, working_set;
// static FD_SET master_set, working_set;
static struct timeval timeout;

static int pubport;
static int pubsock;
static struct sockaddr_in pserv;

static void IPCpub(char *msg);
void IPCClean();
int IPCrecv();

void LoadConfig(char* config_path);
void LoadLogin(char* login_path);
void CheckPassword(char* login_path);

void ReplyCommands(
	int fd,
	std::vector<char*> cmd
	);


#endif