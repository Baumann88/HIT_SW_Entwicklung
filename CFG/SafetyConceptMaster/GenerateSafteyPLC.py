import xlrd
import os
import shutil

#WorkSpacePath="C:\Users\wsun\Dropbox\HIT_Workspace\CFG\SafetyConcept"
#TargetFolderPath="C:\Users\wsun\Dropbox\HIT_Workspace\/auftrage_deutschebahn_STWMaster\libs\BSP\Safety"
WorkSpacePath="..\SafetyConceptMaster"
TargetFolderPath="..\..\/auftrage_deutschebahn_STWMaster\libs\BSP\Safety"



def main():
    GenerateData(WorkSpacePath,TargetFolderPath)

def GenerateData(FilePath,DistPath):
    try:
        read_File = xlrd.open_workbook(FilePath + '\ParameterList.xlsx')
        sheet1 = read_File.sheet_by_index(0)

        PLCSheetNr=int(sheet1.cell(1, 3).value)
        PLCSheet=read_File.sheet_by_index(PLCSheetNr-1)

    except IOError:
        print "no file of parameter list"
        return


    # head content of the headfile SafetyDriveSysData
    HeadTextSafetyPLCDataHeadFile = "#ifndef _SAFETYPLCDATA_H\n" \
                                         "#define _SAFETYPLCDATA_H\n" \
                                         "#include <stwtypes.h>\n" \
                                         "\n"

    # head content of the file SafetyDriveSysData
    HeadTextSafetyPLCData = "#include <SafetyPLCData.h>\n" \
                                 "\n"


    # head content of the file SafetyDriveSys
    HeadTextSafetyPLC = "#include <SafetyData.h>\n" \
                             "#include <Safety.h>\n" \
                             "\n"

    StrMuster = "                                             "
    # erstllen die Head File: SafetyDriveSysData
    open(FilePath + "\SafetyPLCData.txt", "a").close()
    fobj = open(FilePath + "\SafetyPLCData.txt", "w")
    fobj.write(HeadTextSafetyPLCDataHeadFile)

    # main text
    Text = "//====================================================================\n"
    Text += "//define Constant\n"
    Text += "//====================================================================\n"

    iEntry=1
    while True:
        if iEntry >= PLCSheet.nrows: break
        TextTmp=str(PLCSheet.cell(iEntry, 13).value.encode('utf-8'))
        if len(TextTmp)>1:
            TextTmp = "#define " + TextTmp
            Text += TextTmp + StrMuster[len(TextTmp):]  + "(" + str(PLCSheet.cell(iEntry, 14).value.encode('utf-8')) + ")\n"
            iEntry+=1
        else: break
    Text += "\n"
    fobj.write(Text)

    iEntry = 1
    Text = "//====================================================================\n"
    Text += "//intene parameter\n"
    Text += "//====================================================================\n"
    while True:
        if iEntry >= PLCSheet.nrows: break
        TextTmp=str(PLCSheet.cell(iEntry, 11).value.encode('utf-8'))
        if len(TextTmp) > 0:
            Text += "extern " + str(PLCSheet.cell(iEntry, 12).value.encode('utf-8')) + " " + TextTmp  + ";\n"
            iEntry+=1
        else: break

    Text+="\n"
    fobj.write(Text)

    iEntry = 1
    Text = "//====================================================================\n"
    Text += "//input parameter\n"
    Text += "//====================================================================\n"
    while True:
        if iEntry >= PLCSheet.nrows: break
        TextTmp=str(PLCSheet.cell(iEntry, 1).value.encode('utf-8'))
        if len(TextTmp) > 0:
            Text += "extern " + str(PLCSheet.cell(iEntry, 4).value.encode('utf-8')) + " " + TextTmp  + ";\n"
            iEntry+=1
        else: break

    Text+="\n"
    fobj.write(Text)

    iEntry = 1
    Text = "//====================================================================\n"
    Text += "//out parameter\n"
    Text += "//====================================================================\n"
    while True:
        if iEntry >= PLCSheet.nrows: break
        TextTmp=str(PLCSheet.cell(iEntry, 6).value.encode('utf-8'))
        if len(TextTmp)>0:
            Text += "extern " + str(PLCSheet.cell(iEntry, 9).value.encode('utf-8')) + " " + TextTmp  + ";\n"
            iEntry+=1
        else: break
    Text += "#endif"

    fobj.write(Text)
    fobj.close()

    if os.path.exists(FilePath  + "\SafetyPLCData.h"):
        os.remove(FilePath  + "\SafetyPLCData.h")

    os.rename(FilePath+"\SafetyPLCData.txt",FilePath +"\SafetyPLCData.h")
    if os.path.exists(DistPath + "\SafetyPLCData.h"):
        os.remove(DistPath + "\SafetyPLCData.h")
    shutil.move(FilePath + "\SafetyPLCData.h", DistPath)


    # erstllen die File: SafetyDriveSysData
    open(FilePath + "\SafetyPLCData.txt", "a").close()
    fobj = open(FilePath + "\SafetyPLCData.txt", "w")
    fobj.write(HeadTextSafetyPLCData)

    # main text
    iEntry = 1
    Text = "//====================================================================\n"
    Text += "//intene parameter\n"
    Text += "//====================================================================\n"
    while True:
        if iEntry >= PLCSheet.nrows: break
        TextTmp = str(PLCSheet.cell(iEntry, 11).value.encode('utf-8'))
        if len(TextTmp) > 0:
            Text += str(PLCSheet.cell(iEntry, 12).value.encode('utf-8')) + " " + TextTmp + ";\n"
            iEntry += 1
        else:
            break

    Text += "\n"
    fobj.write(Text)

    iEntry = 1
    Text = "//====================================================================\n"
    Text += "//input parameter\n"
    Text += "//====================================================================\n"
    while True:
        if iEntry >= PLCSheet.nrows: break
        TextTmp = str(PLCSheet.cell(iEntry, 1).value.encode('utf-8'))
        if len(TextTmp) > 0:
            Text += str(PLCSheet.cell(iEntry, 4).value.encode('utf-8')) + " " + TextTmp + ";\n"
            iEntry += 1
        else:
            break

    Text += "\n"
    fobj.write(Text)

    iEntry = 1
    Text = "//====================================================================\n"
    Text += "//out parameter\n"
    Text += "//====================================================================\n"
    while True:
        if iEntry >= PLCSheet.nrows: break
        TextTmp = str(PLCSheet.cell(iEntry, 6).value.encode('utf-8'))
        if len(TextTmp) > 0:
            Text += str(PLCSheet.cell(iEntry, 9).value.encode('utf-8')) + " " + TextTmp + ";\n"
            iEntry += 1
        else:
            break

    fobj.write(Text)
    fobj.close()

    if os.path.exists(FilePath  + "\SafetyPLCData.c"):
        os.remove(FilePath  + "\SafetyPLCData.c")

    os.rename(FilePath+"\SafetyPLCData.txt",FilePath +"\SafetyPLCData.c")
    if os.path.exists(DistPath + "\SafetyPLCData.c"):
        os.remove(DistPath + "\SafetyPLCData.c")
    shutil.move(FilePath + "\SafetyPLCData.c", DistPath)


    # erstllen die File: SafetyPLC
    open(FilePath + "\SafetyPLC.txt", "a").close()
    fobj = open(FilePath + "\SafetyPLC.txt", "w")
    fobj.write(HeadTextSafetyPLC)


    # main text
    iEntry = 1
    Text = "//====================================================================\n"
    Text += "/*!\n"
    Text += "Function: initial Satety PLC\n"
    Text += "Output: None\n"
    Text += "*/\n"
    Text += "//====================================================================\n"
    Text += "void InitSafetyPLC(void){\n"
    while True:
        if iEntry >= PLCSheet.nrows: break
        TextTmp = str(PLCSheet.cell(iEntry, 1).value.encode('utf-8'))
        StartValue="=0"
        if len(TextTmp) > 0:
            Text += "    "+TextTmp[1:] + "=BindODMem(" + str(PLCSheet.cell(iEntry, 2).value.encode('utf-8')) + ","
            Text += str(PLCSheet.cell(iEntry, 3).value.encode('utf-8')) + ","
            if str(PLCSheet.cell(iEntry, 4).value.encode('utf-8'))=="uint16":
                Text += "TypeU16,"
                StartValue="=0x0000"
            elif str(PLCSheet.cell(iEntry, 4).value.encode('utf-8'))=="uint8":
                Text += "TypeU8,"
                StartValue = "=0x00"
            elif str(PLCSheet.cell(iEntry, 4).value.encode('utf-8')) == "sint16":
                Text += "TypeS16,"
                StartValue = "=0"
            elif str(PLCSheet.cell(iEntry, 4).value.encode('utf-8')) == "sint32":
                Text += "TypeS32,"
                StartValue = "=0"
            elif str(PLCSheet.cell(iEntry, 4).value.encode('utf-8')) == "uint32":
                Text += "TypeU32,"
                StartValue = "=0x00000000"
            elif str(PLCSheet.cell(iEntry, 4).value.encode('utf-8')) == "float32":
                Text += "TypeF32,"
                StartValue = "=0.0"
            Text += str(PLCSheet.cell(iEntry, 5).value.encode('utf-8')) + ");"
            Text += " " + TextTmp + StartValue + ";\n"
            iEntry += 1
        else:
            break

    fobj.write(Text)

    iEntry = 1
    Text = "\n"
    while True:
        if iEntry >= PLCSheet.nrows: break
        TextTmp = str(PLCSheet.cell(iEntry, 6).value.encode('utf-8'))
        StartValue="=0"
        if len(TextTmp) > 0:
            Text += "    " + TextTmp[1:] + "=BindODMem(" + str(PLCSheet.cell(iEntry, 7).value.encode('utf-8')) + ","
            Text += str(PLCSheet.cell(iEntry, 8).value.encode('utf-8')) + ","
            if str(PLCSheet.cell(iEntry, 9).value.encode('utf-8'))=="uint16":
                Text += "TypeU16,"
                StartValue="=0x0000"
            elif str(PLCSheet.cell(iEntry, 9).value.encode('utf-8'))=="uint8":
                Text += "TypeU8,"
                StartValue = "=0x00"
            elif str(PLCSheet.cell(iEntry, 9).value.encode('utf-8')) == "sint16":
                Text += "TypeS16,"
                StartValue = "=0"
            elif str(PLCSheet.cell(iEntry, 9).value.encode('utf-8')) == "sint32":
                Text += "TypeS32,"
                StartValue = "=0"
            elif str(PLCSheet.cell(iEntry, 9).value.encode('utf-8')) == "uint32":
                Text += "TypeU32,"
                StartValue = "=0x00000000"
            elif str(PLCSheet.cell(iEntry, 9).value.encode('utf-8')) == "float32":
                Text += "TypeF32,"
                StartValue = "=0.0"
            Text += str(PLCSheet.cell(iEntry, 10).value.encode('utf-8')) + ");"
            Text += " " + TextTmp + StartValue + ";\n"
            iEntry += 1
        else:
            break
    Text += "}\n\n"
    fobj.write(Text)


    try:
        read_File_aktion = xlrd.open_workbook(FilePath + '\SafteyPLC\Aktion.xlsx')

    except IOError:
        print "no file of aktion for Safety PLC"
        return

    #Safety Handle Funktion generaieren
    for iSheet in range(read_File_aktion.nsheets):
        akt_sheet = read_File_aktion.sheet_by_index(iSheet)
        Text = "//====================================================================\n"
        Text += "/*!\n"
        Text += "Function: " + str(akt_sheet.cell(1, 0).value.encode('utf-8')) + "\n"
        Text += "Output: None\n"
        Text += "*/\n"
        Text += "//====================================================================\n"
        Text += "void " + str(akt_sheet.cell(1, 0).value.encode('utf-8')) + "(void){\n"
        Text += "    boolean "
        for iM in range(len(akt_sheet.col(6)) - 1):
            if str(akt_sheet.cell(iM+1, 6).value.encode('utf-8'))=="": break
            Text += "m" + str(iM+1) + ","
        Text = Text[:-1]
        Text +=";\n"

        for iM in range(len(akt_sheet.col(8)) - 1):
            if akt_sheet.cell(iM + 1, 9).value.encode('utf-8') == "0": continue
            tmpStr=str(akt_sheet.cell(iM+1, 8).value.encode('utf-8'))
            if tmpStr=="": break
            Text += "    static boolean " + tmpStr + "OldValue" + ";\n"

        Text += "    //1. Layer\n"
        for iM in range(len(akt_sheet.col(6)) - 1):
            if str(akt_sheet.cell(iM+1, 6).value.encode('utf-8')) == "": break
            op=str(akt_sheet.cell(iM+1,6).value.encode('utf-8')).split()
            Text += "    if("
            for iOp_Str in op:
                if iOp_Str.find("In")==0: iStr=str(akt_sheet.cell(int(iOp_Str[2:]),2).value.encode('utf-8'))
                elif iOp_Str.find("C")==0: iStr=str(akt_sheet.cell(int(iOp_Str[1:]),5).value.encode('utf-8'))
                elif iOp_Str.find("inten")==0: iStr=str(akt_sheet.cell(int(iOp_Str[5:]),4).value.encode('utf-8'))
                else: iStr=iOp_Str
                Text += iStr

            Text += ")  m" + str(iM+1) + "=TRUE;\n"
            Text += "    else m" + str(iM+1) + "=FALSE;\n"


        Text += "    //2. Layer\n"
        for iM in range(len(akt_sheet.col(8)) - 1):
            if str(akt_sheet.cell(iM + 1, 8).value.encode('utf-8')) == "": break
            Text += "    " + str(akt_sheet.cell(iM+1,8).value.encode('utf-8')) + "=" + \
                    str(akt_sheet.cell(iM+1,7).value.encode('utf-8')) + ";\n"

        Text += "    //Output\n"
        for iM in range(len(akt_sheet.col(8)) - 1):
            if akt_sheet.cell(iM + 1, 9).value.encode('utf-8') == "0": continue
            if str(akt_sheet.cell(iM + 1, 8).value.encode('utf-8')) == "": break
            tmpStr = str(akt_sheet.cell(iM + 1, 8).value.encode('utf-8'))
            op = str(akt_sheet.cell(iM + 1, 10).value.encode('utf-8')).split()
            Text += "    if(" + str(akt_sheet.cell(iM+1,8).value.encode('utf-8')) +"){\n "
            if str(akt_sheet.cell(iM + 1, 10).value.encode('utf-8')) != "/":
                for iOp_Str in op:
                    if iOp_Str.find("Out")==0: iStr="        " + str(akt_sheet.cell(int(iOp_Str[3:]),3).value.encode('utf-8'))
                    elif iOp_Str.find("inten") == 0: iStr = "        " + str(akt_sheet.cell(int(iOp_Str[5:]), 4).value.encode('utf-8'))
                    elif iOp_Str.find("C")==0: iStr=str(akt_sheet.cell(int(iOp_Str[1:]),5).value.encode('utf-8'))
                    elif iOp_Str.find(";")==0: iStr=";\n"
                    else: iStr=iOp_Str
                    Text += iStr
                Text += ";\n"
            Text += "        if(" + tmpStr + "!=" + tmpStr + "OldValue)\n "
            Text += "           SetErrorCode(" + str(akt_sheet.cell(iM + 1, 9).value.encode('utf-8')) + ");\n"
            Text += "         setFault();\n"
            Text += "    }\n"
            if str(akt_sheet.cell(iM + 1, 11).value.encode('utf-8')) != "/":
                op = str(akt_sheet.cell(iM + 1, 11).value.encode('utf-8')).split()
                Text += "    else {\n"
                for iOp_Str in op:
                    if iOp_Str.find("Out")==0: iStr="        " + str(akt_sheet.cell(int(iOp_Str[3:]),3).value.encode('utf-8'))
                    elif iOp_Str.find("inten") == 0: iStr = "        " + str(akt_sheet.cell(int(iOp_Str[5:]), 4).value.encode('utf-8'))
                    elif iOp_Str.find("C")==0: iStr=str(akt_sheet.cell(int(iOp_Str[1:]),5).value.encode('utf-8'))
                    elif iOp_Str.find(";") == 0: iStr = ";\n"
                    else: iStr=iOp_Str
                    Text += iStr
                Text += ";\n"
                Text += "    }\n"

        Text += "    //OldValue\n"
        for iM in range(len(akt_sheet.col(8)) - 1):
            if akt_sheet.cell(iM + 1, 9).value.encode('utf-8') == "0": continue
            if str(akt_sheet.cell(iM + 1, 8).value.encode('utf-8')) == "": break
            tmpStr = str(akt_sheet.cell(iM + 1, 8).value.encode('utf-8'))
            Text += "    " + tmpStr + "OldValue=" + tmpStr +";\n"


        Text += "}\n\n"
        fobj.write(Text)



    iEntry = 0
    Text = "//====================================================================\n"
    Text += "/*!\n"
    Text += "Function: handle of safety PLC\n"
    Text += "Output: None\n"
    Text += "*/\n"
    Text += "//====================================================================\n"
    Text += "void HandleSafetyPLC(void){\n"
    while True:
        if iEntry >= read_File_aktion.nsheets: break
        akt_sheet=read_File_aktion.sheet_by_index(iEntry)
        Text += "    " + str(akt_sheet.cell(1, 0).value.encode('utf-8')) + "();\n"
        iEntry += 1

    Text += "}\n\n"
    fobj.write(Text)


    try:
        read_File_timer = xlrd.open_workbook(FilePath + '\SafteyPLC\Timer.xlsx')
        sheet_timer=read_File_timer.sheet_by_index(0)
    except IOError:
        print "no file of timer for Safety PLC"
        return


    Text = "//====================================================================\n"
    Text += "/*!\n"
    Text += "Function: timer of safety PLC\n"
    Text += "Output: None\n"
    Text += "*/\n"
    Text += "//====================================================================\n"
    Text += "void TimerSafetyPLC(void){\n"
    Text += "    boolean "
    for iM in range(len(sheet_timer.col(3)) - 1):
        if str(sheet_timer.cell(iM + 1, 3).value.encode('utf-8')) == "": break
        Text += "m" + str(iM + 1) + ","
    Text = Text[:-1]
    Text += ";\n"

    Text += "    static uint16 "
    for iM in range(len(sheet_timer.col(5)) - 1):
        if str(sheet_timer.cell(iM + 1, 5).value.encode('utf-8')) == "": break
        Text += "tick" + str(iM + 1) + ","
    Text = Text[:-1]
    Text += ";\n"

    Text += "    //1. Layer\n"
    for iM in range(len(sheet_timer.col(3)) - 1):
        if str(sheet_timer.cell(iM + 1, 3).value.encode('utf-8')) == "": break
        op = str(sheet_timer.cell(iM + 1, 3).value.encode('utf-8')).split()
        Text += "    if("
        for iOp_Str in op:
            if iOp_Str.find("In") == 0:
                iStr = str(sheet_timer.cell(int(iOp_Str[2:]), 1).value.encode('utf-8'))
            elif iOp_Str.find("C") == 0:
                iStr = str(sheet_timer.cell(int(iOp_Str[1:]), 2).value.encode('utf-8'))
            else:
                iStr = iOp_Str
            Text += iStr

        Text += ")  m" + str(iM + 1) + "=TRUE;\n"
        Text += "    else m" + str(iM + 1) + "=FALSE;\n"

    Text += "    //2. Layer\n"
    for iM in range(len(sheet_timer.col(4)) - 1):
        if str(sheet_timer.cell(iM + 1, 4).value.encode('utf-8')) == "": break
        Text += "    if(" + str(sheet_timer.cell(iM + 1, 4).value.encode('utf-8')) + "){ if(" + \
                "tick" + str(iM + 1) + "<65530) " + "tick" + str(iM + 1) + "++;}\n"
        Text += "    else " + "tick" + str(iM + 1) + "=0;\n"

    Text += "    //output\n"
    for iM in range(len(sheet_timer.col(6)) - 1):
        if str(sheet_timer.cell(iM + 1, 6).value.encode('utf-8')) == "": break
        Text += "    if(tick" + str(iM + 1) + ">=" + str(sheet_timer.cell(iM + 1, 5).value.encode('utf-8')) + ") " + \
                str(sheet_timer.cell(iM + 1, 6).value.encode('utf-8')) + "=TRUE;\n"
        Text += "    else " + str(sheet_timer.cell(iM + 1, 6).value.encode('utf-8')) + "=FALSE;\n"
    Text += "}\n"

    fobj.write(Text)
    fobj.close()

    if os.path.exists(FilePath + "\SafetyPLC.c"):
        os.remove(FilePath + "\SafetyPLC.c")

    os.rename(FilePath + "\SafetyPLC.txt", FilePath + "\SafetyPLC.c")
    if os.path.exists(DistPath + "\SafetyPLC.c"):
        os.remove(DistPath + "\SafetyPLC.c")
    shutil.move(FilePath + "\SafetyPLC.c", DistPath)


if __name__ == "__main__":
    main()