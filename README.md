# myShell

`myShell` is a minimal shell implementation for Windows, created to demonstrate basic shell functionalities and to serve as an educational tool for understanding how shells interact with the operating system.

## Features

- **Built-in Commands:**
  - `cd`: Change the current directory.
  - `help`: Display help information about built-in commands.
  - `exit`: Exit the shell.
  
- **External Command Execution:**
  - Launch external programs and wait for them to complete.

## Requirements

- Windows operating system
- A C compiler (e.g., MinGW)

## Compilation
To compile `myShell`, you can use a C compiler that supports Windows API. For example, if you're using `gcc` from MinGW, you can run:

```sh
gcc -o myShell myShell.c

```
## Usage
Open a command prompt and navigate to the directory containing the compiled `myShell.exe` executable.

Run the shell:

```sh
myShell.exe
```
 - You will be presented with a prompt `>`. 
 - Enter commands and press Enter.


To change the directory, use:
```sh
cd <directory>
```
To view the help information, use:
```sh
help
```
To exit the shell, use:
```sh
exit
```
To execute external programs, simply type the program's name and its arguments, if any.
Example:
```sh
shell
> cd C:\Users
> dir
> help
> exit
```
## Acknowledgements
  - Inspired by educational resources on shell development.
  - Uses Windows API for process management and directory operations.
