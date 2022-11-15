# Project1_474

- Summing up numbers by allowing the user to input how many child processes they would like to create.
- This will create a fork that uses a pipe to communicate back to the parent the total sum that it gets.
- Each process will have a read only instance of the file, and will jump to only the part that it cares about reading with the `fseek` function.
- It will iterate over the file until it gets to the `endIndex` for that child process.
- This allows us to concurrently read the file.

- This program was built to allow the user to specify any number of child processes.
- Please run the main program
- The other programs were all learning feats
