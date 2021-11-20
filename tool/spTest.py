import os
import datetime
import logging

class Logger():
    def __init__(self, name, path):
        # Gets or creates a logger
#        self.logger = logging.getLogger(__name__)  
        self.logger = logging.getLogger(name)  
#        self.logger.propagate = False
        # define file handler and set formatter
        file_handler = logging.FileHandler(
                                        path,
                                        mode='w',
                                        )
        formatter    = logging.Formatter('%(asctime)s : %(levelname)s : %(name)s : %(message)s')
        file_handler.setFormatter(formatter)
        # add file handler to logger
        self.logger.addHandler(file_handler)
        # set log level
#        self.logger.setLevel(logging.INFO)#logging.DEBUG)
        self.logger.setLevel(logging.DEBUG)
        # self.logger.setLevel(logging.INFO)
        
    def var2str(self,   *text):
        return ' '.join(str(x) for x in [*text])
        
    def debug(self,     *text):
        self.logger.debug       ('\n' + self.var2str(*text).encode('utf-8').decode('ascii', 'ignore'))
        
    def info(self,      *text):
        self.logger.info        ('\n' + self.var2str(*text).encode('utf-8').decode('ascii', 'ignore'))
        
    def warning(self,   *text):
        self.logger.warning     ('\n' + self.var2str(*text).encode('utf-8').decode('ascii', 'ignore'))
        
    def error(self,     *text):
        self.logger.error       ('\n' + self.var2str(*text).encode('utf-8').decode('ascii', 'ignore'))
        
    def critical(self,  *text):
        self.logger.critical    ('\n' + self.var2str(*text).encode('utf-8').decode('ascii', 'ignore'))
        
    def exception(self, *text):
        self.logger.exception   ('\n' + self.var2str(*text).encode('utf-8').decode('ascii', 'ignore'))


