// Include the standard library
#include <stdio.h>

// create an array of integers of length 2
int fileStartEndIndex[2];

int getNumber() {
  int userInput;
  printf("Enter the how many chunks you want to split the file into: ");
  scanf("%d", &userInput);
  return userInput;
}

int * getChunk(int fileLength, int numChunks, int chunkIndex) {
  int chunkSize = fileLength / numChunks;
  int remainder = fileLength % numChunks;
  int start = chunkIndex * chunkSize;
  int end = start + chunkSize - 1;
  if (chunkIndex == numChunks - 1) {
    end += remainder;
  }
  fileStartEndIndex[0] = start;
  fileStartEndIndex[1] = end;
  return fileStartEndIndex;
}


// To Run:
// gcc dummy.c -o dummy && ./dummy
int main(void) {
  int fileChunks = getNumber();

  FILE *fpInit;
  fpInit = fopen("numbers/file1.dat", "r");
  // get the length of numbers in the file, seperated by newlines
  int fileLength = 0;
  char c;
  for (c = getc(fpInit); c != EOF; c = getc(fpInit)) {
    if (c == '\n') { fileLength++; }
  }
  fclose(fpInit);

  int sum = 0;

  // For the numbers 1 to fileChunks
  for (int i = 0; i < fileChunks; i++) {
    int chunkIndex = i;
    int startIndex = getChunk(fileLength, fileChunks, chunkIndex)[0];
    int endIndex = getChunk(fileLength, fileChunks, chunkIndex)[1];
    // printf("Start index: %d, End index: %d\n", startIndex, endIndex);

    // Open the file1.dat for the start and end index
    // Sum up all the numbers
    // Close the file
    FILE *fp;
    int num;
    fp = fopen("numbers/file1.dat", "r");
    // fseek(fp, startIndex * sizeof(int), SEEK_SET);
    fseek(fp, (sizeof(int) + 1) * startIndex, SEEK_SET);
    // for the range of start and end index
    for (int i = startIndex; i <= endIndex; i++) {
      fscanf(fp, "%d", &num);
      sum += (int)num;
    }

    // Print the sum
    printf("Sum of chunk(%d): %d\n", i, sum);
  }

  // Print the sum
  printf("TOTAL Sum: %d\n", sum);

  return 0;
}
