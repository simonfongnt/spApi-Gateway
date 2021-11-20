# spApi-Gateway (Testing Tool)


## Requirements
- Python
- Executable (Windows or Linux)
- Broker Account with SPAPI

## Run the tool
`python3 test.py`

## Usage
Suppose the executable has been successfully created and the login details are entered via either modifying the `login.txt` or UI. The account can then be connected with this tool. 

Upon launching this program, the commands would be listed:
```
Commands:
help:            Print this page
exit:            Quit this program
raw:             Toggle raw details
callback:        Toggle callback details
price:           Toggle price callback
tick:            Toggle tick callback
login:           Begin login sequence
logout:          Logout from API
req [|inst|prod|acc|bal|pos|order|trade]:
                 Get desired request reply
last [|callback|acc|bal|price|tick|pos|order|trade]:
                 Get last callback data
order            Place an order
order pending:   Place a pending order
order activate:  Activate order
order inactivate:Inactivate order
order close:     Close an order
```
The executable will wait for `login` command. Before or after the login, the display settings can be changed. This program can show and log the callback messages and request responses.

### Display Setting
#### raw
Raw data output contains all fields of a datatype. Default is off.
#### callback
Callback data output shows every callback from API. Default is on.
#### price
With Callback is on, every price quotation would be showed. Default is off.
#### tick
With Callback is on, every tick would be showed. Default is off.

### Commands
#### login
This is the first command to startup the login procedure that consists of several commands such as `SPAPI_Login`, `SPAPI_AccountLogin`, `SPAPI_LoadInstrumentList`, `SPAPI_LoadProductInfoListByCode`, `SPAPI_SubscribePrice` and `SPAPI_SubscribeTicker`. Once this procedure is done, this tool shall be able to function with other commands.

#### logout
Logout would kill the executable. If running in UI, it will restart the executable itself.

#### req
There are numbers of options for Request command.
| Command  | Related API Function | Info |
| --- | --- | --- |
| req  | | send all the following requests  |
| req inst  | SPAPI_GetInstrumentCount | Number of available instruments |
| req prod  | SPAPI_GetProductCount | Number of available products |
| req acc  | SPAPI_GetAccInfo | Broker Account Details |
| req bal  | SPAPI_GetAccBalCount | Number of Account Balance |
| | SPAPI_GetAllAccBal | Account Balance Details |
| req pos  | SPAPI_GetPosCount | Number of Position |
| | SPAPI_GetAllPos | Position Details |
| | SPAPI_GetPosByProduct | Position Detail of Product |
| req order  | SPAPI_GetOrderCount | Number of Order |
| | SPAPI_GetActiveOrders | Order Details |
| req trade  | SPAPI_GetTradeCount | Number of Trade |
| | SPAPI_GetAllTrades | Trade Details |

#### last
There are numbers of `last` command to show data stored from callback.
| Command  | Related API Function | Info |
| --- | --- | --- |
| last callback | | shows all callback results  |
| last acc   | OnAccountInfoPush | Broker Account Details |
| last bal   | OnUpdatedAccountBalancePush | Account Balance Details |
| last price | OnApiPriceUpdate | Last Price Quotation |
| last tick  | OnApiTickerUpdate | Last Tick |
| last pos   | OnAccountPositionPush | Last Position Details |
| | OnUpdatedAccountPositionPush |  |
| | SPAPI_GetPosByProduct | Position Detail of Product |
| last order  | OnApiOrderRequestFailed | Order Details |
| | OnApiOrderReport | |
| | OnApiOrderBeforeSendReport | |
| last trade  | OnApiTradeReport | Trade Details |
| | OnApiLoadTradeReadyPush | |

#### order
Requires to select product to place an order (`SPAPI_AddOrder`). The order price would be +300 for Short order and -300 for Long order so that it cannot be trade at once.

#### order change
Requires to select position to change the order (`SPAPI_ChangeOrderBy`). Its order price will be changed to market price.

#### order pending
Requires to select product to place an pending order (`SPAPI_AddInactiveOrder`). The order price would be +300 for Short order and -300 for Long order so that it cannot be trade at once.

#### order activate [all]
Requires to select existing order to be activated (`SPAPI_ActivateOrderBy`). if `all` is entered, all existing orders will be activated (`SPAPI_ActivateAllOrders`).

#### order inactivate [all]
Requires to select existing order to be inactivated (`SPAPI_InactivateOrderBy`). if `all` is entered, all existing orders will be inactivated (`SPAPI_InactivateAllOrders`).

#### order close
Requires to select position to place an order (`SPAPI_AddOrder`). Selected position will be ordered with opposite quantity and market price.

#### order delete [all]
Requires to select existing order to be deleted (`SPAPI_DeleteOrderBy`). if `all` is entered, all existing orders will be deleted (`SPAPI_DeleteAllOrders`).