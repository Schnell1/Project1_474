
#include <stdio.h>

// create an array of integers of length 2
int fileStartEndIndex[2];

int getNumber() {
  int userInput;
  printf("Enter the how many blocks you want to split the file into: ");
  scanf("%d", &userInput);
  return userInput;
}

int * getBlock(int fileLength, int numBlocks, int blockIndex) {
  int blockSize = fileLength / numBlocks;
  int remainder = fileLength % numBlocks;
  int start = blockIndex * blockSize;
  int end = start + blockSize - 1;
  if (blockIndex == numBlocks - 1) {
    end += remainder;
  }
  fileStartEndIndex[0] = start;
  fileStartEndIndex[1] = end;
  return fileStartEndIndex;
}


// To Run:
// gcc testBlocks.c -o testBlocks && ./testBlocks
int main(void) {
  int fileBlocks = getNumber();

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

  // For the numbers 1 to fileChunkns
  for (int i = 0; i < fileBlocks; i++) {
    int blockIndex = i;
    int startIndex = getBlock(fileLength, fileBlocks, blockIndex)[0];
    int endIndex = getBlock(fileLength, fileBlocks, blockIndex)[1];
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
    printf("Sum of block(%d): %d\n", i, sum);
  }

  // Print the sum
  printf("TOTAL Sum: %d\n", sum);

  return 0;
}
