#ifndef _TIMERS_LIST__H
#define _TIMERS_LIST__H

#include <stdint.h>

typedef uint32_t timer_id_t;
typedef void (*timer_callback_t)(void *);

struct stimer_t
{
	uint8_t                 config_status;
	timer_id_t              timer_id;
	uint16_t                time;
	uint16_t                milisec;
	uint8_t                 minutes;
        timer_callback_t        callback_func;
        void *                  callback_argument;
};

typedef struct stimer_t stimer_t;

struct timer_list_node_t
{
	struct stimer_t		m_timer;
	struct timer_list_node_t	*next_node;
	struct timer_list_node_t	*previous_node;
};
typedef struct timer_list_node_t timer_list_node_t;

typedef timer_list_node_t * timer_list_t;

timer_list_t create_timer_list();
void		 destroy_timer_list(timer_list_t * list);

timer_list_node_t * add_timer_to_list(timer_list_t, stimer_t);
timer_list_node_t * find_timer_node_by_id(timer_list_t, timer_id_t timer_id);
void remove_timer_from_list(timer_list_t, timer_id_t timer_id);
void remove_all_timers_from_list(timer_list_t);

#endif //_TIMERS_LIST__H
