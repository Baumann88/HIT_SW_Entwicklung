from PCANBasic import *
from ThreadTimer import *

class CANopenPort:
    def __init__(self):

        self.List_CHANNELS = {'DNGBUS': PCAN_DNGBUS1,
                           'PCCBUS': PCAN_PCCBUS1,
                           'ISABUS': PCAN_ISABUS1,
                           'PCIBUS': PCAN_PCIBUS1,
                           'USBBUS': PCAN_USBBUS1}

        self.List_BAUDRATES = {'1M': PCAN_BAUD_1M,
                            '800K': PCAN_BAUD_800K,
                            '500K': PCAN_BAUD_500K,
                            '250K': PCAN_BAUD_250K,
                            '125K': PCAN_BAUD_125K}

        self.interfaceList=[]
        self.objPCAN = PCANBasic()
        self.newMsg = TPCANMsgFD()
        self.taskRX = TimerTask("Rx", 0.0001, self.TaskRxEvent)
        self.taskTX = TimerTask("Tx", 0.0001, self.TaskTxEvent)
        self.isOpen=0
        self.channel=PCAN_USBBUS1
        self.baudrate=PCAN_BAUD_250K
        self.hwtype=PCAN_TYPE_ISA
        self.ioport=0x2A0
        self.interrupt=11


    def open(self,channel, baudrate):
        self.channel=self.List_CHANNELS[channel]
        self.baudrate=self.List_BAUDRATES[baudrate]
        result = self.objPCAN.Initialize(self.channel, self.baudrate, self.hwtype, self.ioport, self.interrupt)
        if result != PCAN_ERROR_OK:
            err = self.objPCAN.GetErrorText(result)
        else:
            err= "Adapter: connected"
            self.taskRX.start()
            self.taskTX.start()
            self.isOpen = 1
        return err

    def close(self):
        self.taskTX.stop()
        self.taskRX.stop()
        self.objPCAN.Uninitialize(self.channel)
        self.isOpen=0
        print "CANopen Port is closed"



    def addInterface(self,InterfaceObj):
        self.interfaceList.append(InterfaceObj)

    # Timer for Read Event
    def TaskRxEvent(self):
        self.ReadMessages()

    def TaskTxEvent(self):
        for iInterface in self.interfaceList:
            theMsg = iInterface.sendReq()
            if len(theMsg) > 0:
                for iMsg in theMsg:
                    DataLen = len(iMsg) - 1
                    if DataLen >=0:
                        Data = iMsg[0:DataLen]
                        ID = iMsg[DataLen]
                        self.SendMessage(ID, DataLen, Data)

    # Message Process
    def ProcessMessage(self, *args):
        # Split the arguments. [0] TPCANMsg, [1] TPCANTimestamp
        #
        theMsg = args[0][0]
        itsTimeStamp = args[0][1]
        time = itsTimeStamp.micros + 1000 * itsTimeStamp.millis + 0x100000000 * 1000 * itsTimeStamp.millis_overflow
        for iInterface in self.interfaceList:
            iInterface.getMsg(theMsg.ID,theMsg.DATA,time)


    def ReadMessage(self):
        # We execute the "Read" function of the PCANBasic
        #
        result = self.objPCAN.Read(self.channel)

        if result[0] == PCAN_ERROR_OK:
            # We show the received message
            self.ProcessMessage(result[1:])

        return result[0]

    def ReadMessages(self):
        stsResult = PCAN_ERROR_OK
        while self.isOpen and (not (stsResult & PCAN_ERROR_QRCVEMPTY)):
            stsResult = self.ReadMessage()
            if stsResult == PCAN_ERROR_ILLOPERATION:
                break

    # write the Frame
    def SendMessage(self, ID, Len, Data):
        CANMsg = TPCANMsg()
        CANMsg.ID = ID
        CANMsg.LEN = Len
        CANMsg.MSGTYPE = PCAN_MESSAGE_STANDARD

        for i in range(Len):
            CANMsg.DATA[i] = Data[i]
        result = self.objPCAN.Write(self.channel, CANMsg)

        stsReturn=self.objPCAN.GetErrorText(result, 0)

        if stsReturn[0] != PCAN_ERROR_OK:
            print "An error occurred. Error-code's text ({0:X}h) couldn't be retrieved".format(result)


