import sys
from PyQt5.uic import loadUi
from PyQt5 import QtWidgets, QtCore, QtGui
from PyQt5.QtWidgets import QDialog, QApplication, QWidget, QStackedWidget, QMainWindow
from PyQt5.QtCore import Qt, QPoint


class StartScreen(QMainWindow):
    def __init__(self):
        super(StartScreen, self).__init__()
        loadUi("start.ui", self)
        self.login.clicked.connect(self.gotologin)

    def gotologin(self):
        login = LoginScreen()
        login.setWindowFlags(QtCore.Qt.FramelessWindowHint)
        login.setAttribute(QtCore.Qt.WA_TranslucentBackground)
        login.setFixedSize(350, 480)
        login.exec()


class LoginScreen(QDialog):
    def __init__(self):
        super(LoginScreen, self).__init__()
        loadUi("login.ui", self)

    def mousePressEvent(self, event):
        if event.button() == QtCore.Qt.LeftButton:
            self.offset = event.pos()
        else:
            super().mousePressEvent(event)

    def mouseMoveEvent(self, event):
        if self.offset is not None and event.buttons() == QtCore.Qt.LeftButton:
            self.move(self.pos() + event.pos() - self.offset)
        else:
            super().mouseMoveEvent(event)

    def mouseReleaseEvent(self, event):
        self.offset = None
        super().mouseReleaseEvent(event)


#main
app = QApplication(sys.argv)
start = StartScreen()
start.setFixedSize(900, 600)
start.show()

try:
    sys.exit(app.exec())
except:
    print("Exiting")
