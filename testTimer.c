#include <stdio.h>
#include <time.h>
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
