//-----------------------------------------------------------------------------
/*!
   \internal
   \file        ProDB_AppErrorManage.c
   \brief       Application for manage the Error Message from STW CPU

   \implementation
   project
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   created     12.11.2017  W.Sun
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author             Description
   12.11.2017        W.Sun              file created
   \endhistory
*/
//-----------------------------------------------------------------------------
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <stwtypes.h>
#include <can.h>
#include <stdlib.h>

/* -- Defines ------------------------------------------------------------- */
#define CAN_BUS1                0            // Define for CAN1


/* -- Module Global Variables --------------------------------------------- */
static sint16 ms16_CAN1;
static uint32 MasterReceData[32][3];
static uint32 SlaveReceData[32][3];
static uint16 AppIsOpen=0;
static uint8 flag_clear_error=0;


/* -- Module Global Function Prototypes ----------------------------------- */
sint32 ms32_InitCAN (void);

/* -- Implementation ------------------------------------------------------ */
//-----------------------------------------------------------------------------
/*!
   \brief   produce_logfile(void)

   function for produce the log file for error message

   \created       13.11.2017  HIT/W.Sun

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   22.11.2017        HITW.Sun       function created
   \endhistory
*/
//-----------------------------------------------------------------------------
void produce_logfile(void){
    uint16 iReg;
    char path[80]="/mnt/dataflash/ErrorHistory/Error.csv";
    uint16 sec,min,hour,day,mon,year;
    char data[60];
    char str[8];
    FILE *fp = NULL;

    remove(path);
    fp = fopen(path, "a");

    fprintf(fp, "Error code;Date\n");
    for(iReg=0;iReg<32;iReg++){
        sec=(uint16)(MasterReceData[iReg][1]&0x000000ff);
        min=(uint16)((MasterReceData[iReg][1]&0x0000ff00)>>8);
        hour=(uint16)((MasterReceData[iReg][1]&0x00ff0000)>>16);
        day=(uint16)((MasterReceData[iReg][1]&0xff000000)>>24);
        mon=(uint16)(MasterReceData[iReg][2]&0x000000ff);
        year=(uint16)((MasterReceData[iReg][2]&0xffff0000)>>16);
        fprintf(fp, "%u;%u-%u-%u-%u-%u-%u\n", MasterReceData[iReg][0],year,mon,day,hour,min,sec);
    }
    for(iReg=0;iReg<32;iReg++){
        sec=(uint16)(SlaveReceData[iReg][1]&0x000000ff);
        min=(uint16)((SlaveReceData[iReg][1]&0x0000ff00)>>8);
        hour=(uint16)((SlaveReceData[iReg][1]&0x00ff0000)>>16);
        day=(uint16)((SlaveReceData[iReg][1]&0xff000000)>>24);
        mon=(uint16)(SlaveReceData[iReg][2]&0x000000ff);
        year=(uint16)((SlaveReceData[iReg][2]&0xffff0000)>>16);
        fprintf(fp, "%u;%u-%u-%u-%u-%u-%u\n", SlaveReceData[iReg][0],year,mon,day,hour,min,sec);
    }
    fclose(fp);
    fp = NULL;
}




