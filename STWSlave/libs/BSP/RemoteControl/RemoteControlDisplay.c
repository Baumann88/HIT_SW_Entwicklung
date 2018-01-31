#include "RemoteControl.h"
#include "RemoteControlData.h"
#include "RemoteControlDisplayErrorText.h"

static uint32 row,column;
static uint16 tmpRowUpdate;

static uint8 ascii_Num[10]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39};

static uint8 PageInit[8][20]={
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x4d,0x6f,0x76,0x65,0x2d,0x65,0x2d,0x53,0x74,0x61,0x72,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x34,0x30,0x30,0x2d,0x31,0x32,0x2d,0x43,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x49,0x6e,0x69,0x74,0x69,0x61,0x6c,0x2e,0x2e,0x2e,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20
};

static uint8 UpdatePointStateInit[2]={6,13};

static uint8 PageReady[8][20]={
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x4d,0x6f,0x76,0x65,0x2d,0x65,0x2d,0x53,0x74,0x61,0x72,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x34,0x30,0x30,0x2d,0x31,0x32,0x2d,0x43,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x42,0x65,0x72,0x65,0x69,0x74,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20
};

static uint8 PageRun[8][20]={
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x46,0x61,0x68,0x72,0x73,0x79,0x73,0x74,0x65,0x6d,
    0x20,0x2d,0x2d,0xa2,0x20,0x20,0x20,0x2d,0x2d,0xa2,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x41,0x20,0xe0,0x2d,0x2d,0x2d,0xe0,0x20,0x42,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x7c,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x7c,0x81,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x7c,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x43,0x20,0xe0,0x2d,0x2d,0x2d,0xe0,0x20,0x44,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x2d,0x2d,0xa2,0x20,0x20,0x20,0x2d,0x2d,0xa2,0x20,0x20,0x20,0x20,0x4e,0x6f,0x72,0x6d,0x61,0x6c
};

static uint8 UpdatePointStateRun[9][2]={6,15,
                                        2,1,
                                        2,7,
                                        8,1,
                                        8,7,
                                        5,1,
                                        5,7,
                                        8,15,
                                        4,15};

static uint8 PageHub[8][20]={
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x48,0x75,0x62,0x73,0x79,0x73,0x74,0x65,0x6d,
    0x2d,0x2d,0x2d,0x6d,0x6d,0x20,0x2d,0x2d,0x2d,0x6d,0x6d,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x41,0x20,0xe0,0x2d,0x2d,0x2d,0xe0,0x20,0x42,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x7c,0x20,0x20,0x20,0x20,0x20,0x20,0x50,0x20,0x69,0x6e,0x20,0x62,0x61,0x72,
    0x20,0x20,0x20,0x20,0x2d,0x7c,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x41,0x3a,0x2d,0x2d,0x2d,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x7c,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x42,0x3a,0x2d,0x2d,0x2d,0x20,0x20,
    0x20,0x43,0x20,0xe0,0x2d,0x2d,0x2d,0xe0,0x20,0x44,0x20,0x20,0x20,0x43,0x3a,0x2d,0x2d,0x2d,0x20,0x20,
    0x2d,0x2d,0x2d,0x6d,0x6d,0x20,0x2d,0x2d,0x2d,0x6d,0x6d,0x20,0x20,0x44,0x3a,0x2d,0x2d,0x2d,0x20,0x20
};

static uint8 UpdatePointStateHub[11][2]={2,1,
                                        2,6,
                                        8,1,
                                        8,6,
                                        5,5,
                                        5,8,
                                        5,15,
                                        6,15,
                                        7,15,
                                        8,15,
                                        2,15};
static uint8 PageAuto[8][20]={
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x41,0x75,0x74,0x6f,0x6e,0x6f,0x6d,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x41,0x20,0xe0,0x2d,0x2d,0x2d,0xe0,0x20,0x42,0x20,0x20,0x20,0x20,0x58,0x3a,0x78,0x78,0x78,0x78,
    0x20,0x20,0x20,0x20,0x20,0x7c,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x7c,0x2d,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x59,0x31,0x3a,0x78,0x78,0x78,
    0x20,0x20,0x20,0x20,0x20,0x7c,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x59,0x32,0x3a,0x78,0x78,0x78,
    0x20,0x43,0x20,0xe0,0x2d,0x2d,0x2d,0xe0,0x20,0x44,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20
};

static uint8 UpdatePointStateAuto[7][2]={1,1,
                                        2,4,
                                        5,7,
                                        3,15,
                                        5,15,
                                        6,15,
                                        8,4};

static uint8 PageError[8][20]={
    0x45,0x72,0x72,0x6f,0x72,0x3a,0x20,0x30,0x2f,0x30,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x83,0x84,
    0x44,0x65,0x76,0x69,0x63,0x65,0x20,0x49,0x44,0x3a,0x2d,0x2d,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x45,0x72,0x72,0x6f,0x72,0x20,0x43,0x6f,0x64,0x65,0x3a,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x2d,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20
};

static uint8 UpdatePointStateError[5][2]={1,1,
                                        1,7,
                                        2,11,
                                        3,12,
                                        3,15};

static uint8 PageNotFall[8][20]={
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x4d,0x6f,0x76,0x65,0x2d,0x65,0x2d,0x53,0x74,0x61,0x72,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x34,0x30,0x30,0x2d,0x31,0x32,0x2d,0x43,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20
};

//Not-Aus: 5,7
//Ladung: 5,7
//Rlais Aus: 5,5

//=================================================================================================
/*!
    Function: find the Number in Error Text List via Errorcode
    output: None
*/
//=================================================================================================
sint16 GetNumErrorTextList(uint32 Errorcode){
    sint16 iItem;
    for(iItem=0;iItem<LengthOfErrorList;iItem++){
        if(ErrorCodeList[iItem]==Errorcode) return iItem;
    }
    return -1;
}

