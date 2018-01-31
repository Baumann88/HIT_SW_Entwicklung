//-----------------------------------------------------------------------------
/*!
   \file        x_fl_types.hpp
   \brief       CPP namespace extention for x_fl_types.h

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

#ifndef __X_FL_TYPES_HPP
#define __X_FL_TYPES_HPP



/*! \brief Flashloader configuration data. */
typedef struct
{
   stw_types::uint32 u32_CommBitrate; //!< communication bitrate in bits/s (e.g. 125000 -> 125kBit/s)
   stw_types::uint32 u32_CommID;    //!< CAN message ID (ID Client -> ECU)
   stw_types::uint8  u8_CommType;   //!< additional parameter for communication interface (for CAN: 0 = 11bit ID; 1 = 29bit ID)
   stw_types::uint8  u8_LocalID;    //!< local ID
   stw_types::uint8  u8_Enabled;    //!< 0 = interface not active; 1 = interface active
   stw_types::uint32 u32_ControlID; //!< control ID
} T_x_fl_interface_parameters;

/*! \brief Flashloader checksum block
   Only used if flashloader protocol version >= 3.00r0 and block based checksum functions are available.
*/
typedef struct
{
   stw_types::uint32 u32_StartAddress;         //!< 1st address of the data block that should be verified by a checksum
   stw_types::uint32 u32_EndAddress;           //!< last address of the data block that should be verified by a checksum
} T_x_fl_checksum_block_addresses;


/*! \brief Flashloader checksum status
   Only used if flashloader protocol version >= 3.00r0 and block based checksum functions are available.
*/
typedef struct
{
   stw_types::uint8  u8_CheckOn;            //!< indication flag weather the data block is verified by a checksum
   stw_types::uint32 u32_StartAddress;      //!< 1st address of the data block that should be verified by a checksum
   stw_types::uint32 u32_EndAddress;        //!< last address of the data block that should be verified by a checksum
   stw_types::uint32 u32_Checksum;          //!< CRC checksum for the data block specified by start- and endaddress
} T_x_fl_checksum_block_status;


/*! \brief Timestamp of finger print */
typedef struct
{
   stw_types::uint8 u8_Seconds;    //0 .. 59
   stw_types::uint8 u8_Minutes;    //0 .. 59
   stw_types::uint8 u8_Hours;      //0 .. 23
} T_x_fl_finger_print_time;

/*! \brief Date of finger print */
typedef struct
{
   stw_types::uint8 u8_Day;        //1 .. 31
   stw_types::uint8 u8_Month;      //1 .. 12
   stw_types::uint8 u8_Year;       //0 .. 99
} T_x_fl_finger_print_date;

/*! \brief read information regarding the latest flash programming procedure
   \note In contrast to the flashloader specification, time and date information is binary coded (not BCD)!
*/
typedef struct
{
   T_x_fl_finger_print_time t_Time;
   T_x_fl_finger_print_date t_Date;
   stw_types::uint8 au8_UserName[17]; //zero terminated
   stw_types::uint32 u32_Checksum;    //checksum of HEX file, calculated by flashloader client (checksum format undefined)
} T_x_fl_finger_print;




#endif  // __X_FL_TYPES_HPP
