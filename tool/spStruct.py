from dataclasses import dataclass, field, asdict
from typing import Optional, Dict, List

SP_MAX_DEPTH    = 20
SP_MAX_LAST     = 20

spDatatypeTag = {
    "128": "DatatypeInitialize",
    "129": "DatatypeSetLoginInfo",
    "130": "DatatypeLogin",
    "131": "DatatypeGetLoginStatus",
    "132": "DatatypeAddOrder",
    "133": "DatatypeAddInactiveOrder",
    "144": "DatatypeChangeOrder",
    "145": "DatatypeChangeOrderBy",
    "146": "DatatypeDeleteOrderBy",
    "147": "DatatypeDeleteAllOrders",
    "148": "DatatypeActivateAllOrders",
    "149": "DatatypeInactivateAllOrders",
    "150": "DatatypeActivateOrderBy",
    "151": "DatatypeInactivateOrderBy",
    "152": "DatatypeGetOrderCount",
    "153": "DatatypeGetOrderByOrderNo",
    "154": "DatatypeGetActiveOrders",
    "155": "DatatypeGetPosCount",
    "156": "DatatypeGetPosByProduct",
    "157": "DatatypeUninitialize",
    "158": "DatatypeLogout",
    "159": "DatatypeAccountLogin",
    "160": "DatatypeAccountLogout",
    "161": "DatatypeGetTradeCount",
    "162": "DatatypeGetAllTrades",
    "163": "DatatypeSubscribePrice",
    "164": "DatatypeSubscribeTicker",
    "165": "DatatypeChangePassword",
    "166": "DatatypeGetDllVersion",
    "167": "DatatypeGetAccBalCount",
    "168": "DatatypeGetAccBalByCurrency",
    "169": "DatatypeGetAllAccBal",
    "170": "DatatypeGetCcyRateByCcy",
    "171": "DatatypeGetAccInfo",
    "172": "DatatypeGetPriceByCode",
    "173": "DatatypeSetApiLogPath",
    "174": "DatatypeLoadProductInfoListByCode",
    "175": "DatatypeLoadProductInfoListByMarket",
    "176": "DatatypeGetProductCount",
    "177": "DatatypeGetProduct",
    "178": "DatatypeGetProductByCode",
    "179": "DatatypeLoadInstrumentList",
    "180": "DatatypeGetInstrumentCount",
    "181": "DatatypeGetInstrument",
    "182": "DatatypeGetInstrumentByCode",
    "183": "DatatypeSetLanguageId",
    "184": "DatatypeSendMarketMakingOrder",
    "185": "DatatypeSubscribeQuoteRequest",
    "186": "DatatypeSubscribeAllQuoteRequest",
    "187": "DatatypeGetAllAccBalByArray",
    "188": "DatatypeGetOrdersByArray",
    "189": "DatatypeGetAllTradesByArray",
    "190": "DatatypeGetInstrumentByArray",
    "191": "DatatypeGetProductByArray",
    "192": "DatatypeGetAllPos",
    "193": "DatatypeGetAllPosByArray",
    "194": "DatatypeSendAccControl",
    "22": "DatatypeSendMMOrder",
    "23": "DatatypeDeleteOrder",
    "28": "DatatypeSetOrderInactive",
    "30": "DatatypePosCount",
    "34": "DatatypeGetPos",
    "35": "DatatypeTradeCount",
    "36": "DatatypeGetAllTrade",
    "40": "DatatypeUninitTicker",
    "47": "DatatypeGetLoginStatus",
    "53": "DatatypeLoadProductList",
    "64": "DatatypeOnLoginReply",
    "65": "DatatypeOnConnectedReply",
    "66": "DatatypeOnApiOrderRequestFailed",
    "67": "DatatypeOnApiOrderReport",
    "68": "DatatypeOnApiOrderBeforeSendReport",
    "69": "DatatypeOnAccountLoginReply",
    "70": "DatatypeOnAccountLogoutReply",
    "71": "DatatypeOnAccountInfoPush",
    "72": "DatatypeOnAccountPositionPush",
    "73": "DatatypeOnUpdatedAccountPositionPush",
    "74": "DatatypeOnUpdatedAccountBalancePush",
    "75": "DatatypeOnApiTradeReport",
    "76": "DatatypeOnApiPriceUpdate",
    "77": "DatatypeOnApiTickerUpdate",
    "78": "DatatypeOnPswChangeReply",
    "79": "DatatypeOnProductListByCodeReply",
    "80": "DatatypeOnInstrumentListReply",
    "81": "DatatypeOnBusinessDateReply",
    "82": "DatatypeOnApiMMOrderBeforeSendReport",
    "83": "DatatypeOnApiMMOrderRequestFailed",
    "84": "DatatypeOnApiQuoteRequestReceived",
    "85": "DatatypeOnApiAccountControlReply",
    "86": "DatatypeOnApiLoadTradeReadyPush",
}

