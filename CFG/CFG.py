import xml.etree.ElementTree as ET
import xlrd
import os
import shutil

MasterCPUListFilePath="C:\Users\wsun\Dropbox\HIT_Workspace\CFG\ODContentCPUMaster"
MasterCPUDistFilePath="C:\Users\wsun\Dropbox\HIT_Workspace\/auftrage_deutschebahn_STW1"
SlaveCPUListFilePath="C:\Users\wsun\Dropbox\HIT_Workspace\CFG\ODContentCPUSlave"
SlaveCPUDistFilePath=""
APPDistFilePath="C:\Users\wsun\Dropbox\HIT_Workspace\/auftrage_deutschebahn_APP\DBProjekt\DBProjekt"



def main():
    ODInfoXmlProduce(MasterCPUListFilePath,APPDistFilePath,"\MasterCPUODInfo.xml")
    #ODContentHeadFileProduce(MasterCPUListFilePath,MasterCPUDistFilePath,"\ODContent")
    ODInfoHeadFileProduce(MasterCPUListFilePath, MasterCPUDistFilePath, "\ODInfo")

#ODInfo XML File erstellen
def ODInfoXmlProduce(FilePath,DistPath,FileName):
    # creat root node
    root_node = ET.Element("ODInfo")
    #for Device Parameter
    try:
        read_File = xlrd.open_workbook(FilePath+'\DevicePara.xlsx')
        sheet1=read_File.sheet_by_index(0)

        # creat a sub node
        subnode = ET.SubElement(root_node, "ODBlock")
        subnode.attrib = {"name": sheet1.cell(1,0).value.encode('utf-8')}

        # creat child node
        child_node = ET.SubElement(subnode,sheet1.cell(0,1).value.encode('utf-8'))
        child_node.text=str(int(sheet1.cell(1,1).value))
        child_node = ET.SubElement(subnode,sheet1.cell(0,2).value.encode('utf-8'))
        child_node.text=str(int(sheet1.cell(1,2).value))
        child_node = ET.SubElement(subnode,sheet1.cell(0,3).value.encode('utf-8'))
        child_node.text=str(int(sheet1.cell(1,3).value))
    except IOError:
        print "no file for Device Parameter !"

    #for Drive System
    try:
        read_File = xlrd.open_workbook(FilePath+'\DriveSys.xlsx')
        sheet1=read_File.sheet_by_index(0)

        # creat a sub node
        subnode = ET.SubElement(root_node, "ODBlock")
        subnode.attrib = {"name": sheet1.cell(1,0).value.encode('utf-8')}

        # creat child node
        child_node = ET.SubElement(subnode,sheet1.cell(0,1).value.encode('utf-8'))
        child_node.text=str(int(sheet1.cell(1,1).value))
        child_node = ET.SubElement(subnode,sheet1.cell(0,2).value.encode('utf-8'))
        child_node.text=str(int(sheet1.cell(1,2).value))
        child_node = ET.SubElement(subnode,sheet1.cell(0,3).value.encode('utf-8'))
        child_node.text=str(int(sheet1.cell(1,3).value))
    except IOError:
        print "no file for Drive System !"

    #for Interter
    try:
        read_File = xlrd.open_workbook(FilePath+'\Inverter.xlsx')
        sheet1=read_File.sheet_by_index(0)

        # creat a sub node
        subnode = ET.SubElement(root_node, "ODBlock")
        subnode.attrib = {"name": sheet1.cell(1,0).value.encode('utf-8')}

        # creat child node
        child_node = ET.SubElement(subnode,sheet1.cell(0,1).value.encode('utf-8'))
        child_node.text=str(int(sheet1.cell(1,1).value))
        child_node = ET.SubElement(subnode,sheet1.cell(0,2).value.encode('utf-8'))
        child_node.text=str(int(sheet1.cell(1,2).value))
        child_node = ET.SubElement(subnode,sheet1.cell(0,3).value.encode('utf-8'))
        child_node.text=str(int(sheet1.cell(1,3).value))
    except IOError:
        print "no file for Inverter !"

    #for IO Port
    try:
        read_File = xlrd.open_workbook(FilePath+'\IOPort.xlsx')
        sheet1=read_File.sheet_by_index(0)

        # creat a sub node
        subnode = ET.SubElement(root_node, "ODBlock")
        subnode.attrib = {"name": sheet1.cell(1,0).value.encode('utf-8')}

        # creat child node
        child_node = ET.SubElement(subnode,sheet1.cell(0,1).value.encode('utf-8'))
        child_node.text=str(int(sheet1.cell(1,1).value))
        child_node = ET.SubElement(subnode,sheet1.cell(0,2).value.encode('utf-8'))
        child_node.text=str(int(sheet1.cell(1,2).value))
        child_node = ET.SubElement(subnode,sheet1.cell(0,3).value.encode('utf-8'))
        child_node.text=str(int(sheet1.cell(1,3).value))
    except IOError:
        print "no file for IO Port !"

    #for Remote Controller
    try:
        read_File = xlrd.open_workbook(FilePath+'\RemoteController.xlsx')
        sheet1 = read_File.sheet_by_index(0)
        # creat a sub node
        subnode = ET.SubElement(root_node, "ODBlock")
        subnode.attrib = {"name": sheet1.cell(1, 0).value.encode('utf-8')}

        # creat child node
        child_node = ET.SubElement(subnode, sheet1.cell(0, 1).value.encode('utf-8'))
        child_node.text = str(int(sheet1.cell(1, 1).value))
        child_node = ET.SubElement(subnode, sheet1.cell(0, 2).value.encode('utf-8'))
        child_node.text = str(int(sheet1.cell(1, 2).value))
        child_node = ET.SubElement(subnode, sheet1.cell(0, 3).value.encode('utf-8'))
        child_node.text = str(int(sheet1.cell(1, 3).value))
    except IOError:
        print "no file for Remote Controller !"

    #for Hub System
    try:
        read_File = xlrd.open_workbook(FilePath+'\HubSys.xlsx')
        sheet1=read_File.sheet_by_index(0)

        # creat a sub node
        subnode = ET.SubElement(root_node, "ODBlock")
        subnode.attrib = {"name": sheet1.cell(1,0).value.encode('utf-8')}

        # creat child node
        child_node = ET.SubElement(subnode,sheet1.cell(0,1).value.encode('utf-8'))
        child_node.text=str(int(sheet1.cell(1,1).value))
        child_node = ET.SubElement(subnode,sheet1.cell(0,2).value.encode('utf-8'))
        child_node.text=str(int(sheet1.cell(1,2).value))
        child_node = ET.SubElement(subnode,sheet1.cell(0,3).value.encode('utf-8'))
        child_node.text=str(int(sheet1.cell(1,3).value))
    except IOError:
        print "no file for Hub System !"

    #for Safety
    try:
        read_File = xlrd.open_workbook(FilePath+'\Safety.xlsx')
        sheet1=read_File.sheet_by_index(0)

        # creat a sub node
        subnode = ET.SubElement(root_node, "ODBlock")
        subnode.attrib = {"name": sheet1.cell(1,0).value.encode('utf-8')}

        # creat child node
        child_node = ET.SubElement(subnode,sheet1.cell(0,1).value.encode('utf-8'))
        child_node.text=str(int(sheet1.cell(1,1).value))
        child_node = ET.SubElement(subnode,sheet1.cell(0,2).value.encode('utf-8'))
        child_node.text=str(int(sheet1.cell(1,2).value))
        child_node = ET.SubElement(subnode,sheet1.cell(0,3).value.encode('utf-8'))
        child_node.text=str(int(sheet1.cell(1,3).value))
    except IOError:
        print "no file for Safety !"


    tree = ET.ElementTree(root_node)
    tree.write(FilePath+FileName)
    if os.path.exists(DistPath+FileName):
        os.remove(DistPath+FileName)
    shutil.move(FilePath+FileName, DistPath)




