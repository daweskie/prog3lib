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
/** \file timer_list.c
    \brief Main file for the timer's linked list unit
*/
#include <stdlib.h>
#include "timers_list.h"


timer_list_node_t * create_list_node()
{
    timer_list_node_t * p_timer_node = (timer_list_node_t *) malloc(sizeof(timer_list_node_t));
    if(p_timer_node != NULL)
    {
        p_timer_node->m_timer.timer_id = (timer_id_t)(-1);
        p_timer_node->next_node = NULL;
        p_timer_node->previous_node = NULL;
    }

    return p_timer_node;
}

void destroy_list_node(timer_list_node_t ** p_node)
{
    free(*p_node);
    *p_node = NULL;
}

timer_list_t create_timer_list()
{
    return create_list_node();
}

void destroy_timer_list(timer_list_t * list)
{
    remove_all_timers_from_list(*list);
    destroy_list_node(list);
}

timer_list_node_t * add_timer_to_list(timer_list_t list, stimer_t timer)
{
    timer_list_node_t * p_timer_node = NULL;
    timer_list_node_t * last_node_in_list = NULL;

    if(list != NULL)
    {
        p_timer_node = create_list_node();
        if(p_timer_node != NULL)
        {
            p_timer_node->m_timer = timer;
            last_node_in_list = list->previous_node;
            if(last_node_in_list != NULL)
            {
                last_node_in_list->next_node = p_timer_node;
                p_timer_node->previous_node = last_node_in_list;
                list->previous_node = p_timer_node;
            }
            else
            {
                list->next_node		= p_timer_node;
                list->previous_node = p_timer_node;
                p_timer_node->previous_node = list;
            }
        }
    }

    return p_timer_node;
}

timer_list_node_t * find_timer_node_by_id(timer_list_t list, timer_id_t timer_id)
{
    timer_list_node_t * p_cur_node = list->next_node;
    while(p_cur_node != NULL)
    {
        if(p_cur_node->m_timer.timer_id == timer_id)
        {
            break;
        }
        else
        {
            p_cur_node = p_cur_node->next_node;
        }
    }

    return p_cur_node;
}

timer_list_node_t *
remove_timer_node_from_list(timer_list_t list, timer_list_node_t * node_to_delete)
{
    timer_list_node_t * next_node = NULL;
    timer_list_node_t * previous_node = NULL;
    if(node_to_delete != NULL)
    {
        next_node = node_to_delete->next_node;
        previous_node = node_to_delete->previous_node;

        if(previous_node != NULL)
        {
            previous_node->next_node = node_to_delete->next_node;
        }

        if(next_node != NULL)
        {
            next_node->previous_node = node_to_delete->previous_node;
        }

        if(list->previous_node == node_to_delete)
        {
            list->previous_node = NULL;
        }

        destroy_list_node(&node_to_delete);
    }

    return next_node;
}

void remove_timer_from_list(timer_list_t list, timer_id_t timer_id)
{
    timer_list_node_t * node_to_delete = find_timer_node_by_id(list, timer_id);
    if(node_to_delete != NULL)
    {
        remove_timer_node_from_list(list, node_to_delete);
    }
}

void remove_all_timers_from_list(timer_list_t list)
{
    timer_list_node_t * first_node = list->next_node;
    while(first_node != NULL)
    {
        first_node = remove_timer_node_from_list(list, first_node);
    }
}

