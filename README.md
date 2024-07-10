# Simple Shell Application

This project is a simple command-line shell application that mimics some functionalities of a Unix shell. It allows users to execute various built-in commands and interact with the file system.

## Features

- Customizable shell prompt
- Built-in commands for clearing the screen, exiting the shell, changing the prompt, displaying file information, and displaying file system information
- Basic error handling and help system

## Built-in Commands

### clear
Clears the terminal screen.
- Usage: `clear`
- Help: `clear -h` or `clear -help`

### exit
Exits the shell. Optionally accepts a numeric argument to set the exit status.
- Usage: `exit [n]`
- Help: `exit -h` or `exit -help`

### prompt
Changes the shell prompt to a new value.
- Usage: `prompt [new_prompt]`
- Help: `prompt -h` or `prompt -help`

### fileinfo
Displays information about a specified file.
- Usage: `fileinfo -switch filename`
- Help: `fileinfo -h` or `fileinfo -help`
- Switches:
  - `-i`: Displays the inode number.
  - `-t`: Displays the type of the file (directory, regular, symbolic link).
  - `-m`: Displays the last modification date.

### osifo
Displays information about the file system.
- Usage: `osifo -switch`
- Help: `osifo -h` or `osifo -help`
- Switches:
  - `-t`: Displays the type of the file system (e.g., EXT, EXT2, MSDOS, etc.).
  - `-b`: Displays the total number of blocks in the file system.
  - `-s`: Displays the maximum number of characters that can be used in a filename.

### man
Provides help information for the built-in commands.
- Usage: `man command`
- Example: `man exit`

## How to Build

To compile the project, use the following command:
```sh
g++ -o shell shell.cpp -lpthread
