//-----------------------------------------------------------------------------
/*!
   \file          GPS_handler.h
   \brief         Provides utility functions to use the gps daemon

   Provides utility functions to use the gps daemon

   \implementation
   copyright   STW (c) 1999-2010
   license     use only under terms of contract / confidential

   created     06.08.10 Florian Belser
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author           Description
   25.03.11          Dragnef          put const to first parameter of gs32_ygpsd_GetGPSData
   06.08.10          Florian Belser   file created
   \endhistory
*/
//-----------------------------------------------------------------------------
#ifndef _GPS_HANDLER_H
#define _GPS_HANDLER_H

#ifdef __cplusplus
extern "C" {
#endif

/* -- Includes ------------------------------------------------------------ */
#include "dbus-utils.h"

/* -- Defines ------------------------------------------------------------- */

/* -- Types --------------------------------------------------------------- */
typedef struct
{
   charn acn_status[32];      // NMEA receiving valid nmea string from gps receiver.
                              // NONE not receiving nmea strings from gps receiver.
   charn acn_latitude[32];    // Degrees notation: DD.dddddd
   charn acn_longitude[32];   // Degrees notation: DD.dddddd
   charn acn_altitude[32];    // meters
   charn acn_time[32];        // hhmmss
   charn acn_satellites[32];  // 1..12
   charn acn_quality[32];     // 0= no reception - 1 good
   charn acn_warn[32];        // V gps position is not valid
                              // A gps position is valid
   charn acn_speed[32];       // km/h XXX.YYYYYY
   charn acn_course[32];      // degrees (0..360) XXX.YYYYYY
   charn acn_date[32];        // Ddmmyy
   charn acn_UTC[64];         // MMDDhhmmYYYY
} T_DBUS_GPS_Data;

/* -- Global Variables ---------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */
extern sint32 ygpsd_get_gps_data(const T_DBUS_Util * const opt_DBusInstance, T_DBUS_GPS_Data * const opt_DBusGpsData);

/* -- Implementation ------------------------------------------------------ */

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* end of _GPS_HANDLER_H */
