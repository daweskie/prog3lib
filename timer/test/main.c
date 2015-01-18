
#include <stdio.h>
#include "../src/stimer.c"

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

int main(void)
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

    ui08 t1, t2, t3, t4;
    t1 = stimer_create(TIMER_ONESHOT);
    t2 = stimer_create(TIMER_CYCLIC);
    t3 = stimer_create(TIMER_ONESHOT);
    stimer_set_time(t1, 1, TIMER_MINUTES);
    stimer_set_time(t2, 10, TIMER_SECONDS);
    stimer_set_time(t3, 30000, TIMER_MILISEC);
    t4 = stimer_create(TIMER_ONESHOT);
    stimer_set_time(t4, 3, TIMER_SECONDS);
    stimer_start(t1);
    stimer_start(t2);
    stimer_start(t3);
    int started = 0;

    while (1)
    {
        if ((started == 1) && (stimer_timeout(t4)))
        {
            printf("Timer 4: timeout\n");
            stimer_reset(t4);
        }
        if (stimer_timeout(t1))
        {
            printf("Timer 1: timeout - 1 min elapsed\n");
        }

        if (stimer_timeout(t2))
        {
            printf("Timer 2: timeout\n");
            stimer_start(t4);
            started = 1;
        }

        if (stimer_timeout(t3))
        {
            printf("Timer 3: timeout - half min elapsed\n");
        }



#if !defined __linux__
        volatile unsigned long counter;
        for (counter = 0; counter < 100000; counter++); // just a delay
        stimer_clock();
#endif

    }

    return 0;
}