spDatatypeNum = {
    "DatatypeInitialize": "128",
    "DatatypeSetLoginInfo": "129",
    "DatatypeLogin": "130",
    "DatatypeGetLoginStatus": "47",
    "DatatypeAddOrder": "132",
    "DatatypeAddInactiveOrder": "133",
    "DatatypeChangeOrder": "144",
    "DatatypeChangeOrderBy": "145",
    "DatatypeDeleteOrderBy": "146",
    "DatatypeDeleteAllOrders": "147",
    "DatatypeActivateAllOrders": "148",
    "DatatypeInactivateAllOrders": "149",
    "DatatypeActivateOrderBy": "150",
    "DatatypeInactivateOrderBy": "151",
    "DatatypeGetOrderCount": "152",
    "DatatypeGetOrderByOrderNo": "153",
    "DatatypeGetActiveOrders": "154",
    "DatatypeGetPosCount": "155",
    "DatatypeGetPosByProduct": "156",
    "DatatypeUninitialize": "157",
    "DatatypeLogout": "158",
    "DatatypeAccountLogin": "159",
    "DatatypeAccountLogout": "160",
    "DatatypeGetTradeCount": "161",
    "DatatypeGetAllTrades": "162",
    "DatatypeSubscribePrice": "163",
    "DatatypeSubscribeTicker": "164",
    "DatatypeChangePassword": "165",
    "DatatypeGetDllVersion": "166",
    "DatatypeGetAccBalCount": "167",
    "DatatypeGetAccBalByCurrency": "168",
    "DatatypeGetAllAccBal": "169",
    "DatatypeGetCcyRateByCcy": "170",
    "DatatypeGetAccInfo": "171",
    "DatatypeGetPriceByCode": "172",
    "DatatypeSetApiLogPath": "173",
    "DatatypeLoadProductInfoListByCode": "174",
    "DatatypeLoadProductInfoListByMarket": "175",
    "DatatypeGetProductCount": "176",
    "DatatypeGetProduct": "177",
    "DatatypeGetProductByCode": "178",
    "DatatypeLoadInstrumentList": "179",
    "DatatypeGetInstrumentCount": "180",
    "DatatypeGetInstrument": "181",
    "DatatypeGetInstrumentByCode": "182",
    "DatatypeSetLanguageId": "183",
    "DatatypeSendMarketMakingOrder": "184",
    "DatatypeSubscribeQuoteRequest": "185",
    "DatatypeSubscribeAllQuoteRequest": "186",
    "DatatypeGetAllAccBalByArray": "187",
    "DatatypeGetOrdersByArray": "188",
    "DatatypeGetAllTradesByArray": "189",
    "DatatypeGetInstrumentByArray": "190",
    "DatatypeGetProductByArray": "191",
    "DatatypeGetAllPos": "192",
    "DatatypeGetAllPosByArray": "193",
    "DatatypeSendAccControl": "194",
    "DatatypeSendMMOrder": "22",
    "DatatypeDeleteOrder": "23",
    "DatatypeSetOrderInactive": "28",
    "DatatypePosCount": "30",
    "DatatypeGetPos": "34",
    "DatatypeTradeCount": "35",
    "DatatypeGetAllTrade": "36",
    "DatatypeUninitTicker": "40",
    "DatatypeLoadProductList": "53",
    "DatatypeOnLoginReply": "64",
    "DatatypeOnConnectedReply": "65",
    "DatatypeOnApiOrderRequestFailed": "66",
    "DatatypeOnApiOrderReport": "67",
    "DatatypeOnApiOrderBeforeSendReport": "68",
    "DatatypeOnAccountLoginReply": "69",
    "DatatypeOnAccountLogoutReply": "70",
    "DatatypeOnAccountInfoPush": "71",
    "DatatypeOnAccountPositionPush": "72",
    "DatatypeOnUpdatedAccountPositionPush": "73",
    "DatatypeOnUpdatedAccountBalancePush": "74",
    "DatatypeOnApiTradeReport": "75",
    "DatatypeOnApiPriceUpdate": "76",
    "DatatypeOnApiTickerUpdate": "77",
    "DatatypeOnPswChangeReply": "78",
    "DatatypeOnProductListByCodeReply": "79",
    "DatatypeOnInstrumentListReply": "80",
    "DatatypeOnBusinessDateReply": "81",
    "DatatypeOnApiMMOrderBeforeSendReport": "82",
    "DatatypeOnApiMMOrderRequestFailed": "83",
    "DatatypeOnApiQuoteRequestReceived": "84",
    "DatatypeOnApiAccountControlReply": "85",
    "DatatypeOnApiLoadTradeReadyPush": "86",
}

