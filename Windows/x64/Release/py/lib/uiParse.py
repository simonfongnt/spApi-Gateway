

from PyQt5.QtCore import (
    pyqtSlot, 
    pyqtSignal,
    Qt, 
    QObject, 
    QThread, 
)
from PyQt5.QtGui import QIcon

from PyQt5.QtWidgets import (
    QApplication,
    QLabel,
    QMainWindow,
    QPushButton,
    QVBoxLayout,
    QWidget,
    
    QMainWindow, 
    QApplication, 
    QPushButton, 
    QWidget, 
    QAction, 
    QTabWidget,
    QVBoxLayout,
    QWidget, 
    QPushButton, 
    QLineEdit, 
    QInputDialog, 
    QApplication, 
    QLabel,
    QDialog,
    QDialogButtonBox,
    QFormLayout,
    QComboBox,
    QTableWidget,
    QTableWidgetItem,
    QHeaderView,
    QAbstractItemView,
    QAbstractScrollArea,
)

class uiParse(
        ):
    
    def __init__(
            self,
            ):
        pass

    def getApiTabtableHeader(
            self,
            ):
        return (
            "ID",
            "Market",
            "Product",
            "Product Type",
            "Transaction Date",
            "Strike Price",
            "Quotation From",
            "Trading On",
            )    

    def addApiTabTableRow(
            self,
            i,
            row,
            tableWidget,
            apiLs,
            ):
        tableWidget.setItem(i,0, QTableWidgetItem(row['ID']))
        tableWidget.setItem(i,1, QTableWidgetItem(row['MKT']))
        tableWidget.setItem(i,2, QTableWidgetItem(row['PROD']))
        tableWidget.setItem(i,3, QTableWidgetItem(row['PTYPE']))
        tableWidget.setItem(i,4, QTableWidgetItem(row['T']))
        tableWidget.setItem(i,5, QTableWidgetItem(row['Strike']))
        
        # creating a combo box widget
        quoteComboBox = QComboBox()# geek list
        # adding list of items to combo box
        quoteComboBox.addItems(
            list(apiLs),
            )
        # creating editable combo box
        quoteComboBox.setEditable(True)    
        # setting insertion policy
        # stopping insertion
        quoteComboBox.setInsertPolicy(QComboBox.NoInsert)
        quoteComboBox.setCurrentIndex(
            apiLs.index(row['SUB']) if row['SUB'] in apiLs else 0
            )
        tableWidget.setCellWidget(i,6, quoteComboBox)
        
        # creating a combo box widget
        tradeComboBox = QComboBox()# geek list
        # adding list of items to combo box
        tradeComboBox.addItems(
            list(apiLs),
            )
        # creating editable combo box
        tradeComboBox.setEditable(True)    
        # setting insertion policy
        # stopping insertion
        tradeComboBox.setInsertPolicy(QComboBox.NoInsert)
        tradeComboBox.setCurrentIndex(
            apiLs.index(row['TRD']) if row['TRD'] in apiLs else 0
            )
        tableWidget.setCellWidget(i,7, tradeComboBox)
        return quoteComboBox, tradeComboBox

    def getPosTabtableHeader(
            self,
            ):
        return (
            "Code",
            "Bid$",
            "Ask$",
            "Order$",
            "Qty",
            "Close?",
            )    

    def addPosTabTableRow(
            self,
            i,
            k,
            v,
            tableWidget,
            ):
        tableWidget.setItem(i,0, QTableWidgetItem(k))

        bid = QLabel('0', self)
        tableWidget.setCellWidget(i,1, bid)
        ask = QLabel('0', self)
        tableWidget.setCellWidget(i,2, ask)
        price = QLabel('0', self)
        tableWidget.setCellWidget(i,3, price)
        qty = QLabel('0', self)
        tableWidget.setCellWidget(i,4, qty)
        closeBtn = QPushButton("Close")
        closeBtn.clicked.connect(lambda: self.closeClicks(k))
        tableWidget.setCellWidget(i,5, closeBtn)

        return bid, ask, price, qty, closeBtn

    def getOrderTabtableHeader(
            self,
            ):
        return (
            "Timestamp",
            "Time",
            "SID",
            "GID",
            "Api",
            "#",
            "Code",
            "Order",
            "Price",
            "Qty",
            "Status",
            "Remove?",
            )

    def addOrderTabTableRow(
            self,
            i,
            row,
            tableWidget,
            ):
        tableWidget.setItem(i,0, QTableWidgetItem(str(row['TIMESTAMP'])))
        tableWidget.setItem(i,1, QTableWidgetItem(row['TIME']))
        tableWidget.setItem(i,2, QTableWidgetItem(str(row['SID'])))
        tableWidget.setItem(i,3, QTableWidgetItem(str(row['GID'])))
        tableWidget.setItem(i,4, QTableWidgetItem(row['API']))
        tableWidget.setItem(i,5, QTableWidgetItem(str(row['REF'])))
        tableWidget.setItem(i,6, QTableWidgetItem(row['CODE']))
        tableWidget.setItem(i,7, QTableWidgetItem(row['ORDER']))
        tableWidget.setItem(i,8, QTableWidgetItem(str(row['PRICE'])))
        tableWidget.setItem(i,9, QTableWidgetItem(str(row['QTY'])))
        tableWidget.setItem(i,10, QTableWidgetItem(row['STATUS']))

        removeBtn = QPushButton("Remove")
        removeBtn.clicked.connect(lambda: self.removeClicks(row['REF']))
        tableWidget.setCellWidget(i,11, removeBtn)

        return removeBtn

    def isTableChange(
            self,
            prevDf,
            thisDf,
            ):
        # quick check
        if len(prevDf) != len(thisDf):
            return True
        if not prevDf.equals(thisDf):
            return True
        return False

    def isDictChange(
            self,
            prev,
            this,
            ):
        # quick check
        if not prev == this:
            return True
        return False