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
    0x20,0x20,0x20,0x20,0x20,0x49,0x6e,0x69,0x74,0x69,0x61,0x6c,0x2e,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
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
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x46,0x61,0x68,0x72,0x65,0x6e,
    0x20,0x2d,0x2d,0xa2,0x20,0x20,0x20,0x2d,0x2d,0xa2,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0xe0,0x2d,0x2d,0x2d,0xe0,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x48,0x61,0x6e,0x64,
    0x20,0x20,0x20,0x20,0x81,0x7c,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x7c,0x20,0x20,0x30,0x6d,0x2f,0x6d,0x69,0x6e,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x7c,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0xe0,0x2d,0x2d,0x2d,0xe0,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x2d,0x2d,0xa2,0x20,0x20,0x20,0x2d,0x2d,0xa2,0x20,0x20,0x20,0x20,0x4e,0x6f,0x72,0x6d,0x61,0x6c
};

static uint8 UpdatePointStateRun[9][2]={6,15,
                                        2,1,
                                        2,7,
                                        8,1,
                                        8,7,
                                        5,1,
                                        5,7,
                                        4,1,
                                        8,15};

static uint8 PageHub[8][20]={
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x48,0x65,0x62,0x65,0x6e,
    0x2d,0x2d,0x2d,0x6d,0x6d,0x20,0x2d,0x2d,0x2d,0x6d,0x6d,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x41,0x20,0xe0,0x2d,0x2d,0x2d,0xe0,0x20,0x42,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x7c,0x20,0x20,0x20,0x20,0x20,0x20,0x50,0x20,0x69,0x6e,0x20,0x62,0x61,0x72,
    0x20,0x20,0x20,0x20,0x2d,0x7c,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x41,0x3a,0x2d,0x2d,0x2d,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x7c,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x42,0x3a,0x2d,0x2d,0x2d,0x20,0x20,
    0x20,0x43,0x20,0xe0,0x2d,0x2d,0x2d,0xe0,0x20,0x44,0x20,0x20,0x20,0x43,0x3a,0x2d,0x2d,0x2d,0x20,0x20,
    0x2d,0x2d,0x2d,0x6d,0x6d,0x20,0x2d,0x2d,0x2d,0x6d,0x6d,0x20,0x20,0x44,0x3a,0x2d,0x2d,0x2d,0x20,0x20
};

static uint8 UpdatePointStateHub[10][2]={2,1,
                                        2,6,
                                        8,1,
                                        8,6,
                                        5,5,
                                        5,15,
                                        6,15,
                                        7,15,
                                        8,15,
                                        2,15};
static uint8 PageAuto[8][20]={
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x41,0x55,0x54,0x4f,0x20,0x20,0x20,0x46,0x61,0x68,0x72,0x65,0x6e,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0xe0,0x2d,0x2d,0x2d,0xe0,0x20,0x20,0x20,0x20,0x20,0x20,0x58,0x3a,0x2d,0x2d,0x2d,0x2d,
    0x20,0x20,0x20,0x20,0x20,0x7c,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x7c,0x2d,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x59,0x31,0x3a,0x2d,0x2d,0x2d,
    0x20,0x20,0x20,0x20,0x20,0x7c,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x59,0x32,0x3a,0x2d,0x2d,0x2d,
    0x20,0x20,0x20,0xe0,0x2d,0x2d,0x2d,0xe0,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20
};

