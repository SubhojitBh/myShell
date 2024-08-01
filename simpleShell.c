// SIMPLE SHELL IMPLEMENTATION FOR WINDOWS

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h> 

// Function declarations for built-in shell commands
int myShell_cd(char **args);
int myShell_help(char **args);
int myShell_exit(char **args);

// List of built-in commands and their corresponding functions
char *builtin_str[] = {
  "cd",
  "help",
  "exit"
};

int (*builtin_func[]) (char **) = {
  &myShell_cd,
  &myShell_help,
  &myShell_exit
};

// Get the number of built-in commands
int myShell_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

// Implementation of built-in functions

// Change directory
int myShell_cd(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "myShell: expected argument to \"cd\"\n");
  } else {
    if (_chdir(args[1]) != 0) {
      perror("myShell");
    }
  }
  return 1;
}

// Print help
int myShell_help(char **args) {
  printf("Subhojit Bhattacherjee's myShell\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built-in:\n");

  for (int i = 0; i < myShell_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

// Exit the shell
int myShell_exit(char **args) {
  return 0;
}

// Launch a program and wait for it to terminate
int myShell_launch(char **args) {
  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si);
  ZeroMemory(&pi, sizeof(pi));

  // Combine arguments into a single command line string
  char commandLine[1024] = "";
  for (int i = 0; args[i] != NULL; i++) {
    strcat(commandLine, args[i]);
    strcat(commandLine, " ");
  }

  // Start the child process
  if (!CreateProcess(NULL, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
    fprintf(stderr, "CreateProcess failed (%d).\n", GetLastError());
    return 1;
  }

  // Wait until the child process exits
  WaitForSingleObject(pi.hProcess, INFINITE);

  // Close process and thread handles
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);

  return 1;
}

// Execute shell built-in or launch program
int myShell_execute(char **args) {
  if (args[0] == NULL) {
    return 1; // Empty command
  }

  for (int i = 0; i < myShell_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return myShell_launch(args);
}

// Read a line of input from stdin
char *myShell_read_line(void) {
  int bufsize = 1024;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "myShell: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    c = getchar();

    if (c == EOF) {
      exit(EXIT_SUCCESS);
    } else if (c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    // If buffer exceeded, reallocate
    if (position >= bufsize) {
      bufsize += 1024;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "myShell: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

// Split a line into tokens
char **myShell_split_line(char *line) {
  int bufsize = 64, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token, **tokens_backup;

  if (!tokens) {
    fprintf(stderr, "myShell: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, " \t\r\n\a");
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += 64;
      tokens_backup = tokens;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        free(tokens_backup);
        fprintf(stderr, "myShell: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, " \t\r\n\a");
  }
  tokens[position] = NULL;
  return tokens;
}

// Main loop for getting input and executing it
void myShell_loop(void) {
  char *line;
  char **args;
  int status;

  do {
    printf("> ");
    line = myShell_read_line();
    args = myShell_split_line(line);
    status = myShell_execute(args);

    free(line);
    free(args);
  } while (status);
}

// Main entry point
int main(int argc, char **argv) {
  // Load config files, if any.

  // Run command loop
  myShell_loop();

  // Perform any shutdown/cleanup

  return EXIT_SUCCESS;
}
