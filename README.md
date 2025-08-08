# MyShell

A tiny educational Unix-style shell written in C. It reads a line, tokenizes it (supports quotes), runs built-ins like `cd`, and executes external programs via `fork()+execvp()`.

## Features
- Prompt shows current working directory (e.g., `/home/user >>`).
- Tokenizer with support for `"quoted strings"`.
- Built-ins:
  - `cd <dir>` — change directory
  - `help` — list built-ins
  - `exit` — exit the shell
- Executes external commands in foreground and waits for completion.

## Build

### Quick build
```bash
gcc -Wall -Wextra -g shell.c execute.c tokenizer.c input.c -o myshell
```

### With Makefile (optional)
```makefile
CC = gcc
CFLAGS = -Wall -Wextra -g
SRC = shell.c execute.c tokenizer.c input.c
TARGET = myshell

all: $(TARGET)
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
```

## Run
```bash
./myshell
```

Example session:
```
/home/alex >> help
MyShell - Built-in Commands:
    cd
    help
    exit
Use man <command> for information on external commands.

/home/alex >> cd projects
/home/alex/projects >> echo "hello world"
hello world
/home/alex/projects >> exit
```

## Project Layout
- `shell.c` — REPL loop: prints prompt, reads a line, tokenizes, executes.  
- `input.c` — line input (dynamically grows a buffer as you type).  
- `tokenizer.c` — splits a line into argv tokens; respects quotes.  
- `execute.c` — built-ins (`cd`, `help`, `exit`) and launching external programs.

## How It Works (High Level)
1. **Prompt & Read:** `shell.c` prints `getcwd()` prompt and calls `read_line()`.
2. **Tokenize:** `tokenizer.c` converts the raw line into `char **argv`, handling spaces and `"quoted tokens"`.
3. **Dispatch:**
   - If `argv[0]` matches a built-in, call the corresponding function.
   - Otherwise `fork()`, `execvp(argv[0], argv)`, and `waitpid()` in the parent.
4. **Loop** until `exit` sets a non-positive status.

## Usage Notes
- Use quotes for arguments containing spaces: `echo "two words"`.
- `cd` requires a directory argument: `cd /tmp`.
- `exit` quits the shell; you can extend it to accept an exit code.

## Extending
Easy next steps:
- Add built-ins: `pwd`, `echo`, `history`.
- Support I/O redirection (`>`, `<`) and pipelines (`|`).
- Background jobs (`&`), `jobs`, `fg`, `bg`.

## License
MIT (or your choice). Add a `LICENSE` file if you want contributions.
