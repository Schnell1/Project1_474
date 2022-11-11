#include <stdio.h>
// Import the fork function from the unistd.h header file.
#include <unistd.h>
// Import the wait function from the unistd.h header file.
#include <sys/wait.h>
// Import the clock_t module
#include <time.h>

// To Run:
// gcc forkAndSum.c -o forkAndSum && ./forkAndSum

// This program creates 4 forks and sums the numbers 1-1000.
// The parent process will wait for all the children to finish before printing the sum.


// Create an array of 4 pipes
int pipefd[4][2];
int fileStartEndIndex[2]; // Only way to return 2 values from a function

int getNumber() {
  int userInput;
  printf("Enter the number of pipes you want to create: ");
  scanf("%d", &userInput);
  return userInput;
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

int main() {
  int numPipes = getNumber();

  int fileLength = myFileLength("numbers/file1.dat");

  // Create the pipe.
  for (int i = 0; i < 4; i++) {
    pipe(pipefd[i]);
  }

  int i;
  int pid;

  for (i = 0; i < numPipes; i++) {
    int chunkIndex = i;

    pid = fork();
    if (pid == 0) {
      // get start time of child
      clock_t start = clock();

      // Child process
      int childSum = 0;
      int chunkIndex = i;
      int startIndex = getChunk(fileLength, numPipes, chunkIndex)[0];
      int endIndex = getChunk(fileLength, numPipes, chunkIndex)[1];
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
        childSum += (int)num;
      }

      printf("Sum of process(%d): %d\n", i, childSum);

      // get end time of child
      clock_t end = clock();

      // get the total time of the child
      double time_taken = ((double)(end - start));
      printf("Time taken by process(%d): %f\n", i, time_taken);

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

  printf("Sum: %d\n", totalSum);
  return 0;
}

