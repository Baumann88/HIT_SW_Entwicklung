from Tkinter import *
import Tix
import time

WINDOW_WIDTH=200
WINDOW_HEIGHT=430

Reve_SDO_COBID=0x583
Send_SDO_COBID=0x603

SDO_Read=0x40

TITLE="Monitor HubSystem"

Time_Intervall_Height=0.3
Time_Intervall_Druck=0.7
Time_Intervall_Temperatur=1.0
Time_Intervall_PWM=0.2

class WndHubMonitor:
    def __init__(self,ParaList):
        self.ParaList=ParaList
        self.IsOpen = 0
        self.width = WINDOW_WIDTH
        self.height = WINDOW_HEIGHT

        self.sendBuffer = []

        self.Height=[0,0,0,0]
        self.Druck=[0,0,0,0,0]
        self.PWMHeben = [0, 0, 0, 0]
        self.PWMSinken = [0, 0, 0, 0]
        self.temperatur=0.0

    # let the window in mitte of the display
    def SetWindowSize(self):
        Desktop = self.window.winfo_toplevel()
        desktopWidth = Desktop.winfo_screenwidth()
        desktopHeight = Desktop.winfo_screenheight()
        self.window.geometry("{0}x{1}+{2}+{3}".format(self.width, self.height, (desktopWidth - self.width) / 2,
                                                      (desktopHeight - self.height) / 2))


    # open the window
    def openWnd(self):
        self.window = Tix.Tk()
        self.window.title(TITLE)
        self.window.resizable(False, False)
        self.window.protocol("WM_DELETE_WINDOW", self.closeWnd)

        self.SetWindowSize()

        self.IsOpen = 2
        # define SubLayout===========================================================================
        self.Frame1 = Frame(self.window)
        self.Frame1.grid(row=0, column=0, padx=1, pady=1, sticky="nwes")
        # Init SubFrame==============================================================================
        self.Frame1Init()
        # ===========================================================================================
        self.timeStampHeight = time.clock()
        self.timeStampDruck = time.clock()
        self.timeStampTemperatur = time.clock()
        self.timeStampPWM = time.clock()
        self.MainLoop()

        self.window.mainloop()

    # close this Layout
    def closeWnd(self):
        # close this window
        # ===============
        self.IsOpen = 1

    def MainLoop(self):
        if self.IsOpen == 2:
            self.DataUpdate()
            self.DataShow()
            self.window.after(1, self.MainLoop)
        if self.IsOpen == 1:
            self.window.destroy()
            self.window = NONE
            self.IsOpen = 0

    # initial Frame 1
    def Frame1Init(self):
        #Sub Frame1 ###############################################################################
        self.LabelFrame11 = LabelFrame(self.Frame1, height=40, width=self.width, text="Temperatur")
        self.LabelFrame11.grid_propagate(0)
        self.LabelFrame11.grid(row=0, column=0, padx=0, pady=0, sticky=NE)

        self.LabelTemp=Label(self.LabelFrame11, text="temperatur: unknown")
        self.LabelTemp.grid(row=0, column=0, sticky=W)

        #Sub Frame 2 ##############################################################################
        self.LabelFrame12 = LabelFrame(self.Frame1, height=120, width=self.width, text="Height")
        self.LabelFrame12.grid_propagate(0)
        self.LabelFrame12.grid(row=1, column=0, padx=0, pady=0, sticky=NE)

        self.LabelDruckMain = Label(self.LabelFrame12, text="Druck in Hauptschlauch: unknown")
        self.LabelDruckMain.grid(row=0, column=0, sticky=W)
        self.LabelDruck11 = Label(self.LabelFrame12, text="Druck 11: unknown")
        self.LabelDruck11.grid(row=1, column=0, sticky=W)
        self.LabelDruck12 = Label(self.LabelFrame12, text="Druck 12: unknown")
        self.LabelDruck12.grid(row=2, column=0, sticky=W)
        self.LabelDruck21 = Label(self.LabelFrame12, text="Druck 21: unknown")
        self.LabelDruck21.grid(row=3, column=0, sticky=W)
        self.LabelDruck22 = Label(self.LabelFrame12, text="Druck 22: unknown")
        self.LabelDruck22.grid(row=4, column=0, sticky=W)

        # Sub Frame 3 ##############################################################################


        self.LabelFrame13 = LabelFrame(self.Frame1, height=100, width=self.width, text="Height")
        self.LabelFrame13.grid_propagate(0)
        self.LabelFrame13.grid(row=2, column=0, padx=0, pady=0, sticky=NE)

        self.LabelHeight11 = Label(self.LabelFrame13, text="Height 11: unknown")
        self.LabelHeight11.grid(row=0, column=0, sticky=W)
        self.LabelHeight12 = Label(self.LabelFrame13, text="Height 12: unknown")
        self.LabelHeight12.grid(row=1, column=0, sticky=W)
        self.LabelHeight21 = Label(self.LabelFrame13, text="Height 21: unknown")
        self.LabelHeight21.grid(row=2, column=0, sticky=W)
        self.LabelHeight22 = Label(self.LabelFrame13, text="Height 22: unknown")
        self.LabelHeight22.grid(row=3, column=0, sticky=W)

        self.LabelFrame14 = LabelFrame(self.Frame1, height=200, width=self.width, text="PWM Output")
        self.LabelFrame14.grid_propagate(0)
        self.LabelFrame14.grid(row=3, column=0, padx=0, pady=0, sticky=NE)

        self.LabelPWM11Heben = Label(self.LabelFrame14, text="PWM11 Heben: unknown")
        self.LabelPWM11Heben.grid(row=0, column=0, sticky=W)
        self.LabelPWM11Sinken = Label(self.LabelFrame14, text="PWM11 Sinken: unknown")
        self.LabelPWM11Sinken.grid(row=4, column=0, sticky=W)
        self.LabelPWM12Heben = Label(self.LabelFrame14, text="PWM12 Heben: unknown")
        self.LabelPWM12Heben.grid(row=1, column=0, sticky=W)
        self.LabelPWM12Sinken = Label(self.LabelFrame14, text="PWM12 Sinken: unknown")
        self.LabelPWM12Sinken.grid(row=5, column=0, sticky=W)
        self.LabelPWM21Heben = Label(self.LabelFrame14, text="PWM21 Heben: unknown")
        self.LabelPWM21Heben.grid(row=2, column=0, sticky=W)
        self.LabelPWM21Sinken = Label(self.LabelFrame14, text="PWM21 Sinken: unknown")
        self.LabelPWM21Sinken.grid(row=6, column=0, sticky=W)
        self.LabelPWM22Heben = Label(self.LabelFrame14, text="PWM22 Heben: unknown")
        self.LabelPWM22Heben.grid(row=3, column=0, sticky=W)
        self.LabelPWM22Sinken = Label(self.LabelFrame14, text="PWM22 Sinken: unknown")
        self.LabelPWM22Sinken.grid(row=7, column=0, sticky=W)



    # write the Frame
    def WriteFrame(self, ID, Data):
        self.sendBuffer.append(Data + [ID])


    # send the Data to CANopen Port
    def sendReq(self):
        tmp = self.sendBuffer
        self.sendBuffer = []
        return tmp


    # get the data from the CANopen Port
    def getMsg(self, ID, DATA, Time):
        if ID == Reve_SDO_COBID:
            if DATA[1:4] == self.ParaList["Druck11"]:
                tmpData = DATA[4] + (DATA[5] << 8) + (DATA[6] << 16) + (DATA[7] << 24)
                if tmpData > 2147483647: tmpData = tmpData - 4294967296
                self.Druck[0]= round(tmpData*0.001)
            elif DATA[1:4] == self.ParaList["Druck12"]:
                tmpData=DATA[4] + (DATA[5] << 8) + (DATA[6] << 16) + (DATA[7] << 24)
                if tmpData > 2147483647: tmpData = tmpData - 4294967296
                self.Druck[1]= round(tmpData*0.001)
            elif DATA[1:4] == self.ParaList["Druck21"]:
                tmpData = DATA[4] + (DATA[5] << 8) + (DATA[6] << 16) + (DATA[7] << 24)
                if tmpData > 2147483647: tmpData = tmpData - 4294967296
                self.Druck[2] = round(tmpData * 0.001)
            elif DATA[1:4] == self.ParaList["Druck22"]:
                tmpData = DATA[4] + (DATA[5] << 8) + (DATA[6] << 16) + (DATA[7] << 24)
                if tmpData > 2147483647: tmpData = tmpData - 4294967296
                self.Druck[3] = round(tmpData * 0.001)
            elif DATA[1:4] == self.ParaList["DruckMain"]:
                tmpData = DATA[4] + (DATA[5] << 8) + (DATA[6] << 16) + (DATA[7] << 24)
                if tmpData > 2147483647: tmpData = tmpData - 4294967296
                self.Druck[4] = round(tmpData * 0.001)
            elif DATA[1:4] == self.ParaList["DruckTemperatur"]:
                tmpData = DATA[4] + (DATA[5] << 8) + (DATA[6] << 16) + (DATA[7] << 24)
                if tmpData > 2147483647: tmpData = tmpData - 4294967296
                self.temperatur = tmpData * 0.001
            elif DATA[1:4] == self.ParaList["Height11"]:
                tmpData = DATA[4] + (DATA[5] << 8) + (DATA[6] << 16) + (DATA[7] << 24)
                self.Height[0]=tmpData
            elif DATA[1:4] == self.ParaList["Height12"]:
                tmpData = DATA[4] + (DATA[5] << 8) + (DATA[6] << 16) + (DATA[7] << 24)
                self.Height[1]=tmpData
            elif DATA[1:4] == self.ParaList["Height21"]:
                tmpData = DATA[4] + (DATA[5] << 8) + (DATA[6] << 16) + (DATA[7] << 24)
                self.Height[2]=tmpData
            elif DATA[1:4] == self.ParaList["Height22"]:
                tmpData = DATA[4] + (DATA[5] << 8) + (DATA[6] << 16) + (DATA[7] << 24)
                self.Height[3]=tmpData
            elif DATA[1:4] == self.ParaList["WegVentil11Heben"]:
                tmpData = DATA[4] + (DATA[5] << 8)
                self.PWMHeben[0]=tmpData
            elif DATA[1:4] == self.ParaList["WegVentil12Heben"]:
                tmpData = DATA[4] + (DATA[5] << 8)
                self.PWMHeben[1]=tmpData
            elif DATA[1:4] == self.ParaList["WegVentil21Heben"]:
                tmpData = DATA[4] + (DATA[5] << 8)
                self.PWMHeben[2]=tmpData
            elif DATA[1:4] == self.ParaList["WegVentil22Heben"]:
                tmpData = DATA[4] + (DATA[5] << 8)
                self.PWMHeben[3]=tmpData
            elif DATA[1:4] == self.ParaList["WegVentil11Sinken"]:
                tmpData = DATA[4] + (DATA[5] << 8)
                self.PWMSinken[0]=tmpData
            elif DATA[1:4] == self.ParaList["WegVentil12Sinken"]:
                tmpData = DATA[4] + (DATA[5] << 8)
                self.PWMSinken[1]=tmpData
            elif DATA[1:4] == self.ParaList["WegVentil21Sinken"]:
                tmpData = DATA[4] + (DATA[5] << 8)
                self.PWMSinken[2]=tmpData
            elif DATA[1:4] == self.ParaList["WegVentil22Sinken"]:
                tmpData = DATA[4] + (DATA[5] << 8)
                self.PWMSinken[3]=tmpData




    # update the data in Window
    def DataShow(self):
        self.LabelDruckMain['text'] = "Druck in Hauptschlauch: " + str(self.Druck[4]) + "bar"
        self.LabelDruck11['text'] = "Druck 11: " + str(self.Druck[0]) + "bar"
        self.LabelDruck12['text'] = "Druck 12: " + str(self.Druck[1]) + "bar"
        self.LabelDruck21['text'] = "Druck 21: " + str(self.Druck[2]) + "bar"
        self.LabelDruck22['text'] = "Druck 22: " + str(self.Druck[3]) + "bar"
        self.LabelHeight11['text'] = "Height 11: " + str(self.Height[0]) + "mm"
        self.LabelHeight12['text'] = "Height 12: " + str(self.Height[1]) + "mm"
        self.LabelHeight21['text'] = "Height 21: " + str(self.Height[2]) + "mm"
        self.LabelHeight22['text'] = "Height 22: " + str(self.Height[3]) + "mm"
        self.LabelTemp['text'] = "temperatur: " + str(self.temperatur) + " Grad"

        self.LabelPWM11Heben['text'] = "PWM11 Heben: " + str(self.PWMHeben[0])
        self.LabelPWM12Heben['text'] = "PWM12 Heben: " + str(self.PWMHeben[1])
        self.LabelPWM21Heben['text'] = "PWM21 Heben: " + str(self.PWMHeben[2])
        self.LabelPWM22Heben['text'] = "PWM22 Heben: " + str(self.PWMHeben[3])

        self.LabelPWM11Sinken['text'] = "PWM11 Sinken: " + str(self.PWMSinken[0])
        self.LabelPWM12Sinken['text'] = "PWM12 Sinken: " + str(self.PWMSinken[1])
        self.LabelPWM21Sinken['text'] = "PWM21 Sinken: " + str(self.PWMSinken[2])
        self.LabelPWM22Sinken['text'] = "PWM22 Sinken: " + str(self.PWMSinken[3])

    # update the data from CANopen
    def DataUpdate(self):
        if time.clock() - self.timeStampDruck > Time_Intervall_Druck:
            self.timeStampDruck = time.clock()
            if self.IsOpen:
                Data = [SDO_Read] + self.ParaList['Druck11'] + [0, 0, 0, 0]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.02)
                Data = [SDO_Read] + self.ParaList['Druck12'] + [0, 0, 0, 0]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.02)
                Data = [SDO_Read] + self.ParaList['Druck21'] + [0, 0, 0, 0]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.02)
                Data = [SDO_Read] + self.ParaList['Druck22'] + [0, 0, 0, 0]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.02)
                Data = [SDO_Read] + self.ParaList['DruckMain'] + [0, 0, 0, 0]
                self.WriteFrame(Send_SDO_COBID, Data)
        if time.clock() - self.timeStampHeight > Time_Intervall_Height:
            self.timeStampHeight = time.clock()
            if self.IsOpen:
                Data = [SDO_Read] + self.ParaList['Height11'] + [0, 0, 0, 0]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.02)
                Data = [SDO_Read] + self.ParaList['Height12'] + [0, 0, 0, 0]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.02)
                Data = [SDO_Read] + self.ParaList['Height21'] + [0, 0, 0, 0]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.02)
                Data = [SDO_Read] + self.ParaList['Height22'] + [0, 0, 0, 0]
                self.WriteFrame(Send_SDO_COBID, Data)
        if time.clock() - self.timeStampPWM > Time_Intervall_PWM:
            self.timeStampPWM = time.clock()
            if self.IsOpen:
                Data = [SDO_Read] + self.ParaList['WegVentil11Heben'] + [0, 0, 0, 0]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.02)
                Data = [SDO_Read] + self.ParaList['WegVentil12Heben'] + [0, 0, 0, 0]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.02)
                Data = [SDO_Read] + self.ParaList['WegVentil21Heben'] + [0, 0, 0, 0]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.02)
                Data = [SDO_Read] + self.ParaList['WegVentil22Heben'] + [0, 0, 0, 0]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.02)
                Data = [SDO_Read] + self.ParaList['WegVentil11Sinken'] + [0, 0, 0, 0]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.02)
                Data = [SDO_Read] + self.ParaList['WegVentil12Sinken'] + [0, 0, 0, 0]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.02)
                Data = [SDO_Read] + self.ParaList['WegVentil21Sinken'] + [0, 0, 0, 0]
                self.WriteFrame(Send_SDO_COBID, Data)
                time.sleep(0.02)
                Data = [SDO_Read] + self.ParaList['WegVentil22Sinken'] + [0, 0, 0, 0]
                self.WriteFrame(Send_SDO_COBID, Data)


        if time.clock() - self.timeStampTemperatur > Time_Intervall_Temperatur:
            self.timeStampTemperatur = time.clock()
            if self.IsOpen:
                Data = [SDO_Read] + self.ParaList['DruckTemperatur'] + [0, 0, 0, 0]
                self.WriteFrame(Send_SDO_COBID, Data)
