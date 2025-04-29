// Ethan O'Connor
// ECE 231
// 3/1/25
// The purpose of this file is to toggle a beaglebones LED every second, while recording timestamps

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define LED_PATH "/sys/class/leds/beaglebone:green:usr1/brightness"
#define SLEEP_DURATION_US 1000000  // 1 sec in micro seconds
#define NUM_MEASUREMENTS 300       // Adjustable number of measurements if wanted

int main(void) {
    // Set up the variables used throughout the code, including:
    FILE *timeFile = fopen("time_diff_file.txt", "w"); // file pointer for timestamps
    int led_state = 0;           // LED state is assumed off
    struct timespec start, end;  // For timestamps
    long long time_diff;         // long long -> 64 bit only, long -> 32 or 64 
    
    for (int i = 0; i < NUM_MEASUREMENTS; i++) {
        
        // Get timestamp before & after sleep
        clock_gettime(CLOCK_MONOTONIC, &start);
        usleep(SLEEP_DURATION_US);            // 1 sleep call, in loop so it is for both toggles
        clock_gettime(CLOCK_MONOTONIC, &end);
        
        // Calculate the difference in nanoseconds (reason for "LL" is to convert to long long)
        time_diff = (end.tv_sec - start.tv_sec) * 1000000000LL + (end.tv_nsec - start.tv_nsec);
        
        // Write time diff to the file ( %lld for long long, \n for new row for each entry)
        fprintf(timeFile, "%lld\n", time_diff);
        fflush(timeFile);            // Force buffer to clear (write to file immediately)
        
        // Toggle the LED state, write to led path to change it
        led_state = !led_state;
        FILE *ledFile = fopen(LED_PATH, "w"); 
        fprintf(ledFile, "%d", led_state);
        fclose(ledFile);
    }
    
    fclose(timeFile); // Once out of loop, close time file
    return 0;
}