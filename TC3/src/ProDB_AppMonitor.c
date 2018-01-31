//-----------------------------------------------------------------------------
/*!
   \internal
   \file        ProDB_AppMonitor.c
   \brief       Application for Monitor the parameter STW CPU

   \implementation
   project
   copyright   HIT (c) 1999-20xx
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
#include <sys/time.h>
#include <can.h>

/* -- Defines ------------------------------------------------------------- */
#define CAN_BUS1                         0            // Define for CAN1
#define CAN_BUS2                         1            // Define for CAN2

#define SDO_Basis_ID                     0x600

#define ControlWordMonitorEnable         0x00000001
#define ControlWordQuitReq               0x00000002
#define ControlWordIsSDO                 0x00000004
#define ControlWordCANBusChannel         0x00000008
#define ControlWordDisplayIsHex          0x00000010

#define DataTypeBool                     0x01
#define DataTypeU8                       0x02
#define DataTypeS8                       0x03
#define DataTypeS16                      0x04
#define DataTypeU16                      0x05
#define DataTypeU32                      0x06
#define DataTypeS32                      0x07
#define DataTypeF32                      0x08


/* -- Module Global Variables --------------------------------------------- */
static sint16 ms16_CAN1;
static sint16 ms16_CAN2;

static uint16 msg_sdo_index;
static uint8 msg_sdo_subindex;

static uint32 send_id;
static uint32 rece_id;

static uint8 rece_data[8];
static uint8 send_data[8];

static uint32 control_word=0;

static uint8 data_type;
static uint8 data_pos;
static char data_name[32];

static uint32 display_intervall;

/* -- Module Global Function Prototypes ----------------------------------- */
sint32 ms32_InitCAN (void);

/* -- Implementation ------------------------------------------------------ */

//-----------------------------------------------------------------------------
/*!
   \brief   ms32_InitCAN(void)

   \return
   C_NO_ERR       terminated with no error \n
   else           error

   \created       28.11.2017  HIT/W.Sun

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   28.11.2017        HIT/W.Sun      function created
   \endhistory
*/
//-----------------------------------------------------------------------------
sint32 ms32_InitCAN (void){
   sint32 s32_retval = C_NO_ERR;
   // try to get socket descriptor
   s32_retval = gs32_CAN_InitBus (&ms16_CAN1, CAN_BUS1);
   if (s32_retval == C_NO_ERR) printf("APP Monitor: CAN1 Initial successful!\n");
   else printf("APP Monitor: CAN1 Initial failed!\n");
   s32_retval = gs32_CAN_InitBus (&ms16_CAN2, CAN_BUS2);
   if (s32_retval == C_NO_ERR) printf("APP Monitor: CAN2 Initial successful!\n");
   else printf("APP Monitor: CAN2 Initial failed!\n");
   return (s32_retval);
}

