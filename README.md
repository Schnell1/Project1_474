# c-fork-testing

- Summing up numbers by allowing the user to input how many child processes they would like to create.
- This will create a fork that uses a pipe to communicate back to the parent the total sum that it gets.
- Each process will have a read only instance of the file, and will jump to only the part that it cares about reading with the `fseek` function.
- It will iterate over the file until it gets to the `endIndex` for that child process.
- This allows us to concurrently read the file.

- This program was built to allow the user to specify any number of child processes. It will be fun to see what the optimal number of processes for a given hardware is once the number set is much larger.

# File Structure
- At the time of this writing, `forkAndSum.c` is a full demo of summing the numbers in parallel. All the other files were learnings to get there.
