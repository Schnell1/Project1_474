#include <stdio.h>

int main(void)

// To run the program, type the following command:
// gcc sumSingleFile.c -o sumSingleFile && ./sumSingleFile
{
  // Opwen nums1.txt and sum up all the numbers
  FILE *fp;
  int num;
  int sum = 0;
  fp = fopen("numbers/file1.dat", "r");
  while (fscanf(fp, "%d", &num) != EOF)
  {
    sum += num;
  }
  fclose(fp);
  printf("Sum of all numbers in file1.dat is %d)", sum);

  return 0;
}