//=================================================================================================
/*!
    Function: initial the display
    output: None
*/
//=================================================================================================
void DisplayPageInit(void){
    uint16 i;
    uint16 StrCol;

    if(column<18) StrCol=column;
    else StrCol=column-4;

    *outputRemoteControlString0=(uint32)(row+1)+((uint32)(StrCol+1)<<8);
    *outputRemoteControlString1=0x00000000;
    *outputRemoteControlString2=(uint32)(20*(row+4)+StrCol)<<8;
    *outputRemoteControlString3=0x00000000;

    for(i=2;i<8;i++){
        if(*inputRCFromMasterPageState==KeyRCDisplayPageStateInit){
            if(i<4){
                *outputRemoteControlString0+=((uint32)PageInit[row][StrCol+i-2]<<i*8);
                *outputRemoteControlString2+=((uint32)PageInit[row+4][StrCol+i-2]<<i*8);
            }
            else {
                *outputRemoteControlString1+=((uint32)PageInit[row][StrCol+i-2]<<(i-4)*8);
                *outputRemoteControlString3+=((uint32)PageInit[row+4][StrCol+i-2]<<(i-4)*8);
            }
        }
        else if((*inputRCFromMasterPageState==KeyRCDisplayPageStateReady)&&(akt_page==0)){
            if(i<4){
                *outputRemoteControlString0+=((uint32)PageReady[row][StrCol+i-2]<<i*8);
                *outputRemoteControlString2+=((uint32)PageReady[row+4][StrCol+i-2]<<i*8);
            }
            else {
                *outputRemoteControlString1+=((uint32)PageReady[row][StrCol+i-2]<<(i-4)*8);
                *outputRemoteControlString3+=((uint32)PageReady[row+4][StrCol+i-2]<<(i-4)*8);
            }
        }
        else if((*inputRCFromMasterPageState==KeyRCDisplayPageStateRun)&&(akt_page==0)){
            if(i<4){
                *outputRemoteControlString0+=((uint32)PageRun[row][StrCol+i-2]<<i*8);
                *outputRemoteControlString2+=((uint32)PageRun[row+4][StrCol+i-2]<<i*8);
            }
            else {
                *outputRemoteControlString1+=((uint32)PageRun[row][StrCol+i-2]<<(i-4)*8);
                *outputRemoteControlString3+=((uint32)PageRun[row+4][StrCol+i-2]<<(i-4)*8);
            }
        }
        else if((*inputRCFromMasterPageState==KeyRCDisplayPageStateHub)&&(akt_page==0)){
            if(i<4){
                *outputRemoteControlString0+=((uint32)PageHub[row][StrCol+i-2]<<i*8);
                *outputRemoteControlString2+=((uint32)PageHub[row+4][StrCol+i-2]<<i*8);
            }
            else {
                *outputRemoteControlString1+=((uint32)PageHub[row][StrCol+i-2]<<(i-4)*8);
                *outputRemoteControlString3+=((uint32)PageHub[row+4][StrCol+i-2]<<(i-4)*8);
            }
        }
        else if((*inputRCFromMasterPageState==KeyRCDisplayPageStateAuto)&&(akt_page==0)){
            if(i<4){
                *outputRemoteControlString0+=((uint32)PageAuto[row][StrCol+i-2]<<i*8);
                *outputRemoteControlString2+=((uint32)PageAuto[row+4][StrCol+i-2]<<i*8);
            }
            else {
                *outputRemoteControlString1+=((uint32)PageAuto[row][StrCol+i-2]<<(i-4)*8);
                *outputRemoteControlString3+=((uint32)PageAuto[row+4][StrCol+i-2]<<(i-4)*8);
            }
        }
        else if((*inputRCFromMasterPageState!=KeyRCDisplayPageStateInit)&&(akt_page==1)){
            if(i<4){
                *outputRemoteControlString0+=((uint32)PageError[row][StrCol+i-2]<<i*8);
                *outputRemoteControlString2+=((uint32)PageError[row+4][StrCol+i-2]<<i*8);
            }
            else {
                *outputRemoteControlString1+=((uint32)PageError[row][StrCol+i-2]<<(i-4)*8);
                *outputRemoteControlString3+=((uint32)PageError[row+4][StrCol+i-2]<<(i-4)*8);
            }
        }
        if(*inputRCFromMasterPageState==KeyRCDisplayPageStateNotFall){
            if(i<4){
                *outputRemoteControlString0+=((uint32)PageNotFall[row][StrCol+i-2]<<i*8);
                *outputRemoteControlString2+=((uint32)PageNotFall[row+4][StrCol+i-2]<<i*8);
            }
            else {
                *outputRemoteControlString1+=((uint32)PageNotFall[row][StrCol+i-2]<<(i-4)*8);
                *outputRemoteControlString3+=((uint32)PageNotFall[row+4][StrCol+i-2]<<(i-4)*8);
            }
        }
    }
    column+=6;
    if(column>=20){
        column=0;
        row++;
        if(row>=4) row=0;
    }
}

