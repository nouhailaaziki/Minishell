# The Execution Part

## 🧠 What is Execution in Minishell?
### Execution means:
➡️ "Taking the command the user typed, and running it on the computer."

### Example:
If I type:
```bash
ls -l
```
Minishell has to find the ls program and run it exactly like the real terminal.

## 🛠️ What Steps Happen in Execution?
### 1. Check if the command is a built-in
Some commands are built inside minishell (like cd, echo, export, etc.).
➡️ If the command is built-in, we call our own C functions directly.
➡️ If it is not built-in, we move to the next step.

### 2.Find the full path of the command

- User types ls, but where is ls stored? In /bin/ls maybe.

- We search inside the system’s $PATH environment variable.

- When we find it, we now know exactly where ls is.

### 3.Prepare Redirections (if needed)

- If user typed ls > file.txt, we must redirect the output into file.txt.

- We use dup2() to change the input/output files before executing.

### 4.Create a new process (child process)

- In Unix, programs run inside processes.

- We use fork() to create a child process.

- In the child process, we run the command using execve().

- execve() replaces the child process with the real program.

### 5.Wait for the command to finish

- In the parent process (the original minishell), we wait() for the child to finish running.

- When it finishes, we return to the prompt ready for the next command.

## 🧩 Simple Visual Map
```bash
User types: ls -l

  ↓

Check: Is "ls" a built-in?
  ⬇️ No
Find full path → /bin/ls
  ↓
Handle redirections if needed
  ↓
fork()
    ├── Parent process: wait() for child
    └── Child process:
          ├── handle dup2() if needed
          └── execve("/bin/ls", args, env)
  ↓
Command finishes
  ↓
Print new prompt
```
## ⚡ In short:
1. Is it a built-in? If yes, run built-in function.
2. Find where the command is located.
3. Setup redirections (like >, <, >>).
4. Fork a child process.
5.	In child: run execve. In parent: wait for child.
## 🎯 Key Functions you must understand:
- fork(): Create a new child process.
- execve():	Run a real program in the child.
- dup2():	Redirect input/output files (for redirections).
- waitpid():	Parent waits for child to finish.
## 🧠 Imagine it like a Chef:
- The user is a customer who orders "ls -l" dish.

- Minishell is the chef.

- The chef checks:

  - Is the dish easy (built-in)? ➡️ Cook it directly.

  - Is it complicated (external)? ➡️ Go get the recipe (find full path) and cook it (execve).

- Sometimes the customer says:

  - "Put the food into a box" (redirection).

- After cooking, the chef cleans up and is ready for a new order (next prompt).

## 🚀 Final words:
Execution = recognize the command → prepare → fork → execve → wait.

You’re basically copying what bash does behind the scenes!

