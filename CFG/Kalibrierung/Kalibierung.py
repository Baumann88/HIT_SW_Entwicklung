import xlrd
from xlutils.copy import copy
import matplotlib.pyplot as plt
import numpy as np
import math
from scipy.optimize import curve_fit

WorkSpacePath="..\Kalibrierung"



def funcDriveModule(x,p1,p2):
  return p1*x+p2

def funcHubModule(x,p1,p2):
  return p1*x+p2

def funcRCKurve(x,p1,p2,p3,p4):
  return p1*pow(x,3)+p2*pow(x,2)+p3*x+p4

def KalibierungDriveSys(FilePath):
    try:
        read_File = xlrd.open_workbook(FilePath + '\Messung.xlsx')
        sheet = read_File.sheet_by_index(0)
        write_File = copy(read_File)
        write_sheet = write_File.get_sheet(0)

    except IOError:
        print "no xls file for Kalibierung"
        return

    iEntry=1
    xdata=[]
    ydata=[]
    while True:
        try:
            TmpValue = float(sheet.cell(iEntry, 2).value)
            xdata.append(TmpValue)
            TmpValue = float(sheet.cell(iEntry, 1).value)
            ydata.append(TmpValue)
            iEntry+=1
        except:
            if iEntry>2:
                xdataArray = np.array(xdata)
                ydataArray = np.array(ydata)
                popt, pcov = curve_fit(funcDriveModule, xdataArray, ydataArray)
                print popt[0]
                print popt[1]
                write_sheet.write(1, 3, str(popt[0]))
                write_sheet.write(2, 3, str(popt[1]))
                tmp=int(round(popt[0],3)*1000.0)
                if tmp < 0: tmp+=4294967296
                print hex(tmp)
                tmp=int(round(popt[1],3)*1000.0)
                if tmp < 0: tmp += 4294967296
                print hex(tmp)
                plt.figure(1)
                plt.scatter(xdataArray, ydataArray)
                plt.plot(xdataArray,funcDriveModule(xdataArray,popt[0],popt[1]),'k')
                plt.show()
                try: write_File.save(FilePath + '\Messung.xlsx')
                except: print "kann nicht den Daten fuer Fahrwerik11 speichern! "
                print "einlesen fuer Fahrwerk11 end! "
            else:
                print "einlesen fuer Fahrwerk11 nicht erfolgt! "
            break

    iEntry=1
    xdata=[]
    ydata=[]
    while True:
        try:
            TmpValue = float(sheet.cell(iEntry, 5).value)
            xdata.append(TmpValue)
            TmpValue = float(sheet.cell(iEntry, 4).value)
            ydata.append(TmpValue)
            iEntry+=1
        except:
            if iEntry>2:
                xdataArray = np.array(xdata)
                ydataArray = np.array(ydata)
                popt, pcov = curve_fit(funcDriveModule, xdataArray, ydataArray)
                print popt[0]
                print popt[1]
                write_sheet.write(1, 6, str(popt[0]))
                write_sheet.write(2, 6, str(popt[1]))
                tmp=int(round(popt[0],3)*1000.0)
                if tmp < 0: tmp+=4294967296
                print hex(tmp)
                tmp=int(round(popt[1],3)*1000.0)
                if tmp < 0: tmp += 4294967296
                print hex(tmp)
                plt.figure(2)
                plt.scatter(xdataArray, ydataArray)
                plt.plot(xdataArray,funcDriveModule(xdataArray,popt[0],popt[1]),'k')
                plt.show()
                try: write_File.save(FilePath + '\Messung.xlsx')
                except: print "kann nicht den Daten fuer Fahrwerik12 speichern! "
                print "einlesen fuer Fahrwerk12 end! "
            else:
                print "einlesen fuer Fahrwerk12 nicht erfolgt! "
            break


    iEntry = 1
    xdata = []
    ydata = []
    while True:
        try:
            TmpValue = float(sheet.cell(iEntry, 8).value)
            xdata.append(TmpValue)
            TmpValue = float(sheet.cell(iEntry, 7).value)
            ydata.append(TmpValue)
            iEntry += 1
        except:
            if iEntry > 2:
                xdataArray = np.array(xdata)
                ydataArray = np.array(ydata)
                popt, pcov = curve_fit(funcDriveModule, xdataArray, ydataArray)
                print popt[0]
                print popt[1]
                write_sheet.write(1, 9, str(popt[0]))
                write_sheet.write(2, 9, str(popt[1]))
                tmp=int(round(popt[0],3)*1000.0)
                if tmp < 0: tmp+=4294967296
                print hex(tmp)
                tmp=int(round(popt[1],3)*1000.0)
                if tmp < 0: tmp += 4294967296
                print hex(tmp)
                plt.figure(3)
                plt.scatter(xdataArray, ydataArray)
                plt.plot(xdataArray,funcDriveModule(xdataArray,popt[0],popt[1]),'k')
                plt.show()
                try: write_File.save(FilePath + '\Messung.xlsx')
                except: print "kann nicht den Daten fuer Fahrwerik21 speichern! "
                print "einlesen fuer Fahrwerk21 end! "
            else:
                print "einlesen fuer Fahrwerk21 nicht erfolgt! "
            break

    iEntry = 1
    xdata = []
    ydata = []
    while True:
        try:
            TmpValue = float(sheet.cell(iEntry, 11).value)
            xdata.append(TmpValue)
            TmpValue = float(sheet.cell(iEntry, 10).value)
            ydata.append(TmpValue)
            iEntry += 1
        except:
            if iEntry > 2:
                xdataArray = np.array(xdata)
                ydataArray = np.array(ydata)
                popt, pcov = curve_fit(funcDriveModule, xdataArray, ydataArray)
                print popt[0]
                print popt[1]
                write_sheet.write(1, 12, str(popt[0]))
                write_sheet.write(2, 12, str(popt[1]))
                tmp=int(round(popt[0],3)*1000.0)
                if tmp < 0: tmp+=4294967296
                print hex(tmp)
                tmp=int(round(popt[1],3)*1000.0)
                if tmp < 0: tmp += 4294967296
                print hex(tmp)
                plt.figure(4)
                plt.scatter(xdataArray, ydataArray)
                plt.plot(xdataArray,funcDriveModule(xdataArray,popt[0],popt[1]),'k')
                plt.show()
                try: write_File.save(FilePath + '\Messung.xlsx')
                except: print "kann nicht den Daten fuer Fahrwerik22 speichern! "
                print "einlesen fuer Fahrwerk22 end! "
            else:
                print "einlesen fuer Fahrwerk22 nicht erfolgt! "
            break

