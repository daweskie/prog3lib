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

#include <stdlib.h>
#include "../include/timers_list.h"
#include "../include/stimer.h"


#define STATUS_MASK     (TIMER_ON | TIMER_PAUSED | TIMER_OVERFLOW)
#define MODE_MASK       (TIMER_ONESHOT | TIMER_CYCLIC)
#define TIME_UNIT_MASK  (TIMER_MILISEC | TIMER_SECONDS | TIMER_MINUTES | TIMER_HOURS)
#define CONFIG_MASK     (MODE_MASK | TIME_UNIT_MASK)


static timer_list_t Timers;
static timer_id_t  uiNextTimerId = 0;

/*!
    Initializes timers environment. Currently it creates list for keeping timers.
    @return 0 if initialization has been succeeded, 1 in other case.
*/
uint8_t	stimer_initialize()
{
	Timers = create_timer_list();
	return Timers == NULL ? 1 : 0;
}

/*!
    Finalizes timers environment. Currently it destroys the list of timers.
*/
void	stimer_finalize()
{
	destroy_timer_list(&Timers);
}

/*!
    timer creation, you can create one timer using this. argument MUST BE TIMER_ONESHOT or TIMER_CYCLIC
    @param TIMER_ONESHOT for one time timer and TIMER_CYCLIC for continuous timer
    @return the timer ID
*/

timer_id_t stimer_create(uint8_t config)
{
	stimer_t timer;
	timer_list_node_t * added_list_node = NULL;
	timer_id_t return_value = TIMER_ERROR;

	timer.timer_id = uiNextTimerId++;
	timer.config_status = (config & CONFIG_MASK);
        timer.callback_func = NULL;
        timer.callback_argument = NULL;
	added_list_node = add_timer_to_list(Timers, timer);
	if(added_list_node != NULL)
	{
		return_value = added_list_node->m_timer.timer_id;
	}

	return return_value;
}

/*!
    delete the timer by ID
    @param ID of the timer you want to delete
*/

void stimer_delete(timer_id_t timer_id)
{
	remove_timer_from_list(Timers, timer_id);
}

/*!
    set the time value and the time unit for the timer by ID
    @param ID of the timer you want to set
    @param value of time
    @param unit of time
*/

void stimer_set_time(timer_id_t timer_id, uint16_t time, uint8_t time_unit)
{
    stimer_t * timer = NULL;

	timer_list_node_t * timer_node = find_timer_node_by_id(Timers, timer_id);
	if(timer_node != NULL)
	{
		timer = &timer_node->m_timer;
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
			timer->minutes = (uint8_t) (time / 60);
			timer->milisec = (1000 * (time % 60));
		}
	}
}

/*!
    Sets callback function.
    @param timer_id             id of timer
    @param callback_func        pointer to callback function
    @param callback_argument    argument that will be passed to callback
*/
uint8_t stimer_set_callback(timer_id_t timer_id, timer_callback_t callback_func, 
        void* callback_argument)
{
    uint8_t return_value = TIMER_ERROR;
    
    timer_list_node_t * timer_node = find_timer_node_by_id(Timers, timer_id);
    if(timer_node != NULL)
    {
        timer_node->m_timer.callback_func = callback_func;
        timer_node->m_timer.callback_argument = callback_argument;
        return_value = 0;
    }
    
    return return_value;
}

/*!
    show the elapsed time
    @param ID of the timer
    @param unit of time

*/

uint16_t stimer_get_time(timer_id_t timer_id, uint8_t time_unit)
{
    stimer_t *timer = NULL;
    uint16_t time = 0;

	timer_list_node_t * timer_node = find_timer_node_by_id(Timers, timer_id);
	if(timer_node != NULL)
	{
		timer = &timer_node->m_timer;
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
	}

	return time;
}

/*!
    starts the timer
    @param ID of the timer

*/