@dataclass
class SPApiPos():

    Qty:            int = 0
    DepQty:         int = 0
    LongQty:        int = 0
    ShortQty:       int = 0
    TotalAmt:       float = 0.0
    DepTotalAmt:    float = 0.0
    LongTotalAmt:   float = 0.0
    ShortTotalAmt:  float = 0.0
    PLBaseCcy:      float = 0.0
    PL:             float = 0.0
    ExchangeRate:   float = 0.0
    AccNo:          str = ''
    ProdCode:       str = ''
    LongShort:      str = ''
    DecInPrice:     int = 0

    def len(self):
        return len(self.String().split(";"))

    def String(self):
        return (
                str(self.Qty)            + ';' +
                str(self.DepQty)         + ';' +
                str(self.LongQty)        + ';' +
                str(self.ShortQty)       + ';' +

                str(self.TotalAmt)       + ';' +
                str(self.DepTotalAmt)    + ';' +
                str(self.LongTotalAmt)   + ';' +
                str(self.ShortTotalAmt)  + ';' +
                str(self.PLBaseCcy)      + ';' +
                str(self.PL)             + ';' +
                str(self.ExchangeRate)   + ';' +

                self.AccNo               + ';' +
                self.ProdCode            + ';' +
                self.LongShort           + ';' +
                str(self.DecInPrice)
                )