//-----------------------------------------------------------------------------
/*!
   \brief   thread_sendMsg(void *ptr)

   function thread for send data via CAN

   \created       13.11.2017  HIT/W.Sun

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   13.11.2017        HITW.Sun      function created
   \endhistory
*/
//-----------------------------------------------------------------------------
void thread_sendMsg(void *ptr){
    T_can_msg t_CanMsg;
    uint32 Master_COB_ID=0x602;
    uint32 Slave_COB_ID=0x603;
    uint16 index=0x6500;
    uint8 start_subindex=0x01;
    sint32 result;
    uint8 iReg;

    t_CanMsg.t_Id.u32_Id = Master_COB_ID;
    t_CanMsg.t_Id.u8_Xtd = 0;
    t_CanMsg.u8_Dlc = 8;
    t_CanMsg.au8_Data[0] = 0x40;
    t_CanMsg.au8_Data[1] = index&0xff;;
    t_CanMsg.au8_Data[2] = (index>>8)&0xff;
    t_CanMsg.au8_Data[3] = start_subindex;
    t_CanMsg.au8_Data[4] = 0x00;
    t_CanMsg.au8_Data[5] = 0x00;
    t_CanMsg.au8_Data[6] = 0x00;
    t_CanMsg.au8_Data[7] = 0x00;
    // Send Message
    while(1){
        t_CanMsg.t_Id.u32_Id = Master_COB_ID;
        for(iReg=0;iReg<32;iReg++){
            t_CanMsg.au8_Data[3] = start_subindex+iReg;
            result = gs32_CAN_SendMsg(&ms16_CAN1, &t_CanMsg);
            if(result!=C_NO_ERR){
                break;
            }
            usleep(50*1000);
            t_CanMsg.au8_Data[3] = start_subindex+0x21+iReg*2;
            result = gs32_CAN_SendMsg(&ms16_CAN1, &t_CanMsg);
            usleep(50*1000);
            t_CanMsg.au8_Data[3] = start_subindex+0x22+iReg*2;
            result = gs32_CAN_SendMsg(&ms16_CAN1, &t_CanMsg);
            usleep(100*1000);
        }
        t_CanMsg.t_Id.u32_Id = Slave_COB_ID;
        for(iReg=0;iReg<32;iReg++){
            t_CanMsg.au8_Data[3] = start_subindex+iReg;
            result = gs32_CAN_SendMsg(&ms16_CAN1, &t_CanMsg);
            if(result!=C_NO_ERR){
                break;
            }
            usleep(50*1000);
            t_CanMsg.au8_Data[3] = start_subindex+0x21+iReg*2;
            result = gs32_CAN_SendMsg(&ms16_CAN1, &t_CanMsg);
            usleep(50*1000);
            t_CanMsg.au8_Data[3] = start_subindex+0x22+iReg*2;
            result = gs32_CAN_SendMsg(&ms16_CAN1, &t_CanMsg);
            usleep(100*1000);
        }
        if(flag_clear_error==1){
            flag_clear_error=0;
            t_CanMsg.au8_Data[0] = 0x23;
            t_CanMsg.au8_Data[1] = 0x00;
            t_CanMsg.au8_Data[2] = 0x10;
            t_CanMsg.au8_Data[3] = 0x02;
            t_CanMsg.au8_Data[4] = 0x08;
            t_CanMsg.au8_Data[5] = 0x00;
            t_CanMsg.au8_Data[6] = 0x00;
            t_CanMsg.au8_Data[7] = 0x00;
            t_CanMsg.t_Id.u32_Id = Master_COB_ID;
            result = gs32_CAN_SendMsg(&ms16_CAN1, &t_CanMsg);
            usleep(100*1000);
            t_CanMsg.t_Id.u32_Id = Slave_COB_ID;
            result = gs32_CAN_SendMsg(&ms16_CAN1, &t_CanMsg);
            usleep(100*1000);
            t_CanMsg.au8_Data[0] = 0x40;
            t_CanMsg.au8_Data[1] = index&0xff;;
            t_CanMsg.au8_Data[2] = (index>>8)&0xff;
            t_CanMsg.au8_Data[3] = start_subindex;
            t_CanMsg.au8_Data[4] = 0x00;
            t_CanMsg.au8_Data[5] = 0x00;
            t_CanMsg.au8_Data[6] = 0x00;
            t_CanMsg.au8_Data[7] = 0x00;
        }

    }
}

