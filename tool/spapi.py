from spStruct import *

import sys
import socket
import threading

import traceback

class EClient(
        # threading.Thread,
        ):
    def __init__(
            self,
            subHost,
            subPort,
            ioHost,
            ioPort,
            ):
        # threading.Thread  .__init__(self) 
        self.__subHost    = subHost
        self.__subPort    = subPort
        self.__ioHost     = ioHost
        self.__ioPort     = ioPort
        self.__initParams()

    def __initParams(
            self,
            ):
        self.subSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.subSocket.bind(
                (
                    # self.__subHost,
                    '',
                    self.__subPort
                    )
            )
        self.__subTh = threading.Thread(target = self.__subRun)
        self.__subTh.daemon   = True
        self.__subTh.start()

    # Subscription
    def __subRun(
            self,
            ):
        while True:
            m = self.subSocket.recvfrom(16384)
            datatype, datls = self.__Callback(m)

    # Raw Input
    def Input(
            self,
            input,
            ):
        if not input:
            return
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as ioSocket:
            ioSocket.connect(
                    (
                        self.__ioHost,
                        self.__ioPort,
                        )
                )
            ioSocket.sendall(str.encode(input))
            data = ioSocket.recv(16384)
        return repr(data)

    # Transmit to Client
    def Send(
            self,
            datatype,
            cmdls,
            ):
        message = self.__Encode(
            datatype,
            cmdls,
            )
        if not message:
            return
        # print(
        #     spDatatypeNum[datatype],
        #     datatype,            
        #     message,
        # )
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as ioSocket:
            ioSocket.connect(
                    (
                        self.__ioHost,
                        self.__ioPort,
                        )
                )
            # ioSocket.sendall(str.encode(input))
            ioSocket.sendall(str.encode(message))
            data = ioSocket.recv(16384)
        # print(repr(data)[2:-1])
        return self.__Decode(repr(data)[2:-1])

    def __Encode(
            self,
            datatype,
            cmdls,
            ):
        if (
                not datatype
            or  datatype not in spDatatypeNum
                ):
            return
        message = spDatatypeNum[datatype]
        for cmd in cmdls:
            try:
                message = message + ';' + cmd.String()
            except Exception as e:
                # print(
                #     '__Encode',
                #     e,
                # )
                message = message + ';' + str(cmd)
        return message

    def __Decode(
            self,
            message,
            ):
        datls = str(message).split(';')
        # print(
        #     datls
        # )
        # datatype = spDatatypeTag[datls[0]]
        # formatting
        for i in range(len(datls)):
            try:
                if datls[i][0] == '[' and datls[i][-1] == ']':
                    datls[i] = list(map(float, datls[i][1:-1].split(',')))
                elif '.' in datls[i]:
                    datls[i] = float(datls[i])
                else:
                    datls[i] = int(datls[i])    
            except Exception:
                pass
        return datls

    def __Callback(
            self,
            m,
            ):
        (data, address) = m
        try:
            message = data.decode('utf-8')
        except Exception as e:
            return None, None

        # datls = str(message).split(';')
        datls = self.__Decode(message)
        datatype = spDatatypeTag[str(datls[0])]
        # if datatype == 'DatatypeOnApiOrderReport':
        #     print(
        #         datls
        #     )
            
        # Callbacks
        if      datatype == 'DatatypeOnLoginReply':                 self.OnLoginReply                   (datls[1], int(datls[2]), datls[3],)
        elif    datatype == 'DatatypeOnConnectedReply':             self.OnConnectingReply              (int(datls[1]), int(datls[2]),)
        elif    datatype == 'DatatypeOnApiOrderRequestFailed':      self.OnApiOrderRequestFailed        (int(datls[1]), SPApiOrder(*datls[4:]), datls[2], datls[3], )
        elif    datatype == 'DatatypeOnApiOrderReport':             self.OnApiOrderReport               (int(datls[1]), SPApiOrder(*datls[2:]),)
        elif    datatype == 'DatatypeOnApiOrderBeforeSendReport':   self.OnApiOrderBeforeSendReport     (SPApiOrder(*datls[1:]),)
        elif    datatype == 'DatatypeOnAccountLoginReply':          self.OnAccountLoginReply            (datls[1], int(datls[2]), datls[3])
        elif    datatype == 'DatatypeOnAccountLogoutReply':         self.OnAccountLogoutReply           (datls[1], int(datls[2]), datls[3])
        elif    datatype == 'DatatypeOnAccountInfoPush':            self.OnAccountInfoPush              (SPApiAccInfo(*datls[1:]),)
        elif    datatype == 'DatatypeOnAccountPositionPush':        self.OnAccountPositionPush          (SPApiPos(*datls[1:]),)
        elif    datatype == 'DatatypeOnUpdatedAccountPositionPush': self.OnUpdatedAccountPositionPush   (SPApiPos(*datls[1:]),)
        elif    datatype == 'DatatypeOnUpdatedAccountBalancePush':  self.OnUpdatedAccountBalancePush    (SPApiAccBal(*datls[1:]),)
        elif    datatype == 'DatatypeOnApiTradeReport':             self.OnApiTradeReport               (int(datls[1]), SPApiTrade(*datls[2:]),)
        elif    datatype == 'DatatypeOnApiPriceUpdate':             self.OnApiPriceUpdate               (SPApiPrice(*datls[1:]),)
        elif    datatype == 'DatatypeOnApiTickerUpdate':            self.OnApiTickerUpdate              (SPApiTicker(*datls[1:]),)
        elif    datatype == 'DatatypeOnPswChangeReply':             self.OnPswChangeReply               (datls[1], datls[2],)
        elif    datatype == 'DatatypeOnProductListByCodeReply':     self.OnProductListByCodeReply       (int(datls[1]), datls[2], int(datls[3]), datls[4],)
        elif    datatype == 'DatatypeOnInstrumentListReply':        self.OnInstrumentListReply          (int(datls[1]), int(datls[2]), datls[3],)
        elif    datatype == 'DatatypeOnBusinessDateReply':          self.OnBusinessDateReply            (int(datls[1]),)
        elif    datatype == 'DatatypeOnApiMMOrderBeforeSendReport': self.OnApiMMOrderBeforeSendReport   (SPApiMMOrder(*datls[1:]),)
        elif    datatype == 'DatatypeOnApiMMOrderRequestFailed':    self.OnApiMMOrderRequestFailed      (int(datls[1]), datls[2], SPApiMMOrder(*datls[3:]),)
        elif    datatype == 'DatatypeOnApiQuoteRequestReceived':    self.OnApiQuoteRequestReceived      (datls[1], datls[2], datls[3],)
        elif    datatype == 'DatatypeOnApiAccountControlReply':     self.OnApiAccountControlReply       (int(datls[1]), datls[2],)
        elif    datatype == 'DatatypeOnApiLoadTradeReadyPush':      self.OnApiLoadTradeReadyPush        (int(datls[1]), SPApiTrade(*datls[2:]),)
        else:
            print(                
                datls,
            )
        return None, None
        
    # Callbacks
    def OnLoginReply(self, user_id, ret_code, ret_msg):
        print('#######', sys._getframe().f_code.co_name, '#######', )
    def OnConnectingReply(self, host_type, con_status):
        print('#######', sys._getframe().f_code.co_name, '#######', )
    def OnApiOrderRequestFailed(self, action, order, err_code, err_msg):
        print('#######', sys._getframe().f_code.co_name, '#######', )
    def OnApiOrderReport(self, rec_no, order):
        print('#######', sys._getframe().f_code.co_name, '#######', )
    def OnApiOrderBeforeSendReport(self, order):
        print('#######', sys._getframe().f_code.co_name, '#######', )
    def OnAccountLoginReply(self, accNo, ret_code, ret_msg):
        print('#######', sys._getframe().f_code.co_name, '#######', )
    def OnAccountLogoutReply(self, accNo, ret_code, ret_msg):
        print('#######', sys._getframe().f_code.co_name, '#######', )
    def OnAccountInfoPush(self, acc_info):
        print('#######', sys._getframe().f_code.co_name, '#######', )
    def OnAccountPositionPush(self, pos):
        print('#######', sys._getframe().f_code.co_name, '#######', )
    def OnUpdatedAccountPositionPush(self, pos):
        print('#######', sys._getframe().f_code.co_name, '#######', )
    def OnUpdatedAccountBalancePush(self, acc_bal):
        print('#######', sys._getframe().f_code.co_name, '#######', )
    def OnApiTradeReport(self, rec_no, trade):
        print('#######', sys._getframe().f_code.co_name, '#######', )
    def OnApiPriceUpdate(self, price):
        print('#######', sys._getframe().f_code.co_name, '#######', )
    def OnApiTickerUpdate(self, ticker):
        print('#######', sys._getframe().f_code.co_name, '#######', )
    def OnPswChangeReply(self, ret_code, ret_msg):
        print('#######', sys._getframe().f_code.co_name, '#######', )
    def OnProductListByCodeReply(self, req_id, inst_code, is_ready, ret_msg):
        print('#######', sys._getframe().f_code.co_name, '#######', )
    def OnInstrumentListReply(self, req_id, is_ready, ret_msg):
        print('#######', sys._getframe().f_code.co_name, '#######', )
    def OnBusinessDateReply(self, business_date):
        print('#######', sys._getframe().f_code.co_name, '#######', )
    def OnApiMMOrderBeforeSendReport(self, mm_order):
        print('#######', sys._getframe().f_code.co_name, '#######', )
    def OnApiMMOrderRequestFailed(self, mm_order, err_code, err_msg):
        print('#######', sys._getframe().f_code.co_name, '#######', )
    def OnApiQuoteRequestReceived(self, prod_code, buy_sell, qty):
        print('#######', sys._getframe().f_code.co_name, '#######', )
    def OnApiAccountControlReply(self, ret_code, ret_msg):
        print('#######', sys._getframe().f_code.co_name, '#######', )
    def OnApiLoadTradeReadyPush(self, rec_no, trade):
        print('#######', sys._getframe().f_code.co_name, '#######', )

    # API Functions
    # int SPAPI_Initialize();
    def SPAPI_Initialize(self):
        rcvals = self.Send("DatatypeInitialize", [],)
        return rcvals[0]
    # void SPAPI_SetLoginInfo(char *host, int port, char *license, char *app_id, char *user_id, char *password);
    def SPAPI_SetLoginInfo(self, host, port, license, app_id, user_id, password):
        rcvals = self.Send("DatatypeSetLoginInfo", [host, port, license, app_id, user_id, password],)
    # int SPAPI_Login();
    def SPAPI_Login(self, ):
        rcvals = self.Send("DatatypeLogin", [],)
        return rcvals[0]
    # int SPAPI_GetLoginStatus(char *user_id, short host_id);
    def SPAPI_GetLoginStatus(self, user_id, host_id):
        rcvals = self.Send("DatatypeGetLoginStatus", [user_id, host_id],)
        return rcvals[0]
    # int SPAPI_AddOrder(SPApiOrder *order);
    def SPAPI_AddOrder(self, order):
        rcvals = self.Send("DatatypeAddOrder", [order],)
        return rcvals[0]
    # int SPAPI_AddInactiveOrder(SPApiOrder* order);
    def SPAPI_AddInactiveOrder(self, order):
        rcvals = self.Send("DatatypeAddInactiveOrder", [order],)
        return rcvals[0]
    # int SPAPI_ChangeOrder(char *user_id, SPApiOrder* order, double org_price, long org_qty);
    def SPAPI_ChangeOrder(self, user_id, order, org_price, org_qty):
        rcvals = self.Send("DatatypeChangeOrder", [user_id, order, org_price, org_qty],)
        return rcvals[0]
    # int SPAPI_ChangeOrderBy(char *user_id, char *acc_no, long accOrderNo, double org_price, long org_qty, double newPrice, long newQty);
    def SPAPI_ChangeOrderBy(self, user_id, acc_no, accOrderNo, org_price, org_qty, newPrice, newQty):
        rcvals = self.Send("DatatypeChangeOrderBy", [user_id, acc_no, accOrderNo, org_price, org_qty, newPrice, newQty],)
        return rcvals[0]
    # int SPAPI_DeleteOrderBy(char *user_id, char *acc_no, long accOrderNo, char* productCode, char* clOrderId);
    def SPAPI_DeleteOrderBy(self, user_id, acc_no, accOrderNo, productCode, clOrderId):
        rcvals = self.Send("DatatypeDeleteOrderBy", [user_id, acc_no, accOrderNo, productCode, clOrderId],)
        return rcvals[0]
    # int SPAPI_DeleteAllOrders(char *user_id, char *acc_no);
    def SPAPI_DeleteAllOrders(self, user_id, acc_no):
        rcvals = self.Send("DatatypeDeleteAllOrders", [user_id, acc_no],)
        return rcvals[0]
    # int SPAPI_ActivateAllOrders(char *user_id, char *acc_no);
    def SPAPI_ActivateAllOrders(self, user_id, acc_no):
        rcvals = self.Send("DatatypeActivateAllOrders", [user_id, acc_no],)
        return rcvals[0]
    # int SPAPI_InactivateAllOrders(char *user_id, char *acc_no);
    def SPAPI_InactivateAllOrders(self, user_id, acc_no):
        rcvals = self.Send("DatatypeInactivateAllOrders", [user_id, acc_no],)
        return rcvals[0]
    # int SPAPI_ActivateOrderBy(char *user_id, char *acc_no, long accOrderNo);
    def SPAPI_ActivateOrderBy(self, user_id, acc_no, accOrderNo):
        rcvals = self.Send("DatatypeActivateOrderBy", [user_id, acc_no, accOrderNo],)
        return rcvals[0]
    # int SPAPI_InactivateOrderBy(char *user_id, char *acc_no, long accOrderNo);
    def SPAPI_InactivateOrderBy(self, user_id, acc_no, accOrderNo):
        rcvals = self.Send("DatatypeInactivateOrderBy", [user_id, acc_no, accOrderNo],)
        return rcvals[0]
    # int SPAPI_GetOrderCount(char *user_id, char* acc_no);
    def SPAPI_GetOrderCount(self, user_id, acc_no):
        rcvals = self.Send("DatatypeGetOrderCount", [user_id, acc_no],)
        return rcvals[0]
    # int SPAPI_GetOrderByOrderNo(char *user_id, char *acc_no, long int_order_no, SPApiOrder *order);
    def SPAPI_GetOrderByOrderNo(self, user_id, acc_no, int_order_no, order):
        rcvals = self.Send("DatatypeGetOrderByOrderNo", [user_id, acc_no, int_order_no, order],)
        return rcvals[0]
    # int SPAPI_GetActiveOrders(char *user_id, char *acc_no, vector<SPApiOrder>& apiOrderList);
    # def SPAPI_GetActiveOrders(self, user_id, acc_no, apiOrderList):
    #     rcvals = self.Send("DatatypeGetActiveOrders", [user_id, acc_no, apiOrderList],)
    #     return rcvals[0]
    def SPAPI_GetActiveOrders(self, user_id, acc_no):
        rcvals = self.Send("DatatypeGetActiveOrders", [user_id, acc_no],)
        rclist = []
        dclen = SPApiOrder().len()
        if len(rcvals) < dclen:
            return
        for i in range(len(rcvals), 0, -dclen):
            rclist.append(
                SPApiOrder(
                    *rcvals[i - dclen : i]
                )
            )
        return rclist
    # int SPAPI_GetPosCount(char *user_id);
    def SPAPI_GetPosCount(self, user_id):
        rcvals = self.Send("DatatypeGetPosCount", [user_id],)
        return rcvals[0]
    # int SPAPI_GetPosByProduct(char *user_id, char *prod_code, SPApiPos *pos);
    # def SPAPI_GetPosByProduct(self, user_id, prod_code, pos):
    #     rcvals = self.Send("DatatypeGetPosByProduct", [user_id, prod_code, pos],)
    #     return rcvals[0]
    def SPAPI_GetPosByProduct(self, user_id, prod_code):
        rcvals = self.Send("DatatypeGetPosByProduct", [user_id, prod_code],)
        dclen = SPApiPos().len()
        # if len(rcvals) < dclen:
        #     return            
        return SPApiPos(
                    *rcvals[-dclen:]
                )
    # int SPAPI_Uninitialize(char *user_id);
    def SPAPI_Uninitialize(self, user_id):
        rcvals = self.Send("DatatypeUninitialize", [user_id],)
        return rcvals[0]
    # int SPAPI_Logout(char *user_id);
    def SPAPI_Logout(self, user_id):
        rcvals = self.Send("DatatypeLogout", [user_id],)
        return rcvals[0]
    # int SPAPI_AccountLogin(char *user_id, char *acc_no);
    def SPAPI_AccountLogin(self, user_id, acc_no):
        rcvals = self.Send("DatatypeAccountLogin", [user_id, acc_no],)
        return rcvals[0]
    # int SPAPI_AccountLogout(char *user_id, char *acc_no);
    def SPAPI_AccountLogout(self, user_id, acc_no):
        rcvals = self.Send("DatatypeAccountLogout", [user_id, acc_no],)
        return rcvals[0]
    # int SPAPI_GetTradeCount(char *user_id, char *acc_no);
    def SPAPI_GetTradeCount(self, user_id, acc_no):
        rcvals = self.Send("DatatypeGetTradeCount", [user_id, acc_no],)
        return rcvals[0]
    # int SPAPI_GetAllTrades(char *user_id, char *acc_no, vector<SPApiTrade>& apiTradeList);
    # def SPAPI_GetAllTrades(self, user_id, acc_no, apiTradeList):
    #     rcvals = self.Send("DatatypeGetAllTrades", [user_id, acc_no, apiTradeList],)
    #     return rcvals[0]
    def SPAPI_GetAllTrades(self, user_id, acc_no):
        rcvals = self.Send("DatatypeGetAllTrades", [user_id, acc_no],)
        rclist = []
        dclen = SPApiTrade().len()
        if len(rcvals) < dclen:
            return
        for i in range(len(rcvals), 0, -dclen):
            rclist.append(
                SPApiTrade(
                    *rcvals[i - dclen : i]
                )
            )
        return rclist
    # int SPAPI_SubscribePrice(char *user_id, char *prod_code, int mode);
    def SPAPI_SubscribePrice(self, user_id, prod_code, mode):
        rcvals = self.Send("DatatypeSubscribePrice", [user_id, prod_code, mode],)
        return rcvals[0]
    # int SPAPI_SubscribeTicker(char *user_id, char *prod_code, int mode);
    def SPAPI_SubscribeTicker(self, user_id, prod_code, mode):
        rcvals = self.Send("DatatypeSubscribeTicker", [user_id, prod_code, mode],)
        return rcvals[0]
    # int SPAPI_ChangePassword(char *user_id, char *old_password, char *new_password);
    def SPAPI_ChangePassword(self, user_id, old_password, new_password):
        rcvals = self.Send("DatatypeChangePassword", [user_id, old_password, new_password],)
        return rcvals[0]
    # int SPAPI_GetDllVersion(char *dll_ver_no, char *dll_rel_no, char *dll_suffix);
    def SPAPI_GetDllVersion(self, dll_ver_no, dll_rel_no, dll_suffix):
        rcvals = self.Send("DatatypeGetDllVersion", [dll_ver_no, dll_rel_no, dll_suffix],)
        return rcvals[0]
    # int SPAPI_GetAccBalCount(char* user_id);
    def SPAPI_GetAccBalCount(self, user_id):
        rcvals = self.Send("DatatypeGetAccBalCount", [user_id],)
        return rcvals[0]
    # int SPAPI_GetAccBalByCurrency(char *user_id, char *ccy, SPApiAccBal *acc_bal);
    def SPAPI_GetAccBalByCurrency(self, user_id, ccy, acc_bal):
        rcvals = self.Send("DatatypeGetAccBalByCurrency", [user_id, ccy, acc_bal],)
        return rcvals[0]
    # int SPAPI_GetAllAccBal(char *user_id, vector<SPApiAccBal>& apiAccBalList);
    # def SPAPI_GetAllAccBal(self, user_id, apiAccBalList):
    #     rcvals = self.Send("DatatypeGetAllAccBal", [user_id, apiAccBalList],)
    #     return rcvals[0]
    def SPAPI_GetAllAccBal(self, user_id):
        rcvals = self.Send("DatatypeGetAllAccBal", [user_id],)
        rclist = []
        dclen = SPApiAccBal().len()
        if len(rcvals) < dclen:
            return
        for i in range(len(rcvals), 0, -dclen):
            rclist.append(
                SPApiAccBal(
                    *rcvals[i - dclen : i]
                )
            )
        return rclist
    # int SPAPI_GetCcyRateByCcy(char *user_id, char *ccy, double &rate);
    def SPAPI_GetCcyRateByCcy(self, user_id, ccy, rate):
        rcvals = self.Send("DatatypeGetCcyRateByCcy", [user_id, ccy, rate],)
        return rcvals[0]
    # int SPAPI_GetAccInfo(char *user_id, SPApiAccInfo *acc_info);
    # def SPAPI_GetAccInfo(self, user_id, acc_info):
        # rcvals = self.Send("DatatypeGetAccInfo", [user_id, acc_info],)
    def SPAPI_GetAccInfo(self, user_id):
        rcvals = self.Send("DatatypeGetAccInfo", [user_id],)
        rclist = []
        dclen = SPApiAccInfo().len()
        if len(rcvals) < dclen:
            return
        for i in range(len(rcvals), 0, -dclen):
            rclist.append(
                SPApiAccInfo(
                    *rcvals[i - dclen : i]
                )
            )
        return rclist
        
    # int SPAPI_GetPriceByCode(char *user_id, char *prod_code, SPApiPrice *price);
    def SPAPI_GetPriceByCode(self, user_id, prod_code, price):
        rcvals = self.Send("DatatypeGetPriceByCode", [user_id, prod_code, price],)
        return rcvals[0]
    # int SPAPI_SetApiLogPath(char *path);
    def SPAPI_SetApiLogPath(self, path):
        rcvals = self.Send("DatatypeSetApiLogPath", [path],)
        return rcvals[0]
    # int SPAPI_LoadProductInfoListByCode(char *inst_code);
    def SPAPI_LoadProductInfoListByCode(self, inst_code):
        rcvals = self.Send("DatatypeLoadProductInfoListByCode", [inst_code],)
        return rcvals[0]
    # int SPAPI_LoadProductInfoListByMarket(char *market_code);
    def SPAPI_LoadProductInfoListByMarket(self, market_code):
        rcvals = self.Send("DatatypeLoadProductInfoListByMarket", [market_code],)
        return rcvals[0]
    # int SPAPI_GetProductCount();
    def SPAPI_GetProductCount(self, ):
        rcvals = self.Send("DatatypeGetProductCount", [],)
        return rcvals[0]
    # int SPAPI_GetProduct(vector<SPApiProduct>& apiProdList);
    def SPAPI_GetProduct(self, apiProdList):
        rcvals = self.Send("DatatypeGetProduct", [apiProdList],)
        return rcvals[0]
    # int SPAPI_GetProductByCode(char *prod_code, SPApiProduct *prod);
    def SPAPI_GetProductByCode(self, prod_code, prod):
        rcvals = self.Send("DatatypeGetProductByCode", [prod_code, prod],)
        return rcvals[0]
    # int SPAPI_LoadInstrumentList();
    def SPAPI_LoadInstrumentList(self, ):
        rcvals = self.Send("DatatypeLoadInstrumentList", [],)
        return rcvals[0]
    # int SPAPI_GetInstrumentCount();
    def SPAPI_GetInstrumentCount(self, ):
        rcvals = self.Send("DatatypeGetInstrumentCount", [],)
        return rcvals[0]
    # int SPAPI_GetInstrument(vector<SPApiInstrument>& apiInstList);
    def SPAPI_GetInstrument(self, apiInstList):
        rcvals = self.Send("DatatypeGetInstrument", [apiInstList],)
        return rcvals[0]
    # int SPAPI_GetInstrumentByCode(char *inst_code, SPApiInstrument *inst);
    def SPAPI_GetInstrumentByCode(self, inst_code, inst):
        rcvals = self.Send("DatatypeGetInstrumentByCode", [inst_code, inst],)
        return rcvals[0]
    # void SPAPI_SetLanguageId(int langid);
    def SPAPI_SetLanguageId(self, langid):
        rcvals = self.Send("DatatypeSetLanguageId", [langid],)
        pass
    # int SPAPI_SendMarketMakingOrder(char *user_id, SPApiMMOrder *mm_order);
    def SPAPI_SendMarketMakingOrder(self, user_id, mm_order):
        rcvals = self.Send("DatatypeSendMarketMakingOrder", [user_id, mm_order],)
        return rcvals[0]
    # int SPAPI_SubscribeQuoteRequest(char *user_id, char *prod_code, int mode);
    def SPAPI_SubscribeQuoteRequest(self, user_id, prod_code, mode):
        rcvals = self.Send("DatatypeSubscribeQuoteRequest", [user_id, prod_code, mode],)
        return rcvals[0]
    # int SPAPI_SubscribeAllQuoteRequest(char *user_id, int mode);
    def SPAPI_SubscribeAllQuoteRequest(self, user_id, mode):
        rcvals = self.Send("DatatypeSubscribeAllQuoteRequest", [user_id, mode],)
        return rcvals[0]
    # int SPAPI_GetAllAccBalByArray(char *acc_no, SPApiAccBal* apiAccBalList);
    def SPAPI_GetAllAccBalByArray(self, acc_no, apiAccBalList):
        rcvals = self.Send("DatatypeGetAllAccBalByArray", [acc_no, apiAccBalList],)
        return rcvals[0]
    # int SPAPI_GetOrdersByArray(char* userId, char* acc_no, SPApiOrder* apiOrderList);
    def SPAPI_GetOrdersByArray(self, userId, acc_no, apiOrderList):
        rcvals = self.Send("DatatypeGetOrdersByArray", [userId, acc_no, apiOrderList],)
        return rcvals[0]
    # int SPAPI_GetAllTradesByArray(char* userId, char* acc_no, SPApiTrade* apiTradeList);
    def SPAPI_GetAllTradesByArray(self, userId, acc_no, apiTradeList):
        rcvals = self.Send("DatatypeGetAllTradesByArray", [userId, acc_no, apiTradeList],)
        return rcvals[0]
    # int SPAPI_GetInstrumentByArray(SPApiInstrument* apiInstList);
    def SPAPI_GetInstrumentByArray(self, apiInstList):
        rcvals = self.Send("DatatypeGetInstrumentByArray", [apiInstList],)
        return rcvals[0]
    # int SPAPI_GetProductByArray(SPApiProduct* apiProdList);
    def SPAPI_GetProductByArray(self, apiProdList):
        rcvals = self.Send("DatatypeGetProductByArray", [apiProdList],)
        return rcvals[0]
    # int SPAPI_GetAllPos(char *user_id, vector<SPApiPos>& apiPosList);
    # def SPAPI_GetAllPos(self, user_id, apiPosList):
    #     rcvals = self.Send("DatatypeGetAllPos", [user_id, apiPosList],)
    #     return rcvals[0]
    def SPAPI_GetAllPos(self, user_id):
        rcvals = self.Send("DatatypeGetAllPos", [user_id],)
        rclist = []
        dclen = SPApiPos().len()
        if len(rcvals) < dclen:
            return rclist
        for i in range(len(rcvals), 0, -dclen):
            rclist.append(
                SPApiPos(
                    *rcvals[i - dclen : i]
                )
            )
        return rclist
    # int SPAPI_GetAllPosByArray(char *user_id, SPApiPos* apiPosList);
    def SPAPI_GetAllPosByArray(self, user_id, apiPosList):
        rcvals = self.Send("DatatypeGetAllPosByArray", [user_id, apiPosList],)
        return rcvals[0]
    # int SPAPI_SendAccControl(char *user_id, char *acc_no, char ctrl_mask, char ctrl_level);
    def SPAPI_SendAccControl(self, user_id, acc_no, ctrl_mask, ctrl_level):
        rcvals = self.Send("DatatypeSendAccControl", [user_id, acc_no, ctrl_mask, ctrl_level],)
        return rcvals[0]