@dataclass
class SPApiOrder():

    Price:          float = 0.0
    StopLevel:      float = 0.0
    UpLevel:        float = 0.0
    UpPrice:        float = 0.0
    DownLevel:      float = 0.0
    DownPrice:      float = 0.0
    ExtOrderNo:     int = 0
    IntOrderNo:     int = 0
    Qty:            int = 0
    TradedQty:      int = 0
    TotalQty:       int = 0
    ValidTime:      int = 0
    SchedTime:      int = 0
    TimeStamp:      int = 0
    OrderOptions:   int = 0

    AccNo:          str = ' '
    ProdCode:       str = ' '
    Initiator:      str = ' '
    Ref:            str = ' '
    Ref2:           str = ' '
    GatewayCode:    str = ' '
    ClOrderId:      str = ' '
    BuySell:        str = ' '
    StopType:       str = ' '
    OpenClose:      str = ' '

    CondType:       int = 0
    OrderType:      int = 0
    ValidType:      int = 0
    Status:         int = 0
    DecInPrice:     int = 0
    OrderAction:    int = 0
    UpdateTime:     int = 0
    UpdateSeqNo:    int = 0

    def len(self):
        return len(self.String().split(";"))

    def String(self):
        return (
                str(self.Price)          + ';' +
                str(self.StopLevel)      + ';' +
                str(self.UpLevel)        + ';' +
                str(self.UpPrice)        + ';' +
                str(self.DownLevel)      + ';' +
                str(self.DownPrice)      + ';' +

                str(self.ExtOrderNo)     + ';' +
                str(self.IntOrderNo)     + ';' +
                str(self.Qty)            + ';' +
                str(self.TradedQty)      + ';' +
                str(self.TotalQty)       + ';' +
                str(self.ValidTime)      + ';' +
                str(self.SchedTime)      + ';' +
                str(self.TimeStamp)      + ';' +
                str(self.OrderOptions)   + ';' +

                self.AccNo               + ';' +
                self.ProdCode            + ';' +
                self.Initiator           + ';' +
                self.Ref                 + ';' +
                self.Ref2                + ';' +
                self.GatewayCode         + ';' +
                self.ClOrderId           + ';' +
                self.BuySell             + ';' +
                self.StopType            + ';' +
                self.OpenClose           + ';' +

                str(self.CondType)       + ';' +
                str(self.OrderType)      + ';' +
                str(self.ValidType)      + ';' +
                str(self.Status)         + ';' +
                str(self.DecInPrice)     + ';' +
                str(self.OrderAction)    + ';' +
                str(self.UpdateTime)     + ';' +
                str(self.UpdateSeqNo)
                )

@dataclass
class SPApiMMOrder():
    BidExtOrderNo:  int = 0
    AskExtOrderNo:  int = 0
    BidAccOrderNo:  int = 0
    AskAccOrderNo:  int = 0
    BidPrice:       float = 0.0
    AskPrice:       float = 0.0
    BidQty:         int = 0
    AskQty:         int = 0
    SpecTime:       int = 0
    OrderOptions:   int = 0
    ProdCode:       str = ''
    AccNo:          str = ''
    ClOrderId:      str = ''
    OrigClOrdId:    str = ''
    OrderType:      int = 0
    ValidType:      int = 0
    DecInPrice:     int = 0

    def len(self):
        return len(self.String().split(";"))

    def String(self):
        return (
                str(self.BidExtOrderNo)  + ';' +
                str(self.AskExtOrderNo)  + ';' +
                str(self.BidAccOrderNo)  + ';' +
                str(self.AskAccOrderNo)  + ';' +
                str(self.BidPrice)       + ';' +
                str(self.AskPrice)       + ';' +
                str(self.BidQty)         + ';' +
                str(self.AskQty)         + ';' +
                str(self.SpecTime)       + ';' +
                str(self.OrderOptions)   + ';' +
                self.ProdCode            + ';' +
                self.AccNo               + ';' +
                self.ClOrderId           + ';' +
                self.OrigClOrdId         + ';' +
                str(self.OrderType)      + ';' +
                str(self.ValidType)      + ';' +
                str(self.DecInPrice)
                )


