import xlrd
import os
import shutil

WorkSpacePath="..\SafetyConceptSlave"
TargetFolderPath="..\..\/auftrage_deutschebahn_STWSlave\libs\BSP\Safety"


def main():
    GenerateData(WorkSpacePath,TargetFolderPath)

def GenerateData(FilePath,DistPath):
    # head content of the file SafetyDriveSys
    HeadTextSafetyNormal = "#include <SafetyData.h>\n" \
                             "#include <Safety.h>\n" \
                             "\n"

    open(FilePath + "\SafetyNormal.txt", "a").close()
    fobj = open(FilePath + "\SafetyNormal.txt", "w")
    fobj.write(HeadTextSafetyNormal)

    try:
        read_File_aktion = xlrd.open_workbook(FilePath + '\SafteyNormal\Aktion.xlsx')

    except IOError:
        print "no file of aktion for Safety Normal"
        return

    #Safety Handle Funktion generaieren
    akt_sheet = read_File_aktion.sheet_by_index(0)
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


    Text += "    //1. Layer\n"
    for iM in range(len(akt_sheet.col(6)) - 1):
        if str(akt_sheet.cell(iM+1, 6).value.encode('utf-8')) == "": break
        op=str(akt_sheet.cell(iM+1,6).value.encode('utf-8')).split()
        Text += "    m" + str(iM+1) + "="
        for iOp_Str in op:
            if iOp_Str.find("In")==0: iStr=str(akt_sheet.cell(int(iOp_Str[2:]),2).value.encode('utf-8'))
            elif iOp_Str.find("C")==0: iStr=str(akt_sheet.cell(int(iOp_Str[1:]),5).value.encode('utf-8'))
            elif iOp_Str.find("inten")==0: iStr=str(akt_sheet.cell(int(iOp_Str[5:]),4).value.encode('utf-8'))
            else: iStr=iOp_Str
            Text += iStr

        Text += ";\n"

    Text += "    //Output\n"
    for iM in range(len(akt_sheet.col(6)) - 1):
        if str(akt_sheet.cell(iM + 1, 6).value.encode('utf-8')) == "": break
        if str(akt_sheet.cell(iM + 1, 7).value.encode('utf-8')) != "/":
            op = str(akt_sheet.cell(iM + 1, 7).value.encode('utf-8')).split()
            Text += "    if(m" + str(iM + 1) + "){\n "
            for iOp_Str in op:
                if iOp_Str.find("Out")==0: iStr="        " + str(akt_sheet.cell(int(iOp_Str[3:]),3).value.encode('utf-8'))
                elif iOp_Str.find("inten") == 0: iStr = "        " + str(akt_sheet.cell(int(iOp_Str[5:]), 4).value.encode('utf-8'))
                elif iOp_Str.find("C")==0: iStr=str(akt_sheet.cell(int(iOp_Str[1:]),5).value.encode('utf-8'))
                elif iOp_Str.find(";")==0: iStr=";\n"
                else: iStr=iOp_Str
                Text += iStr
            Text += ";\n"
            Text += "    }\n"
        else: continue

        if str(akt_sheet.cell(iM + 1, 8).value.encode('utf-8')) != "/":
            op = str(akt_sheet.cell(iM + 1, 8).value.encode('utf-8')).split()
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

    Text += "}\n\n"
    fobj.write(Text)


    fobj.close()

    if os.path.exists(FilePath + "\SafetyNormal.c"):
        os.remove(FilePath + "\SafetyNormal.c")

    os.rename(FilePath + "\SafetyNormal.txt", FilePath + "\SafetyNormal.c")
    if os.path.exists(DistPath + "\SafetyNormal.c"):
        os.remove(DistPath + "\SafetyNormal.c")
    shutil.move(FilePath + "\SafetyNormal.c", DistPath)


if __name__ == "__main__":
    main()