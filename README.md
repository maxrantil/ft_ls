# ft_ls
In this project, I reverse engineered the Unix command ls and built my own version of it. "ls" is used as a command line interface utility to print the contents of the current working directory. While working on this project, I gained a deeper understanding of how file systems are organized in Unix systems, how file permissions and other metadata work. It required a deep dive into operating system API functions and data structures, as well as learning about memory management in C.

To compile the program, run ``make`` in the root directory and the makefile will handle everything. You can then run ``./ft_ls`` to execute the program. The output will be displayed in neat columns, which will be adjusted to fit the terminal window each time the program runs.

This program was built on a Mac system and runs best in that environment. However, it will also compile and run on Linux, although some features may be missing.

 The goal was to recreate the ls command with some of its options, including:

```
-l: List the files in long format, including file permissions, number of links, owner, group, size, and last modification date.
-R: Recursively list the files in all subdirectories.
-a: Include hidden files in the list.
-r: Reverse the order of the files.
-t: Sort the files by last modification time.
```

## challenges
One of the main challenges of this project was getting a good understanding of the operating system functions and data structures needed to manipulate the file system. I also had to be mindful of error handling and ensuring that the program could handle illegal options.


## conclusion
Overall, this was a very educational and rewarding project. I gained a deeper understanding of C programming and how it can be used to interact with the file system.

<img width="965" alt="Screen Shot 2022-07-22 at 12 05 51 PM" src="https://user-images.githubusercontent.com/69106035/180405041-e373dbe4-df3c-476e-ba2c-3d02a429a4d8.png">