class spTestFunc():
    def __init__(
            self,
            ):
        self.callbackEn = True
        self.rawEn      = False
        self.priceEn    = False
        self.tickEn     = False
        
        self.logpath    = os.path.join(
                                'log',
                                "%s.log",
                                )
        self.logpath    = self.logpath% (datetime.datetime.now().strftime("%Y%m%d-%H%M%S"))
        self.logger     = Logger(
                                "TESTER", 
                                self.logpath,
                                )

    def printHelp(
            self,
            ):
        print('Commands:')
        print('help:            Print this page')
        print('exit:            Quit this program')
        print('raw:             Toggle raw details')
        print('callback:        Toggle callback details')
        print('price:           Toggle price callback')
        print('tick:            Toggle tick callback')
        print('login:           Begin login sequence')
        print('logout:          Logout from API')
        print('req [|inst|prod|acc|bal|pos|order|trade]:')
        print('                 Get desired request reply')
        print('last [|callback|acc|bal|price|tick|pos|order|trade]:')
        print('                 Get last callback data')
        print('order            Place an order')
        print('order pending:   Place a pending order')
        print('order activate:  Activate order')
        print('order inactivate:Inactivate order')
        print('order close:     Close an order')

    def print(
            self,
            *text,
            ):
        print(*text)
        self.logger.debug(*text)

    def ktmonth(self, expType, tdate):
        if (
                expType == '3rdFriday'
                ):
            first_day = tdate.replace(day=1)
    
            dom = tdate.day
            adjusted_dom = dom + first_day.weekday()
        
            week_of_month   = int(ceil(adjusted_dom/7.0))
            weekday         = tdate.weekday()
            if (    # more than 3 week of month
                    week_of_month > 3
                or  (
                        # 3rd week of month
                        week_of_month == 3
                        # Friday
                    and weekday >= 4
                        )
                    ):
                theMonth = tdate.month + 1 
                theYear  = tdate.year
                if theMonth > 12:
                    theMonth = theMonth - 12
                    theYear  = theYear + 1

                return theMonth, theYear
            
        return tdate.month, tdate.year

    def strMkt(
            self,
            mkt,
            ):
        if self.rawEn:
            return mkt
        return "%s %s"%(
                mkt.MarketCode,
                mkt.MarketName,
                )

    def strInst(
            self,
            inst,
            ):
        if self.rawEn:
            return inst
        return "%s %s %s %s"%(
                inst.MarketCode,
                inst.InstCode,
                inst.InstName,
                inst.Ccy,
                )

    def strProd(
            self,
            prod,
            ):
        if self.rawEn:
            return prod
        return "%s %s %s %s %s"%(
                prod.ProdCode,
                prod.ProdType,
                prod.ProdName,
                prod.InstCode,
                )

    def strAcc(
            self,
            acc,
            ):
        if self.rawEn:
            return acc
        return "%s %s %f %f %f"%(
                acc.ClientId,
                acc.AccName,
                acc.NAV,
                acc.BuyingPower,
                acc.CashBal,
                )

    def strBal(
            self,
            bal,
            ):
        if self.rawEn:
            return bal
        return "%s %f %f %f %f %f"%(
                bal.Ccy,
                bal.CashBf,
                bal.TodayCash,
                bal.NotYetValue,
                bal.Unpresented,
                bal.TodayOut,
                )

    def strPrice(
            self,
            price,
            ):
        if self.rawEn:
            return price
        return "%s %f %f %d %f %d %f %f %f %f"%(
                price.ProdCode,
                price.Timestamp,
                price.Bid[0],
                price.BidQty[0],
                price.Ask[0],
                price.AskQty[0],
                price.Open,
                price.High,
                price.Low,
                price.Close,
                )

    def strTick(
            self,
            tick,
            ):
        if self.rawEn:
            return tick
        return "%s %f %f %d"%(
                tick.ProdCode,
                tick.TickerTime,
                tick.Price,
                tick.Qty,
                )

    def strOrder(
            self,
            order,
            ):
            if self.rawEn:
                return order
            return "%s %d %d %s %s %d %d %d %d"%(
                    order.ClOrderId,
                    order.ExtOrderNo,
                    order.IntOrderNo,
                    order.ProdCode,
                    order.BuySell,
                    order.Qty,
                    order.TradedQty,
                    order.TotalQty,
                    order.Status,
                    )

    def strTrade(
            self,
            trade,
            ):
            if self.rawEn:
                return trade
            return "%s %d %d %s %s %d %d %d %d %d"%(
                    trade.ClOrderId,
                    trade.ExtOrderNo,
                    trade.IntOrderNo,
                    trade.ProdCode,
                    trade.BuySell,
                    trade.Qty,
                    trade.TradedQty,
                    trade.TotalQty,
                    trade.RemainingQty,
                    trade.Status,
                    )

    def strPos(
            self,
            pos,
            ):
            if self.rawEn:
                return pos
            return "%s %d %d %d %d %s"%(
                    pos.ProdCode,
                    pos.Qty,
                    pos.DepQty,
                    pos.LongQty,
                    pos.ShortQty,
                    pos.LongShort,
                    )

    def updatePos(
            self,
            ):
        for pos in self.SPAPI_GetAllPos(self.user_id):
            self.pos[pos.ProdCode] = pos

    def loadOrder(
            self,
            ):
        orders = self.SPAPI_GetActiveOrders(self.user_id, self.user_id)
        if orders:
            lastId = None
            for order in orders:
                self.order[order.ClOrderId] = order
                if not lastId or int(lastId) < int(order.ClOrderId):
                    lastId = order.ClOrderId

    def selOrder(
            self,
            ):
        order = None
        if self.order:
            orders = list(self.order.values())
            for i in range(len(orders)):
                print(
                    i, 
                    self.strOrder(orders[i])
                    )
            idx = int(input('Select Order: '))
            order = orders[idx]
        if not order:
            raise sys._getframe().f_code.co_name
        return order

    def selPos(
            self,
            ):
        pos = None
        if self.pos:
            positions = list(self.pos.values())
            for i in range(len(positions)):
                print(
                    i, 
                    self.strPos(positions[i]),
                    )
            idx = int(input('Select Position: '))
            pos = positions[idx]
        if not pos:
            raise sys._getframe().f_code.co_name
        return pos

    def selCode(
            self,
            ):
        code = None
        if self.price:
            codes = list(self.price.keys())
            for i in range(len(codes)):
                print(i, codes[i])
            idx = int(input('Select Position: '))
            code = codes[idx]
        if not code:
            raise sys._getframe().f_code.co_name
        return code

    def selQty(
            self,
            ):
        qty = int(input('Qty? '))
        if not qty:
            raise sys._getframe().f_code.co_name
        return qty