//-----------------------------------------------------------------------------
/*!
   \brief   data_Display(void)

   \return
   C_NO_ERR       terminated with no error \n
   else           error

   \created       28.11.2017  HIT/W.Sun

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   28.11.2017        HIT/W.Sun      function created
   \endhistory
*/
//-----------------------------------------------------------------------------
void data_Display(void){
    static uint32 timestamp;

    uint32 u32_tmp;
    sint32 s32_tmp;
    uint16 u16_tmp;
    sint16 s16_tmp;
    uint8 u8_tmp;
    sint8 s8_tmp;
    float32 f32_tmp;

    if((utils_get_time_ms()-timestamp)>display_intervall) timestamp=utils_get_time_ms();
    else return;

    switch(data_type){
    case DataTypeBool:
        u8_tmp=(rece_data[data_pos/8]>>(data_pos%8))&0x01;
        if(u8_tmp>0) printf("the recedata %s is: true\n",data_name);
        else printf("the recedata %s is: false\n",data_name);
    break;
    case DataTypeU8:
        u8_tmp=rece_data[data_pos];
        if(control_word&ControlWordDisplayIsHex) printf("the recedata %s is: %x\n",data_name,u8_tmp);
        else printf("the recedata %s is: %u\n",data_name,u8_tmp);
    break;
    case DataTypeS8:
        u8_tmp=rece_data[data_pos];
        if(u8_tmp>127) s8_tmp=(sint8)(u8_tmp-255);
        else s8_tmp=(sint8)u8_tmp;
        if(control_word&ControlWordDisplayIsHex) printf("the recedata %s is: %x\n",data_name,s8_tmp);
        else printf("the recedata %s is: %d\n",data_name,s8_tmp);
    break;
    case DataTypeU16:
        if(control_word&ControlWordDisplayIsHex){
            printf("the recedata %s is: %x ; %x\n",data_name,rece_data[data_pos*2],rece_data[data_pos*2+1]);
        }
        else{
            u16_tmp=rece_data[data_pos*2]+((rece_data[data_pos*2+1]&0x00ff)<<8);
            printf("the recedata %s is: %u\n",data_name,u16_tmp);
        }
    break;
    case DataTypeS16:
        if(control_word&ControlWordDisplayIsHex){
            printf("the recedata %s is: %x ; %x\n",data_name,rece_data[data_pos*2],rece_data[data_pos*2+1]);
        }
        else{
            u16_tmp=rece_data[data_pos*2]+((rece_data[data_pos*2+1]&0x00ff)<<8);
            if(u16_tmp>32767) s16_tmp=(sint16)(u16_tmp-65535);
            else s16_tmp=(sint16)u16_tmp;
            printf("the recedata %s is: %d\n",data_name,s16_tmp);
        }
    break;
    case DataTypeU32:
    if(control_word&ControlWordDisplayIsHex){
        printf("the recedata %s is: %x ; %x ; %x ; %x\n",data_name,rece_data[data_pos*4],rece_data[data_pos*4+1],rece_data[data_pos*4+2],rece_data[data_pos*4+3]);
    }
    else{
        u32_tmp=rece_data[data_pos*4+3];
        u32_tmp=rece_data[data_pos*4+2]+(u32_tmp<<8);
        u32_tmp=rece_data[data_pos*4+1]+(u32_tmp<<16);
        u32_tmp=rece_data[data_pos*4]+(u32_tmp<<24);
        printf("the recedata %s is: %u\n",data_name,u32_tmp);
    }
    break;
    case DataTypeS32:
        u32_tmp=rece_data[data_pos*4+3];
        u32_tmp=rece_data[data_pos*4+2]+(u32_tmp<<8);
        u32_tmp=rece_data[data_pos*4+1]+(u32_tmp<<16);
        u32_tmp=rece_data[data_pos*4]+(u32_tmp<<24);
        if(u32_tmp>2147483647) s32_tmp=(sint32)(u32_tmp-4294967296);
        else s32_tmp=u32_tmp;
        printf("the recedata %s is: %d\n",data_name,s32_tmp);
    break;
    case DataTypeF32:
        u32_tmp=rece_data[data_pos*4+3];
        u32_tmp=rece_data[data_pos*4+2]+(u32_tmp<<8);
        u32_tmp=rece_data[data_pos*4+1]+(u32_tmp<<16);
        u32_tmp=rece_data[data_pos*4]+(u32_tmp<<24);
        if(u32_tmp>2147483647) s32_tmp=(sint32)(u32_tmp-4294967296);
        else s32_tmp=u32_tmp;
        f32_tmp=(float32)s32_tmp*0.001;
        printf("the recedata %s is: %f\n",data_name,f32_tmp);
    break;
    }
}

//-----------------------------------------------------------------------------
/*!
   \brief   thread_receMsg(void *ptr)

   function thread for receive data via CAN

   \created       28.11.2017  HIT/W.Sun

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   28.11.2017        HITW.Sun      function created
   \endhistory
*/
//-----------------------------------------------------------------------------
void thread_receMsg(void *ptr){
    T_can_msg t_CanMsg;
    uint16 index;
    uint16 iData;
    uint8 subindex;
    uint32 value;
    sint32 result;
    sint16 can_bus_handle;

    while(1){
        if((control_word&ControlWordCANBusChannel)==0) can_bus_handle=ms16_CAN1;
        else can_bus_handle=ms16_CAN2;
        t_CanMsg.t_Id.u32_Id=0;
        result=gs32_CAN_RecvMsg (&can_bus_handle, &t_CanMsg);
        if(result==C_NO_ERR){
            if(t_CanMsg.t_Id.u32_Id == rece_id){
                if((control_word&ControlWordMonitorEnable)==0) continue;
                if(control_word&ControlWordIsSDO){
                    index=t_CanMsg.au8_Data[2];
                    index=(uint16)t_CanMsg.au8_Data[1]+(index<<8);
                    subindex=t_CanMsg.au8_Data[3];
                    if((index==msg_sdo_index)&&(subindex==msg_sdo_subindex)){
                        for(iData=0;iData<4;iData++){
                            rece_data[iData]=t_CanMsg.au8_Data[iData+4];
                        }
                        data_Display();
                    }
                }
                else{

                    for(iData=0;iData<8;iData++){
                        rece_data[iData]=t_CanMsg.au8_Data[iData];
                    }
                    data_Display();
                }
            }
        }
    }
}

//-----------------------------------------------------------------------------
/*!
   \brief   thread_sendMsg(void *ptr)

   function thread for send data via CAN

   \created       28.11.2017  HIT/W.Sun

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   28.11.2017        HIT/W.Sun      function created
   \endhistory
*/
//-----------------------------------------------------------------------------
void thread_sendMsg(void *ptr){
    T_can_msg t_CanMsg;
    uint16 iData;
    sint16 can_bus_handle;

    // Send Message
    while(1){
        if((control_word&ControlWordMonitorEnable)==0) continue;
        if((control_word&ControlWordIsSDO)==0) continue;

        t_CanMsg.t_Id.u32_Id = send_id;
        t_CanMsg.t_Id.u8_Xtd = 0;
        t_CanMsg.u8_Dlc = 8;
        t_CanMsg.au8_Data[0]=0x40;
        t_CanMsg.au8_Data[1] = msg_sdo_index&0xff;;
        t_CanMsg.au8_Data[2] = (msg_sdo_index>>8)&0xff;
        t_CanMsg.au8_Data[3] = msg_sdo_subindex;

        if((control_word&ControlWordCANBusChannel)==0) can_bus_handle=ms16_CAN1;
        else can_bus_handle=ms16_CAN2;

        gs32_CAN_SendMsg(&can_bus_handle, &t_CanMsg);

        usleep(20000);
    }
}

