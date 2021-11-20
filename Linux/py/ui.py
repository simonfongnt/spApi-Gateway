# from PyQt5.QtGui import (
#     QIcon,
# )
from PyQt5.QtCore import (
    # Qt,
    # QObject, 
    # QThread, 
    pyqtSlot,
    # pyqtSignal,
)

from PyQt5.QtWidgets import (
    # QApplication,
    QLabel,
    # QMainWindow,
    # QPushButton,
    # QVBoxLayout,
    # QWidget,    
    # QAction, 
    # QTabWidget,
    # QComboBox,
)

from PyQt5.QtWidgets import (
    # QApplication,
    QLabel,
    # QMainWindow,
    # QPushButton,
    # QVBoxLayout,
    # QWidget,
    
    # QAction, 
    # QTabWidget,
    QLineEdit, 
    # QInputDialog, 
    QDialog,
    QDialogButtonBox,
    QFormLayout,
    # QComboBox,
    # QTableWidget,
    # QTableWidgetItem,
    # QHeaderView,
    # QAbstractItemView,
    # QAbstractScrollArea,
    # QPlainTextEdit,
)

class ChangePWDialog(QDialog):
    def __init__(
            self, 
            oldPW,
            parent=None
            ):
        super().__init__(parent)

        self.oldPW = oldPW
        newPW = oldPW
        self.newPW = QLineEdit(self)
        self.newPW.setText(newPW)
        buttonBox = QDialogButtonBox(QDialogButtonBox.Ok, self)

        self.setWindowTitle("Change Password")
        layout = QFormLayout(self)
        layout.addRow("New Password", self.newPW)
        layout.addWidget(buttonBox)

        buttonBox.accepted.connect(self.accept)
        # buttonBox.rejected.connect(self.reject)

    def getInputs(self):
        return (self.oldPW, self.newPW.text())

class ChangeLoginDialog(QDialog):
    def __init__(
            self, 
            host,
            port,
            user_id,
            password,
            license,
            app_id,
            parent=None
            ):
        super().__init__(parent)

        self.label = QLabel("Saving will restart the Client")
        self.host       = QLineEdit(self)
        self.host.setText(str(host))
        self.port       = QLineEdit(self)
        self.port.setText(str(port))
        self.user_id    = QLineEdit(self)
        self.user_id.setText(str(user_id))
        self.password   = QLineEdit(self)
        self.password.setText(str(password))
        self.license    = QLineEdit(self)
        self.license.setText(str(license))
        self.app_id     = QLineEdit(self)
        self.app_id.setText(str(app_id))
        # buttonBox = QDialogButtonBox(QDialogButtonBox.Ok | QDialogButtonBox.Cancel, self);
        buttonBox = QDialogButtonBox(QDialogButtonBox.Ok, self)

        self.setWindowTitle("Change Login Details")
        layout = QFormLayout(self)
        layout.addRow(self.label)
        layout.addRow("Host",       self.host)
        layout.addRow("Port",       self.port)
        layout.addRow("User Id",    self.user_id)
        layout.addRow("Password",   self.password)
        layout.addRow("License",    self.license)
        layout.addRow("App Id",     self.app_id)
        layout.addWidget(buttonBox)

        buttonBox.accepted.connect(self.accept)
        # buttonBox.rejected.connect(self.reject)

    def getInputs(self):
        return (
            self.host.text(),
            int(self.port.text()),
            self.user_id.text(),
            self.password.text(),
            self.license.text(),
            self.app_id.text(),
            )