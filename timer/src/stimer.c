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
/** \file stimer.c
    \brief main file of the timer unit
*/


#include "../include/stimer.h"


#define STATUS_MASK     (TIMER_ON | TIMER_PAUSED | TIMER_OVERFLOW | TIMER_USED)
#define MODE_MASK       (TIMER_ONESHOT | TIMER_CYCLIC)
#define TIME_UNIT_MASK  (TIMER_MILISEC | TIMER_SECONDS | TIMER_MINUTES | TIMER_HOURS)
#define CONFIG_MASK     (MODE_MASK | TIME_UNIT_MASK)


typedef struct STIMER_T
{
    ui08 config_status;
    ui16 time;
    ui16 milisec;
    ui08 minutes;
} stimer_t;


static stimer_t Timers[TIMER_AMOUNT];
static ui08 LastTimerCreated = 0xFF;

/*!
    timer creation, you can create one imer using this. argument MUST BE TIMER_ONESHOT or TIMER_CYCLIC
    @param TIMER_ONESHOT for one time timer and TIMER_CYCLIC for continous timer
    @return the timer ID
*/

ui08 stimer_create(ui08 config)
{
	stimer_t *timer;
    ui08 i;

    i = LastTimerCreated + 1;
    timer = &Timers[i];

    if (timer->config_status & TIMER_USED)
    {
        for (i = 0; i < TIMER_AMOUNT; i++)
        {
            timer = &Timers[i];
            if ((timer->config_status & TIMER_USED) == 0) break;
        }
    }

    if (i == TIMER_AMOUNT) return TIMER_ERROR;

    timer->config_status = (config & CONFIG_MASK) | TIMER_USED;
    LastTimerCreated = i;

    return i;
}

/*!
    delete the timer by ID
    @param ID of the timer you want to delete
*/

void stimer_delete(ui08 timer_id)
{
    stimer_t *timer;

    timer = &Timers[timer_id];
    timer->config_status = 0;
}

/*!
    set the time value and the time unit for the timer by ID
    @param ID of the timer you want to set
    @param value of time
    @param unit of time
*/

void stimer_set_time(ui08 timer_id, ui16 time, ui08 time_unit)
{
    stimer_t *timer;

    if (time == 0) return;

    timer = &Timers[timer_id];
    timer->time = time;

    time_unit &= TIME_UNIT_MASK;
    timer->config_status &= ~TIME_UNIT_MASK;
    timer->config_status |= time_unit;

    timer->minutes = 0;
    timer->milisec = time;

    if (time_unit == TIMER_HOURS)
    {
        timer->minutes = ((time * 60) - 1);
        timer->milisec = 60000;
    }
    else if (time_unit == TIMER_MINUTES)
    {
        timer->minutes = (time - 1);
        timer->milisec = 60000;
    }
    else if (time_unit == TIMER_SECONDS)
    {
        timer->minutes = (ui08) (time / 60);
        timer->milisec = (1000 * (time % 60));
    }
}

/*!
    show the elapsed time
    @param ID of the timer
    @param unit of time

*/

ui16 stimer_get_time(ui08 timer_id, ui08 time_unit)
{
    stimer_t *timer;
    ui16 time;

    timer = &Timers[timer_id];
    time = timer->time;
    time_unit &= TIME_UNIT_MASK;

    if (time_unit == TIMER_HOURS)
    {
        time -= (timer->minutes / 60);
        if (timer->milisec >= 30000 && time > 0)
        {
            time--;
        }
    }
    else if (time_unit == TIMER_MINUTES)
    {
        time -= (timer->minutes);
        if (timer->milisec >= 30000 && time > 0)
        {
            time--;
        }
    }
    else if (time_unit == TIMER_SECONDS)
    {
        time -= (timer->minutes * 60);
        time -= (timer->milisec / 1000);
    }
    else if (time_unit == TIMER_MILISEC)
    {
        time -= timer->milisec;
    }

    return time;
}

/*!
    starts the timer
    @param ID of the timer

*/

void stimer_start(ui08 timer_id)
{
    stimer_t *timer;

    timer = &Timers[timer_id];
    timer->config_status &= ~STATUS_MASK;
    timer->config_status |= TIMER_ON;
}

/*!
    pause the timer by ID
    @param ID of the timer

*/

void stimer_pause(ui08 timer_id)
{
    stimer_t *timer;

    timer = &Timers[timer_id];
    timer->config_status &= ~STATUS_MASK;
    timer->config_status |= TIMER_PAUSED;
}

/*!
    stop the timer and resets its value and status
    @param ID of the timer

*/

void stimer_stop(ui08 timer_id)
{
    stimer_t *timer;
    ui08 time_unit;

    timer = &Timers[timer_id];
    timer->config_status &= ~STATUS_MASK;

    time_unit = (timer->config_status & TIME_UNIT_MASK);
    stimer_set_time(timer_id, timer->time, time_unit);
}

/*!
    reset the timer, no change in status
    @param ID of the timer

*/

void stimer_reset(ui08 timer_id)
{
    stimer_t *timer;
    ui08 time_unit;

    timer = &Timers[timer_id];
    time_unit = (timer->config_status & TIME_UNIT_MASK);
    stimer_set_time(timer_id, timer->time, time_unit);
}

/*!
    status of the timer
    @param Id of the timer
    @return return the value of the status, see the constant macros
*/

ui08 stimer_status(ui08 timer_id)
{
    stimer_t *timer;

    timer = &Timers[timer_id];
    return (timer->config_status & STATUS_MASK);
}

/*!
    callback for the timed out timer
    @param ID of the timer
    @return 1 if its still running, 0 if stopped
*/

ui08 stimer_timeout(ui08 timer_id)
{
	stimer_t *timer;
    ui08 config, status, time_unit;

    timer = &Timers[timer_id];
    config = (timer->config_status & CONFIG_MASK);
    status = (timer->config_status & STATUS_MASK);

    if (status & TIMER_OVERFLOW)
    {
        timer->config_status &= ~STATUS_MASK;

        if (TIMER_CYCLIC == (config & MODE_MASK))
        {
            time_unit = (timer->config_status & TIME_UNIT_MASK);
            stimer_set_time(timer_id, timer->time, time_unit);
            timer->config_status &= ~STATUS_MASK;
            timer->config_status |= TIMER_ON;
        }

        return 1;
    }

    return 0;
}

/*!
    clock for measuring the time elapsed

*/

void stimer_clock(void)
{
    stimer_t *timer;
	ui08 i, status;

	for (i = 0; i < TIMER_AMOUNT; i++)
	{
		timer = &Timers[i];
		status = timer->config_status & STATUS_MASK;

		if (status & (TIMER_USED | TIMER_ON))
		{
			if (timer->milisec == 0)
            {
                if (timer->minutes == 0)
                {
                    timer->config_status &= ~STATUS_MASK;
                    timer->config_status |= TIMER_OVERFLOW;
                }
                else
                {
                    timer->milisec = 60000;
                    timer->minutes--;
                }
            }
            else
            {
                timer->milisec--;
            }
		}
	}
}
