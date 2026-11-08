// Dylan Bodoh, 111

// pinfo.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sched.h>
#include <string.h>

int main(int argc, char* argv[])
{

    pid_t pid;

    if(argc > 2)
    {
        printf("Invalid input");
        return 1;
    }

    if(argc == 2)
    {
        pid = atoi(argv[1]);
    }
    else
    {
        pid = getpid();
    }
    //get priority
    int priority = getpriority(PRIO_PROCESS, pid);

    if(priority == -1)
    {
        perror("Invalid process ID");
        return 1;
    }
    //get schedualing method
    int sced = sched_getscheduler(pid);

    if(sced == -1)
    {
        perror("sched_getscheduler");
        return 1;
    }

    printf("PID: %d\n", pid);
    printf("Priority: %d\n", priority);
    char met[15];
    //convert to string
    switch (sced) {
        case SCHED_OTHER:
            strcpy(met, "SCHED_OTHER");
            break;
        case SCHED_FIFO:
            strcpy(met, "SCHED_FIFO");
            break;
        case SCHED_RR:
            strcpy(met, "SCHED_RR");
            break;
        default:
            strcpy(met, "Unknowing");
}

    printf("Scheduling Method: %s\n", met);

    return 0;
}