//=================================================================================================
/*!
    Function: Update the display
    output: None
*/
//=================================================================================================
void DisplayPageUpdate(void){
    uint16 i;
    static uint8 iErrorText;

    if(*inputRCFromMasterPageState==KeyRCDisplayPageStateInit){
        *outputRemoteControlString0=(uint32)(UpdatePointStateInit[0])+((uint32)(UpdatePointStateInit[1])<<8);
        *outputRemoteControlString1=0x00000000;
        *outputRemoteControlString2=0x20200000;
        *outputRemoteControlString3=0x20202020;
        for(i=2;i<8;i++){
            if(i<4) *outputRemoteControlString0+=((uint32)PageInit[UpdatePointStateInit[0]-1][UpdatePointStateInit[1]-3+i]<<i*8);
            else *outputRemoteControlString1+=((uint32)PageInit[UpdatePointStateInit[0]-1][UpdatePointStateInit[1]-3+i]<<(i-4)*8);
        }
    }
    if((*inputRCFromMasterPageState==KeyRCDisplayPageStateRun)&&(akt_page==0)){
        *outputRemoteControlString0=(uint32)(UpdatePointStateRun[tmpRowUpdate][0])+((uint32)(UpdatePointStateRun[tmpRowUpdate][1])<<8);
        *outputRemoteControlString1=0x00000000;
        *outputRemoteControlString2=0x20200000;
        *outputRemoteControlString3=0x20202020;
        for(i=2;i<8;i++){
            if(i<4) *outputRemoteControlString0+=((uint32)PageRun[UpdatePointStateRun[tmpRowUpdate][0]-1][UpdatePointStateRun[tmpRowUpdate][1]-3+i]<<i*8);
            else {
                if(UpdatePointStateRun[tmpRowUpdate][1]<19) *outputRemoteControlString1+=((uint32)PageRun[UpdatePointStateRun[tmpRowUpdate][0]-1][UpdatePointStateRun[tmpRowUpdate][1]-3+i]<<(i-4)*8);
            }
        }
        tmpRowUpdate++;
        if(tmpRowUpdate>=9) tmpRowUpdate=0;
    }
    else if((*inputRCFromMasterPageState==KeyRCDisplayPageStateHub)&&(akt_page==0)){
        *outputRemoteControlString0=(uint32)(UpdatePointStateHub[tmpRowUpdate][0])+((uint32)(UpdatePointStateHub[tmpRowUpdate][1])<<8);
        *outputRemoteControlString1=0x00000000;
        *outputRemoteControlString2=0x20200000;
        *outputRemoteControlString3=0x20202020;
        for(i=2;i<8;i++){
            if(i<4) *outputRemoteControlString0+=((uint32)PageHub[UpdatePointStateHub[tmpRowUpdate][0]-1][UpdatePointStateHub[tmpRowUpdate][1]-3+i]<<i*8);
            else {
                if(UpdatePointStateHub[tmpRowUpdate][1]<19) *outputRemoteControlString1+=((uint32)PageHub[UpdatePointStateHub[tmpRowUpdate][0]-1][UpdatePointStateHub[tmpRowUpdate][1]-3+i]<<(i-4)*8);
            }
        }
        tmpRowUpdate++;
        if(tmpRowUpdate>=11) tmpRowUpdate=0;
    }
    else if((*inputRCFromMasterPageState==KeyRCDisplayPageStateAuto)&&(akt_page==0)){
        *outputRemoteControlString0=(uint32)(UpdatePointStateAuto[tmpRowUpdate][0])+((uint32)(UpdatePointStateAuto[tmpRowUpdate][1])<<8);
        *outputRemoteControlString1=0x00000000;
        *outputRemoteControlString2=0x20200000;
        *outputRemoteControlString3=0x20202020;
        for(i=2;i<8;i++){
            if(i<4) *outputRemoteControlString0+=((uint32)PageAuto[UpdatePointStateAuto[tmpRowUpdate][0]-1][UpdatePointStateAuto[tmpRowUpdate][1]-3+i]<<i*8);
            else {
                if(UpdatePointStateAuto[tmpRowUpdate][1]<19) *outputRemoteControlString1+=((uint32)PageAuto[UpdatePointStateAuto[tmpRowUpdate][0]-1][UpdatePointStateAuto[tmpRowUpdate][1]-3+i]<<(i-4)*8);
            }
        }
        tmpRowUpdate++;
        if(tmpRowUpdate>=7) tmpRowUpdate=0;
    }
    if((*inputRCFromMasterPageState!=KeyRCDisplayPageStateInit)&&(akt_page==1)){
        if(*inputRCFromMasterPageState!=KeyRCDisplayPageStateNotFall){
            *outputRemoteControlString0=(uint32)(UpdatePointStateError[tmpRowUpdate][0])+((uint32)(UpdatePointStateError[tmpRowUpdate][1])<<8);
            *outputRemoteControlString1=0x00000000;
            if(iErrorText<0x3c) iErrorText=0x3c;
            *outputRemoteControlString2=(uint32)(iErrorText)<<8;
            *outputRemoteControlString3=0x00000000;
            for(i=2;i<8;i++){
                if(i<4) {
                    *outputRemoteControlString0+=((uint32)PageError[UpdatePointStateError[tmpRowUpdate][0]-1][UpdatePointStateError[tmpRowUpdate][1]-3+i]<<i*8);
                    *outputRemoteControlString2+=((uint32)PageError[3+(iErrorText-0x3c)/19][(iErrorText-0x3c)%19]<<i*8);
                }
                else {
                    if(UpdatePointStateError[tmpRowUpdate][1]<19) *outputRemoteControlString1+=((uint32)PageError[UpdatePointStateError[tmpRowUpdate][0]-1][UpdatePointStateError[tmpRowUpdate][1]-3+i]<<(i-4)*8);
                    if(((iErrorText-0x3c)%19)<18) *outputRemoteControlString3+=((uint32)PageError[3+(iErrorText-0x3c)/19][(iErrorText-0x3c)%19]<<(i-4)*8);
                }
                iErrorText++;
                if(iErrorText>0x8b){
                    iErrorText=0x3c;
                    return;
                }
            }
            tmpRowUpdate++;
            if(tmpRowUpdate>=5) tmpRowUpdate=0;
        }
    }
}

//=================================================================================================
/*!
    Function: Display of Initial
    output: None
*/
//=================================================================================================
void DisplayInit(void){
    static uint32 timeStampInitAnimation;
    if((RCActualTime-timeStampInitAnimation)>1000){
       timeStampInitAnimation=RCActualTime;
       if(PageInit[5][14]==0x2e){PageInit[5][13]=0x20;PageInit[5][14]=0x20;}
       else if(PageInit[5][13]==0x2e)PageInit[5][14]=0x2e;
       else if(PageInit[5][13]==0x20)PageInit[5][13]=0x2e;
    }

}


//=================================================================================================
/*!
    Function: Display of Ready Page
    output: None
*/
//=================================================================================================
void DisplayReady(void){
    //static sint16 Displayflag=1;

    //Displayflag=0-Displayflag;
    /*if((*inputRCGetErrorNum+*inputRCGetMasterCPUErrorNum)>0){
        PageReady[5][5]=0x20;
        PageReady[5][6]=0xe0;
        PageReady[5][7]=0xc6;
        PageReady[5][8]=0xe5;
        PageReady[5][9]=0xe8;
        PageReady[5][10]=0xec;
        PageReady[5][11]=0xe5;
        PageReady[5][12]=0xf2;
        PageReady[5][13]=0xe0;
        if(Displayflag==1) PageReady[5][14]=0x21;
        else PageReady[5][14]=0x20;
    }
    else{
        PageReady[5][5]=0x20;
        PageReady[5][6]=0x20;
        PageReady[5][7]=0x42;
        PageReady[5][8]=0x65;
        PageReady[5][9]=0x72;
        PageReady[5][10]=0x65;
        PageReady[5][11]=0x69;
        PageReady[5][12]=0x74;
        PageReady[5][13]=0x20;
        PageReady[5][14]=0x20;
    }*/
    PageReady[5][5]=0x20;
    PageReady[5][6]=0x20;
    PageReady[5][7]=0x42;
    PageReady[5][8]=0x65;
    PageReady[5][9]=0x72;
    PageReady[5][10]=0x65;
    PageReady[5][11]=0x69;
    PageReady[5][12]=0x74;
    PageReady[5][13]=0x20;
    PageReady[5][14]=0x20;
}