@dataclass
class SPApiTrade():

    RecNo:          int = 0

    Price:          float = 0.0
    
    TradeNo:        int = 0
    ExtOrderNo:     int = 0
    IntOrderNo:     int = 0
    Qty:            int = 0
    TradeDate:      int = 0
    TradeTime:      int = 0
    
    AccNo:          str = ''
    ProdCode:       str = ''
    Initiator:      str = ''
    Ref:            str = ''
    Ref2:           str = ''
    GatewayCode:    str = ''
    ClOrderId:      str = ''
    
    BuySell:        str = ''
    OpenClose:      str = ''
    
    Status:         int = 0
    DecInPrice:     int = 0
    
    OrderPrice:     float = 0.0
    
    TradeRef:       str = ''
    
    TotalQty:       int = 0
    RemainingQty:   int = 0
    TradedQty:      int = 0
    
    AvgTradedPrice: float = 0.0

    def len(self):
        return len(self.String().split(";"))

    def String(self):
        return (
                str(self.RecNo)          + ';' +
                str(self.Price)          + ';' +
                str(self.TradeNo)        + ';' +
                str(self.ExtOrderNo)     + ';' +
                str(self.IntOrderNo)     + ';' +
                str(self.Qty)            + ';' +
                str(self.TradeDate)      + ';' +
                str(self.TradeTime)      + ';' +
                self.AccNo               + ';' +
                self.ProdCode            + ';' +
                self.Initiator           + ';' +
                self.Ref                 + ';' +
                self.Ref2                + ';' +
                self.GatewayCode         + ';' +
                self.ClOrderId           + ';' +
                self.BuySell             + ';' +
                self.OpenClose           + ';' +
                str(self.Status)         + ';' +
                str(self.DecInPrice)     + ';' +
                str(self.OrderPrice)     + ';' +
                self.TradeRef            + ';' +
                str(self.TotalQty)       + ';' +
                str(self.RemainingQty)   + ';' +
                str(self.TradedQty)      + ';' +
                str(self.AvgTradedPrice)
                )

@dataclass
class SPApiMarket():
    
    MarketCode:     str = ''
    MarketName:     str = ''

    def len(self):
        return len(self.String().split(";"))

    def String(self):
        return (
                self.MarketCode          + ';' +
                self.MarketName
                )

@dataclass
class SPApiInstrument():

    Margin:         float = 0.0
    ContractSize:   float = 0.0
    MarketCode:     str = ''
    InstCode:       str = ''
    InstName:       str = ''
    InstName1:      str = ''
    InstName2:      str = ''
    Ccy:            str = ''
    # DecInPrice:     int = 0
    InstType:       str = ''

    def len(self):
        return len(self.String().split(";"))

    def String(self):
        return (
                str(self.Margin)         + ';' +
                str(self.ContractSize)   + ';' +
                self.MarketCode          + ';' +
                self.InstCode            + ';' +
                self.InstName            + ';' +
                self.InstName1           + ';' +
                self.InstName2           + ';' +
                self.Ccy                 + ';' +
                # str(self.DecInPrice)     + ';' +
                self.InstType
                )

@dataclass
class SPApiProduct():
    ProdCode:       str = ''
    ProdType:       str = ''
    ProdName:       str = ''
    Underlying:     str = ''
    InstCode:       str = ''
    ExpiryDate:     int = 0
    CallPut:        str = ''
    Strike:         int = 0
    LotSize:        int = 0
    ProdName1:      str = ''
    ProdName2:      str = ''
    OptStyle:       str = ''
    TickSize:       int = 0

    def len(self):
        return len(self.String().split(";"))

    def String(self):
        return (
                self.ProdCode        + ';' +
                self.ProdType        + ';' +
                self.ProdName        + ';' +
                self.Underlying      + ';' +
                self.InstCode        + ';' +
                str(self.ExpiryDate) + ';' +
                self.CallPut         + ';' +
                str(self.Strike)     + ';' +
                str(self.LotSize)    + ';' +
                self.ProdName1       + ';' +
                self.ProdName2       + ';' +
                self.OptStyle        + ';' +
                str(self.TickSize)
                )

@dataclass
class SPApiPrice():

    Bid:            List[float] = field(default_factory=list)
    BidQty:         List[int]   = field(default_factory=list)
    BidTicket:      List[int]   = field(default_factory=list)
    Ask:            List[float] = field(default_factory=list)
    AskQty:         List[int]   = field(default_factory=list)
    AskTicket:      List[int]   = field(default_factory=list)
    Last:           List[float] = field(default_factory=list)
    LastQty:        List[int]   = field(default_factory=list)
    LastTime:       List[int]   = field(default_factory=list)

    Equil:          float = 0.0
    Open:           float = 0.0
    High:           float = 0.0
    Low:            float = 0.0
    Close:          float = 0.0

    CloseDate:      int = 0

    TurnoverVol:    float = 0.0
    TurnoverAmt:    float = 0.0

    OpenInt:        int = 0

    ProdCode:       str = ''
    ProdName:       str = ''
    DecInPrice:     str = ''

    ExStateNo:      int = 0
    TradeStateNo:   int = 0

    Suspend:        bool = False
    ExpiryYMD:      int = 0
    ContractYMD:    int = 0
    Timestamp:      int = 0

    def len(self):
        return len(self.String().split(";"))

    def String(self):
        return ''

