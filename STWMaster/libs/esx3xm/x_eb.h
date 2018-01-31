//-----------------------------------------------------------------------------
/*!
   \internal
   \file       x_eb.h
   \brief      defines for ESX-3XM expansion boards


   \implementation
   project     project name
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   \created     09.09.2009  Herb
   \endimplementation

*/
//-----------------------------------------------------------------------------

#ifndef _X_EB_H
#define _X_EB_H

/* -- Includes ------------------------------------------------------------ */



#ifdef __cplusplus
extern "C" {
#endif


/* -- Defines ------------------------------------------------------------- */

// defines for valid expansion board slot numbers
#define X_EXPBOARD_SLOT_A           (0)            // expansion board A = slot0
#define X_EXPBOARD_SLOT_B           (1)            // expansion board B = slot1
#define X_EXPBOARD_SLOT_C           (2)            // expansion board C = slot2
#define X_EXPBOARD_NUM_SLOTS        (3)            // number of expansion board slots

// alternative slot labels
#define X_EXPBOARD_SLOT0            (0)            // expansion board slot0
#define X_EXPBOARD_SLOT1            (1)            // expansion board slot1
#define X_EXPBOARD_SLOT2            (2)            // expansion board slot2

// defines for expansion board channel numbers
#define X_EXPBOARD_CHANNEL_01       (0)            // expansion board IO channel 1
#define X_EXPBOARD_CHANNEL_02       (1)            // expansion board IO channel 2
#define X_EXPBOARD_CHANNEL_03       (2)            // expansion board IO channel 3
#define X_EXPBOARD_CHANNEL_04       (3)            // expansion board IO channel 4
#define X_EXPBOARD_CHANNEL_05       (4)            // expansion board IO channel 5
#define X_EXPBOARD_CHANNEL_06       (5)            // expansion board IO channel 6
#define X_EXPBOARD_CHANNEL_07       (6)            // expansion board IO channel 7
#define X_EXPBOARD_CHANNEL_08       (7)            // expansion board IO channel 8
#define X_EXPBOARD_CHANNEL_09       (8)            // expansion board IO channel 9
#define X_EXPBOARD_CHANNEL_10       (9)            // expansion board IO channel 10
#define X_EXPBOARD_CHANNEL_11       (10)           // expansion board IO channel 11
#define X_EXPBOARD_CHANNEL_12       (11)           // expansion board IO channel 12
#define X_EXPBOARD_CHANNEL_13       (12)           // expansion board IO channel 13 (PWR_OPT pin)
#define X_EXPBOARD_CHANNEL_14       (13)           // expansion board IO channel 14 (POWER pin)

// alternative channel labels
#define X_EXPBOARD_PWR_OPT          (12)           // expansion board PWR_OPT pin
#define X_EXPBOARD_POWER            (13)           // expansion board POWER pin


#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif  /* _X_EB_H */