#ODContent.h erstellen
def ODContentHeadFileProduce(FilePath,DistPath,FileName):
    #head content of this file
    HeadTextODContent = "#ifndef _ODCONTENT_H\n" \
                        "#define _ODCONTENT_H\n" \
                        "\n" \
                        "/*====================================================================\n" \
                        "OD Definition\n" \
                        "====================================================================*/\n" \
                        "\n"

    StrMuster = "                                             "
    # erstllen die Head File
    open(FilePath+FileName+".txt", "a").close()
    fobj = open(FilePath+FileName+".txt", "w")
    fobj.write(HeadTextODContent)

    try:
        #for Device Parameter
        read_File = xlrd.open_workbook(FilePath+'\DevicePara.xlsx')
        sheet1 = read_File.sheet_by_index(0)
        sheet2 = read_File.sheet_by_index(1)

        #main text
        Text = "//====================================================================\n"
        Text += "//*1 "+ sheet1.cell(1,0).value.encode('utf-8')+ "\n"
        Text += "#define DevParaStartIndex" + StrMuster[len("#define DevParaStartIndex"):] + "0x" + str(int(sheet1.cell(1,2).value))+"\n"
        Text += "#define NrEntryDevPara" + StrMuster[len("#define NrEntryDevPara"):] + str(int(sheet1.cell(1,3).value))+"\n"
        Text += "\n\n"
        Text += "//*1.1 Parameter\n"
        fobj.write(Text)
        Text=""
        for iPara in range(int(sheet1.cell(1,3).value)):
            Testtmp="#define "+str(sheet2.cell(iPara+1,0).value.encode('utf-8'))
            Text += Testtmp + StrMuster[len(Testtmp):] + str(sheet2.cell(iPara+1,1).value.encode('utf-8')) + "//" + str(sheet2.cell(iPara+1,3).value.encode('utf-8'))+"\n"
            fobj.write(Text)
            Text=""

    except IOError:
        print "no file for Device Parameter !"

    try:
        #for Device Parameter
        read_File = xlrd.open_workbook(FilePath+'\DriveSys.xlsx')
        sheet1 = read_File.sheet_by_index(0)
        sheet2 = read_File.sheet_by_index(1)

        #main text
        Text = "//====================================================================\n"
        Text += "//*2 "+ sheet1.cell(1,0).value.encode('utf-8')+ "\n"
        Text += "#define DriveModuleStartIndex" + StrMuster[len("#define DriveModuleStartIndex"):] + "0x" + str(int(sheet1.cell(1,2).value))+"\n"
        Text += "#define NrEntryDriveModule" + StrMuster[len("#define NrEntryDriveModule"):] + str(int(sheet1.cell(1,3).value))+"\n"
        Text += "\n\n"
        Text += "//*2.1 Parameter\n"
        fobj.write(Text)
        Text=""
        for iPara in range(int(sheet1.cell(1,3).value)):
            Testtmp="#define "+str(sheet2.cell(iPara+1,0).value.encode('utf-8'))
            Text += Testtmp + StrMuster[len(Testtmp):] + str(sheet2.cell(iPara+1,1).value.encode('utf-8')) + "//" + str(sheet2.cell(iPara+1,3).value.encode('utf-8'))+"\n"
            fobj.write(Text)
            Text=""

    except IOError:
        print "no file for Drive System !"

    try:
        #for Inverter
        read_File = xlrd.open_workbook(FilePath+'\Inverter.xlsx')
        sheet1 = read_File.sheet_by_index(0)
        sheet2 = read_File.sheet_by_index(1)

        #main text
        Text = "//====================================================================\n"
        Text += "//*3 "+ sheet1.cell(1,0).value.encode('utf-8')+ "\n"
        Text += "#define InverterStartIndex" + StrMuster[len("#define InverterStartIndex"):] + "0x" + str(int(sheet1.cell(1,2).value))+"\n"
        Text += "#define NrEntryInverter" + StrMuster[len("#define NrEntryInverter"):] + str(int(sheet1.cell(1,3).value))+"\n"
        Text += "\n\n"
        Text += "//*3.1 Parameter\n"
        fobj.write(Text)
        Text=""
        for iPara in range(int(sheet1.cell(1,3).value)):
            Testtmp="#define "+str(sheet2.cell(iPara+1,0).value.encode('utf-8'))
            Text += Testtmp + StrMuster[len(Testtmp):] + str(sheet2.cell(iPara+1,1).value.encode('utf-8')) + "//" + str(sheet2.cell(iPara+1,3).value.encode('utf-8'))+"\n"
            fobj.write(Text)
            Text=""

    except IOError:
        print "no file for Inverter !"

    try:
        #for I/O Port
        read_File = xlrd.open_workbook(FilePath+'\IOPort.xlsx')
        sheet1 = read_File.sheet_by_index(0)
        sheet2 = read_File.sheet_by_index(1)

        #main text
        Text = "//====================================================================\n"
        Text += "//*4 "+ sheet1.cell(1,0).value.encode('utf-8')+ "\n"
        Text += "#define IOPortStartIndex" + StrMuster[len("#define IOPortStartIndex"):] + "0x" + str(int(sheet1.cell(1,2).value))+"\n"
        Text += "#define NrEntryIOPort" + StrMuster[len("#define NrEntryIOPort"):] + str(int(sheet1.cell(1,3).value))+"\n"
        Text += "\n\n"
        Text += "//*4.1 Parameter\n"
        fobj.write(Text)
        Text=""
        for iPara in range(int(sheet1.cell(1,3).value)):
            Testtmp="#define "+str(sheet2.cell(iPara+1,0).value.encode('utf-8'))
            Text += Testtmp + StrMuster[len(Testtmp):] + str(sheet2.cell(iPara+1,1).value.encode('utf-8')) + "//" + str(sheet2.cell(iPara+1,3).value.encode('utf-8'))+"\n"
            fobj.write(Text)
            Text=""

    except IOError:
        print "no file for I/O Port !"

    try:
        #for Remote Control
        read_File = xlrd.open_workbook(FilePath+'\RemoteController.xlsx')
        sheet1 = read_File.sheet_by_index(0)
        sheet2 = read_File.sheet_by_index(1)

        #main text
        Text = "//====================================================================\n"
        Text += "//*5 "+ sheet1.cell(1,0).value.encode('utf-8')+ "\n"
        Text += "#define RemoteControlStartIndex" + StrMuster[len("#define RemoteControlStartIndex"):] + "0x" + str(int(sheet1.cell(1,2).value))+"\n"
        Text += "#define NrEntryRemoteControl" + StrMuster[len("#define NrEntryRemoteControl"):] + str(int(sheet1.cell(1,3).value))+"\n"
        Text += "\n\n"
        Text += "//*5.1 Parameter\n"
        fobj.write(Text)
        Text=""
        for iPara in range(int(sheet1.cell(1,3).value)):
            Testtmp="#define "+str(sheet2.cell(iPara+1,0).value.encode('utf-8'))
            Text += Testtmp + StrMuster[len(Testtmp):] + str(sheet2.cell(iPara+1,1).value.encode('utf-8')) + "//" + str(sheet2.cell(iPara+1,3).value.encode('utf-8'))+"\n"
            fobj.write(Text)
            Text=""

    except IOError:
        print "no file for Remote Controller !"

    try:
        #for Hub System
        read_File = xlrd.open_workbook(FilePath+'\HubSys.xlsx')
        sheet1 = read_File.sheet_by_index(0)
        sheet2 = read_File.sheet_by_index(1)

        #main text
        Text = "//====================================================================\n"
        Text += "//*6 "+ sheet1.cell(1,0).value.encode('utf-8')+ "\n"
        Text += "#define HubSystemStartIndex" + StrMuster[len("#define HubSystemStartIndex"):] + "0x" + str(int(sheet1.cell(1,2).value))+"\n"
        Text += "#define NrEntryHubSystem" + StrMuster[len("#define NrEntryHubSystem"):] + str(int(sheet1.cell(1,3).value))+"\n"
        Text += "\n\n"
        Text += "//*6.1 Parameter\n"
        fobj.write(Text)
        Text=""
        for iPara in range(int(sheet1.cell(1,3).value)):
            Testtmp="#define "+str(sheet2.cell(iPara+1,0).value.encode('utf-8'))
            Text += Testtmp + StrMuster[len(Testtmp):] + str(sheet2.cell(iPara+1,1).value.encode('utf-8')) + "//" + str(sheet2.cell(iPara+1,3).value.encode('utf-8'))+"\n"
            fobj.write(Text)
            Text=""

    except IOError:
        print "no file for Hub System !"

    try:
        # for Safety
        read_File = xlrd.open_workbook(FilePath + '\Safety.xlsx')
        sheet1 = read_File.sheet_by_index(0)
        sheet2 = read_File.sheet_by_index(1)

        # main text
        Text = "//====================================================================\n"
        Text += "//*7 " + sheet1.cell(1, 0).value.encode('utf-8') + "\n"
        Text += "#define SafetyStartIndex" + StrMuster[len("#define SafetyStartIndex"):] + "0x" + str(
            int(sheet1.cell(1, 2).value)) + "\n"
        Text += "#define NrEntrySafety" + StrMuster[len("#define NrEntrySafety"):] + str(
            int(sheet1.cell(1, 3).value)) + "\n"
        Text += "\n\n"
        Text += "//*7.1 Parameter\n"
        fobj.write(Text)
        Text = ""
        for iPara in range(int(sheet1.cell(1, 3).value)):
            Testtmp = "#define " + str(sheet2.cell(iPara + 1, 0).value.encode('utf-8'))
            Text += Testtmp + StrMuster[len(Testtmp):] + str(
                sheet2.cell(iPara + 1, 1).value.encode('utf-8')) + "//" + str(
                sheet2.cell(iPara + 1, 3).value.encode('utf-8')) + "\n"
            fobj.write(Text)
            Text = ""

    except IOError:
        print "no file for Safety !"


    fobj.write("#endif")
    fobj.close()

