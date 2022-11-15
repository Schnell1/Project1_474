#include <stdio.h>
#include <time.h>
#include <unistd.h>

// Create a function that sums up all the numbers in a file
int sumFile(char *fileName) {
  // Open the file
  FILE *fp;
  int num;
  int sum = 0;
  fp = fopen(fileName, "r");
  while (fscanf(fp, "%d", &num) != EOF)
  {
    sum += num;
  }
  fclose(fp);
  return sum;
}


// To Run:
// gcc sumFilesWithTimer.c -o sumFilesWithTimer && ./sumFilesWithTimer
int main(void)
{
  clock_t start = time(NULL);

  int sum1 = sumFile("numbers/file1.dat"); // 454019
  int sum2 = sumFile("numbers/file2.dat"); // 5014959
  int sum3 = sumFile("numbers/file3.dat"); // 51450896

  clock_t end = time(NULL);

  printf("Elapsed time: %ld\n", end - start);
  // Print sum of all the files
  printf("Sum of all the files: %d\n", sum1 + sum2 + sum3); // 56919874
  // Print empty line
  printf("\n");

  return 0;
}
