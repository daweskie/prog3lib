
#include <stdio.h>
#include "../include/stimer.h"

#if defined __linux__
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

void event_handler (int signum) // 1ms interrupt
{
    if (signum == SIGALRM)
    {
        stimer_clock();
    }
}

#endif

void set_timer_for_linux()
{
#if defined __linux__
    struct sigaction sa;
    struct itimerval timer;
    memset (&sa, 0, sizeof (sa));
    sa.sa_handler = &event_handler;
    sigaction (SIGALRM, &sa, NULL);
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 1000;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 1000;
    setitimer (ITIMER_REAL, &timer, NULL);
#endif
}

void timer_callback_function_2_seconds(void * timer_id)
{
    unsigned int uiTimerId = (unsigned int) *((timer_id_t*) timer_id);
    printf("Timer %u: 2 seconds elapsed.\n", uiTimerId + 1);
}

void timer_callback_function_5_seconds(void * timer_id)
{
    unsigned int uiTimerId = (unsigned int) *((timer_id_t*) timer_id);
    printf("Timer %u: 5 seconds elapsed.\n", uiTimerId + 1);
}

void timer_callback_function_15_seconds(void * timer_id)
{
    unsigned int uiTimerId = (unsigned int) *((timer_id_t*) timer_id);
    printf("Timer %u: 15 seconds elapsed.\n", uiTimerId + 1);
}

int main(void)
{
	timer_id_t t1, t2, tn;
	const unsigned int cuiOneShotTimersCount = 300;
	timer_id_t OneShotTimersIds[cuiOneShotTimersCount];

 	unsigned int uiTimersCounter = 0;
	char cSymbolToExit;
	if(stimer_initialize() == 0)
	{
		set_timer_for_linux();
                t1 = stimer_create(TIMER_CYCLIC);
                stimer_set_callback(t1, timer_callback_function_2_seconds, &t1);
                stimer_set_time(t1, 2, TIMER_SECONDS);
                stimer_start(t1);

		t2 = stimer_create(TIMER_CYCLIC);
                stimer_set_callback(t2, timer_callback_function_5_seconds, &t2);
		stimer_set_time(t2, 5, TIMER_SECONDS);
		stimer_start(t2);

		for(; uiTimersCounter < cuiOneShotTimersCount; ++uiTimersCounter)
		{
			tn = stimer_create(TIMER_ONESHOT);
			OneShotTimersIds[uiTimersCounter] = tn; 
			stimer_set_time(tn, 15, TIMER_SECONDS);
			stimer_set_callback(tn, timer_callback_function_15_seconds, &OneShotTimersIds[uiTimersCounter]);
			stimer_start((timer_id_t)tn);
		}
		
		while(1) sleep(5);				

		stimer_finalize();
	}

    return 0;
}

