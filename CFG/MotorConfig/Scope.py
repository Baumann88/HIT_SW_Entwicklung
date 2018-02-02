from Tkinter import *
import time

MAX_RPM=3240.0

class RPMScope:
    def __init__(self,root,width,height):
        self.origin = [0, 0]
        self.gap_x = 48  # Randbreite des Fensters in x-Richtung
        self.gap_y = 6  # Randbreite des Fensters in y-Richtung
        self.step_width_x = 0  # Entfernung zwischen zwei Strichmarkierungen auf der Abszissenachse
        self.step_width_y = 0  # Entfernung zwischen zwei Strichmarkierungen auf der Ordinatenachse
        self.step_line_len = 5  # Strichlaenge der Strichmarkierungen an den Koordinatenachsen
        self.bg_color = "black"
        self.LengthX = 0
        self.LengthY = 0
        self.DeltaX = 0
        self.DeltaY = 0
        self.MaxDataValue=MAX_RPM
        self.yStartValue = 0-int(self.MaxDataValue)
        self.yInvervall = 270

        self.updateTimeStamp=0.0
        self.updateTime=0.2

        self.timeIntervallFactor=1
        self.count=0

        self.Data1=[]
        self.Data2=[]
        self.oldData1=[]
        self.oldData2=[]


        self.isOpen=0

        self.frame = root
        self.segments_x = 100  # Anzahl der Strichmarkierungen bzw. der Segemente auf der Abszissenachse
        self.segments_y = 24  # Anzahl der Strichmarkierungen bzw. der Segemente auf der Abszissenachse
        self.cv_width = width  # Breite des Canvas-Objektes
        self.cv_height = height - 20  # Hoehe des Canvas-Objektes

        self.create_CoordSys()

    def open(self):
        self.isOpen = 1

    def close(self):
        self.isOpen = 0

    def AddPopMenu(self,PopMenuObj):
        self.cv.bind("<Button-3>", lambda event: PopMenuObj.post(event.x_root, event.y_root))

    def getData(self,DATA1,DATA2):
        if self.isOpen==1 and len(self.Data1)<self.segments_x+1:
            if self.count==self.timeIntervallFactor:
                tmp=DATA1
                if tmp>32767:
                    tmp-=65536
                self.Data1.append(tmp)
                self.Data2.append(DATA2)
                self.count = 0
            self.count+=1

    def create_CoordSys(self):
        self.cv = Canvas(self.frame, width=self.cv_width, height=self.cv_height, bg=self.bg_color)
        self.cv.grid(row=0, column=0)

        # Abszissenachse
        x0 = self.gap_x
        x1 = self.cv_width
        self.LengthX = x1 - x0


        # Ordinatenachse
        x0 = self.gap_x
        y0 = self.cv_height - self.gap_y
        x1 = x0
        y1 = self.gap_y
        ca_y = self.cv.create_line(x0, y0, x1, y1,fill="white")
        self.LengthY = y0 - y1

        self.origin = [x0, y0]
        self.step_width_x = self.LengthX / self.segments_x  # Entfernung zwischen zwei Strichmarkierungen auf der Abszissenachse
        self.step_width_y = self.LengthY / self.segments_y  # Entfernung zwischen zwei Strichmarkierungen auf der Ordinatenachse

        # Speicherung des Koordinatenursprungs in der globalen Variable 'self.origin'
        self.origin = (self.cv.coords(ca_y)[0], self.cv.coords(ca_y)[1])

        # Vertikale graue Hilfslinien
        for i in range(self.segments_x):
            self.cv.create_line((self.origin[0] + (i + 1) * self.step_width_x, self.origin[1]),
                                (self.origin[0] + (i + 1) * self.step_width_x,
                                 self.origin[1] - self.step_width_y * self.segments_y),
                                fill="gray")

        # Horizontale graue Hilfslinien
        self.segments_y += 1
        for i in range(self.segments_y):
            if i == self.segments_y / 2:
                self.cv.create_line((self.origin[0], self.origin[1] - i * self.step_width_y),
                                    (self.origin[0] + self.step_width_x * self.segments_x,
                                     self.origin[1] - i * self.step_width_y),fill="white")

            else:
                self.cv.create_line((self.origin[0], self.origin[1] - i * self.step_width_y),
                                    (self.origin[0] + self.step_width_x * self.segments_x,
                                     self.origin[1] - i * self.step_width_y),
                                    fill="gray")

        # Beschriftung der Ordinatenachse
        for i in range(self.segments_y):
            t_x0 = self.cv.coords(ca_y)[0] - self.step_line_len
            t_y0 = self.cv.coords(ca_y)[1] - i * self.step_width_y
            self.cv.create_text((t_x0 - 10, t_y0), text=str(self.yStartValue + self.yInvervall * i), fill="white", anchor=E)

        self.FactorY = float(self.LengthY) / 2.0

        self.yOffset = self.step_width_y*0.88

    def PlotUpdate(self):
        if time.clock()-self.updateTimeStamp>self.updateTime:
            self.updateTimeStamp=time.clock()
            if len(self.Data1)==self.segments_x+1:
                for i in range(self.segments_x+1):
                    self.Data1[i] = int((1.0 - float(self.Data1[i]) / self.MaxDataValue) * self.FactorY + self.gap_y + self.step_width_y / 2 + self.yOffset)
                    self.Data2[i] = int((1.0 - float(self.Data2[i]) / self.MaxDataValue) * self.FactorY + self.gap_y + self.step_width_y / 2 + self.yOffset)
                if len(self.oldData1)>0:
                    for iItem in self.oldData1:
                        self.cv.delete(iItem)
                    self.oldData1 = []
                if len(self.oldData2) > 0:
                    for iItem in self.oldData2:
                        self.cv.delete(iItem)
                    self.oldData2 = []
                for i in range(self.segments_x):
                    IdLine=self.cv.create_line(self.origin[0]+i*self.step_width_x, self.Data1[i], self.origin[0]+(i+1)*self.step_width_x, self.Data1[i+1], fill="yellow")
                    self.oldData1.append(IdLine)
                    IdLine=self.cv.create_line(self.origin[0]+i*self.step_width_x, self.Data2[i], self.origin[0]+(i+1)*self.step_width_x, self.Data2[i+1], fill="red")
                    self.oldData2.append(IdLine)
                self.Data1 = []
                self.Data2 = []