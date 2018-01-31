//-----------------------------------------------------------------------------
/*!
   \internal
   \file        beeper.c
   \brief       main module of Beeper example application for TC3

   \implementation
   project
   copyright   STW (c) 1999-200x
   license     use only under terms of contract / confidential

   created     23.03.2010  F.Belser
   \endimplementation

   \internal
   \history
   Date(dd.mm.yyyy)  Author             Description
   23.03.2010        F.Belser           file created
   \endhistory
*/
//-----------------------------------------------------------------------------

/* -- Includes ------------------------------------------------------------ */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "stwtypes.h"
#include "stwerror.h"   //STW errors
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>

/* -- Defines ------------------------------------------------------------- */
#define CX0 "130"
#define CX1 "128"
#define DX0 "146"
#define DX1 "155"
#define EX0 "164"
#define FX0 "174"
#define FX1 "184"
#define GX0 "195"
#define GX1 "207"
#define AX0 "220"
#define BX0 "233"
#define HX0 "246"
#define C00 "264"
#define C01 "282"
#define D00 "297"
#define D01 "316"
#define E00 "330"
#define F00 "352"
#define F01 "371"
#define G00 "396"
#define G01 "422"
#define A00 "440"
#define B00 "475"
#define H00 "495"
#define C10 "528"
#define C11 "564"
#define D10 "594"
#define D11 "632"
#define E10 "660"
#define F10 "704"
#define F11 "742"
#define G10 "792"
#define G11 "844"
#define A10 "880"
#define B10 "950"
#define H10 "990"
#define C20 "1056"

#define BEEPER         "/proc/stw_beep/beep"
#define TIME_TO_PLAY   250   // in ms
#define GAP_AFTER_PLAY 20    // in ms
#define TATA_LENGTH    10
/* -- Types --------------------------------------------------------------- */
typedef struct
{
   charn acn_Note[7];        // note to play
   uint16 u16_NotePlayTime;  // defines the time how long the note will be played
   uint16 u16_NoteGap;       // gap after playing the note
}T_Note;
/* -- Global Variables ---------------------------------------------------- */

/* -- Module Global Variables --------------------------------------------- */
static sint16 ms16_fd; // file descriptor
static T_Note mt_Tata[]  = {{ C00, 200, 20  },
                            { E00, 200, 20  },
                            { G00, 400, 100 },
                            { E00, 200, 20  },
                            { G00, 800, 400 },
                            { C10, 200, 20  },
                            { E10, 200, 20  },
                            { G10, 400, 100 },
                            { E10, 200, 20  },
                            { G10, 800, 20  }};

/* -- Module Global Function Prototypes ----------------------------------- */
static void mv_play (const charn* const pcn_Note, const uint16 ou16_NotePlayTime, const uint16 ou16_NoteGap);

/* -- Implementation ------------------------------------------------------ */

//-----------------------------------------------------------------------------
/*!
   \brief   mv_play (const charn* const pcn_Note, const uint16 ou16_NotePlayTime, const uint16 ou16_NoteGap)

   \param[in] pcn_Note               note to play
   \param[in] ou16_NotePlayTime      time how long the note should be played (ms)
   \param[in] ou16_NoteGap           time to wait after playing the note

   \return
   --

   \created       23.03.2010  STW/F.Belser

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   23.03.2010        STW/F.Belser   function created
   \endhistory
*/
//-----------------------------------------------------------------------------
static void mv_play (const charn* const pcn_Note, const uint16 ou16_NotePlayTime, const uint16 ou16_NoteGap)
{
   static uint8 hu8_Stop = 0;
   if (ms16_fd >=0)
   {
      (void)write (ms16_fd, pcn_Note, strlen (pcn_Note));
      // wait for x ms
      usleep (ou16_NotePlayTime * 1000);
      (void)write (ms16_fd, &hu8_Stop, sizeof (uint8));
      // sleep after playing the note
      usleep (ou16_NoteGap * 1000);
   }
   else
   {
      printf ("Can't write in file\n");
   }
}


//-----------------------------------------------------------------------------
/*!
   \brief   int main(void)

   \return

   \created       23.03.2010  STW/F.Belser

   \internal
   \history
   Date(dd.mm.yyyy)  Author         Description
   23.03.2010        STW/F.Belser   function created
   \endhistory
*/
//-----------------------------------------------------------------------------
int main(void)
{
   charn cn_Input = '\0';
   uint8 u8_counter = 0;

   // open the beeper file
   ms16_fd = open (BEEPER, O_WRONLY);
   // check if we could open the file
   if (ms16_fd < 0)
   {
      printf ("Can't open the file: %i \n", ms16_fd);
   }
   else
   {
      while (1)
      {
         if (cn_Input != '\n')
         {
            printf ("\nBeeper Test Application TC3\n");
            printf (".---------------------------------.\n");
            printf ("|              Menu               |\n");
            printf ("'---------------------------------'\n");
            printf ("\t(0) Exit\n");
            printf ("\t(1) Play TaTa\n");
            printf ("\t(c) Play C\n");
            printf ("\t(d) Play D\n");
            printf ("\t(e) Play E\n");
            printf ("\t(f) Play F\n");
            printf ("\t(g) Play G\n");
            printf ("\t(a) Play A\n");
            printf ("\t(h) Play H\n");
         }
         cn_Input = getchar ();
         // switch between the different input values
         //------------------------------------------------------------------
         //
         //------------------------------------------------------------------
         if (cn_Input == '0')
         {
            // check if we have an filedescriptor
            if (ms16_fd >= 0)
            {
               close(ms16_fd);
            }
            break;
         }
         else if (cn_Input == '1')
         {
            // play tata
            for (u8_counter =0; u8_counter < TATA_LENGTH; u8_counter++)
            {
               mv_play(mt_Tata[u8_counter].acn_Note, mt_Tata[u8_counter].u16_NotePlayTime, mt_Tata[u8_counter].u16_NoteGap);
            }
         }
         else if (cn_Input == 'c')
         {
            // play 'C'
            mv_play (C00, TIME_TO_PLAY, GAP_AFTER_PLAY);
         }
         else if (cn_Input == 'd')
         {
            // play 'D'
            mv_play (D00, TIME_TO_PLAY, GAP_AFTER_PLAY);
         }
         else if (cn_Input == 'e')
         {
            // play 'E'
            mv_play (E00, TIME_TO_PLAY, GAP_AFTER_PLAY);
         }
         else if (cn_Input == 'f')
         {
            // play 'F'
            mv_play (F00, TIME_TO_PLAY, GAP_AFTER_PLAY);
         }
         else if (cn_Input == 'g')
         {
            // play 'G'
            mv_play (G00, TIME_TO_PLAY, GAP_AFTER_PLAY);
         }
         else if (cn_Input == 'a')
         {
            // play 'A'
            mv_play (A00, TIME_TO_PLAY, GAP_AFTER_PLAY);
         }
         else if (cn_Input == 'h')
         {
            // play 'H'
            mv_play (D00, TIME_TO_PLAY, GAP_AFTER_PLAY);
         }
      }
   }
   return (0);
}
