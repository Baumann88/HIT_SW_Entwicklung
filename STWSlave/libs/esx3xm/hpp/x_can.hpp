//-----------------------------------------------------------------------------
/*!
   \file        x_can.hpp
   \brief       CPP namespace extention for x_can.h

   This header was automatically created. DO NOT EDIT!

   \implementation
   copyright   STW (c) 1999-20xx
   license     use only under terms of contract / confidential

   created     by hpp_generator.pl
   \endimplementation


   \internal
   \history
   Date(dd.mm.yyyy)  Author                Description
   \endhistory
*/
//-----------------------------------------------------------------------------

#ifndef __X_CAN_HPP
#define __X_CAN_HPP



/* -- Types --------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */
stw_types::sint16 x_can_self_test(void);
stw_types::sint16 x_can_bus_close(const stw_types::uint16 ou16_Channel);
stw_types::sint16 x_can_bus_get_status(const stw_types::uint16 ou16_Channel, T_x_can_bus_status * const opt_Status);
stw_types::sint16 x_can_bus_init(const stw_types::uint16 ou16_Channel, const stw_types::uint32 ou32_Bitrate);
stw_types::sint16 x_can_bus_init_ext(const stw_types::uint16 ou16_Channel, const stw_types::uint32 ou32_Bitrate,
                                     const stw_types::uint16 ou16_SamplePoint, stw_types::uint16* const opu16_ActSamplePoint);
stw_types::sint16 x_can_bus_get_sample_point(const stw_types::uint16 ou16_Channel, stw_types::uint16* const opu16_ActSamplePoint);
stw_types::sint16 x_can_bus_init_failure_callback(const stw_types::uint16 ou16_Channel, const stw_types::uint32 ou32_CallbackParameter,
                                                  const PR_x_can_bus_FailureCallback opr_FailureCallback);
stw_types::sint16 x_can_bus_perform_busoff_recovery(const stw_types::uint16 ou16_Channel);
stw_types::sint16 x_can_obj_clear_buf(void * const opv_Handle);
stw_types::sint16 x_can_obj_close(void * const opv_Handle);
stw_types::sint16 x_can_obj_get_buf_count(const void * const opv_Handle, stw_types::uint16 * const opu16_Count);
stw_types::sint16 x_can_obj_get_msg(const void * const opv_Handle, T_x_can_msg * const opt_Msg);
stw_types::sint16 x_can_obj_get_status(void * const opv_Handle, T_x_can_obj_status * const opt_Status);
stw_types::sint16 x_can_obj_init(const stw_types::uint16 ou16_Channel, const T_x_can_obj_config * const opt_Config,
                                 void ** const oppv_Handle);
stw_types::sint16 x_can_obj_send_msg(void * const opv_Handle, const T_x_can_msg * const opt_Msg);
stw_types::sint16 x_can_obj_send_rtr_req(const void * const opv_Handle, const T_x_can_id * const opt_Id);
stw_types::sint16 x_can_obj_set_pause(void * const opv_Handle, const stw_types::uint16 ou16_Pause);
stw_types::sint16 x_can_obj_set_filter(void * const opv_Handle, const T_x_can_id * const opt_CompareId,
                                       const T_x_can_id * const opt_Mask);
stw_types::sint16 x_can_bus_change_busoff_time(const stw_types::uint16 ou16_Channel, const stw_types::uint16 ou16_Time1, const stw_types::uint16 ou16_Time2,
                                               const stw_types::uint16 ou16_Time3, const stw_types::uint16 ou16_Time4, const stw_types::uint16 ou16_Time5,
                                               const stw_types::uint16 ou16_WaitTime);
stw_types::sint16 x_can_bus_lock(const stw_types::uint16 ou16_Channel, const stw_types::uint8 ou8_OnOff);
stw_types::sint16 x_can_bus_set_masks(const stw_types::uint16 ou16_Channel, const stw_types::uint32 ou32_11BitMask, const stw_types::uint32 ou32_29BitMask);
stw_types::sint16 x_can_obj_init_gateway(const stw_types::uint16 ou16_ChannelSrc, const stw_types::uint16 ou16_ChannelDst,
                                         const T_x_can_gateway_config * const opt_Config,  void ** const oppv_Handle);
stw_types::sint16 x_can_obj_lock(void * const opv_Handle, const stw_types::uint8 ou8_OnOff);
stw_types::sint16 x_can_obj_set_auto_response(const void * const opv_Handle, const stw_types::uint8 ou8_OnOff);

/* -- Implementation ------------------------------------------------------ */


#endif  // __X_CAN_HPP