def KalibierungHubSys(FilePath):
    try:
        read_File = xlrd.open_workbook(FilePath + '\Messung.xlsx')
        sheet = read_File.sheet_by_index(1)
        write_File = copy(read_File)
        write_sheet = write_File.get_sheet(1)

    except IOError:
        print "no xls file for Kalibierung"
        return

    iEntry=1
    xdata=[]
    ydata=[]
    while True:
        try:
            TmpValue = float(sheet.cell(iEntry, 2).value)
            xdata.append(TmpValue)
            TmpValue = float(sheet.cell(iEntry, 1).value)
            ydata.append(TmpValue)
            iEntry+=1
        except:
            if iEntry>2:
                xdataArray = np.array(xdata)
                ydataArray = np.array(ydata)
                popt, pcov = curve_fit(funcHubModule, xdataArray, ydataArray)
                print popt[0]
                print popt[1]
                write_sheet.write(1, 3, str(popt[0]))
                write_sheet.write(2, 3, str(popt[1]))
                tmp=int(round(popt[0],3)*1000.0)
                if tmp < 0: tmp+=4294967296
                print hex(tmp)
                tmp=int(round(popt[1],3)*1000.0)
                if tmp < 0: tmp += 4294967296
                print hex(tmp)
                plt.figure(1)
                plt.scatter(xdataArray, ydataArray)
                plt.plot(xdataArray,funcHubModule(xdataArray,popt[0],popt[1]),'k')
                plt.show()
                try: write_File.save(FilePath + '\Messung.xlsx')
                except: print "kann nicht den Daten fuer Hubwerik11 speichern! "
                print "einlesen fuer Hubwerk11 end! "
            else:
                print "einlesen fuer Hubwerk11 nicht erfolgt! "
            break

    iEntry=1
    xdata=[]
    ydata=[]
    while True:
        try:
            TmpValue = float(sheet.cell(iEntry, 5).value)
            xdata.append(TmpValue)
            TmpValue = float(sheet.cell(iEntry, 4).value)
            ydata.append(TmpValue)
            iEntry+=1
        except:
            if iEntry>2:
                xdataArray = np.array(xdata)
                ydataArray = np.array(ydata)
                popt, pcov = curve_fit(funcHubModule, xdataArray, ydataArray)
                print popt[0]
                print popt[1]
                write_sheet.write(1, 6, str(popt[0]))
                write_sheet.write(2, 6, str(popt[1]))
                tmp=int(round(popt[0],3)*1000.0)
                if tmp < 0: tmp+=4294967296
                print hex(tmp)
                tmp=int(round(popt[1],3)*1000.0)
                if tmp < 0: tmp += 4294967296
                print hex(tmp)
                plt.figure(2)
                plt.scatter(xdataArray, ydataArray)
                plt.plot(xdataArray,funcHubModule(xdataArray,popt[0],popt[1]),'k')
                plt.show()
                try: write_File.save(FilePath + '\Messung.xlsx')
                except: print "kann nicht den Daten fuer Hubwerik12 speichern! "
                print "einlesen fuer Hubwerk12 end! "
            else:
                print "einlesen fuer Hubwerk12 nicht erfolgt! "
            break


    iEntry = 1
    xdata = []
    ydata = []
    while True:
        try:
            TmpValue = float(sheet.cell(iEntry, 8).value)
            xdata.append(TmpValue)
            TmpValue = float(sheet.cell(iEntry, 7).value)
            ydata.append(TmpValue)
            iEntry += 1
        except:
            if iEntry > 2:
                xdataArray = np.array(xdata)
                ydataArray = np.array(ydata)
                popt, pcov = curve_fit(funcHubModule, xdataArray, ydataArray)
                print popt[0]
                print popt[1]
                write_sheet.write(1, 9, str(popt[0]))
                write_sheet.write(2, 9, str(popt[1]))
                tmp=int(round(popt[0],3)*1000.0)
                if tmp < 0: tmp+=4294967296
                print hex(tmp)
                tmp=int(round(popt[1],3)*1000.0)
                if tmp < 0: tmp += 4294967296
                print hex(tmp)
                plt.figure(3)
                plt.scatter(xdataArray, ydataArray)
                plt.plot(xdataArray,funcHubModule(xdataArray,popt[0],popt[1]),'k')
                plt.show()
                try: write_File.save(FilePath + '\Messung.xlsx')
                except: print "kann nicht den Daten fuer Hubwerik21 speichern! "
                print "einlesen fuer Hubwerk21 end! "
            else:
                print "einlesen fuer Hubwerk21 nicht erfolgt! "
            break

    iEntry = 1
    xdata = []
    ydata = []
    while True:
        try:
            TmpValue = float(sheet.cell(iEntry, 11).value)
            xdata.append(TmpValue)
            TmpValue = float(sheet.cell(iEntry, 10).value)
            ydata.append(TmpValue)
            iEntry += 1
        except:
            if iEntry > 2:
                xdataArray = np.array(xdata)
                ydataArray = np.array(ydata)
                popt, pcov = curve_fit(funcHubModule, xdataArray, ydataArray)
                print popt[0]
                print popt[1]
                write_sheet.write(1, 12, str(popt[0]))
                write_sheet.write(2, 12, str(popt[1]))
                tmp=int(round(popt[0],3)*1000.0)
                if tmp < 0: tmp+=4294967296
                print hex(tmp)
                tmp=int(round(popt[1],3)*1000.0)
                if tmp < 0: tmp += 4294967296
                print hex(tmp)
                plt.figure(4)
                plt.scatter(xdataArray, ydataArray)
                plt.plot(xdataArray,funcHubModule(xdataArray,popt[0],popt[1]),'k')
                plt.show()
                try: write_File.save(FilePath + '\Messung.xlsx')
                except: print "kann nicht den Daten fuer Hubwerik22 speichern! "
                print "einlesen fuer Hubwerk22 end! "
            else:
                print "einlesen fuer Hubwerk22 nicht erfolgt! "
            break




if __name__ == "__main__":
    #KalibierungDriveSys(WorkSpacePath)
    KalibierungHubSys(WorkSpacePath)