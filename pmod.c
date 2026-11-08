// Dylan Bodoh, 111
 
// pmod.c
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char* argv[])
{
    //Reduce priority by 10
    if (nice(10) == -1)
    {
        perror("cant reduce priority");
    }

    /* Sleep for 1,837,272,638 ns */
    struct timespec delay;
    delay.tv_sec = 1;
    delay.tv_nsec = 837272638;

    nanosleep(&delay, NULL);
    printf("Goodbye.\n");
    return 0;
}