# myShell

`myShell` is a minimal shell implementation for Windows, created to demonstrate basic shell functionalities and to serve as an educational tool for understanding how shells interact with the operating system.

## Features

- **Built-in Commands:**
  - `changedir`: Change the current directory.
  - `assist`: Display help information about built-in commands.
  - `quit`: Exit the shell.
  
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
- You will be presented with a prompt >.
- Enter commands and press Enter.

### Custom Commands
- To change the directory, use:

```sh
changedir <directory>
```

- To view the help information, use:

```sh
assist
```

- To exit the shell, use:

```sh
quit
```

- To create a directory, use:

```sh
makedir <directory>
```

- To remove a directory, use:

```sh
removedir <directory>
```

- To list the contents of the current directory, use:

```sh
listdir
```

- To display the current working directory, use:

```sh
currworkdir
```

- To create an empty file (touch), use:
```sh
createtouch <filename>
```

- To remove a file, use:

```sh
removefile <filename>
```


- To copy a file, use:

```sh
copyfile <source> <destination>
```


- To move a file, use:
```sh
movefile <source> <destination>
```

### Example Usage

```sh
shell
> changedir C:\Users
> listdir
> assist
> quit
```

## Acknowledgements
  - Inspired by educational resources on shell development.
  - Uses Windows API for process management and directory operations.