//=================================================================================================
/*!
    Function: Display of Drive
    output: None
*/
//=================================================================================================
void DisplayRun(void){
    static uint16 flag;
    sint32 tmp;

    if(flag==5){
        tmp=*inputRCFromMasterDriveSysAngle11;
        if(tmp>9||tmp<-9){
            if(tmp<0) {
                PageRun[1][0]=0x2d;
                tmp=0-tmp;
            }
            else PageRun[1][0]=0x20;
            PageRun[1][1]=ascii_Num[tmp/10];
            PageRun[1][2]=ascii_Num[tmp%10];
        }
        else{
            PageRun[1][0]=0x20;
            if(tmp<0) {
                PageRun[1][1]=0x2d;
                tmp=0-tmp;
            }
            else PageRun[1][1]=0x20;
            PageRun[1][2]=ascii_Num[tmp%10];
        }

        tmp=*inputRCFromMasterDriveSysAngle12;
        if(tmp>9||tmp<-9){
            if(tmp<0) {
                PageRun[1][6]=0x2d;
                tmp=0-tmp;
            }
            else PageRun[1][6]=0x20;
            PageRun[1][7]=ascii_Num[tmp/10];
            PageRun[1][8]=ascii_Num[tmp%10];
        }
        else{
            PageRun[1][6]=0x20;
            if(tmp<0) {
                PageRun[1][7]=0x2d;
                tmp=0-tmp;
            }
            else PageRun[1][7]=0x20;
            PageRun[1][8]=ascii_Num[tmp%10];
        }
    }
    else if(flag==4){
        tmp=*inputRCFromMasterDriveSysAngle21;
        if(tmp>9||tmp<-9){
            if(tmp<0) {
                PageRun[7][0]=0x2d;
                tmp=0-tmp;
            }
            else PageRun[7][0]=0x20;
            PageRun[7][1]=ascii_Num[tmp/10];
            PageRun[7][2]=ascii_Num[tmp%10];
        }
        else{
            PageRun[7][0]=0x20;
            if(tmp<0) {
                PageRun[7][1]=0x2d;
                tmp=0-tmp;
            }
            else PageRun[7][1]=0x20;
            PageRun[7][2]=ascii_Num[tmp%10];
        }

        tmp=*inputRCFromMasterDriveSysAngle22;
        if(tmp>9||tmp<-9){
            if(tmp<0) {
                PageRun[7][6]=0x2d;
                tmp=0-tmp;
            }
            else PageRun[7][6]=0x20;
            PageRun[7][7]=ascii_Num[tmp/10];
            PageRun[7][8]=ascii_Num[tmp%10];
        }
        else{
            PageRun[7][6]=0x20;
            if(tmp<0) {
                PageRun[7][7]=0x2d;
                tmp=0-tmp;
            }
            else PageRun[7][7]=0x20;
            PageRun[7][8]=ascii_Num[tmp%10];
        }
    }
    else if(flag==3){
        if((*inputRCGetErrorNum+*inputRCGetMasterCPUErrorNum)>0){
            PageRun[5][15]=0x45;
            PageRun[5][16]=0x72;
            PageRun[5][17]=0x72;
            PageRun[5][18]=0x6f;
            PageRun[5][19]=0x72;
        }
        else {
            PageRun[5][15]=0x20;
            PageRun[5][16]=0x20;
            PageRun[5][17]=0x20;
            PageRun[5][18]=0x20;
            PageRun[5][19]=0x20;
        }
    }
    else if(flag==2){
        if(*inputRCGetSafetyMasterControlWord&KeyRCSetSafetySysLaserscanner1Deaktiv){
            PageRun[1][5]=0x20;
        }
        else{
            if(*inputRCGetSafetyMasterControlWord&KeyRCGetSafetySysLaserscanner1Stop) PageRun[1][5]=0x2d;
            else{
                if(*inputRCGetSafetyMasterControlWord&KeyRCGetSafetySysLaserscanner1Warn) PageRun[1][5]=0x21;
                else PageRun[1][5]=0x78;
            }
        }
        if(*inputRCGetSafetyMasterControlWord&KeyRCSetSafetySysLaserscanner2Deaktiv){
            PageRun[7][5]=0x20;
        }
        else{
            if(*inputRCGetSafetyMasterControlWord&KeyRCGetSafetySysLaserscanner2Stop) PageRun[7][5]=0x2d;
            else{
                if(*inputRCGetSafetyMasterControlWord&KeyRCGetSafetySysLaserscanner2Warn) PageRun[7][5]=0x21;
                else PageRun[7][5]=0x78;
            }
        }
       if(*inputRCFromMasterStatusExtMES&KeyRCDisplayStatusExtLSDeaktiv){
            PageRun[3][14]=0x4e;
            PageRun[3][15]=0x6f;
            PageRun[3][16]=0x20;
            PageRun[3][17]=0x53;
            PageRun[3][18]=0x4c;
            PageRun[3][19]=0x53;
        }
        else{
            PageRun[3][14]=0x20;
            PageRun[3][15]=0x20;
            PageRun[3][16]=0x20;
            PageRun[3][17]=0x53;
            PageRun[3][18]=0x4c;
            PageRun[3][19]=0x53;
        }
    }
    else if(flag==1){
        if(*inputRCFromMasterStatusExtMES&KeyRCDisplayStatusExtCrossIsSwitch){
            PageRun[4][6]=0x77;
            PageRun[4][7]=0x61;
            PageRun[4][8]=0x69;
            PageRun[4][9]=0x74;
            PageRun[4][10]=0x2e;
            PageRun[4][11]=0x2e;
        }
        else{
            if(*inputRCFromMasterStatusMES&KeyRCDisplayStatusCrossDrive) PageRun[4][6]=0x80;
            else PageRun[4][6]=0x81;
            PageRun[4][7]=0x20;
            PageRun[4][8]=0x20;
            PageRun[4][9]=0x20;
            PageRun[4][10]=0x20;
            PageRun[4][11]=0x20;
        }
        //display steering mode
        if(*inputRCFromMasterSteeringMode==KeyRCDisplaySteeringModePark){
            PageRun[4][0]=0x50;
            PageRun[4][1]=0x20;
        }
        else if(*inputRCFromMasterSteeringMode==KeyRCDisplaySteeringModeAllrad){
            PageRun[4][0]=0x41;
            PageRun[4][1]=0x52;
        }
        else if(*inputRCFromMasterSteeringMode==KeyRCDisplaySteeringModeVorderrad){
            PageRun[4][0]=0x56;
            PageRun[4][1]=0x52;
        }
        else if(*inputRCFromMasterSteeringMode==KeyRCDisplaySteeringModeHinterrad){
            PageRun[4][0]=0x48;
            PageRun[4][1]=0x52;
        }
        else if(*inputRCFromMasterSteeringMode==KeyRCDisplaySteeringModeKrebsgang){
            PageRun[4][0]=0x4b;
            PageRun[4][1]=0x47;
        }
        else if(*inputRCFromMasterSteeringMode==KeyRCDisplaySteeringModeRundgang){
            PageRun[4][0]=0x52;
            PageRun[4][1]=0x47;
        }

        if(*inputRCFromMasterStatusMES&KeyRCDisplayStatusIsSteeringMotion){
            PageRun[7][14]=0x4d;
            PageRun[7][15]=0x6f;
            PageRun[7][16]=0x74;
            PageRun[7][17]=0x69;
            PageRun[7][18]=0x6f;
            PageRun[7][19]=0x6e;
        }
        else {
            PageRun[7][14]=0x4e;
            PageRun[7][15]=0x6f;
            PageRun[7][16]=0x72;
            PageRun[7][17]=0x6d;
            PageRun[7][18]=0x61;
            PageRun[7][19]=0x6c;
        }
    }
    else if(flag==0){
        if(*inputRCFromMasterStatusMES&KeyRCDisplayStatusZeroSet){
            PageRun[4][2]=0x80;
            PageRun[4][3]=0x7c;
            PageRun[4][4]=0x7f;
        }
        else{
            PageRun[4][2]=0x20;
            PageRun[4][3]=0x20;
            PageRun[4][4]=0x20;
        }
    }
    if(flag>0) flag--;
    else flag=5;
}

