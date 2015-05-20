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
#include "../include/timers_list.h"
/* Status definitions */
#define TIMER_OFF           0x00
#define TIMER_ON			0x01

#define TIMER_RUNNING       0x00
#define TIMER_PAUSED        0x02

#define TIMER_COUNTING      0x00
#define TIMER_OVERFLOW      0x04

/* Configuration definitions */
#define TIMER_ONESHOT       0x00
#define TIMER_CYCLIC        0x10

#define TIMER_MILISEC       0x00
#define TIMER_SECONDS       0x20
#define TIMER_MINUTES       0x40
#define TIMER_HOURS         0x60

/* Errors definitions */
#define TIMER_ERROR         0xFF



extern uint8_t		stimer_initialize();
extern void		stimer_finalize();
extern timer_id_t	stimer_create(uint8_t config);
extern void		stimer_delete(timer_id_t timer_id);
extern void		stimer_set_time(timer_id_t timer_id, uint16_t time, uint8_t time_unit);
extern uint8_t          stimer_set_callback(timer_id_t, timer_callback_t, void* callback_argument);
extern uint16_t		stimer_get_time(timer_id_t timer_id, uint8_t time_unit);
extern void		stimer_start(timer_id_t timer_id);
extern void		stimer_pause(timer_id_t timer_id);
extern void		stimer_stop(timer_id_t timer_id);
extern void		stimer_reset(timer_id_t timer_id);
extern uint8_t		stimer_status(timer_id_t timer_id);
extern uint8_t		stimer_timeout(timer_id_t timer_id);
extern void		stimer_clock(void);



#endif
