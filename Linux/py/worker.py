import os, sys
# clientDir = os.path.abspath(sys.argv[0] + "/..")
# print(os.getcwd())
# os.chdir(getattr(sys, '_MEIPASS', os.path.dirname(os.path.abspath(__file__))))

from PyQt5.QtCore import (
    # pyqtSlot, 
    pyqtSignal,
    # Qt, 
    QObject, 
    QThread, 
)
from PyQt5.QtWidgets import (
    QPlainTextEdit,
)
# import time
# import logging
# from queue import Queue
# from threading import Thread, Event
from threading import Event
import subprocess
# import datetime
# import json
# import pandas as pd
import datetime
# from dateutil import tz
# import signal
# from multiprocessing import Process, Manager, freeze_support

class Worker(QObject):
    # signals from MainWindow
    finished = pyqtSignal()
    # # progress = pyqtSignal(int)
    # progress = pyqtSignal(list)

    appendPlainText = pyqtSignal(str)
    def __init__(
            self,
            parent,
            ):
        super().__init__()
        QObject.__init__(self)
        self.widget = QPlainTextEdit(parent)
        self.widget.setReadOnly(True)
        self.appendPlainText.connect(self.widget.appendPlainText)

        self.killWorkerEvent = Event()
        self.killWorkerEvent.clear()

        # self.exePath    = None
        self.exec       = []
        self.p          = None

    def kill(self):
        self.killWorkerEvent.set()          # send kill event
        self.killProc()

    def killProc(self):
        self.p.kill()                       # kill running proc
        self.p.terminate()
        while self.p.poll() is None: pass   # wait until proc dead

    mainCmds = []
    def recvMainCmds(self, cmd, v):
        self.mainCmds.append([cmd, v])

    def run(self):
        # keep restarting until worker is killed
        while not self.killWorkerEvent.isSet():
            self.p = subprocess.Popen(
                self.exec,
                # shell=True,             # required if pyinstaller --noconsole in Windows
                stdout=subprocess.PIPE, 
                stderr=subprocess.STDOUT,
                # stderr=subprocess.PIPE, # required if pyinstaller --noconsole in Windows
                # stdin=subprocess.PIPE,  # required if pyinstaller --noconsole in Windows
                )
            # monitor if proc is existed
            while self.p.poll() is None:       
                try:
                    line = self.p.stdout.readline()
                    if line:
                        self.appendPlainText.emit(
                            line.decode(),
                            )
                except Exception as e:
                    print(e)

        self.finished.emit()