//=================================================================================================
/*!
    Function: Display of Hub system
    output: None
*/
//=================================================================================================
void DisplayHub(void){
    static uint16 flag;
    sint8 tmp[8];

    if(flag==3){
        tmp[0]=(uint16)(*inputRCGetHubWerk11Height);
        if(tmp[0]>99){PageHub[1][0]=ascii_Num[tmp[0]/100];tmp[0]=tmp[0]%100;}
        else PageHub[1][0]=0x30;
        if(tmp[0]>9){PageHub[1][1]=ascii_Num[tmp[0]/10];tmp[0]=tmp[0]%10;}
        else PageHub[1][1]=0x30;
        if(tmp[0]<=9) PageHub[1][2]=ascii_Num[tmp[0]];

        tmp[1]=(uint16)(*inputRCGetHubWerk12Height);
        if(tmp[1]>99){PageHub[1][6]=ascii_Num[tmp[1]/100];tmp[1]=tmp[1]%100;}
        else PageHub[1][6]=0x30;
        if(tmp[1]>9){PageHub[1][7]=ascii_Num[tmp[1]/10];tmp[1]=tmp[1]%10;}
        else PageHub[1][7]=0x30;
        if(tmp[1]<=9) PageHub[1][8]=ascii_Num[tmp[1]];

        tmp[2]=(uint16)(*inputRCGetHubWerk21Height);
        if(tmp[2]>99){PageHub[7][0]=ascii_Num[tmp[2]/100];tmp[2]=tmp[2]%100;}
        else PageHub[7][0]=0x30;
        if(tmp[2]>9){PageHub[7][1]=ascii_Num[tmp[2]/10]; tmp[2]=tmp[2]%10;}
        else PageHub[7][1]=0x30;
        if(tmp[2]<=9) PageHub[7][2]=ascii_Num[tmp[2]];

        tmp[3]=(uint16)(*inputRCGetHubWerk22Height);
        if(tmp[3]>99){PageHub[7][6]=ascii_Num[tmp[3]/100];tmp[3]=tmp[3]%100;}
        else PageHub[7][6]=0x30;
        if(tmp[3]>9){PageHub[7][7]=ascii_Num[tmp[3]/10]; tmp[3]=tmp[3]%10;}
        else PageHub[7][7]=0x30;
        if(tmp[3]<=9) PageHub[7][8]=ascii_Num[tmp[3]];
    }
    else if(flag==2){
        tmp[4]=(uint16)(*inputRCGetHubWerk11Pressure/1000);
        if(tmp[4]>99){PageHub[4][15]=ascii_Num[tmp[4]/100];tmp[4]=tmp[4]%100;}
        else PageHub[4][15]=0x30;
        if(tmp[4]>9){PageHub[4][16]=ascii_Num[tmp[4]/10];tmp[4]=tmp[4]%10;}
        else PageHub[4][16]=0x30;
        if(tmp[4]<=9) PageHub[4][17]=ascii_Num[tmp[4]];

        tmp[5]=(uint16)(*inputRCGetHubWerk12Pressure/1000);
        if(tmp[5]>99){PageHub[5][15]=ascii_Num[tmp[5]/100];tmp[5]=tmp[5]%100;}
        else PageHub[5][15]=0x30;
        if(tmp[5]>9){PageHub[5][16]=ascii_Num[tmp[5]/10];tmp[5]=tmp[5]%10;}
        else PageHub[5][16]=0x30;
        if(tmp[5]<=9) PageHub[5][17]=ascii_Num[tmp[5]];

        tmp[6]=(uint16)(*inputRCGetHubWerk21Pressure/1000);
        if(tmp[6]>99){PageHub[6][15]=ascii_Num[tmp[6]/100];tmp[6]=tmp[6]%100;}
        else PageHub[6][15]=0x30;
        if(tmp[6]>9){PageHub[6][16]=ascii_Num[tmp[6]/10];tmp[6]=tmp[6]%10;}
        else PageHub[6][16]=0x30;
        if(tmp[6]<=9) PageHub[6][17]=ascii_Num[tmp[6]];

        tmp[7]=(uint16)(*inputRCGetHubWerk22Pressure/1000);
        if(tmp[7]>99){PageHub[7][15]=ascii_Num[tmp[7]/100];tmp[7]=tmp[7]%100;}
        else PageHub[7][15]=0x30;
        if(tmp[7]>9){PageHub[7][16]=ascii_Num[tmp[7]/10];tmp[7]=tmp[7]%10;}
        else PageHub[7][16]=0x30;
        if(tmp[7]<=9) PageHub[7][17]=ascii_Num[tmp[7]];
    }
    else if(flag==1){
        if((*inputRCGetErrorNum+*inputRCGetMasterCPUErrorNum)>0){
            PageHub[1][15]=0x45;
            PageHub[1][16]=0x72;
            PageHub[1][17]=0x72;
            PageHub[1][18]=0x6f;
            PageHub[1][19]=0x72;
        }
        else {
            PageHub[1][15]=0x20;
            PageHub[1][16]=0x20;
            PageHub[1][17]=0x20;
            PageHub[1][18]=0x20;
            PageHub[1][19]=0x20;
        }
    }
    else if(flag==0){
        if((*inputRCGetHubSystemControlWord&KeyRCSetHubSysEnable)==0){
            PageHub[4][6]=0x77;
            PageHub[4][7]=0x61;
            PageHub[4][8]=0x69;
            PageHub[4][9]=0x74;
            PageHub[4][10]=0x2e;
            PageHub[4][11]=0x2e;
        }
        else{
            PageHub[4][6]=0x20;
            PageHub[4][7]=0x20;
            PageHub[4][8]=0x20;
            PageHub[4][9]=0x20;
            PageHub[4][10]=0x20;
            PageHub[4][11]=0x20;
        }
        if(*inputRCGetHubSystemControlWord&KeyRCSetHubSysHeben)PageHub[4][4]=0x81;
        else if(*inputRCGetHubSystemControlWord&KeyRCSetHubSysSinken)PageHub[4][4]=0x82;
        else PageHub[4][4]=0x2d;
    }
    if(flag>0) flag--;
    else flag=3;
}

