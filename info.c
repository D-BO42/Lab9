// Dylan Bodoh, 111

// info.c
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <netdb.h>  
#include <string.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
int main(int argc, char* argv[])
{
    struct timespec tp;
    //get time in nanoseconds
    clock_gettime(CLOCK_REALTIME , &tp);
    printf("Time(ns): %ld\n", tp.tv_nsec);

    //network name
    char hostname[256];
    // Get the system's hostname
    if (gethostname(hostname, sizeof(hostname)) == -1) {
        perror("gethostname");
        exit(1);
    }
    printf("Hostname: %s\n", hostname);
    //system stuff
    struct utsname buffer;
    if (uname(&buffer) < 0) {
        perror("uname");
        exit(EXIT_FAILURE);
    }
    printf("OS     : %s\n", buffer.sysname);
    printf("release: %s\n", buffer.release);
    printf("version: %s\n", buffer.version);
    printf("machine: %s\n", buffer.machine);
    
    int ncore = get_nprocs();
    printf("Cores: %d\n", ncore);
    long page_size = sysconf(_SC_PAGE_SIZE);
    long phys_pages = sysconf(_SC_PHYS_PAGES);
    long total = page_size * phys_pages;
    printf("Mem size bytes: %ld\n", total);
    long free_pages = sysconf(_SC_AVPHYS_PAGES);
    long free = free_pages * page_size;
    printf("Free mem:  %ld\n", free);
    return 0;
}