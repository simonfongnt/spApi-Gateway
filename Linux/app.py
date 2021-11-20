import os, sys
clientDir = os.path.abspath(sys.argv[0] + "/..")
# print(clientDir)
# # print(os.getcwd())
# # os.chdir(getattr(sys, '_MEIPASS', os.path.dirname(os.path.abspath(__file__))))
# # print(os.getcwd())
dataDir = getattr(sys, '_MEIPASS', os.path.dirname(os.path.abspath(__file__)))
# print(dataDir)

from py.lib.uiClass import (
    uiClass,
)

from PyQt5.QtCore import (
    # Qt,
    # QObject, 
    # QThread, 
    pyqtSlot,
    # pyqtSignal,    
)

from PyQt5.QtWidgets import (
    QApplication,
    # QLabel,
    QMainWindow,
    # QPushButton,
    # QVBoxLayout,
    # QWidget,    
    # QAction, 
    # QTabWidget,
    # QComboBox,
)

# from PyQt5.QtGui import (
#     QIcon,
# )


class Window(
        QMainWindow,
        uiClass,
        ):
    def __init__(self, parent=None):
        super().__init__(parent)
        # QMainWindow.__init__(parent)
        uiClass.__init__(self,)

        self.getLogin(
            os.path.join(
                # clientDir,
                'login.txt',
                ),
            )
        self.workerExec = [
            'sh',
            os.path.join(
                # clientDir,
                dataDir,
                'spGateway.sh',
                ),
        ]
        self.title = 'SPAPI Gateway'
        self.setupUi()
        self.initQThread()        

app = QApplication(sys.argv)
win = Window()
win.show()
sys.exit(app.exec())
