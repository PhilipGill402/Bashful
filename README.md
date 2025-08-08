# Bashful

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

### With Makefile
```makefile
make && ./bashful
```

Example session:
```
/home/philip >> help
Bashful - Built-in Commands:
    cd
    help
    exit
Use man <command> for information on external commands.

/home/philip >> cd projects
/home/philip/projects >> echo "hello world"
hello world
/home/philip/projects >> exit
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
- `exit` quits the shell.

## TODO
Easy next steps:
- Add built-ins: `history`.
- Support I/O redirection (`>`, `<`) and pipelines (`|`).

## License
MIT.