@dataclass
class SPApiTicker():
    Price:          float = 0.0
    Qty:            int = 0
    TickerTime:     int = 0
    DealSrc:        int = 0
    ProdCode:       str = ''
    DecInPrice:     str = ''

    def len(self):
        return len(self.String().split(";"))

    def String(self):
        return (
                str(self.Price)      + ';' +
                str(self.Qty)        + ';' +
                str(self.TickerTime) + ';' +
                str(self.DealSrc)    + ';' +
                self.ProdCode        + ';' +
                self.DecInPrice
                )

@dataclass
class SPApiAccInfo():
    NAV:            float = 0.0
    BuyingPower:    float = 0.0
    CashBal:        float = 0.0
    MarginCall:     float = 0.0
    CommodityPL:    float = 0.0
    LockupAmt:      float = 0.0
    CreditLimit:    float = 0.0
    MaxMargin:      float = 0.0
    MaxLoanLimit:   float = 0.0
    TradingLimit:   float = 0.0
    RawMargin:      float = 0.0
    IMargin:        float = 0.0
    MMargin:        float = 0.0
    TodayTrans:     float = 0.0
    LoanLimit:      float = 0.0
    TotalFee:       float = 0.0
    LoanToMR:       float = 0.0
    LoanToMV:       float = 0.0

    AccName:        str = ''
    BaseCcy:        str = ''
    MarginClass:    str = ''
    TradeClass:     str = ''
    ClientId:       str = ''
    AEId:           str = ''
    
    AccType:        str = ''
    CtrlLevel:      str = ''
    Active:         str = ''
    MarginPeriod:   str = ''

    def len(self):
        return len(self.String().split(";"))

    def String(self):
        return (
                str(self.NAV)            + ';' +
                str(self.BuyingPower)    + ';' +
                str(self.CashBal)        + ';' +
                str(self.MarginCall)     + ';' +
                str(self.CommodityPL)    + ';' +
                str(self.LockupAmt)      + ';' +
                str(self.CreditLimit)    + ';' +
                str(self.MaxMargin)      + ';' +
                str(self.MaxLoanLimit)   + ';' +
                str(self.TradingLimit)   + ';' +
                str(self.RawMargin)      + ';' +
                str(self.IMargin)        + ';' +
                str(self.MMargin)        + ';' +
                str(self.TodayTrans)     + ';' +
                str(self.LoanLimit)      + ';' +
                str(self.TotalFee)       + ';' +
                str(self.LoanToMR)       + ';' +
                str(self.LoanToMV)       + ';' +
                self.AccName             + ';' +
                self.BaseCcy             + ';' +
                self.MarginClass         + ';' +
                self.TradeClass          + ';' +
                self.ClientId            + ';' +
                self.AEId                + ';' +
                self.AccType             + ';' +
                self.CtrlLevel           + ';' +
                self.Active              + ';' +
                self.MarginPeriod
                )

@dataclass
class SPApiAccBal():
    CashBf:         float = 0.0
    TodayCash:      float = 0.0
    NotYetValue:    float = 0.0
    Unpresented:    float = 0.0
    TodayOut:       float = 0.0
    Ccy:            str = ''

    def len(self):
        return len(self.String().split(";"))

    def String(self):
        return (
                str(self.CashBf)         + ';' +
                str(self.TodayCash)      + ';' +
                str(self.NotYetValue)    + ';' +
                str(self.Unpresented)    + ';' +
                str(self.TodayOut)       + ';' +
                self.Ccy
                )



