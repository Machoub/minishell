# 💻 Minishell – 42 Project

A simplified UNIX shell written in C.  
This project aims to reproduce basic shell behavior: parsing, executing commands, managing redirections, pipes, environment variables, and signals.

---

## 📌 Description

`minishell` is a minimal shell that reproduces core behaviors of bash:

- Interactive prompt with command execution
- Pipes, redirections (`>`, `>>`, `<`, `<<`)
- Environment variable management and expansion (`$HOME`, `$?`, etc.)
- Built-in commands like `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`
- Signal handling (`CTRL+C`, `CTRL+\`)
- Command line parsing with proper quote handling

---

## 🧠 Implemented Features

✅ Built-in commands:
echo cd pwd export unset env exit

markdown
Copier
Modifier

✅ Other features:
- Pipes (`|`)
- Redirections (`>`, `>>`, `<`, `<<`)
- Environment variable expansion (`$USER`, `$?`)
- Quote management (`'`, `"`)
- Signal handling
- Exit codes
- Executable binary search using `$PATH`
- Heredocs with EOF limiters

---

## ⚙️ How to Build

```
make
```
To clean:

```
make clean      # Removes .o files
make fclean     # Removes .o and executable
make re         # Full rebuild
```
▶️ Usage
```
./minishell
```
Example:

```
minishell$ echo Hello | grep H > out.txt
minishell$ cat out.txt
Hello
```
Supports interactive input with real-time updates and line editing (via readline if used).


🛠️ Constraints
No fork() inside builtins like cd

- No memory leaks allowed

- No external parser (like bash or sh)

- Only authorized functions per subject

---


## 🧠 What I Learned
- Writing a shell parser and managing syntax trees

- Implementing a pipeline executor with proper fork/exec

- Handling environment state with envp

- Signal management (SIGINT, SIGQUIT, SIGTERM)

- Building a clean architecture with modular files

- Debugging complex I/O and subprocesses

---


## 👨‍💻 Author
**Mehdi Adel Achouba and Gino Helio Doubremelle**  
Login: machouba
Login: gdoubrem
42 Paris
GitHub: https://github.com/Machoub
GitHub: https://github.com/GinoDbm