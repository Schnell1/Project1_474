#include <stdio.h>

// To run the program, type the following command:
// gcc readUserInput.c -o readUserInput && ./readUserInput

int getNumber() {
  int userInput;
  printf("Enter a number: ");
  scanf("%d", &userInput);
  return userInput;
}

int main(void) {
  int usersNumber = getNumber();
  printf("You entered: %d\n", usersNumber);

  return 0;
}
