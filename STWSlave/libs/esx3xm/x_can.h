//-----------------------------------------------------------------------------
/*!
   \file        x_can.h
   \brief       Generic CAN functions.

   Header defines generic CAN functions.

   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   created     28.06.2006        STW/Herb
   \endimplementation

*/
//-----------------------------------------------------------------------------

#ifndef _X_CAN_H
#define _X_CAN_H

/* -- Includes ------------------------------------------------------------ */
#include "x_stdtypes.h"
#include "x_can_types.h"


#ifdef __cplusplus
extern "C" {
#endif

/* -- Defines ------------------------------------------------------------- */

#define X_CAN_CH_MAX                (4)

#define X_CAN_BUS_01                (0)      // main board CAN bus 1
#define X_CAN_BUS_02                (1)      // main board CAN bus 2
#define X_CAN_BUS_03                (2)      // main board CAN bus 3
#define X_CAN_BUS_04                (3)      // main board CAN bus 4

/*********************************************************************
 *  STW SEPI functions, data types and error codes are each          *
 *  placed into a separate namespace for C++.                        *
 *  The following #ifdef instruction will load either the standard   *
 *  C - API style or the C++ style with namespaces.                  *
 *********************************************************************/
#ifdef __cplusplus
namespace stw_sepi
{
   #include "./hpp/x_can.hpp"
}
#else


/* -- Types --------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */
sint16 x_can_self_test(void);
sint16 x_can_bus_close(const uint16 ou16_Channel);
sint16 x_can_bus_get_status(const uint16 ou16_Channel, T_x_can_bus_status * const opt_Status);
sint16 x_can_bus_init(const uint16 ou16_Channel, const uint32 ou32_Bitrate);
sint16 x_can_bus_init_ext(const uint16 ou16_Channel, const uint32 ou32_Bitrate,
                          const uint16 ou16_SamplePoint, uint16* const opu16_ActSamplePoint);
sint16 x_can_bus_get_sample_point(const uint16 ou16_Channel, uint16* const opu16_ActSamplePoint);
sint16 x_can_bus_init_failure_callback(const uint16 ou16_Channel, const uint32 ou32_CallbackParameter,
                                       const PR_x_can_bus_FailureCallback opr_FailureCallback);
sint16 x_can_bus_perform_busoff_recovery(const uint16 ou16_Channel);
sint16 x_can_obj_clear_buf(void * const opv_Handle);
sint16 x_can_obj_close(void * const opv_Handle);
sint16 x_can_obj_get_buf_count(const void * const opv_Handle, uint16 * const opu16_Count);
sint16 x_can_obj_get_msg(const void * const opv_Handle, T_x_can_msg * const opt_Msg);
sint16 x_can_obj_get_status(void * const opv_Handle, T_x_can_obj_status * const opt_Status);
sint16 x_can_obj_init(const uint16 ou16_Channel, const T_x_can_obj_config * const opt_Config,
                      void ** const oppv_Handle);
sint16 x_can_obj_send_msg(void * const opv_Handle, const T_x_can_msg * const opt_Msg);
sint16 x_can_obj_send_rtr_req(const void * const opv_Handle, const T_x_can_id * const opt_Id);
sint16 x_can_obj_set_pause(void * const opv_Handle, const uint16 ou16_Pause);
sint16 x_can_obj_set_filter(void * const opv_Handle, const T_x_can_id * const opt_CompareId,
                            const T_x_can_id * const opt_Mask);
sint16 x_can_bus_change_busoff_time(const uint16 ou16_Channel, const uint16 ou16_Time1, const uint16 ou16_Time2,
                                    const uint16 ou16_Time3, const uint16 ou16_Time4, const uint16 ou16_Time5,
                                    const uint16 ou16_WaitTime);
sint16 x_can_bus_lock(const uint16 ou16_Channel, const uint8 ou8_OnOff);
sint16 x_can_bus_set_masks(const uint16 ou16_Channel, const uint32 ou32_11BitMask, const uint32 ou32_29BitMask);
sint16 x_can_obj_init_gateway(const uint16 ou16_ChannelSrc, const uint16 ou16_ChannelDst,
                             const T_x_can_gateway_config * const opt_Config,  void ** const oppv_Handle);
sint16 x_can_obj_lock(void * const opv_Handle, const uint8 ou8_OnOff);
sint16 x_can_obj_set_auto_response(const void * const opv_Handle, const uint8 ou8_OnOff);

/* -- Implementation ------------------------------------------------------ */


#endif  //__cplusplus

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif   // _X_CAN_H
