//---------------------------------------------------------------------------

#ifndef spGatewayH
#define spGatewayH
//---------------------------------------------------------------------------
#include<string.h>
#include "ApiProxyWrapper.h"
#include "ApiProxyWrapperReply.h"


#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// #include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

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

#define PUBLISH_BUFFER_SIZE		4096
#define IO_BUFFER_SIZE			16384

#define TRUE             1
#define FALSE            0

class ApiGateway :  public ApiProxyWrapperReply
{
public:
	// Exit Criteria
	time_t thists, prevts;
	const int tsConnectTimeout 	= 30;
	const int tsPollingTimeout 	= 6;
	bool isConnected 			= false;
	bool isPolling 				= false;

	// int rc, on = 1;
	int rc;
	
	int ioport;
    int iosock;
    socklen_t iolen;
    struct sockaddr_in ioserv;
	fd_set master_set, working_set;
    struct timeval timeout;

	int pubport;
    int pubsock;
    socklen_t plen;
    struct sockaddr_in pserv;

	void IPCpub(char *msg);
	void IPCClean();
	int IPCrecv();

	char host[256],user_id[256],password[256],acc_no[16], license[256], app_id[16];
	char npassword[256];
	bool login_status = false;			//��¼״̬���� //�n�����A�аO
	int  port;							//��¼�˿� //�n���ݤf
	int ACount=1;

	ApiGateway(void);
	~ApiGateway(void);

	void InitAPI();
    void Unload();
	void RegisterReply();

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
	// void DeleteOrder(std::vector<char*> cmd, char* msg);
	void DeleteOrderBy(std::vector<char*> cmd, char* msg);
	void DeleteAllOrders(std::vector<char*> cmd, char* msg);
	// void ChangeOrder(); 
	void ChangeOrderBy(std::vector<char*> cmd, char* msg);
	void GetActiveOrders(std::vector<char*> cmd, char* msg);
	// void SetOrderInactive();
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

	virtual void OnLoginReply(char *user_id, long ret_code,char *ret_msg);
	virtual void OnConnectedReply(long host_type, long con_status);
	virtual void OnApiOrderRequestFailed(tinyint action, const SPApiOrder *order, long err_code, char *err_msg);
	virtual void OnApiOrderReport(long rec_no, const SPApiOrder *order);
	virtual void OnApiOrderBeforeSendReport(const SPApiOrder *order);
	virtual void OnAccountLoginReply(char *accNo, long ret_code, char* ret_msg);
	virtual void OnAccountLogoutReply(char *accNo, long ret_code, char* ret_msg);
	virtual void OnAccountInfoPush(const SPApiAccInfo *acc_info);
	virtual void OnAccountPositionPush(const SPApiPos *pos);
	virtual void OnUpdatedAccountPositionPush(const SPApiPos *pos);
	virtual void OnUpdatedAccountBalancePush(const SPApiAccBal *acc_bal);
	virtual void OnApiTradeReport(long rec_no, const SPApiTrade *trade);
	virtual void OnApiPriceUpdate(const SPApiPrice *price);
	virtual void OnApiTickerUpdate(const SPApiTicker *ticker);
	virtual void OnPswChangeReply(long ret_code, char *ret_msg);
	virtual void OnProductListByCodeReply(long req_id, char *inst_code, bool is_ready, char *ret_msg);
	virtual void OnInstrumentListReply(long req_id, bool is_ready, char *ret_msg);
	virtual void OnBusinessDateReply(long business_date);
	virtual void OnApiMMOrderBeforeSendReport(SPApiMMOrder *mm_order);
	virtual void OnApiMMOrderRequestFailed(SPApiMMOrder *mm_order, long err_code, char *err_msg);
	virtual void OnApiQuoteRequestReceived(char *product_code, char buy_sell, long qty);
    virtual void OnApiAccountControlReply(long ret_code, char *ret_msg);
    virtual void OnApiLoadTradeReadyPush(long rec_no, const SPApiTrade *trade);
private:
	void LoadConfig(char* config_path);
	void LoadLogin(char* login_path);
	void CheckPassword(char* login_path);

	void ReplyCommands(
		int fd,
		std::vector<char*> cmd
		);

	ApiProxyWrapper apiProxyWrapper;
};

#endif