//-----------------------------------------------------------------------------
/*!
   \brief   int main(void)

   \return

   \created       28.11.2017  HIT/W.Sun

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   28.11.2017        HIT/W.Sun      function created
   \endhistory
*/
//-----------------------------------------------------------------------------
int main(void){
    int error;
    pthread_t thread_send_handle, thread_rece_handle;
    char str[32];
    char strCMDQuit[]="q";
    char strCMDMani[]="c";
    uint8 state=0;
    int cmd;
    uint32 tmp;

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

    while(1){
        if(state==0){
            printf("//==============================\n");
            printf("Haupt Menu:\n");
            printf("(q): quit the Applikation\n");
            printf("(c): geben the Befehl ein\n");
            printf("//==============================\n");
            scanf("%s", str);
            if(strcmp(str,strCMDQuit)==0){
                printf("quit the Application!\n");
                return 0;
            }
            else if(strcmp(str,strCMDMani)==0){
                printf("Sub Menu | Monitor:\n");
                state=1;
            }
            rece_id=0x0;
            control_word&=~ControlWordMonitorEnable;
        }
        else if(state==1){
            printf("welche CAN Bus Kannel? (1):CAN bus 1,(2):CAN Bus 2\n");
            scanf("%d",&cmd);
            if(cmd==1){
                control_word&=~ControlWordCANBusChannel;
            }
            else if(cmd==2){
                control_word|=ControlWordCANBusChannel;
            }
            else{
                printf("ungueltige eingabe: zürück zur haupt Menu !\n");
                state=0;
                continue;
            }
            printf("Ist es SDO or normal Telegram? (1):SDO,(2):Normal\n");
            scanf("%d",&cmd);
            if(cmd==1){
                printf("enter the id: \n");
                scanf("%x",&send_id);
                rece_id=send_id-0x600+0x580;
                control_word|=ControlWordIsSDO;
                printf("enter the index: \n");
                scanf("%x",&tmp);
                msg_sdo_index=(uint16)tmp;
                printf("enter the subindex: \n");
                scanf("%x",&tmp);
                msg_sdo_subindex=(uint8)tmp;
                printf("enter the position: \n");
                scanf("%u",&tmp);
                data_pos=(uint8)tmp;
                printf("enter the data type: \n");
                printf("(1): boolean \n");
                printf("(2): uint8 \n");
                printf("(3): sint8 \n");
                printf("(4): sint16 \n");
                printf("(5): uint16 \n");
                printf("(6): uint32 \n");
                printf("(7): sint32 \n");
                printf("(8): float32 \n");
                scanf("%u",&tmp);
                data_type=(uint8)tmp;
            }
            else if(cmd==2){
                printf("enter the id: \n");
                scanf("%x",&rece_id);
                control_word&=~ControlWordIsSDO;
                printf("enter the position: \n");
                scanf("%u",&tmp);
                data_pos=(uint8)tmp;
                printf("enter the data type: \n");
                printf("(1): boolean \n");
                printf("(2): uint8 \n");
                printf("(3): sint8 \n");
                printf("(4): sint16 \n");
                printf("(5): uint16 \n");
                printf("(6): uint32 \n");
                printf("(7): sint32 \n");
                printf("(8): float32 \n");
                scanf("%u",&tmp);
                data_type=(uint8)tmp;
            }
            else{
               printf("ungueltige eingabe: zürück zur haupt Menu !\n");
               state=0;
               continue;
            }
            printf("set the format in thedisplay:\n");
            printf("(1): decimal\n");
            printf("(2): hex\n");
            scanf("%d",&cmd);
            if(cmd==1){
                control_word&=~ControlWordDisplayIsHex;
            }
            else if(cmd==2){
                control_word|=ControlWordDisplayIsHex;
            }
            else{
               printf("ungueltige eingabe: zürück zur haupt Menu !\n");
               state=0;
               continue;
            }
            printf("set a name of variable:\n");
            scanf("%s",data_name);
            printf("set the interval (ms) for display:\n");
            scanf("%u",&display_intervall);
            control_word|=ControlWordMonitorEnable;
            state=2;
        }
        else if(state==2){
            scanf("%s", str);
            if(strcmp(str,strCMDQuit)==0){
                control_word&=~ControlWordMonitorEnable;
                state=0;
            }
        }
    }
}

