//-----------------------------------------------------------------------------
/*!
   \file          utils.h
   \brief         Provides utility functions

   Provides utility functions

   \implementation
   copyright   STW (c) 1999-2008
   license     use only under terms of contract / confidential

   created     30.10.08 Sven Dittmer
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   30.10.08          Sven Dittmer   file created
   \endhistory
*/
//-----------------------------------------------------------------------------
#ifndef _UTILS_H
#define _UTILS_H

/* -- Includes ------------------------------------------------------------ */
#include <stdio.h>
#include <stddef.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include "stwtypes.h"
#include "stwerrors.h"

/* -- Defines ------------------------------------------------------------- */
#define TARGET_HOSTNAME "HOSTNAME"
/* -- Types --------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------- */

/* -- Function Prototypes ------------------------------------------------- */
extern sint32 utils_create_directory(const charn * const opcn_Path, const mode_t oun_Mode);
extern sint32 utils_remove_directory(const charn * const opcn_DirPath);
extern sint32 utils_file_exists(const charn * const opcn_FileName);
extern sint32 utils_reg_file_exists(const charn * const opcn_FileName);
extern sint32 utils_directory_exists(const charn * const opcn_DirName);
extern sint32 utils_link_exists(const charn * const opcn_LinkName);
extern sint32 utils_socket_exists(const charn * const opcn_SocketName);
extern sint32 utils_fifo_exists(const charn * const opcn_FifoName);
extern sint32 utils_strlcpy(charn * opcn_Destiny, const charn * opcn_Source, sint32 os32_Size);
extern sint32 utils_search_first_value(FILE * opt_File,
                                       const charn * const opcn_SearchString,
                                       charn * const opcn_ValueTarget,
                                       const uint32 ou32_ValueTargetBufferSize);
extern sint32 utils_search_next_value(FILE * opt_File,
                                      const charn * const opcn_SearchString,
                                      charn * const opcn_ValueTarget,
                                      const uint32 ou32_ValueTargetBufferSize);
extern sint32 utils_open_log_file(charn * opcn_FileName);
extern sint32 utils_log_print(const charn * const opcn_LogString);
extern sint32 utils_log_close(void);
extern sint32 utils_remove_file(const charn * const opcn_FileName);
extern sint32 utils_init_semaphore(key_t const osn_SHMKey, const uint32 ou32_SemCounter, sint32 * const ops32_SemID);
extern sint32 utils_semaphore_lock(const sint32 os32_SemID, const uint8 ou8_Mode);
extern sint32 utils_semaphore_unlock(const sint32 os32_SemID, const uint8 ou8_Mode);
extern void utils_get_hostname(charn * const opcn_Hostname);
extern sint32 utils_write_string_value(FILE* opt_File, const charn * const opcn_String);
extern sint32 utils_get_time_sig(charn * const opcn_Time);
extern charn* utils_get_time(charn * const opcn_Time);
extern charn * utils_get_GM_time(charn * const opcn_Time);
extern uint32 utils_get_time_ms (void);
/* -- Implementation ------------------------------------------------------ */

#endif
