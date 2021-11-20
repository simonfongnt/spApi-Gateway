#!/usr/bin/env python3
import spapi
from spStruct import *
import spTest
import time
import datetime

import sys
import socket
import threading
import traceback
import argparse

HOST = '127.0.0.1'  # The server's hostname or IP address
IOPORT  = 58101        # The port used by the server
SUBPORT = 58111        # The port used by the server

class tester(
    spapi.EClient,
    spTest.spTestFunc,
    threading.Thread,
    ):
    def __init__(
            self,
            subHost = HOST,
            subPort = SUBPORT,
            ioHost  = HOST,
            ioPort  = IOPORT,
            ):
        spapi.EClient.__init__(
            self,
            subHost,
            subPort,
            ioHost,
            ioPort,
            )
        spTest.spTestFunc.__init__(self)
        threading.Thread  .__init__(self)

        self.user_id    = None
        self.AccName    = None
        self.ClientId   = None
        self.AEId       = None
        self.BaseCcy    = None

        self.test       = {

        }
        self.pos        = {}
        self.acc        = {}
        self.bal        = {}

        self.price      = {}
        self.tick       = {}
        self.order      = {}
        self.trade      = {}

        self.ConnStatus = {
                            80: 0,
                            81: 0,
                            83: 0,
                            88: 0,
                            }

        self.InstCode = ['HSI', 'MHI']
        suffix = {
                "1"    :"F",
                "2"    :"G",
                "3"    :"H",
                "4"    :"J",
                "5"    :"K",
                "6"    :"M",
                "7"    :"N",
                "8"    :"Q",
                "9"    :"U",
                "10"   :"V",
                "11"   :"X",
                "12"   :"Z"
            }
        tdate = datetime.datetime.now()
        symMonth, symYear = self.ktmonth("ENDOFMONTH", tdate)
        # symMonth = symMonth + 1
        self.ProdCode = self.InstCode[0] + suffix[str(symMonth)] + str(symYear)[-1]

        self.OptCode = []
        self.printHelp()

    # Overrided Callbacks
    def OnLoginReply(self, user_id, ret_code, ret_msg):   
        self.test[sys._getframe().f_code.co_name]     = [user_id, ret_code, ret_msg]
        self.logger.debug(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        if self.callbackEn: 
            print(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        self.user_id    = user_id
        self.ClientId   = user_id
        self.SPAPI_AccountLogin(self.user_id, self.user_id)

    def OnConnectingReply(self, host_type, con_status):
        self.test[sys._getframe().f_code.co_name]     = [host_type, con_status]
        self.logger.debug(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        if self.callbackEn: 
            print(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        self.ConnStatus[host_type] = con_status
        if (                
                (self.ConnStatus[80] == 2 or self.ConnStatus[81] == 2)
            and self.ConnStatus[83] == 2
            and self.ConnStatus[88] == 2
                ):
            self.SPAPI_LoadInstrumentList()

    def OnApiOrderRequestFailed(self, action, order, err_code, err_msg):
        self.test[sys._getframe().f_code.co_name]     = [action, err_code, err_msg, self.strOrder(order)]
        self.logger.debug(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        if self.callbackEn: 
            print(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        self.order[order.ClOrderId] = order
    def OnApiOrderReport(self, rec_no, order):
        self.test[sys._getframe().f_code.co_name]     = [rec_no, self.strOrder(order)]
        self.logger.debug(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        if self.callbackEn: 
            print(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        self.order[order.ClOrderId] = order
    def OnApiOrderBeforeSendReport(self, order):
        self.test[sys._getframe().f_code.co_name]     = [self.strOrder(order)]
        self.logger.debug(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        if self.callbackEn: 
            print(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        self.order[order.ClOrderId] = order
    def OnAccountLoginReply(self, accNo, ret_code, ret_msg):
        self.test[sys._getframe().f_code.co_name]     = [accNo, ret_code, ret_msg]
        self.logger.debug(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        if self.callbackEn: 
            print(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
    def OnAccountLogoutReply(self, accNo, ret_code, ret_msg):
        self.test[sys._getframe().f_code.co_name]     = [accNo, ret_code, ret_msg]
        self.logger.debug(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        if self.callbackEn: 
            print(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
    def OnAccountInfoPush(self, acc_info):
        self.test[sys._getframe().f_code.co_name]     = [self.strAcc(acc_info)]
        self.logger.debug(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        if self.callbackEn: 
            print(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        self.acc[acc_info.ClientId] = acc_info

        self.AccName    = acc_info.AccName
        self.user_id    = acc_info.ClientId
        self.ClientId   = acc_info.ClientId
        self.AEId       = acc_info.AEId
        self.BaseCcy    = acc_info.BaseCcy
    def OnAccountPositionPush(self, pos):
        self.test[sys._getframe().f_code.co_name]     = [self.strPos(pos)]
        self.logger.debug(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        if self.callbackEn: 
            print(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        self.pos[pos.ProdCode] = pos
    def OnUpdatedAccountPositionPush(self, pos):
        self.test[sys._getframe().f_code.co_name]     = [self.strPos(pos)]
        self.logger.debug(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        if self.callbackEn: 
            print(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        self.pos[pos.ProdCode] = pos
    def OnUpdatedAccountBalancePush(self, acc_bal):
        self.test[sys._getframe().f_code.co_name]     = [self.strBal(acc_bal)]
        self.logger.debug(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        if self.callbackEn: 
            print(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        self.bal[acc_bal.Ccy]
    def OnApiTradeReport(self, rec_no, trade):
        self.test[sys._getframe().f_code.co_name]     = [rec_no, self.strTrade(trade)]
        self.logger.debug(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        if self.callbackEn: 
            print(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        self.trade[trade.ClOrderId] = trade
        self.updatePos()
    def OnApiPriceUpdate(self, price):
        self.test[sys._getframe().f_code.co_name]     = [self.strPrice(price)]
        if self.priceEn: 
            self.logger.debug(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        if self.callbackEn and self.priceEn: 
            print(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        self.price[price.ProdCode] = price

        # Keep the Gateway alive
        self.SPAPI_GetAllPos(self.user_id)

    def OnApiTickerUpdate(self, ticker):
        self.test[sys._getframe().f_code.co_name]     = [self.strTick(ticker)]
        if self.tickEn: 
            self.logger.debug(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        if self.callbackEn and self.tickEn: 
            print(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        self.tick[ticker.ProdCode] = ticker
    def OnPswChangeReply(self, ret_code, ret_msg):
        self.test[sys._getframe().f_code.co_name]     = [ret_code, ret_msg]
        self.logger.debug(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        if self.callbackEn: 
            print(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
    def OnProductListByCodeReply(self, req_id, inst_code, is_ready, ret_msg):
        self.test[sys._getframe().f_code.co_name]     = [req_id, inst_code, is_ready, ret_msg]
        self.logger.debug(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        if self.callbackEn: 
            print(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        # self.SPAPI_GetProductCount()
        if (
                # inst_code == ','.join(self.InstCode)
                inst_code in ','.join(self.InstCode)
            and is_ready    == 1
                ):
            suffix = {
                    "1"    :"F",
                    "2"    :"G",
                    "3"    :"H",
                    "4"    :"J",
                    "5"    :"K",
                    "6"    :"M",
                    "7"    :"N",
                    "8"    :"Q",
                    "9"    :"U",
                    "10"   :"V",
                    "11"   :"X",
                    "12"   :"Z"
                }
            tdate = datetime.datetime.now()
            symMonth, symYear = self.ktmonth("ENDOFMONTH", tdate)
            for prod in self.InstCode:
                code = prod + suffix[str(symMonth)] + str(symYear)[-1]
                self.SPAPI_SubscribePrice('', code, 1)
                self.SPAPI_SubscribeTicker('', code, 1)
                # for strike in range(
                #                 int(14400),
                #                 int(40000), 
                #                 int(200),
                #                 ):
                #     suffix = {
                #             "1"    :"A",
                #             "2"    :"B",
                #             "3"    :"C",
                #             "4"    :"D",
                #             "5"    :"E",
                #             "6"    :"F",
                #             "7"    :"G",
                #             "8"    :"H",
                #             "9"    :"I",
                #             "10"   :"J",
                #             "11"   :"K",
                #             "12"   :"L"
                #         }
                #     code = prod + str(strike) + suffix[str(symMonth)] + str(symYear)[-1]
                #     self.SPAPI_SubscribePrice('', code, 1)
                #     self.SPAPI_SubscribeTicker('', code, 1)

            self.updatePos()
            self.loadOrder()
            
    def OnInstrumentListReply(self, req_id, is_ready, ret_msg):
        self.test[sys._getframe().f_code.co_name]     = [req_id, is_ready, ret_msg]
        self.logger.debug(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        if self.callbackEn: 
            print(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        if is_ready == 1:
            self.SPAPI_LoadProductInfoListByCode(','.join(self.InstCode))

    def OnBusinessDateReply(self, business_date):
        self.test[sys._getframe().f_code.co_name]     = [business_date]
        self.logger.debug(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        if self.callbackEn: 
            print(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
    def OnApiMMOrderBeforeSendReport(self, mm_order):
        self.test[sys._getframe().f_code.co_name]     = [mm_order]
        self.logger.debug(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        if self.callbackEn: 
            print(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
    def OnApiMMOrderRequestFailed(self, mm_order, err_code, err_msg):
        self.test[sys._getframe().f_code.co_name]     = [mm_order, err_code, err_msg]
        self.logger.debug(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        if self.callbackEn: 
            print(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
    def OnApiQuoteRequestReceived(self, prod_code, buy_sell, qty):
        self.test[sys._getframe().f_code.co_name]     = [prod_code, buy_sell, qty]
        self.logger.debug(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        if self.callbackEn: 
            print(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
    def OnApiAccountControlReply(self, ret_code, ret_msg):
        self.test[sys._getframe().f_code.co_name]     = [ret_code, ret_msg]
        self.logger.debug(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        if self.callbackEn: 
            print(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
    def OnApiLoadTradeReadyPush(self, rec_no, trade):
        self.test[sys._getframe().f_code.co_name]     = [rec_no, self.strTrade(trade)]
        self.logger.debug(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        if self.callbackEn: 
            print(sys._getframe().f_code.co_name, *self.test[sys._getframe().f_code.co_name])
        self.trade[trade.ClOrderId] = trade
        self.updatePos()

    def run(
            self,
            ):
        while True:
            try:
                cmds     = input()
                cmd = cmds.split(' ')
                if     (cmd[0] == 'help' ):
                    self.printHelp()
                elif   (cmd[0] == 'exit' ):
                    exit()
                elif   (cmd[0] == 'raw' ):
                    self.rawEn = False if self.rawEn else True
                    self.print('Raw output is', 'on' if self.rawEn else 'off')
                elif   (cmd[0] == 'callback' ):
                    self.callbackEn = False if self.callbackEn else True
                    self.print('Callback output is', 'on' if self.callbackEn else 'off')
                elif   (cmd[0] == 'price' ):
                    self.priceEn = False if self.priceEn else True
                    self.print('Price output is', 'on' if self.priceEn else 'off')
                elif   (cmd[0] == 'tick' ):
                    self.tickEn = False if self.tickEn else True
                    self.print('Tick output is', 'on' if self.tickEn else 'off')
                    
                elif (cmd[0] == 'login' ):
                    self.print(
                        self.SPAPI_Login(),
                    )
                elif (cmd[0] == 'logout' ):
                    self.print(
                        self.SPAPI_Logout(self.user_id),
                    )
                elif cmd[0] == 'last' or cmd[0] == 'req':
                    self.print('###################### %s ######################'%cmd[0].upper())
                    if cmd[0] == 'last':
                        if len(cmd) == 1 or 'callback' in cmd:
                            self.print('Callback:')
                            for key, item in self.test.items():
                                self.print(key, item)

                    if cmd[0] == 'req':
                        if len(cmd) == 1 or 'inst' in cmd:
                            self.print('Instruments:', 'SPAPI_GetInstrumentCount', self.SPAPI_GetInstrumentCount())
                            # self.print(self.SPAPI_GetInstrument(' '))

                    if cmd[0] == 'req':
                        if len(cmd) == 1 or 'prod' in cmd:
                            self.print('Product:', 'SPAPI_GetProductCount', self.SPAPI_GetProductCount())
                            # self.print(self.SPAPI_GetProduct(' '))

                    if len(cmd) == 1 or 'acc' in cmd:
                        self.print('AccInfo:')
                        if cmd[0] == 'last': data = self.acc
                        else:
                            data = {}
                            itemlist = self.SPAPI_GetAccInfo(' ')
                            if itemlist:
                                for item in itemlist:
                                    data[item.ClientId] = item
                                for key, item in data.items():
                                    self.print(key, self.strAcc(item))

                    if len(cmd) == 1 or 'bal' in cmd:
                        self.print('AccBal:', 'SPAPI_GetAccBalCount', self.SPAPI_GetAccBalCount(self.user_id),)
                        if cmd[0] == 'last': data = self.bal
                        else:
                            data = {}
                            itemlist = self.SPAPI_GetAllAccBal(' ')
                            if itemlist:
                                for item in itemlist:
                                    data[item.Ccy] = item
                                for key, item in data.items():
                                    self.print(key, self.strBal(item))

                    if cmd[0] == 'last':
                        if len(cmd) == 1 or 'price' in cmd:
                            self.print('Price:')
                            for key, item in self.price.items():
                                self.print(key, self.strPrice(item))

                    if cmd[0] == 'last':
                        if len(cmd) == 1 or 'tick' in cmd:
                            self.print('Tick:')
                            for key, item in self.tick.items():
                                self.print(key, self.strTick(item))  

                    if len(cmd) == 1 or 'pos' in cmd:
                        self.print('Pos:', 'SPAPI_GetPosCount', self.SPAPI_GetPosCount(self.user_id))
                        if cmd[0] == 'last': data = self.pos
                        else:
                            data = {}
                            itemlist = self.SPAPI_GetAllPos(' ')
                            if itemlist:
                                for item in itemlist:
                                    data[item.ProdCode] = item
                                for key, item in data.items():
                                    self.print(key, self.strPos(item))

                        # Extra
                        self.print(self.ProdCode, 'SPAPI_GetPosByProduct:')
                        item = self.SPAPI_GetPosByProduct(self.user_id, self.ProdCode)
                        self.print(self.strPos(item))
                            
                    if len(cmd) == 1 or 'order' in cmd:
                        self.print('Order:', 'SPAPI_GetOrderCount', self.SPAPI_GetOrderCount(self.user_id, self.user_id))
                        if cmd[0] == 'last': data = self.order
                        else:
                            data = {}
                            itemlist = self.SPAPI_GetActiveOrders(self.user_id, self.user_id)
                            if itemlist:
                                for item in itemlist:
                                    data[item.ClOrderId] = item
                                for key, item in data.items():
                                    self.print(key, self.strOrder(item))

                    if len(cmd) == 1 or 'trade' in cmd:
                        self.print('Trade:', 'SPAPI_GetTradeCount', self.SPAPI_GetTradeCount(self.user_id, self.user_id))
                        if cmd[0] == 'last': data = self.trade
                        else:
                            data = {}
                            itemlist = self.SPAPI_GetAllTrades(self.user_id, self.user_id)
                            if itemlist:
                                for item in itemlist:
                                    data[item.ClOrderId] = item
                                for key, item in data.items():
                                    self.print(key, self.strTrade(item))
                    self.print('####################################################')
                elif (cmd[0] == 'order' ):
                    if len(cmd) == 1:
                        self.print('###################### Order ######################')
                        code = self.selCode()
                        Qty = self.selQty()
                        if   Qty > 0:
                            BS = 'B'
                        elif Qty < 0:
                            BS = 'S'
                        price = self.price[code]
                        order               = SPApiOrder()
                        order.AccNo         = self.user_id
                        order.ProdCode      = code
                        order.Price         = price.Ask[0] + 300 if 'BS' == 'S' else price.Bid[0] - 300
                        order.Qty           = abs(Qty)
                        order.BuySell       = BS
                        order.OrderType     = 0
                        order.OrderOptions  = 0
                        order.Ref           = '@APITRADER'
                        order.DecInPrice    = price.DecInPrice
                        order.ClOrderId     = str(int(time.time()))
                        self.print(
                            self.SPAPI_AddOrder(order),
                            self.strOrder(order)
                        )
                        self.print('####################################################')
                    elif (cmd[1] == 'pending' ):
                        self.print('###################### Pend ######################')
                        code = self.selCode()
                        Qty = self.selQty()
                        if   Qty > 0:
                            BS = 'B'
                        elif Qty < 0:
                            BS = 'S'
                        price = self.price[code]
                        order               = SPApiOrder()
                        order.AccNo         = self.user_id
                        order.ProdCode      = code
                        order.Price         = price.Ask[0] + 300 if 'BS' == 'S' else price.Bid[0] - 300
                        order.Qty           = abs(Qty)
                        order.BuySell       = BS
                        order.OrderType     = 0
                        order.OrderOptions  = 0
                        order.Ref           = '@APITRADER'
                        order.DecInPrice    = price.DecInPrice
                        order.ClOrderId     = str(int(time.time()))
                        self.print(
                            self.SPAPI_AddInactiveOrder(order),
                            self.strOrder(order)
                        )
                        self.print('####################################################')
                    elif (cmd[1] == 'activate' ):
                        self.print('###################### Activate ######################')                    
                        if len(cmd) == 2:
                            self.SPAPI_ActivateAllOrders(
                                self.user_id,
                                self.user_id,
                            )
                        else:
                            order = self.selOrder()
                            self.SPAPI_ActivateOrderBy(
                                self.user_id,
                                self.user_id,
                                order.ClOrderId,
                            )
                        self.print('####################################################')
                    elif (cmd[1] == 'inactivate' ):
                        self.print('###################### Inactivate ######################')                  
                        if len(cmd) == 2:
                            self.SPAPI_InactivateAllOrders(
                                self.user_id, 
                                self.user_id, 
                            )
                        else:
                            order = self.selOrder()
                            self.SPAPI_InactivateOrderBy(
                                self.user_id,
                                self.user_id,
                                order.ClOrderId,
                            )
                        self.print('####################################################')
                    elif (cmd[1] == 'close' ):
                        self.print('###################### Close ######################')
                        pos = self.selPos()
                        price = self.price[pos.ProdCode]
                        Qty = pos.LongQty - pos.ShortQty
                        if Qty != 0:                           
                            order               = SPApiOrder()
                            order.AccNo         = self.user_id
                            order.ProdCode      = pos.ProdCode
                            order.Price         = price.Ask[0] if Qty > 0 else price.Bid[0]
                            order.Qty           = abs(Qty)
                            order.BuySell       = 'S' if Qty > 0 else 'B'
                            order.OrderType     = 0
                            order.OrderOptions  = 0
                            order.Ref           = '@APITRADER'
                            order.DecInPrice    = price.DecInPrice
                            order.ClOrderId     = str(int(time.time()))
                            self.print(
                                self.SPAPI_AddOrder(order),
                                self.strOrder(order),
                            )
                        self.print('####################################################')
                    elif (cmd[1] == 'delete' ):
                        self.print('###################### Delete ######################')
                        if len(cmd) >= 2 and (cmd[1] == '-a' or cmd[1] == '--all'):
                            self.print(
                                self.SPAPI_DeleteAllOrders(
                                        self.user_id, 
                                        self.user_id, 
                                        )
                                )
                        else:
                            order = self.selOrder()
                            self.print(
                                self.SPAPI_DeleteOrderBy(
                                        self.user_id, 
                                        self.user_id, 
                                        order.IntOrderNo, 
                                        order.ProdCode,
                                        order.ClOrderId,
                                        )
                                )
                        self.print('####################################################')
                    elif (cmd[1] == 'change' ):
                        self.print('###################### Change ######################')
                        order = self.selOrder()
                        price = self.price[self.ProdCode]
                        self.print(
                            self.SPAPI_ChangeOrderBy(
                                    self.user_id, 
                                    self.user_id, 
                                    order.IntOrderNo, 
                                    order.Price,
                                    order.Qty,
                                    price.Ask[0] if order.BuySell == 'B' else price.Bid[0],
                                    order.Qty,
                                    )
                            )
                        self.print('####################################################')
            except Exception as e:
                self.print(e)
                traceback.print_exc()

if __name__ == '__main__':

    parser = argparse.ArgumentParser(
        description='Personal information')
    parser.add_argument(
        '-H', 
        '--host', 
        dest = 'host', 
        type = str, 
        default = HOST,
        help = 'Host of SP Gateway, Default: localhost',
        )
    parser.add_argument(
        '-PSP', 
        '--psport', 
        dest = 'psport', 
        type = int, 
        default = SUBPORT,
        help = 'Callback Port of SP Gateway, Default: %d'%SUBPORT,
        )
    parser.add_argument(
        '-IOP', 
        '--ioport', 
        dest = 'ioport', 
        type = int, 
        default = IOPORT,
        help = 'I/O Port of SP Gateway, Default: %d'%IOPORT,
        )
    args = parser.parse_args()
    mainTh = tester(
            args.host, 
            args.psport, 
            args.host, 
            args.ioport, 
            )
    mainTh.daemon = True
    mainTh.start()

    while True:
        pass