//=================================================================================================
/*!
    Function: Display of Auto Drive
    output: None
*/
//=================================================================================================
void DisplayAutoDrive(void){
    static uint16 flag;
    sint32 tmp;
    if(flag==5){
        if(*inputRCFromMasterAutoDriveState==KeyRCDisplayAutoDriveStateNoLane){
            PageAuto[0][0]=0x4e;
            PageAuto[0][1]=0x6f;
            PageAuto[0][2]=0x6e;
            PageAuto[0][3]=0x65;
            PageAuto[0][4]=0x20;
            PageAuto[0][5]=0x20;
            PageAuto[0][6]=0x20;
        }
        else if(*inputRCFromMasterAutoDriveState==KeyRCDisplayAutoDriveStateOnLane){
            PageAuto[0][0]=0x4c;
            PageAuto[0][1]=0x61;
            PageAuto[0][2]=0x6e;
            PageAuto[0][3]=0x65;
            PageAuto[0][4]=0x20;
            PageAuto[0][5]=0x20;
            PageAuto[0][6]=0x20;
        }
        else if(*inputRCFromMasterAutoDriveState==KeyRCDisplayAutoDriveStateOnTagNoUsed){
            PageAuto[0][0]=0x4c;
            PageAuto[0][1]=0x61;
            PageAuto[0][2]=0x6e;
            PageAuto[0][3]=0x65;
            PageAuto[0][4]=0x20;
            PageAuto[0][5]=0x20;
            PageAuto[0][6]=0x20;
        }
        else if(*inputRCFromMasterAutoDriveState==KeyRCDisplayAutoDriveStateOnTagUsed){
            PageAuto[0][0]=0x4c;
            PageAuto[0][1]=0x61;
            PageAuto[0][2]=0x6e;
            PageAuto[0][3]=0x65;
            PageAuto[0][4]=0x20;
            PageAuto[0][5]=0x20;
            PageAuto[0][6]=0x20;
        }
        else if(*inputRCFromMasterAutoDriveState==KeyRCDisplayAutoDriveStateInPos){
            PageAuto[0][0]=0x49;
            PageAuto[0][1]=0x6e;
            PageAuto[0][2]=0x20;
            PageAuto[0][3]=0x50;
            PageAuto[0][4]=0x6f;
            PageAuto[0][5]=0x73;
            PageAuto[0][6]=0x2e;
        }
        else if(*inputRCFromMasterAutoDriveState==KeyRCDisplayAutoDriveStateLiftButtom){
            PageAuto[0][0]=0x49;
            PageAuto[0][1]=0x6e;
            PageAuto[0][2]=0x20;
            PageAuto[0][3]=0x50;
            PageAuto[0][4]=0x6f;
            PageAuto[0][5]=0x73;
            PageAuto[0][6]=0x2e;
        }
    }
    else if(flag==4){
        if(*inputRCFromMasterStatusAutoDrive&KeyRCDisplayAutoStatusAutoInit){
            PageAuto[4][6]=0x77;
            PageAuto[4][7]=0x61;
            PageAuto[4][8]=0x69;
            PageAuto[4][9]=0x74;
            PageAuto[4][10]=0x2e;
            PageAuto[4][11]=0x2e;
        }
        else{
            PageAuto[4][6]=0x20;
            PageAuto[4][7]=0x20;
            PageAuto[4][8]=0x20;
            PageAuto[4][9]=0x20;
            PageAuto[4][10]=0x20;
            PageAuto[4][11]=0x20;
        }
    }
    else if(flag==3){
        if(*inputRCFromMasterStatusAutoDrive&KeyRCDisplayAutoStatusAutoStopZone){
            tmp=*inputRCFromMasterXValue;
            if(tmp>999){PageAuto[2][16]=ascii_Num[tmp/1000];tmp=tmp%1000;}
            else PageAuto[2][16]=0x30;
            if(tmp>99){PageAuto[2][17]=ascii_Num[tmp/100];tmp=tmp%100;}
            else PageAuto[2][17]=0x30;
            if(tmp>9){PageAuto[2][18]=ascii_Num[tmp/10];tmp=tmp%10;}
            else PageAuto[2][18]=0x30;
            if(tmp<=9) PageAuto[2][19]=ascii_Num[tmp];
        }
        else{
            PageAuto[2][16]=0x2d;
            PageAuto[2][17]=0x2d;
            PageAuto[2][18]=0x2d;
            PageAuto[2][19]=0x2d;
        }
    }
    else if(flag==2){
        if(*inputRCFromMasterStatusAutoDrive&KeyRCDisplayAutoStatusK1BandFind){
            tmp=*inputRCFromMasterY1Value;
            if(tmp>=0) PageAuto[4][17]=0x2b;
            else { PageAuto[4][17]=0x2d; tmp=0-tmp;}
            if(tmp>9){PageAuto[4][18]=ascii_Num[tmp/10];tmp=tmp%10;}
            else PageAuto[4][18]=0x30;
            if(tmp<=9) PageAuto[4][19]=ascii_Num[tmp];
        }
        else{
            PageAuto[4][17]=0x2d;
            PageAuto[4][18]=0x2d;
            PageAuto[4][19]=0x2d;
        }
        if(*inputRCFromMasterStatusAutoDrive&KeyRCDisplayAutoStatusK2BandFind){
            tmp=*inputRCFromMasterY2Value;
            if(tmp>=0) PageAuto[5][17]=0x2b;
            else { PageAuto[5][17]=0x2d; tmp=0-tmp;}
            if(tmp>9){PageAuto[5][18]=ascii_Num[tmp/10];tmp=tmp%10;}
            else PageAuto[5][18]=0x30;
            if(tmp<=9) PageAuto[5][19]=ascii_Num[tmp];
        }
        else{
            PageAuto[5][17]=0x2d;
            PageAuto[5][18]=0x2d;
            PageAuto[5][19]=0x2d;
        }
    }
    else if(flag==1){
        if((*inputRCGetErrorNum+*inputRCGetMasterCPUErrorNum)>0){
            PageAuto[7][15]=0x45;
            PageAuto[7][16]=0x72;
            PageAuto[7][17]=0x72;
            PageAuto[7][18]=0x6f;
            PageAuto[7][19]=0x72;
            /*PageAuto[7][15]=0x20;
            PageAuto[7][16]=0x20;
            PageAuto[7][17]=0x20;
            PageAuto[7][18]=0x20;
            PageAuto[7][19]=0x20;*/
        }
        else {
            PageAuto[7][15]=0x20;
            PageAuto[7][16]=0x20;
            PageAuto[7][17]=0x20;
            PageAuto[7][18]=0x20;
            PageAuto[7][19]=0x20;
        }
        if((*inputRCFromMasterStatusAutoDrive&KeyRCDisplayAutoStatusAutoInit)==0){
            if(*inputRCFromMasterStatusAutoDrive&KeyRCDisplayAutoStatusDriveForward) PageAuto[4][6]=0x81;
            else if(*inputRCFromMasterStatusAutoDrive&KeyRCDisplayAutoStatusDriveBackward) PageAuto[4][6]=0x82;
            else PageAuto[4][6]=0x20;
        }
    }
    else if(flag==0){
        if(*inputRCGetSafetyMasterControlWord&KeyRCSetSafetySysLaserscanner1Deaktiv){
            PageAuto[1][5]=0x20;
        }
        else{
            if(*inputRCGetSafetyMasterControlWord&KeyRCGetSafetySysLaserscanner1Stop) PageAuto[1][5]=0x2d;
            else PageAuto[1][5]=0x78;
        }
        if(*inputRCGetSafetyMasterControlWord&KeyRCSetSafetySysLaserscanner2Deaktiv){
            PageAuto[7][5]=0x20;
        }
        else{
            if(*inputRCGetSafetyMasterControlWord&KeyRCGetSafetySysLaserscanner2Stop) PageAuto[7][5]=0x2d;
            else PageAuto[7][5]=0x78;
        }
    }
    if(flag>0) flag--;
    else flag=5;
}

