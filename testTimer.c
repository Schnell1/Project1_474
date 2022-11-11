// Create a hello world in C

#include <stdio.h>
// Import clock module from time library
#include <time.h>
// Import the sleep module from the time library
#include <unistd.h>

// To Run:
// gcc testTimer.c -o testTimer && ./testTimer
int main(void)
{
  // Get the epoch time
  clock_t start = time(NULL);
  // Print start
  printf("Start: %ld", start);

  // Sleep 5 seconds
  sleep(1);

  // Get the end time
  clock_t end = time(NULL);
  // Print end
  printf("End: %ld", end);

  // Print the elapsed time
  printf("Elapsed time: %ld", end - start);
  return 0;
}
