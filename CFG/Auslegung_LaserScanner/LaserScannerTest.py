import time
import threading

SEND_ID=0x602
RECE_ID=0x582

class LaserScannerTest:
    def __init__(self):
        self.receBuffer = []
        self.sendBuffer = []

        self.IsOpen=0

        self.LS1Slow = False
        self.LS1Warn = False
        self.LS1AbschaltCH1 = False
        self.LS1AbschaltCH2 = False
        self.LS1Quit = False

        self.LS2Slow = False
        self.LS2Warn = False
        self.LS2AbschaltCH1 = False
        self.LS2AbschaltCH2 = False
        self.LS2Quit = False

        self.taskMonitor = threading.Thread(name='Monitor', target=self.Task_LaserScannerMonitor)
        self.taskSend = threading.Thread(name='MsgSend', target=self.Task_LaserScannerSend)

    def openMonitor(self):
        self.taskMonitor.start()


    def AddCANPort(self, ObjCAN):
        self.objCAN = ObjCAN


    def Start(self):
        result = self.objCAN.open('USBBUS', '250K')
        print result
        if result == "Adapter: connected":
            self.IsOpen = 1
            self.taskSend.start()

    def Close(self):
        self.IsOpen = 0
        time.sleep(1)
        self.objCAN.close()
        print "Adapter: disconnected"


    # ===================================================================================================================
    # write the Frame
    def WriteFrame(self, ID, Data):
        self.sendBuffer.append(Data + [ID])

    def sendReq(self):
        tmp = self.sendBuffer
        self.sendBuffer = []
        return tmp

    # ===================================================================================================================
    # get the Frame
    def getMsg(self,ID,DATA,Time):
        self.DataLoggen(ID,DATA, Time)


    def DataLoggen(self, ID, DATA, Time):
        if ID == RECE_ID:
            if DATA[0]==0x43 and DATA[2]==0x62:
                if DATA[3]==0x17:
                    if DATA[4]==0x01: self.LS1Slow=True
                    else: self.LS1Slow=False
                elif DATA[3]==0x14:
                    if DATA[4]==0x01: self.LS1Warn=True
                    else: self.LS1Warn=False
                elif DATA[3] == 0x15:
                    if DATA[4] == 0x01: self.LS1AbschaltCH1 = True
                    else: self.LS1AbschaltCH1 = False
                elif DATA[3] == 0x21:
                    if DATA[4] == 0x01: self.LS1AbschaltCH2 = True
                    else: self.LS1AbschaltCH2 = False
                elif DATA[3] == 0x23:
                    if DATA[4] == 0x01: self.LS2Slow = True
                    else: self.LS1Slow = False
                elif DATA[3] == 0x20:
                    if DATA[4] == 0x01: self.LS2Warn = True
                    else: self.LS2Warn = False
                elif DATA[3] == 0x16:
                    if DATA[4] == 0x01: self.LS2AbschaltCH1 = True
                    else: self.LS2AbschaltCH1 = False
                elif DATA[3] == 0x22:
                    if DATA[4] == 0x01: self.LS2AbschaltCH2 = True
                    else: self.LS2AbschaltCH2 = False
                elif DATA[3] == 0x34:
                    if DATA[4] == 0x01: self.LS1Quit = True
                    else: self.LS1Quit = False
                elif DATA[3] == 0x35:
                    if DATA[4] == 0x01: self.LS2Quit = True
                    else: self.LS2Quit = False

    # ===================================================================================================================
    # cycle work
    def Task_LaserScannerSend(self):
        while True:
            self.WriteFrame(SEND_ID, [0x40, 0x00, 0x62, 0x17, 0x00, 0x00, 0x00, 0x00])
            time.sleep(0.1)
            self.WriteFrame(SEND_ID, [0x40, 0x00, 0x62, 0x14, 0x00, 0x00, 0x00, 0x00])
            time.sleep(0.1)
            self.WriteFrame(SEND_ID, [0x40, 0x00, 0x62, 0x15, 0x00, 0x00, 0x00, 0x00])
            time.sleep(0.1)
            self.WriteFrame(SEND_ID, [0x40, 0x00, 0x62, 0x21, 0x00, 0x00, 0x00, 0x00])
            time.sleep(0.1)
            self.WriteFrame(SEND_ID, [0x40, 0x00, 0x62, 0x23, 0x00, 0x00, 0x00, 0x00])
            time.sleep(0.1)
            self.WriteFrame(SEND_ID, [0x40, 0x00, 0x62, 0x20, 0x00, 0x00, 0x00, 0x00])
            time.sleep(0.1)
            self.WriteFrame(SEND_ID, [0x40, 0x00, 0x62, 0x16, 0x00, 0x00, 0x00, 0x00])
            time.sleep(0.1)
            self.WriteFrame(SEND_ID, [0x40, 0x00, 0x62, 0x22, 0x00, 0x00, 0x00, 0x00])
            time.sleep(0.1)
            self.WriteFrame(SEND_ID, [0x40, 0x00, 0x62, 0x34, 0x00, 0x00, 0x00, 0x00])
            time.sleep(0.1)
            self.WriteFrame(SEND_ID, [0x40, 0x00, 0x62, 0x35, 0x00, 0x00, 0x00, 0x00])
            time.sleep(0.1)
            if self.IsOpen==0: break;
        print "task send end!"

    # ===================================================================================================================
    # print
    def printLaserScanner(self,cmd):
        if cmd=="LS1":
            print "LS1 Warnfeld2 ist: " + str(self.LS1Slow)
            print "LS1 Warnfeld1 ist: " + str(self.LS1Warn)
            print "LS1 Abschalten ist: " + str(self.LS1AbschaltCH1 or self.LS1AbschaltCH2)
            print "LS1 Quittierung ist: " + str(self.LS1Quit)
        elif cmd=="LS2":
            print "LS2 Warnfeld2 ist: " + str(self.LS2Slow)
            print "LS2 Warnfeld1 ist: " + str(self.LS2Warn)
            print "LS2 Abschalten ist: " + str(self.LS2AbschaltCH1 or self.LS2AbschaltCH2)
            print "LS2 Quittierung ist: " + str(self.LS2Quit)


    # ===================================================================================================================
    # monitor
    def Task_LaserScannerMonitor(self):
        print "welcome to Laser Scanner Monitor"
        while True:
            cmd=raw_input("cmd: ")
            if cmd=="start":
                print "PeakCAN Start!"
                self.Start()
            elif cmd=="close":
                print "PeakCAN Close!"
                self.Close()
            elif cmd=="quit":
                print "App end! "
                self.Close()
                break
            elif cmd=="LS1":
                self.printLaserScanner("LS1")
            elif cmd=="LS2":
                self.printLaserScanner("LS2")