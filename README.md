<h1 align="center">
    Minishell
</h1>

<br />

# About

As beautiful as a shell. Welcome to mininshell! This repository GNU like operating system, inspired by bash.

<br />


# Setup

<details>
<summary>Mac OS</summary>

### Install Readline Mac OS

Minishell makes use of the [GNU Readline](https://man7.org/linux/man-pages/man3/readline.3.html) library. To run the project, you will need to install this library. For Mac OS, the Readline library can be installed using Brew. If you already have Brew installed, skip to step 2.

``` bash
# STEP 1: Install brew
rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update
```

``` bash
# STEP 2: Install readline
brew install readline
```
---
<br />
</details>

<details>
<summary>Linux</summary>


### Install Readline Linux

Minishell makes use of the [GNU Readline](https://man7.org/linux/man-pages/man3/readline.3.html) library. To run the project, you will need to install this library. For Linux, the Readline library can be installed using apt.

To simulate a Linux machine, emulators such as [OrbStack](https://orbstack.dev) are available for free.


``` bash
# STEP 1: nstall readline
sudo apt install libreadline-dev
```
---
<br />
</details>

<br />


# Compile Minishell

To run minishell, first compile the program using make. Whether using Mac OS or Linux, the make recipies do not differ.

```bash
make            # Compile
make valgrind   # Complie and monitor memory leaks
make re         # Recompile
make clean      # Compile and delete all object files
make fclean     # Remove all objects and executables
```

<br />

# Run Minishell

```bash
./minishell     # Run executable
./minishell -p  # Run executable in debug mode
```

<br />

# Usage

### Prompt
* `[minishell]:` Each successive operation of the program displayes a new prompt.

### History

* `^` Using the up arrow will display the previous command. 
* `history` The history command will list all previously entered commands.

### Expander

* `' '` Single quotes do not expand contained input.
* `" "` Double quotes expand the contained input.
* `$` The perameter or variable expansion operator is used to expand the value for a given key found in the program environment or evn.
* `$?` Exit code. Expand the exit code of the last executed command.

### Redirections

* `>` Redirect output. Redirect the standard output of a command to a file. If the file does not exist, it is created. If the file does exist, contents are overwritten.
* `>>` Redirect append. Include multiple lines of input in a command. Given a delimiter, read the input until a line containing the delimiter is seen.
* `<` Redirect the standard input of a command from a file. It takes the contents of the file and proviedes the as an input for the command.
* `<<` Heredoc. Redirect the standard output of a command to a file, appended to the end of the contents of the file without overwriting. Heredoc reads until the given end of file or EOF. e.g. `echo << EOF`.


### Pipes

* `|` A single pipe operator connects the output of one command to the input of another. By default, pipe sends `stdout(1)` to `stdin(0)`. The first command writes to an open file on the write fd, upon completion of the open process, the second command reads from the read fd of the open file.


### Signals

* `ctrl-c` Ends the current process and displays a new prompt on a new line.
* `crtl-d` Kills all processes and exit the minishell program.


### Builtins

\* **man(1-3)** General Commands Manual

| Builtin   | Description |
| :---:     | :---        |
| `echo`    | The echo utility writes any specified operands, separated by single blank (‘ ’) characters and followed by a newline (‘\n’) character, to the standard output. |
| `pwd`     | The pwd utility writes the absolute pathname of the current working directory to the standard output. |
| `cd`      | The cd utility shall change the working directory of the current shell execution environment. |
| `env`     | The env utility executes another utility after modifying the environment as specified on the command line.  Each name=value option specifies the setting of an environment variable, name, with a value of value.  All such environment variables are set before the utility is executed. |
| `export`  | Minishell shall give the export attribute to the variables corresponding to the specified names, which shall cause them to be in the environment of subsequently executed commands. If the name of a variable is followed by =word, then the value of that variable shall be set to word. |
| `unset`   | Each variable or function specified by the given key shall be unset in the environment. |
| `exit`    | The exit() function causes normal process termination. |

