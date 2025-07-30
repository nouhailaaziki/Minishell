# Minishell (with Bonus)

Minishell is a small Unix shell developed in C as part of the 42 curriculum.  
It reproduces core Bash behavior including command execution, redirections, pipes, environment management, and more.  
The bonus part implements support for logical operators `&&`, `||` with parentheses for priority, and wildcard `*` expansion in the current working directory.

---

## 📑 Table of Contents

- [Features](#features)
  - [Mandatory Part](#mandatory-part)
  - [Bonus Part](#bonus-part)
- [Learning Objectives](#learning-objectives)
- [Installing Dependencies (Readline & Homebrew)](#installing-dependencies-readline--homebrew)
- [Contributors](#contributors)

---

## Features

### Mandatory Part
- Interactive prompt with user input handling
- Execution of commands with arguments and path resolution
- Built-in commands:
  - `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Redirections:
  - Input `<`, Output `>`, Append `>>`, Heredoc `<<`
- Pipelines: `cmd1 | cmd2 | cmd3`
- Environment variable expansion: `$VAR`, `$?`
- Quote handling: `'`, `"`
- Signal handling:
  - `CTRL+C`, `CTRL+\`, `CTRL+D`
- Correct exit status propagation

### Bonus Part
- **Logical Operators with Parentheses**
  - Support for `&&` and `||` to control execution based on command status
  - Parentheses for prioritizing evaluation (subshell-like behavior)
    ```bash
    (echo one && echo two) || echo fallback
    ```
- **Wildcard Expansion**
  - Support for `*` to match files and folders in the **current working directory** only
    ```bash
    echo *.c
    echo test_*.txt
    ```

---

## Learning Objectives

- Build a functional shell from scratch
- Implement lexical analysis and recursive parsing
- Manage processes and file descriptors
- Handle Unix signals correctly
- Perform globbing (wildcards) without using `glob()`
- Evaluate command groups with priority logic

---

## Installing Dependencies (Readline && Homebrew)

```This shell uses the GNU Readline library to handle input, command history, and arrow key navigation.```

If you do not have Homebrew and Readline installed:
Run this in your terminal:

```bash
curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
```

✓ Homebrew will now be available in your session.

Then, install Readline:

```bash
brew install readline
```
```bash
brew link --force readline
```

Update your environment variables so the compiler can find it:

```bash
echo 'export C_INCLUDE_PATH="$HOME/.brew/include:$C_INCLUDE_PATH"' >> ~/.zshrc
```
```bash
echo 'export LIBRARY_PATH="$HOME/.brew/lib:$LIBRARY_PATH"' >> ~/.zshrc
```
```bash
source ~/.zshrc
```

You can now compile and run your Minishell using make.

---

## Contributors

- Nouhaila Aziki
- Youssef Rhandoumi