#ODContent.h erstellen
def ODInfoHeadFileProduce(FilePath,DistPath,FileName):
    #head content of this file
    HeadTextODInfo = "#ifndef _ODINFO_H\n" \
                        "#define _ODINFO_H\n" \
                        "\n" \
                        "\n"

    TitleText1 = "/*====================================================================\n" \
                 "Remote Node Configuration\n" \
                 "====================================================================*/\n"

    TitleText2 = "/*====================================================================\n" \
                 "Parameter of the memory for object dictionary definition\n" \
                 "====================================================================*/\n"

    StrMuster = "                                     "

    # erstllen die Head File
    open(FilePath+FileName+".txt", "a").close()
    fobj = open(FilePath+FileName+".txt", "w")


    StrMemLength = "#define ODMemLength      (NrEntryDevPara"
    StrMemMapListLenght = "#define ODMemMapListLength      (1"

    fobj.write(HeadTextODInfo)
    fobj.write(TitleText1)

    try:
        # for Device Parameter
        read_File = xlrd.open_workbook(FilePath + '\DriveSys.xlsx')
        sheet1 = read_File.sheet_by_index(0)

        # main text
        Text = "#define NrOfDriveSys" + StrMuster[len("#define NrOfDriveSys"):]  + str(int(sheet1.cell(1, 1).value)) + "\n"
        fobj.write(Text)
        StrMemLength += "+NrEntryDriveModule*NrOfDriveSys"
        StrMemMapListLenght += "+NrOfDriveSys"

    except IOError:
        print "no file for Drive System !"

    try:
        # for Inverter
        read_File = xlrd.open_workbook(FilePath + '\Inverter.xlsx')
        sheet1 = read_File.sheet_by_index(0)

        # main text
        Text = "#define NrOfMotorInverter" + StrMuster[len("#define NrOfMotorInverter"):]  + str(int(sheet1.cell(1, 1).value)) + "\n"
        fobj.write(Text)
        StrMemLength += "+NrEntryInverter*NrOfMotorInverter"
        StrMemMapListLenght += "+NrOfMotorInverter"

    except IOError:
        print "no file for Inverter !"

    try:
        # for I/O Port
        read_File = xlrd.open_workbook(FilePath + '\IOPort.xlsx')
        sheet1 = read_File.sheet_by_index(0)

        # main text
        Text = "#define NrOfIOPortGroup" + StrMuster[len("#define NrOfIOPortGroup"):]  + str(int(sheet1.cell(1, 1).value)) + "\n"
        fobj.write(Text)
        StrMemLength += "+NrEntryIOPort*NrOfIOPortGroup"
        StrMemMapListLenght += "+NrOfIOPortGroup"

    except IOError:
        print "no file for I/O Port !"

    try:
        # for Remote Control
        read_File = xlrd.open_workbook(FilePath + '\RemoteController.xlsx')
        sheet1 = read_File.sheet_by_index(0)

        # main text
        Text = "#define NrOfRemoteControl" + StrMuster[len("#define NrOfRemoteControl"):]  + str(int(sheet1.cell(1, 1).value)) + "\n"
        fobj.write(Text)
        StrMemLength += "+NrEntryRemoteControl*NrOfRemoteControl"
        StrMemMapListLenght += "+NrOfRemoteControl"

    except IOError:
        print "no file for Remote Controller !"

    try:
        # for Hub System
        read_File = xlrd.open_workbook(FilePath + '\HubSys.xlsx')
        sheet1 = read_File.sheet_by_index(0)

        # main text
        Text = "#define NrOfHubSys" + StrMuster[len("#define NrOfHubSys"):]  + str(int(sheet1.cell(1, 1).value)) + "\n"
        fobj.write(Text)
        StrMemLength += "+NrEntryHubSystem*NrOfHubSys"
        StrMemMapListLenght += "+NrOfHubSys"

    except IOError:
        print "no file for Hub System !"

    try:
        # for Safety
        read_File = xlrd.open_workbook(FilePath + '\Safety.xlsx')
        sheet1 = read_File.sheet_by_index(0)

        # main text
        Text = "#define NrOfSafety" + StrMuster[len("#define NrOfSafety"):]  + str(int(sheet1.cell(1, 1).value)) + "\n"
        fobj.write(Text)
        StrMemLength += "+NrEntrySafety*NrOfSafety"
        StrMemMapListLenght += "+NrOfSafety"

    except IOError:
        print "no file for Safety !"

    fobj.write("\n"+TitleText2)
    fobj.write(StrMemLength + ")\n")
    fobj.write(StrMemMapListLenght + ")\n")
    fobj.write("\n\n#endif")
    fobj.close()

    if os.path.exists(FilePath + FileName + ".h"):
        os.remove(FilePath + FileName + ".h")

    os.rename(FilePath+FileName+".txt",FilePath+FileName +".h")
    if os.path.exists(DistPath+"\libs\BSP\OD"+FileName +".h"):
        os.remove(DistPath+"\libs\BSP\OD"+FileName +".h")
    shutil.move(FilePath+FileName+".h", DistPath+"\libs\BSP\OD")




if __name__ == "__main__":
    main()
