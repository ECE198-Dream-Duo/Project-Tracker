import subprocess
import pkg_resources
import sys

required_packages = ['pyqt5', 'pyserial']

def install(package):
    subprocess.check_call([sys.executable, "-m", "pip", "install", package])

def check_and_install_packages():
    for package in required_packages:
        try:
            pkg_resources.require(package)
        except pkg_resources.DistributionNotFound:
            print(f"{package} is not installed.")
            print(f"Installing {package}")
            install(package)
        except pkg_resources.VersionConflict:
            print(f"{package} version is installed and incompatible.")


check_and_install_packages()

from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QPushButton
import serial.tools.list_ports
import serial
import time
import threading

def read_uart(stop_event, port, baud_rate):
    try:
        with serial.Serial(port, baud_rate, timeout=1) as ser:
            while not stop_event.is_set():
                if ser.in_waiting:
                    data = ser.readline().decode('utf-8').rstrip()
                    print(f"Received: {data}")
                else:
                    time.sleep(0.1)  # Short sleep to prevent tight loop
    except serial.SerialException as e:
        print(f"Error: {e}")

class SerialPortSelector(QWidget):
    global COM_PORT
    def __init__(self):
        super().__init__()
        self.initUI()
        self.COM_PORT = 'COM'
        self.BAUD_RATE = 9600  
        self.uart_thread = None
        self.stop_event = threading.Event()

    def ChangeCOM_Port(self, p):
        self.COM_PORT=p
        print(self.COM_PORT)

    def initUI(self):
        self.setWindowTitle('Select Serial Port')
        layout = QVBoxLayout()
        ports = serial.tools.list_ports.comports()
        for port in ports:
            btn = QPushButton(port.device, self)
            btn.clicked.connect(lambda checked, p=port.device : self.ChangeCOM_Port(p))
            btn.clicked.connect(lambda checked, p=port.device: self.start_uart_thread(p))
            layout.addWidget(btn)

        self.setLayout(layout)
        self.setGeometry(300, 300, 300, 150)
    
    def start_uart_thread(self, port):
        if self.uart_thread is not None:
            self.stop_event.set()
            self.uart_thread.join()

        self.stop_event.clear()
        self.uart_thread = threading.Thread(target=read_uart, args=(self.stop_event, port, 9600))
        self.uart_thread.start()

    def closeEvent(self, event):
        if self.uart_thread is not None:
            self.stop_event.set()
            self.uart_thread.join(timeout=2)  # Wait for 2 seconds
        if self.uart_thread.is_alive():
            print("Thread did not exit in time. It may still be running.")
        super().closeEvent(event)

app = QApplication(sys.argv)
ex = SerialPortSelector()
ex.show()
sys.exit(app.exec_())