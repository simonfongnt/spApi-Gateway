from ctypes import DEFAULT_MODE
import os, sys, logging
# clientDir = os.path.abspath(sys.argv[0] + "/..")

from py.lib.uiParse import uiParse
from py.worker import Worker

from py.ui import (
    ChangePWDialog,
    ChangeLoginDialog,
)

# import json
import time

from PyQt5.QtCore import (
    pyqtSlot, 
    # pyqtSignal,
    # Qt, 
    # QObject, 
    QThread, 
)
from PyQt5.QtGui import QIcon

from PyQt5.QtWidgets import (
    # QApplication,
    # QLabel,
    # QMainWindow,
    # QPushButton,
    QVBoxLayout,
    QWidget,
    
    QAction, 
    # QTabWidget,
    # QLineEdit, 
    # QInputDialog, 
    # QDialog,
    # QDialogButtonBox,
    # QFormLayout,
    # QComboBox,
    # QTableWidget,
    # QTableWidgetItem,
    # QHeaderView,
    # QAbstractItemView,
    # QAbstractScrollArea,
    # QPlainTextEdit,
)

import json

class uiClass(
        uiParse,
        ):
    def __init__(
            self,
            ):
        uiParse   .__init__(self,)
        # Configuration                            
        self.params                 = {}

        self.updateTsLimit          = 1.0
        self.prevUpdateTs           = time.time()

        # apiTab elements - create after RESTful res
        self.apiTabtableWidget      = None
        self.apiTabQuoteApis        = {}
        self.apiTabTradeApis        = {}

        # orderTab elements - create after ledger received
        self.orderTabtableWidget    = None
        self.orderTabRemoveBtns     = {}
        self.ORDER                  = None

        # posTab elements - create after quotation
        self.posTabtableWidget      = None
        self.posTabBid              = {}
        self.posTabAsk              = {}
        self.posTabPrice            = {}
        self.posTabQty              = {}
        self.posTabCloseBtn         = {}
        self.POS                    = None

    def setupUi(self):

        # Title - BEGIN
        self.left = 0
        self.top = 0
        self.width = 800
        self.height = 500
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)
        # self.resize(300, 150)    
        # Title - END    

        # centralWidget - BEGIN
        self.centralWidget = QWidget()
        layout = QVBoxLayout()

        # centralWidget > menuBar - BEGIN
        mainMenu = self.menuBar()
        fileMenu = mainMenu.addMenu('File')
        helpMenu = mainMenu.addMenu('Help')

        changeLoginButton = QAction('Change Login', self)
        changeLoginButton.triggered.connect(self.showChangeLoginUi)
        fileMenu.addAction(changeLoginButton)
        changePWButton = QAction('Change Password', self)
        changePWButton.triggered.connect(self.showChangePWUi)
        fileMenu.addAction(changePWButton)
        # fileMenu.addAction(ChangePWButton)

        exitButton = QAction('Exit', self)
        exitButton.setShortcut('Ctrl+Q')
        exitButton.setStatusTip('Exit application')
        exitButton.triggered.connect(self.close)
        fileMenu.addAction(exitButton)
        
        self.worker = Worker(self)
        self.worker.exec = self.workerExec

        layout.addWidget(self.worker.widget)
        
        # centralWidget - END
        self.centralWidget.setLayout(layout)
        self.setCentralWidget(self.centralWidget)

    def getLogin(
            self,
            path,
            ):
        self.loginPath = path
        file = open(path, 'r')
        lines = file.readlines()
        
        count = 0
        # Strips the newline character
        self.host       = lines[0].strip()
        self.port       = int(lines[1].strip())
        self.user_id    = lines[2].strip()
        self.password   = lines[3].strip()
        self.license    = lines[4].strip()
        self.app_id     = lines[5].strip()
    
    def updateLogin(
            self,
            host,
            port,
            user_id,
            password,
            license,
            app_id,
            ):
        f = open(
            self.loginPath, 
            'w',
            )        
        # Strips the newline character
        f.write("%s\n" % host)
        f.write("%d\n" % port)
        f.write("%s\n" % user_id)
        f.write("%s\n" % password)
        f.write("%s\n" % license)
        f.write("%s\n" % app_id)
        f.close()

    def updatePassword(
            self,
            newPW,
            ):
        self.password = newPW
        self.updateLogin(
            self.host,
            self.port,
            self.user_id,
            self.password,
            self.license,
            self.app_id,
        )

    def showChangePWUi(self):
        dialog = ChangePWDialog(
            oldPW = self.password,
        )
        if dialog.exec():
            oldPW, newPW = dialog.getInputs()
            if not oldPW or not newPW:
                self.close
            self.updatePassword(
                newPW,
            )

    def showChangeLoginUi(self):
        dialog = ChangeLoginDialog(
            self.host,
            self.port,
            self.user_id,
            self.password,
            self.license,
            self.app_id,
        )
        if dialog.exec():
            self.host, self.port, self.user_id, self.password, self.license, self.app_id = dialog.getInputs()
            self.updateLogin(
                self.host,
                self.port,
                self.user_id,
                self.password,
                self.license,
                self.app_id,
            )
            # restart process
            self.worker.killProc()

    def closeEvent(self, event):
        print(
            'closeEvent',
        )
        self.worker.kill()
        event.accept() # let the window close

    def initQThread(self):
        # Step 2: Create a QThread object
        self.thread = QThread()
        # # Step 3: Create a worker object
        # self.worker = Worker()
        # Step 4: Move worker to the thread
        self.worker.moveToThread(self.thread)
        # Step 5: Connect signals and slots
        self.thread.started.connect(self.worker.run)
        self.worker.finished.connect(self.thread.quit)
        self.worker.finished.connect(self.worker.deleteLater)
        self.thread.finished.connect(self.thread.deleteLater)
        # self.worker.progress.connect(self.reportProgress)
        # Step 6: Start the thread
        self.thread.start()
        
    def loginClick(self):
        self.initQThread()

    def countClicks(self):
        self.clicksCount += 1
        self.clicksLabel.setText(f"Counting: {self.clicksCount} clicks")

    def submitClicks(self):
        rCode = self.configDfs['RCODE'].copy()
        for k, v in self.apiTabQuoteApis.items():
            rCode.loc[rCode['ID'] == k, 'SUB'] = v.currentText()
        for k, v in self.apiTabTradeApis.items():
            rCode.loc[rCode['ID'] == k, 'TRD'] = v.currentText()
        self.worker.recvMainCmds(
            'codeInfo',
            rCode,
        )

    def closeClicks(
            self,
            code,
            ):
        print(
            'closeClicks',
            code,
        )

    # def reportProgress(self, params):
    #     self.params = params
    #     if (
    #             len(params)
    #         and params[0]
    #             ):
    #         logging.debug(params[0])