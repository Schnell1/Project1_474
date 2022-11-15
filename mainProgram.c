#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

// To Run:
// gcc mainProgram.c -o mainProgram && ./mainProgram


int pipefd[4][2];
int fileStartEndIndex[2]; // Only way to return 2 values from a function

int getNumber() {
  int userInput;
  printf("Enter the number of child processes you want to create: ");
  scanf("%d", &userInput);
  return userInput;
}
char* getFile() {
  int userInput;
  char* outPut = "";
  printf("\n Which file do you want to prcoess? \n Option: 1 = file1(contains 1000 lines), 2 = file2(contains 10,000 lines) , 3 = file3(contain 100,000 lines): ");
  scanf("%d", &userInput);
  if(userInput == 1)
  {
    outPut = "numbers/file1.dat";
  }
  if(userInput == 2)
  {
    outPut = "numbers/file2.dat";
  }
   if(userInput == 3)
  {
    outPut = "numbers/file3.dat";
  }
  return outPut;
}

// Function that returns the length of the file, seperated by newlines. Given a file name.
int myFileLength(char *fileName) {
  FILE *fpInit;
  fpInit = fopen(fileName, "r");
  // get the length of numbers in the file, seperated by newlines
  int fileLength = 0;
  char c;
  for (c = getc(fpInit); c != EOF; c = getc(fpInit)) {
    if (c == '\n') { fileLength++; }
  }
  fclose(fpInit);
  return fileLength;
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

int main() {
  
  int numPipes = getNumber();
  char * filePath = getFile();
  int fileLength = myFileLength(filePath);

  // Create the pipe.
  for (int i = 0; i < 4; i++) {
    pipe(pipefd[i]);
  }

  int i;
  int pid;

  for (i = 0; i < numPipes; i++) {
    int blockIndex = i;

    pid = fork();
    if (pid == 0) {
      // get start time of child
      clock_t start = clock();

      // Child process
      int childSum = 0;
      int blockIndex = i;
      int startIndex = getBlock(fileLength, numPipes, blockIndex)[0];
      int endIndex = getBlock(fileLength, numPipes, blockIndex)[1];
      // printf("Start index: %d, End index: %d\n", startIndex, endIndex);

      // Open the file for the start and end index
      // Sum up all the numbers
      // Close the file
      FILE *fp;
      int num;
      fp = fopen(filePath, "r");
      // fseek(fp, startIndex * sizeof(int), SEEK_SET);
      fseek(fp, (sizeof(int) + 1) * startIndex, SEEK_SET);
      // for the range of start and end index
      for (int i = startIndex; i <= endIndex; i++) {
        fscanf(fp, "%d", &num);
        childSum += (int)num;
      }

      printf("Sum of process(%d): %d\n", i, childSum);

      // get end time of child
      clock_t end = clock();

      // get the total time of the child 
      double time_taken = ((double)(end - start));
      printf("Time taken by process: (%d): %f\n\n", i, time_taken);

      write(pipefd[i][1], &childSum, sizeof(childSum));
      return 0;
    }
  }

  // Parent process
  int status;

  for (i = 0; i < numPipes; i++) {
    wait(&status);
  }

  int totalSum = 0;
  int sumFromPipe;
  // Read 100 from the pipe.
  // For each child process, read the sum from the pipe and add it to the total sum.
  for (i = 0; i < numPipes; i++) {
    read(pipefd[i][0], &sumFromPipe, sizeof(sumFromPipe));
    totalSum += sumFromPipe;
  }

  printf("Final Time = The longest child time process \n");
  printf("Sum of numbers: %d\n", totalSum);
  return 0;
}