//-----------------------------------------------------------------------------
/*!
   \brief   thread_receMsg(void *ptr)

   function thread for receive data via CAN

   \created       13.11.2017  HIT/W.Sun

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   13.11.2017        HITW.Sun      function created
   \endhistory
*/
//-----------------------------------------------------------------------------
void thread_receMsg(void *ptr){
    T_can_msg t_CanMsg;
    uint32 Master_COB_ID=0x582;
    uint32 Slave_COB_ID=0x583;
    uint16 index;
    uint8 subindex;
    uint32 value;
    sint32 result;

    while(1){
        result=gs32_CAN_RecvMsg (&ms16_CAN1, &t_CanMsg);
        if(result==C_NO_ERR){
            if(t_CanMsg.au8_Data[0]!=0x43) continue;
            if(t_CanMsg.t_Id.u32_Id == Master_COB_ID){
                index=t_CanMsg.au8_Data[2];
                index=(uint16)t_CanMsg.au8_Data[1]+(index<<8);
                subindex=t_CanMsg.au8_Data[3];
                if(index==0x6500){
                    if((subindex>=0x01)&&(subindex<=0x20)){
                        value=t_CanMsg.au8_Data[7];
                        value=t_CanMsg.au8_Data[6]+(value<<8);
                        value=t_CanMsg.au8_Data[5]+(value<<8);
                        value=t_CanMsg.au8_Data[4]+(value<<8);
                        MasterReceData[subindex-1][0]=value;
                    }
                    else if((subindex>=0x21)&&(subindex<=0x60)){
                        value=t_CanMsg.au8_Data[7];
                        value=t_CanMsg.au8_Data[6]+(value<<8);
                        value=t_CanMsg.au8_Data[5]+(value<<8);
                        value=t_CanMsg.au8_Data[4]+(value<<8);
                        MasterReceData[(subindex-0x21)/2][(subindex-0x21)%2+1]=value;
                    }
                }
            }
            else if(t_CanMsg.t_Id.u32_Id == Slave_COB_ID){
                index=t_CanMsg.au8_Data[2];
                index=(uint16)t_CanMsg.au8_Data[1]+(index<<8);
                subindex=t_CanMsg.au8_Data[3];
                if(index==0x6500){
                    if((subindex>=0x01)&&(subindex<=0x20)){
                        value=t_CanMsg.au8_Data[7];
                        value=t_CanMsg.au8_Data[6]+(value<<8);
                        value=t_CanMsg.au8_Data[5]+(value<<8);
                        value=t_CanMsg.au8_Data[4]+(value<<8);
                        SlaveReceData[subindex-1][0]=value;
                    }
                    else if((subindex>=0x21)&&(subindex<=0x60)){
                        value=t_CanMsg.au8_Data[7];
                        value=t_CanMsg.au8_Data[6]+(value<<8);
                        value=t_CanMsg.au8_Data[5]+(value<<8);
                        value=t_CanMsg.au8_Data[4]+(value<<8);
                        SlaveReceData[(subindex-0x21)/2][(subindex-0x21)%2+1]=value;
                    }
                }
            }
        }
    }
}
//-----------------------------------------------------------------------------
/*!
   \brief   thread_terminal(void *ptr)

   function thread for handle the command

   \created       13.11.2017  HIT/W.Sun

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   13.11.2017        HITW.Sun      function created
   \endhistory
*/
//-----------------------------------------------------------------------------
void thread_terminal(void *ptr){
    char str[32];
    char strQuitApp[]="quit";
    char strStoreFile[]="store";
    char strClearError[]="clear";

    while(1){
        scanf("%s", str);
        if(strcmp(str,strQuitApp)==0){
            // close everything
            printf("quit App: Error manage !\n");
            gs32_CAN_CloseBus (&ms16_CAN1);
            AppIsOpen=0;
        }
        else if(strcmp(str,strStoreFile)==0){
            // close everything
            printf("store the error in csv file !\n");
            produce_logfile();
        }
        else if(strcmp(str,strClearError)==0){
            printf("clear the error history !\n");
            flag_clear_error=1;
        }
    }
}


//-----------------------------------------------------------------------------
/*!
   \brief   ms32_InitCAN(void)

   \return
   C_NO_ERR       terminated with no error \n
   else           error

   \created       13.11.2017  HIT/W.Sun

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   13.11.2017        HIT/W.Sun      function created
   \endhistory
*/
//-----------------------------------------------------------------------------
sint32 ms32_InitCAN (void)
{
   sint32 s32_retval = C_NO_ERR;

   // try to get socket descriptor
   s32_retval = gs32_CAN_InitBus (&ms16_CAN1, CAN_BUS1);
   if (s32_retval == C_NO_ERR){
      printf("APP ErrorManage: CAN Initial successful!");
   }
   else{
      printf("APP ErrorManage: CAN Initial failed!");
   }
   return (s32_retval);
}




//-----------------------------------------------------------------------------
/*!
   \brief   int main(void)

   \return

   \created       12.11.2017  HIT/W.Sun

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   13.11.2017        HIT/W.Sun      function created
   \endhistory
*/
//-----------------------------------------------------------------------------
int main(void){
    int error;
    pthread_t thread_send_handle, thread_rece_handle, thread_terminal_handle;

    error=ms32_InitCAN();
    if(error!=C_NO_ERR) return -1;

    error=pthread_create(&thread_send_handle, NULL, (void *)&thread_sendMsg, NULL);
    if(error != 0){
        printf("create task send failed\n");
    }
    else{
        printf("create task send success\n");
    }
    error=pthread_create(&thread_rece_handle, NULL, (void *)&thread_receMsg, NULL);
    if(error != 0){
        printf("create task receive failed\n");
    }
    else{
        printf("create task receive success\n");
    }
    error=pthread_create(&thread_terminal_handle, NULL, (void *)&thread_terminal, NULL);
    if(error != 0){
        printf("create task terminal failed\n");
    }
    else{
        printf("create task terminal success\n");
    }
    AppIsOpen=1;
    //produce_logfile();
    while(1){
        if(AppIsOpen==0) break;
    }

}
