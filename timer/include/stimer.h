/*
 * Copyright (C)  2011 Zoltan Zidarics (Zamek)
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * DEVELOPERS : ANDRAS GARDANFALVI, DAVID DOBO
 */
/** \file stimer.h
    \brief Header file for the timer unit
*/

#ifndef  LTIMER_H
#define  LTIMER_H

#include <stdint.h>
	typedef int8_t si08;
	typedef int16_t si16;
	typedef int32_t si32;
	typedef uint8_t ui08;
	typedef uint16_t ui16;
	typedef uint32_t ui32;


/* Status definitions */
#define TIMER_OFF           0x00
#define TIMER_ON			0x01

#define TIMER_RUNNING       0x00
#define TIMER_PAUSED        0x02

#define TIMER_COUNTING      0x00
#define TIMER_OVERFLOW      0x04

#define TIMER_FREE          0x00
#define TIMER_USED          0x08

/* Configuration definitions */
#define TIMER_ONESHOT       0x00
#define TIMER_CYCLIC        0x10

#define TIMER_MILISEC       0x00
#define TIMER_SECONDS       0x20
#define TIMER_MINUTES       0x40
#define TIMER_HOURS         0x60

/* Errors definitions */
#define TIMER_ERROR         0xFF


//------------------------------------//

#define TIMER_AMOUNT        10        // You can set here the amount of maximum timers

//------------------------------------//


extern ui08 stimer_create(ui08 config);
extern void stimer_delete(ui08 timer_id);
extern void stimer_set_time(ui08 timer_id, ui16 time, ui08 time_unit);
extern ui16 stimer_get_time(ui08 timer_id, ui08 time_unit);
extern void stimer_start(ui08 timer_id);
extern void stimer_pause(ui08 timer_id);
extern void stimer_stop(ui08 timer_id);
extern void stimer_reset(ui08 timer_id);
extern ui08 stimer_status(ui08 timer_id);
extern ui08 stimer_timeout(ui08 timer_id);
extern void stimer_clock(void);



#endif