static uint8 UpdatePointStateAuto[6][2]={2,4,
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

//=================================================================================================
/*!
    Function: find the Number in Error Text List via Errorcode
    output: None
*/
//=================================================================================================
uint16 GetNumErrorTextList(uint32 Errorcode){
    uint16 iItem;
    for(iItem=0;iItem<LengthOfErrorList;iItem++){
        if(ErrorCodeList[iItem]==Errorcode) return iItem;
    }
    return 0;
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
        if(State==RCStateInit){
            if(i<4){
                *outputRemoteControlString0+=((uint32)PageInit[row][StrCol+i-2]<<i*8);
                *outputRemoteControlString2+=((uint32)PageInit[row+4][StrCol+i-2]<<i*8);
            }
            else {
                *outputRemoteControlString1+=((uint32)PageInit[row][StrCol+i-2]<<(i-4)*8);
                *outputRemoteControlString3+=((uint32)PageInit[row+4][StrCol+i-2]<<(i-4)*8);
            }
        }
        else if((State==RCStateReady)&&(akt_page==0)){
            if(i<4){
                *outputRemoteControlString0+=((uint32)PageReady[row][StrCol+i-2]<<i*8);
                *outputRemoteControlString2+=((uint32)PageReady[row+4][StrCol+i-2]<<i*8);
            }
            else {
                *outputRemoteControlString1+=((uint32)PageReady[row][StrCol+i-2]<<(i-4)*8);
                *outputRemoteControlString3+=((uint32)PageReady[row+4][StrCol+i-2]<<(i-4)*8);
            }
        }
        else if((State==RCStateRun)&&(akt_page==0)){
            if(i<4){
                *outputRemoteControlString0+=((uint32)PageRun[row][StrCol+i-2]<<i*8);
                *outputRemoteControlString2+=((uint32)PageRun[row+4][StrCol+i-2]<<i*8);
            }
            else {
                *outputRemoteControlString1+=((uint32)PageRun[row][StrCol+i-2]<<(i-4)*8);
                *outputRemoteControlString3+=((uint32)PageRun[row+4][StrCol+i-2]<<(i-4)*8);
            }
        }
        else if((State==RCStateHub)&&(akt_page==0)){
            if(i<4){
                *outputRemoteControlString0+=((uint32)PageHub[row][StrCol+i-2]<<i*8);
                *outputRemoteControlString2+=((uint32)PageHub[row+4][StrCol+i-2]<<i*8);
            }
            else {
                *outputRemoteControlString1+=((uint32)PageHub[row][StrCol+i-2]<<(i-4)*8);
                *outputRemoteControlString3+=((uint32)PageHub[row+4][StrCol+i-2]<<(i-4)*8);
            }
        }
        else if((State==RCStateAutoDrive)&&(akt_page==0)){
            if(i<4){
                *outputRemoteControlString0+=((uint32)PageAuto[row][StrCol+i-2]<<i*8);
                *outputRemoteControlString2+=((uint32)PageAuto[row+4][StrCol+i-2]<<i*8);
            }
            else {
                *outputRemoteControlString1+=((uint32)PageAuto[row][StrCol+i-2]<<(i-4)*8);
                *outputRemoteControlString3+=((uint32)PageAuto[row+4][StrCol+i-2]<<(i-4)*8);
            }
        }
        else if((State!=RCStateInit)&&(akt_page==1)){
            if(i<4){
                *outputRemoteControlString0+=((uint32)PageError[row][StrCol+i-2]<<i*8);
                *outputRemoteControlString2+=((uint32)PageError[row+4][StrCol+i-2]<<i*8);
            }
            else {
                *outputRemoteControlString1+=((uint32)PageError[row][StrCol+i-2]<<(i-4)*8);
                *outputRemoteControlString3+=((uint32)PageError[row+4][StrCol+i-2]<<(i-4)*8);
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

    if(State==RCStateInit){
        *outputRemoteControlString0=(uint32)(UpdatePointStateInit[0])+((uint32)(UpdatePointStateInit[1])<<8);
        *outputRemoteControlString1=0x00000000;
        *outputRemoteControlString2=0x20200000;
        *outputRemoteControlString3=0x20202020;
        for(i=2;i<8;i++){
            if(i<4) *outputRemoteControlString0+=((uint32)PageInit[UpdatePointStateInit[0]-1][UpdatePointStateInit[1]-3+i]<<i*8);
            else *outputRemoteControlString1+=((uint32)PageInit[UpdatePointStateInit[0]-1][UpdatePointStateInit[1]-3+i]<<(i-4)*8);
        }
    }
    if((State==RCStateRun)&&(akt_page==0)){
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
    else if((State==RCStateHub)&&(akt_page==0)){
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
        if(tmpRowUpdate>=10) tmpRowUpdate=0;
    }
    else if((State==RCStateAutoDrive)&&(akt_page==0)){
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
        if(tmpRowUpdate>=6) tmpRowUpdate=0;
    }
    if((State!=RCStateInit)&&(akt_page==1)){
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
    static sint16 Displayflag=1;

    Displayflag=0-Displayflag;
    if((*outputRCSetSafetyControlWord&KeyRCGetSafetyIsError)||(*inputRCGetSlaveSafetyControlWord&KeyRCGetSafetyIsError)){
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
    }
}

//=================================================================================================
/*!
    Function: Display of Drive
    output: None
*/
//=================================================================================================
void DisplayRun(void){
    static uint32 timeStampRunAnimation;
    static uint16 flag;
    sint32 tmp;

    if(flag==5){
        tmp=*inputRCGetDriveModule11Angle;
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

        tmp=*inputRCGetDriveModule12Angle;
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
        tmp=*inputRCGetDriveModule21Angle;
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

        tmp=*inputRCGetDriveModule22Angle;
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
        if((*outputRCSetSafetyControlWord&KeyRCGetSafetyIsError)||(*inputRCGetSlaveSafetyControlWord&KeyRCGetSafetyIsError)){
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
        if(RCReqWord&KeyRCReqWordCrossDrive) PageRun[3][4]=0x80;
        else PageRun[3][4]=0x81;
        if(*inputRemoteControlDigitalIn&Parken) PageRun[4][0]=0x50;
        else PageRun[4][0]=0x20;
        if(*outputRCSetSafetyControlWord&KeyRCSetSafetySysLaserscannerDeaktiv){
            PageRun[1][5]=0x78;
            PageRun[7][5]=0x78;
        }
        else{
            if(*outputRCSetSafetyControlWord&KeyRCGetSafetySysLaserscanner1Stop) PageRun[1][5]=0x2d;
            else{
                if(*outputRCSetSafetyControlWord&KeyRCGetSafetySysLaserscanner1Warn) PageRun[1][5]=0x21;
                else PageRun[1][5]=0x20;
            }
            if(*outputRCSetSafetyControlWord&KeyRCGetSafetySysLaserscanner2Stop) PageRun[7][5]=0x2d;
            else{
                if(*outputRCSetSafetyControlWord&KeyRCGetSafetySysLaserscanner2Warn) PageRun[7][5]=0x21;
                else PageRun[7][5]=0x20;
            }
        }
    }
    else if(flag==1){
        if(RCReqWord&KeyRCReqWordIndDrive){
            PageRun[7][14]=0x49;
            PageRun[7][15]=0x6e;
            PageRun[7][16]=0x64;
            PageRun[7][17]=0x2e;
            PageRun[7][18]=0x20;
            PageRun[7][19]=0x20;
        }
        else{
            PageRun[7][14]=0x4e;
            PageRun[7][15]=0x6f;
            PageRun[7][16]=0x72;
            PageRun[7][17]=0x6d;
            PageRun[7][18]=0x61;
            PageRun[7][19]=0x6c;
        }
    }
    else if(flag==0){
        if(RCReqWord&KeyRCReqWordZeroSet){
            PageRun[4][2]=0x80;
            PageRun[4][3]=0x7c;
            PageRun[4][4]=0x7f;
        }
        else{
            PageRun[4][2]=0x20;
            PageRun[4][3]=0x20;
            PageRun[4][4]=0x20;
        }


        tmp=(sint32)(*outputRCSetDriveSysSpeed*60.0);

        if(tmp>9||tmp<-9){
            if(tmp<0) {
                PageRun[4][6]=0x2d;
                tmp=0-tmp;
            }
            else PageRun[4][6]=0x20;
            PageRun[4][7]=ascii_Num[tmp/10];
            PageRun[4][8]=ascii_Num[tmp%10];
        }
        else{
            PageRun[4][6]=0x20;
            if(tmp<0) {
                PageRun[4][7]=0x2d;
                tmp=0-tmp;
            }
            else PageRun[4][7]=0x20;
            PageRun[4][8]=ascii_Num[tmp%10];
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
    sint8 tmp;

    if(flag==3){
        tmp=(uint16)(*inputRCGetHubWerk11Height);
        if(tmp>99){PageHub[1][0]=ascii_Num[tmp/100];tmp=tmp%100;}
        else PageHub[1][0]=0x30;
        if(tmp>9){PageHub[1][1]=ascii_Num[tmp/10];tmp=tmp%10;}
        else PageHub[1][1]=0x30;
        if(tmp<=9) PageHub[1][2]=ascii_Num[tmp];

        tmp=(uint16)(*inputRCGetHubWerk12Height);
        if(tmp>99){PageHub[1][6]=ascii_Num[tmp/100];tmp=tmp%100;}
        else PageHub[1][6]=0x30;
        if(tmp>9){PageHub[1][7]=ascii_Num[tmp/10];tmp=tmp%10;}
        else PageHub[1][7]=0x30;
        if(tmp<=9) PageHub[1][8]=ascii_Num[tmp];

        tmp=(uint16)(*inputRCGetHubWerk21Height);
        if(tmp>99){PageHub[7][0]=ascii_Num[tmp/100];tmp=tmp%100;}
        else PageHub[7][0]=0x30;
        if(tmp>9){PageHub[7][1]=ascii_Num[tmp/10]; tmp=tmp%10;}
        else PageHub[7][1]=0x30;
        if(tmp<=9) PageHub[7][2]=ascii_Num[tmp];

        tmp=(uint16)(*inputRCGetHubWerk22Height);
        if(tmp>99){PageHub[7][6]=ascii_Num[tmp/100];tmp=tmp%100;}
        else PageHub[7][6]=0x30;
        if(tmp>9){PageHub[7][7]=ascii_Num[tmp/10]; tmp=tmp%10;}
        else PageHub[7][7]=0x30;
        if(tmp<=9) PageHub[7][8]=ascii_Num[tmp];
    }
    else if(flag==2){
        tmp=(uint16)(*inputRCGetHubWerk11Pressure/1000);
        if(tmp>99){PageHub[4][15]=ascii_Num[tmp/100];tmp=tmp%100;}
        else PageHub[4][15]=0x30;
        if(tmp>9){PageHub[4][16]=ascii_Num[tmp/10];tmp=tmp%10;}
        else PageHub[4][16]=0x30;
        if(tmp<=9) PageHub[4][17]=ascii_Num[tmp];

        tmp=(uint16)(*inputRCGetHubWerk12Pressure/1000);
        if(tmp>99){PageHub[5][15]=ascii_Num[tmp/100];tmp=tmp%100;}
        else PageHub[5][15]=0x30;
        if(tmp>9){PageHub[6][16]=ascii_Num[tmp/10];tmp=tmp%10;}
        else PageHub[5][16]=0x30;
        if(tmp<=9) PageHub[5][17]=ascii_Num[tmp];

        tmp=(uint16)(*inputRCGetHubWerk21Pressure/1000);
        if(tmp>99){PageHub[6][15]=ascii_Num[tmp/100];tmp=tmp%100;}
        else PageHub[6][15]=0x30;
        if(tmp>9){PageHub[7][16]=ascii_Num[tmp/10];tmp=tmp%10;}
        else PageHub[6][16]=0x30;
        if(tmp<=9) PageHub[6][17]=ascii_Num[tmp];

        tmp=(uint16)(*inputRCGetHubWerk22Pressure/1000);
        if(tmp>99){PageHub[7][15]=ascii_Num[tmp/100];tmp=tmp%100;}
        else PageHub[7][15]=0x30;
        if(tmp>9){PageHub[7][16]=ascii_Num[tmp/10];tmp=tmp%10;}
        else PageHub[7][16]=0x30;
        if(tmp<=9) PageHub[7][17]=ascii_Num[tmp];
    }
    else if(flag==1){
        if((*outputRCSetSafetyControlWord&KeyRCGetSafetyIsError)||(*inputRCGetSlaveSafetyControlWord&KeyRCGetSafetyIsError)){
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
        if(*inputRemoteControlY1Var>127)PageHub[4][4]=0x81;
        else if(*inputRemoteControlY1Var<127)PageHub[4][4]=0x82;
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
    sint16 tmp;
    if(flag==3){
        if(*outputRCSetAutoDriveControlWord&KeyRCGetAutoDriveInStopZone){
            tmp=*inputRCGetAutoDriveXValue;
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
        if(*outputRCSetAutoDriveControlWord&KeyRCGetAutoDriveK1BandFind){
            tmp=*inputRCGetAutoDriveY1Value;
            if(tmp>=0) PageAuto[4][17]=0x20;
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
        if(*outputRCSetAutoDriveControlWord&KeyRCGetAutoDriveK2BandFind){
            tmp=*inputRCGetAutoDriveY2Value;
            if(tmp>=0) PageAuto[5][17]=0x20;
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
        if((*outputRCSetSafetyControlWord&KeyRCGetSafetyIsError)||(*inputRCGetSlaveSafetyControlWord&KeyRCGetSafetyIsError)){
            PageAuto[7][15]=0x45;
            PageAuto[7][16]=0x72;
            PageAuto[7][17]=0x72;
            PageAuto[7][18]=0x6f;
            PageAuto[7][19]=0x72;
        }
        else {
            PageAuto[7][15]=0x20;
            PageAuto[7][16]=0x20;
            PageAuto[7][17]=0x20;
            PageAuto[7][18]=0x20;
            PageAuto[7][19]=0x20;
        }
        if(*outputRCSetAutoDriveControlWord&KeyRCSetAutoDriveForwardDrive) PageAuto[4][6]=0x81;
        else if(*outputRCSetAutoDriveControlWord&KeyRCSetAutoDriveBackwardDrive) PageAuto[4][6]=0x82;
        else PageAuto[4][6]=0x2d;
    }
    else if(flag==0){
        if(*outputRCSetSafetyControlWord&KeyRCSetSafetySysLaserscannerDeaktiv){
            PageAuto[1][5]=0x78;
            PageAuto[7][5]=0x78;
        }
        else{
            if(*outputRCSetSafetyControlWord&KeyRCGetSafetySysLaserscanner1Stop) PageAuto[1][5]=0x2d;
            else{
                if(*outputRCSetSafetyControlWord&KeyRCGetSafetySysLaserscanner1Warn) PageAuto[1][5]=0x21;
                else PageAuto[1][5]=0x20;
            }
            if(*outputRCSetSafetyControlWord&KeyRCGetSafetySysLaserscanner2Stop) PageAuto[7][5]=0x2d;
            else{
                if(*outputRCSetSafetyControlWord&KeyRCGetSafetySysLaserscanner2Warn) PageAuto[7][5]=0x21;
                else PageAuto[7][5]=0x20;
            }
        }
    }
    if(flag>0) flag--;
    else flag=3;
}

//=================================================================================================
/*!
    Function: Display of Error
    output: None
*/
//=================================================================================================
void DisplayError(void){
    static uint16 flag;
    static uint16 Error_page;
    uint16 ErrorNum;
    uint32 ErrorCode;
    uint16 NumErrorList;
    uint32 tmp;
    uint16 i;

    ErrorNum=*inputRCGetErrorNum;

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
        if(Error_page<ErrorNum) ErrorCode=*inputRCGetErrorCode[Error_page];
        //else ErrorCode=*inputRCGetErrorCodeSalveCPU[Error_page-ErrorNum];
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
                if(ErrorText[NumErrorList][i]==0x7f) break;
                PageError[3+i/20][i%20]=ErrorText[NumErrorList][i];
            }
        }
        else {
            for(i=0;i<60;i++){
                if(PageError[3+i/20][i%20]==0x20) break;
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
        flag_changeState=1;
        *outputRCToSlaveStatusMES|=KeyRCDisplayStatusPageUpdate;
    }
    if ((UpdateFlag<300)||(tick<20)) DisplayPageInit();
    else DisplayPageUpdate();
    if(akt_page==0){
        if(State==RCStateInit) DisplayInit();
        else if(State==RCStateReady) DisplayReady();
        else if(State==RCStateRun) DisplayRun();
        else if(State==RCStateHub) DisplayHub();
        else if(State==RCStateAutoDrive) DisplayAutoDrive();
    }
    if((akt_page==1)&&(State!=RCStateInit)) DisplayError();

    if(UpdateFlag<305) UpdateFlag++;

    if(tick>=2000) tick==0;

    //if(flag_changeState==1){flag_changeState=0;UpdateFlag=0;}
    if(*outputRCToSlaveStatusMES&KeyRCDisplayStatusPageUpdate){*outputRCToSlaveStatusMES&=~KeyRCDisplayStatusPageUpdate;UpdateFlag=0;}
}




