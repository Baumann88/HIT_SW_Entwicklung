#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os
import shutil

TextHead="#include \"CANopenComm.h\"\n " \
         "\n" \
         "TPDOType TPDOList[MaxNrTPDO];\n" \
         "RPDOType RPDOList[MaxNrRPDO];\n" \
         "\n" \
         "void PDOListSetup(void){\n" \
         "    uint16 ODMemAddr;\n" \
         "    uint16 Index;\n"\
         "    uint8 Subindex;\n" \
         "    uint16 tmp;\n" \
         "    uint32 Value;\n" \
         "    uint16 iByte;\n" \
         "\n"

TPDOCFGTextTemplate=[
                        "    //TPDO",
                        "    TPDOList[k].enable=1; \n",
                        "    TPDOList[k].COBID=x; \n",
                        "    TPDOList[k].BusNumber=x; \n",
                        "    TPDOList[k].EventTime=x; \n",
                        "    TPDOList[k].DataCount=0; \n",
                        "    Value=x; \n",
                        "    Index=(uint16)((Value&0xffff0000)>>16); \n"
                        "    Subindex=(uint16)((Value&0x0000ff00)>>8); \n"
                        "    tmp = (uint16)(Value & 0x000000ff); \n"
                        "    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); \n"
                        "    for(iByte=0;iByte<tmp;iByte++){\n",
                        "        TPDOList[k].Data[TPDOList[k].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; \n"
                        "        TPDOList[k].DataCount++;} \n"
                     ]
RPDOCFGTextTemplate = [
                        "    //RPDO",
                        "    RPDOList[k].enable=1; \n",
                        "    RPDOList[k].COBID=x; \n",
                        "    RPDOList[k].BusNumber=x; \n",
                        "    RPDOList[k].DataCount=0; \n",
                        "    col2_pdo_register(mpv_Bus[RPDOList[k].BusNumber], RPDOList[k].COBID, &RPDOList[k].RPDOHandle);\n",
                        "    Value=x; \n",
                        "    Index=(uint16)((Value&0xffff0000)>>16); \n"
                        "    Subindex=(uint16)((Value&0x0000ff00)>>8); \n"
                        "    tmp = (uint16)(Value & 0x000000ff); \n"
                        "    GetSetOD(Index,Subindex,&ODMemAddr,&Value,GetOD); \n"
                        "    for(iByte=0;iByte<tmp;iByte++){\n",
                        "        RPDOList[k].Data[RPDOList[k].DataCount]=(uint8 *)&ODMem[ODMemAddr]+iByte; \n"
                        "        RPDOList[k].DataCount++;} \n"
                       ]

#SourcePath="C:\Users\wsun.HIT-WARDENBURG\Desktop\/auftrage_deuschebahn\CFG\PDOConfig.c"
#DistPath="C:\Users\wsun.HIT-WARDENBURG\Desktop\/auftrage_deuschebahn\libs\BSP\CommPort"
SourcePath="..\CFG"
DistPath="..\libs\BSP\CommPort"

def main():
    fobjSource = open("pdo_cfg.txt", "r")
    open("PDOConfig.txt", "a").close()
    fobjDist = open("PDOConfig.txt", "w")

    iterm=-1
    TPDOWrite = 0
    RPDOWrite = 0
    CodeText=""
    for line in fobjSource:
        if line.find("TPDO CFG")!=-1:
            TPDOWrite = 1
            RPDOWrite = 0
            CodeText+= "    //TPDO Configuation \n"
        if line.find("RPDO CFG")!=-1:
            TPDOWrite = 0
            RPDOWrite = 1
            CodeText+= "    //RPDO Configuration \n"
        if line.find("--------------------------------------")!=-1:
            TPDOWrite = 0
            RPDOWrite = 0
            iterm = -1

        if TPDOWrite==1 and iterm>=0:
            tmpValue=[s for s in line.split()]
            CodeText+=TPDOCFGTextTemplate[0]+str(iterm)+"\n"+TPDOCFGTextTemplate[1].replace("k",str(iterm))
            TmpStr=TPDOCFGTextTemplate[2].replace("k", str(iterm))
            TmpStr=TmpStr.replace("x","0x"+str(tmpValue.pop(0)))
            CodeText+=TmpStr
            TmpStr=TPDOCFGTextTemplate[3].replace("k", str(iterm))
            TmpStr=TmpStr.replace("x",str(tmpValue.pop(0)))
            CodeText+=TmpStr
            TmpStr=TPDOCFGTextTemplate[4].replace("k", str(iterm))
            TmpStr=TmpStr.replace("x",str(tmpValue.pop(0)))
            CodeText+=TmpStr
            CodeText+=TPDOCFGTextTemplate[5].replace("k", str(iterm))+"\n"
            for iMapValue in tmpValue:
                CodeText += TPDOCFGTextTemplate[6].replace("x","0x"+str(iMapValue))+TPDOCFGTextTemplate[7]+\
                            TPDOCFGTextTemplate[8].replace("k", str(iterm))+"\n"
            CodeText +="\n\n"

        if RPDOWrite == 1 and iterm >= 0:
            tmpValue = [s for s in line.split()]
            CodeText += RPDOCFGTextTemplate[0] + str(iterm) + "\n" + RPDOCFGTextTemplate[1].replace("k", str(iterm))
            TmpStr = RPDOCFGTextTemplate[2].replace("k", str(iterm))
            TmpStr = TmpStr.replace("x", "0x" + str(tmpValue.pop(0)))
            CodeText += TmpStr
            TmpStr = RPDOCFGTextTemplate[3].replace("k", str(iterm))
            TmpStr = TmpStr.replace("x", str(tmpValue.pop(0)))
            CodeText += TmpStr
            CodeText += RPDOCFGTextTemplate[4].replace("k", str(iterm))
            CodeText += RPDOCFGTextTemplate[5].replace("k", str(iterm)) + "\n"
            for iMapValue in tmpValue:
                CodeText += RPDOCFGTextTemplate[6].replace("x","0x"+str(iMapValue)) + RPDOCFGTextTemplate[7] + \
                            RPDOCFGTextTemplate[8].replace("k", str(iterm)) + "\n"

            CodeText += "\n\n"

        if TPDOWrite==1 or RPDOWrite==1:
            iterm += 1




    fobjDist.write(TextHead+CodeText+"}")
    fobjDist.close()
    fobjSource.close()

    if os.path.exists(SourcePath + "\PDOConfig.c"):
        os.remove(SourcePath + "\PDOConfig.c")

    os.rename(SourcePath + "\PDOConfig.txt", SourcePath + "\PDOConfig.c")
    if os.path.exists(DistPath + "\PDOConfig.c"):
        os.remove(DistPath + "\PDOConfig.c")
    shutil.move(SourcePath + "\PDOConfig.c", DistPath)


if __name__ == "__main__":
    main()