void stimer_start(timer_id_t timer_id)
{
    stimer_t *timer;
	timer_list_node_t * timer_node = find_timer_node_by_id(Timers, timer_id);
	if(timer_node != NULL)
	{
		timer = &timer_node->m_timer;
		timer->config_status &= ~STATUS_MASK;
		timer->config_status |= TIMER_ON;
	}
}

/*!
    pause the timer by ID
    @param ID of the timer

*/

void stimer_pause(timer_id_t timer_id)
{
    stimer_t *timer;
	timer_list_node_t * timer_node = find_timer_node_by_id(Timers, timer_id);
	if(timer_node != NULL)
	{
		timer = &timer_node->m_timer;		
		timer->config_status &= ~STATUS_MASK;
		timer->config_status |= TIMER_PAUSED;
	}
}

/*!
    stop the timer and resets its value and status
    @param ID of the timer

*/

void stimer_stop(timer_id_t timer_id)
{
    stimer_t *timer;
    uint8_t time_unit;

	timer_list_node_t * timer_node = find_timer_node_by_id(Timers, timer_id);
	if(timer_node != NULL)
	{
		timer = &timer_node->m_timer;	
		timer->config_status &= ~STATUS_MASK;

		time_unit = (timer->config_status & TIME_UNIT_MASK);
		stimer_set_time(timer_id, timer->time, time_unit);
	}
}

/*!
    reset the timer, no change in status
    @param ID of the timer

*/

void stimer_reset(timer_id_t timer_id)
{
    stimer_t *timer;
    uint8_t time_unit;

	timer_list_node_t * timer_node = find_timer_node_by_id(Timers, timer_id);
	if(timer_node != NULL)
	{
		timer = &timer_node->m_timer;	
		time_unit = (timer->config_status & TIME_UNIT_MASK);
		stimer_set_time(timer_id, timer->time, time_unit);
	}
}

/*!
    status of the timer
    @param Id of the timer
    @return return the value of the status, see the constant macros
*/

uint8_t stimer_status(timer_id_t timer_id)
{
    stimer_t *timer;
	uint8_t status = TIMER_ERROR;

	timer_list_node_t * timer_node = find_timer_node_by_id(Timers, timer_id);
	if(timer_node != NULL)
	{
		timer = &timer_node->m_timer;	
		status = (timer->config_status & STATUS_MASK);
	}

    return status;
}

/*!
    callback for the timed out timer
    @param ID of the timer
    @return 1 if its still running, 0 if stopped
*/

uint8_t stimer_timeout(timer_id_t timer_id)
{
	stimer_t *timer;
    uint8_t config, status, time_unit;

	timer_list_node_t * timer_node = find_timer_node_by_id(Timers, timer_id);
	if(timer_node != NULL)
	{
		timer = &timer_node->m_timer;	
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
	}

    return 0;
}

/*!
    clock for measuring the time elapsed

*/

void stimer_clock(void)
{
    stimer_t *timer;
	uint8_t status;
	uint8_t time_unit;

	timer_list_node_t * node = NULL;
	for (node = Timers->next_node; node != NULL; node = node->next_node)
	{
		timer = &node->m_timer;
		status = timer->config_status & STATUS_MASK;

		if (status & TIMER_ON)
		{
			if (timer->milisec == 0)
            {
                if (timer->minutes == 0)
                {
                        if (TIMER_CYCLIC == (timer->config_status & MODE_MASK))
                        {
                                time_unit = (timer->config_status & TIME_UNIT_MASK);
                                stimer_set_time(timer->timer_id, timer->time, time_unit);
                                timer->config_status &= ~STATUS_MASK;
                                timer->config_status |= TIMER_ON;
                        }
			else
			{
		                timer->config_status &= ~STATUS_MASK;
        	                timer->config_status |= TIMER_OVERFLOW;
			}

                    	if(timer->callback_func != NULL)
                    	{
                    	    timer->callback_func(timer->callback_argument);
                    	}
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