//=================================================================================================
/*!
    Function: Display of NotFall
    output: None
*/
//=================================================================================================
void DisplayNotFall(void){
    if(*inputRCFromMasterStatusMES&KeyRCDisplayStatusNotAus){
        if((*inputRemoteControlDigitalIn&RemoteControlSchutzRealis)==0){
            if((*inputRemoteControlDigitalIn&RemoteControlButtonNotAus)==0){
                PageNotFall[5][6]=0x4e;
                PageNotFall[5][7]=0x6f;
                PageNotFall[5][8]=0x74;
                PageNotFall[5][9]=0x2d;
                PageNotFall[5][10]=0x41;
                PageNotFall[5][11]=0x75;
                PageNotFall[5][12]=0x73;
                PageNotFall[6][6]=0x20;
                PageNotFall[6][7]=0x20;
                PageNotFall[6][8]=0x20;
                PageNotFall[6][9]=0x20;
                PageNotFall[6][10]=0x20;
                PageNotFall[6][11]=0x20;
                PageNotFall[6][12]=0x20;
            }
            else{
                PageNotFall[5][6]=0x20;
                PageNotFall[5][7]=0x53;
                PageNotFall[5][8]=0x74;
                PageNotFall[5][9]=0x61;
                PageNotFall[5][10]=0x72;
                PageNotFall[5][11]=0x74;
                PageNotFall[5][12]=0x20;
                PageNotFall[6][6]=0x44;
                PageNotFall[6][7]=0x72;
                PageNotFall[6][8]=0x75;
                PageNotFall[6][9]=0x63;
                PageNotFall[6][10]=0x6b;
                PageNotFall[6][11]=0x65;
                PageNotFall[6][12]=0x6e;
            }
        }
        else{
            PageNotFall[5][6]=0x4e;
            PageNotFall[5][7]=0x6f;
            PageNotFall[5][8]=0x74;
            PageNotFall[5][9]=0x2d;
            PageNotFall[5][10]=0x41;
            PageNotFall[5][11]=0x75;
            PageNotFall[5][12]=0x73;
            PageNotFall[6][6]=0x20;
            PageNotFall[6][7]=0x20;
            PageNotFall[6][8]=0x20;
            PageNotFall[6][9]=0x20;
            PageNotFall[6][10]=0x20;
            PageNotFall[6][11]=0x20;
            PageNotFall[6][12]=0x20;
        }
    }
    else{
        if(*inputRCFromMasterStatusMES&KeyRCDisplayStatusLadung){
            PageNotFall[5][6]=0x20;
            PageNotFall[5][7]=0x4c;
            PageNotFall[5][8]=0x61;
            PageNotFall[5][9]=0x64;
            PageNotFall[5][10]=0x75;
            PageNotFall[5][11]=0x6e;
            PageNotFall[5][12]=0x67;
            PageNotFall[6][6]=0x20;
            PageNotFall[6][7]=0x20;
            PageNotFall[6][8]=0x20;
            PageNotFall[6][9]=0x20;
            PageNotFall[6][10]=0x20;
            PageNotFall[6][11]=0x20;
            PageNotFall[6][12]=0x20;
        }
        else if((*inputRemoteControlDigitalIn&RemoteControlSchutzRealis)==0){
            PageNotFall[5][6]=0x20;
            PageNotFall[5][7]=0x53;
            PageNotFall[5][8]=0x74;
            PageNotFall[5][9]=0x61;
            PageNotFall[5][10]=0x72;
            PageNotFall[5][11]=0x74;
            PageNotFall[5][12]=0x20;
            PageNotFall[6][6]=0x44;
            PageNotFall[6][7]=0x72;
            PageNotFall[6][8]=0x75;
            PageNotFall[6][9]=0x63;
            PageNotFall[6][10]=0x6b;
            PageNotFall[6][11]=0x65;
            PageNotFall[6][12]=0x6e;
        }
        else{
            PageNotFall[5][6]=0x20;
            PageNotFall[5][7]=0x20;
            PageNotFall[5][8]=0x20;
            PageNotFall[5][9]=0x20;
            PageNotFall[5][10]=0x20;
            PageNotFall[5][11]=0x20;
            PageNotFall[5][12]=0x20;
            PageNotFall[6][6]=0x20;
            PageNotFall[6][7]=0x20;
            PageNotFall[6][8]=0x20;
            PageNotFall[6][9]=0x20;
            PageNotFall[6][10]=0x20;
            PageNotFall[6][11]=0x20;
            PageNotFall[6][12]=0x20;
        }
    }
}

