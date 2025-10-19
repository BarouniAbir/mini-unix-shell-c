# OurShell : Mini UNIX Command Interpreter

> **Academic Project** A lightweight mini shell written in C for UNIX systems. Supports interactive and batch modes, with a simple command history.

## Features

* **Interactive mode**: Displays the prompt `[~$PWD] %`, reads a command, and executes it using `fork` + `exec*`.
* **History**: Shows the **last 10 executed commands** (`history`).
* **Batch mode**: If a **file** is passed as an argument (`argc == 2`), it executes each line sequentially.
* **Error handling**: Simple error messages are displayed if command execution fails.

## Project Structure

* `shell.c` — C source code of the shell.
* `LICENSE` — MIT license.
* `.gitignore` — ignores build and object files.

## Compilation

```bash
gcc shell.c -o ourshell
```

## Usage

### Interactive Mode

```bash
./ourshell
# Example commands:
ls -la
history     # displays the last 10 commands
quit        # exits the shell
```

### Batch Mode (Script)

```bash
./ourshell commands.txt
```

## Implementation Overview

* Main loop displays the prompt, reads input, and executes it with `fork()` / `execl` / `execvp` + `waitpid()`.
* Built-in command `quit` for clean exit.
* Special `history` command with a circular buffer storing the last 10 entries.
* In batch mode: opens the file, reads line by line, uses `splitLine()` to parse and execute.

## Roadmap

* Add support for redirections (`>`, `<`) and pipes (`|`).
* Line editing & autocompletion (GNU Readline).
* Persistent history between sessions (`~/.ourshell_history`).
* Automated testing (bats/CTest) + GitHub Actions CI.

## Authors

Developed as part of an academic project by **Barouni Abir**.
