import xlrd
import os
import shutil

SymbolTabelle={'A': '0x41','B': '0x42','C': '0x43','D': '0x44','E': '0x45','F': '0x46','G': '0x47','H': '0x48',
               'I': '0x49','J': '0x4a','K': '0x4b','L': '0x4c','M': '0x4d','N': '0x4e','O': '0x4f','P': '0x50',
               'Q': '0x51','R': '0x52','S': '0x53','T': '0x54','U': '0x55','V': '0x56','W': '0x57','X': '0x58',
               'Y': '0x59','Z': '0x5a','a': '0x61','b': '0x62','c': '0x63','d': '0x64','e': '0x65','f': '0x66',
               'g': '0x67','h': '0x68','i': '0x69','j': '0x6a','k': '0x6b','l': '0x6c','m': '0x6d','n': '0x6e',
               'o': '0x6f','p': '0x70','q': '0x71','r': '0x72','s': '0x73','t': '0x74','u': '0x75','v': '0x76',
               'w': '0x77','x': '0x78','y': '0x79','z': '0x7a',',': '0x2c',' ': '0x20','0': '0x30','1': '0x31',
               '2': '0x32','3': '0x33','4': '0x34','5': '0x35','6': '0x36','7': '0x37','8': '0x38','9': '0x39'}

WorkSpacePath="..\ErrorTestGenerate"
TargetFolderPath="..\..\/auftrage_deutschebahn_STWSlave\libs\BSP\RemoteControl"


def main():
    GenerateErrorText(WorkSpacePath,TargetFolderPath)

def GenerateErrorText(FilePath,DistPath):
    try:
        read_File = xlrd.open_workbook(FilePath + '\SicherheitPlan.xlsx')
    except IOError:
        print "no file for error text"
        return

    akt_sheet = read_File.sheet_by_index(0)
    Entry=len(akt_sheet.col(0)) - 1



    # head content of the headfile RemoteControlDisplayErrorText
    HeadTextErrorTextHeadFile = "#ifndef _REMOTECONTROLDISPLAYERRORTEXT_H\n" \
                                "#define _REMOTECONTROLDISPLAYERRORTEXT_H\n" \
                                "#include <stwtypes.h>\n" \
                                "\n"

    # head content of the file RemoteControlDisplayErrorText
    HeadTextErrorText = "#include <RemoteControlDisplayErrorText.h>\n" \
                         "\n"

    # erstllen die Head File: RemoteControlDisplayErrorText
    open(FilePath + "\RemoteControlDisplayErrorText.txt", "a").close()
    fobj = open(FilePath + "\RemoteControlDisplayErrorText.txt", "w")
    fobj.write(HeadTextErrorTextHeadFile)


    # main text
    Text = "#define LengthOfErrorList                     " + str(Entry) + "\n"
    Text += "\n"
    Text += "extern uint32 ErrorCodeList[LengthOfErrorList];\n"
    Text += "extern uint8 ErrorText[LengthOfErrorList][60];\n"
    Text += "\n"
    Text += "\n"
    Text += "#endif"
    fobj.write(Text)
    fobj.close()

    if os.path.exists(FilePath + "\RemoteControlDisplayErrorText.h"):
        os.remove(FilePath + "\RemoteControlDisplayErrorText.h")

    os.rename(FilePath + "\RemoteControlDisplayErrorText.txt", FilePath + "\RemoteControlDisplayErrorText.h")
    if os.path.exists(DistPath + "\RemoteControlDisplayErrorText.h"):
        os.remove(DistPath + "\RemoteControlDisplayErrorText.h")
    shutil.move(FilePath + "\RemoteControlDisplayErrorText.h", DistPath)

    # erstllen die File: RemoteControlDisplayErrorText
    open(FilePath + "\RemoteControlDisplayErrorText.txt", "a").close()
    fobj = open(FilePath + "\RemoteControlDisplayErrorText.txt", "w")
    fobj.write(HeadTextErrorText)

    Text = "uint32 ErrorCodeList[LengthOfErrorList]={\n"
    for iM in range(Entry):
        Text += "        " + str(akt_sheet.cell(iM+1, 0).value.encode('utf-8'))
        if iM < Entry-1: Text +=",\n"
        else: Text +="\n"
    Text += "};\n"
    fobj.write(Text)

    Text = "uint8 ErrorText[LengthOfErrorList][60]={\n"
    for iM in range(Entry):
        tmpStr = str(akt_sheet.cell(iM+1, 1).value.encode('utf-8'))
        for iStr in range(60):
            if iStr<len(tmpStr): Text+=SymbolTabelle[tmpStr[iStr]]
            #elif iStr==len(tmpStr): Text+="0x7f"
            else: Text+=SymbolTabelle[" "]
            if iStr==59:
                if iM < Entry-1: Text +=",\n"
                else: Text +="\n"
            else: Text += ", "
    Text += "};\n"
    fobj.write(Text)
    fobj.close()


    if os.path.exists(FilePath + "\RemoteControlDisplayErrorText.c"):
        os.remove(FilePath + "\RemoteControlDisplayErrorText.c")

    os.rename(FilePath + "\RemoteControlDisplayErrorText.txt", FilePath + "\RemoteControlDisplayErrorText.c")
    if os.path.exists(DistPath + "\RemoteControlDisplayErrorText.c"):
        os.remove(DistPath + "\RemoteControlDisplayErrorText.c")
    shutil.move(FilePath + "\RemoteControlDisplayErrorText.c", DistPath)

if __name__ == "__main__":
    main()