//=================================================================================================
/*!
    Function: Display of Error
    output: None
*/
//=================================================================================================
void DisplayError(void){
    static uint16 flag;
    static uint8 Error_page;
    uint8 ErrorNum;
    uint32 ErrorCode;
    sint16 NumErrorList;
    uint32 tmp;
    uint16 i;

    ErrorNum=*inputRCGetErrorNum+*inputRCGetMasterCPUErrorNum;

    if(RCReqWord&KeyRCReqWordMeunTasterLeft){
        RCReqWord&=~KeyRCReqWordMeunTasterLeft;
        if(Error_page>0) Error_page--;
        else Error_page=0;
    }
    if(RCReqWord&KeyRCReqWordMeunTasterRight){
        RCReqWord&=~KeyRCReqWordMeunTasterRight;
        if(Error_page<(ErrorNum-1)) Error_page++;
        else Error_page=ErrorNum-1;
    }
    if(ErrorNum!=0){
        if(Error_page<*inputRCGetErrorNum) ErrorCode=*inputRCGetErrorCode[Error_page];
        else ErrorCode=*inputRCGetErrorCodeMasterCPU[Error_page-*inputRCGetErrorNum];
    }
    else ErrorCode=0;
    if(flag==2){
        if(ErrorNum!=0){
            if(Error_page>8) PageError[0][6]=ascii_Num[(Error_page+1)/10];
            else PageError[0][6]=0x20;
            PageError[0][7]=ascii_Num[(Error_page+1)%10];
            if(ErrorNum>9){
                PageError[0][9]=ascii_Num[ErrorNum/10];
                PageError[0][10]=ascii_Num[ErrorNum%10];
            }
            else{
                PageError[0][9]=ascii_Num[ErrorNum];
                PageError[0][10]=0x20;
            }
        }
        else{
            PageError[0][18]=0x20;
            PageError[0][19]=0x20;
            PageError[0][6]=0x20;
            PageError[0][7]=0x30;
            PageError[0][9]=0x30;
            PageError[0][10]=0x20;
        }
    }
    else if(flag==1){
        if(ErrorNum!=0){
            tmp=ErrorCode%1000000;
            PageError[1][10]=ascii_Num[(uint16)(tmp/100000)];
            tmp=tmp%100000;
            PageError[1][11]=ascii_Num[(uint16)(tmp/10000)];

            PageError[2][11]=ascii_Num[(uint16)(ErrorCode/1000000)];
            tmp=ErrorCode%1000000;
            PageError[2][12]=ascii_Num[(uint16)(tmp/100000)];
            tmp=tmp%100000;
            PageError[2][13]=ascii_Num[(uint16)(tmp/10000)];
            tmp=tmp%10000;
            PageError[2][14]=ascii_Num[(uint16)(tmp/1000)];
            tmp=tmp%1000;
            PageError[2][15]=ascii_Num[(uint16)(tmp/100)];
            tmp=tmp%100;
            PageError[2][16]=ascii_Num[(uint16)(tmp/10)];
            tmp=tmp%10;
            PageError[2][17]=ascii_Num[(uint16)(tmp)];
        }
        else{
            PageError[1][10]=0x2d;
            PageError[1][11]=0x2d;
            PageError[2][11]=0x2d;
            PageError[2][12]=0x2d;
            PageError[2][13]=0x2d;
            PageError[2][14]=0x2d;
            PageError[2][15]=0x2d;
            PageError[2][16]=0x2d;
            PageError[2][17]=0x2d;
        }
    }
    else if(flag==0){
        if(ErrorNum!=0){
            NumErrorList=GetNumErrorTextList(ErrorCode);
            for(i=0;i<60;i++){
                //if(ErrorText[NumErrorList][i]==0x7f) break;
                if(NumErrorList==-1) break;
                PageError[3+i/20][i%20]=ErrorText[NumErrorList][i];
            }
        }
        else {
            for(i=0;i<60;i++){
                //if(PageError[3+i/20][i%20]==0x20) break;
                PageError[3+i/20][i%20]=0x20;
            }
        }
    }
    if(flag>0) flag--;
    else flag=2;
}


void SetPageInit(void){
    tmpRowUpdate=0;
    row=0;
    column=0;
}




//=================================================================================================
/*!
    Function: Main Handle of the Display of the RC
    output: None
*/
//=================================================================================================
void Display(void){
    static uint16 UpdateFlag;
    static uint16 tick;

    if(RCReqWord&KeyRCReqWordMeunTasterPush){
        RCReqWord&=~KeyRCReqWordMeunTasterPush;
        if(akt_page==0) akt_page=1;
        else akt_page=0;
        *inputRCFromMasterStatusMES|=KeyRCDisplayStatusPageUpdate;
    }

    if ((UpdateFlag<300)||(tick<20)) DisplayPageInit();
    else DisplayPageUpdate();
    if(akt_page==0){
        if(*inputRCFromMasterPageState==KeyRCDisplayPageStateInit) DisplayInit();
        else if(*inputRCFromMasterPageState==KeyRCDisplayPageStateReady) DisplayReady();
        else if(*inputRCFromMasterPageState==KeyRCDisplayPageStateRun) DisplayRun();
        else if(*inputRCFromMasterPageState==KeyRCDisplayPageStateHub) DisplayHub();
        else if(*inputRCFromMasterPageState==KeyRCDisplayPageStateAuto) DisplayAutoDrive();
    }
    else{
        if((*inputRCFromMasterPageState!=KeyRCDisplayPageStateInit)&&(*inputRCFromMasterPageState!=KeyRCDisplayPageStateNotFall)) DisplayError();
    }
    if(*inputRCFromMasterPageState==KeyRCDisplayPageStateNotFall) DisplayNotFall();

    if(UpdateFlag<305) UpdateFlag++;

    if(tick>=2000) tick==0;

    if(*inputRCFromMasterStatusMES&KeyRCDisplayStatusPageUpdate){*inputRCFromMasterStatusMES&=~KeyRCDisplayStatusPageUpdate;UpdateFlag=0;}
}




