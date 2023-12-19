<h1 align="center">
	Commands
</h1>

<div style="text-align: center;">
Documentation on available commands in the Codam Minishell project.
</div>

<br />

## Out of scope

`\`, `;` and unmatched quotes `"`.

<br />


## Environment

### `env`

The env utility executes another utility after modifying the environment.

### `PATH`

Path is an environment variable. The function is to exicute commands without specifying the full path. It points to the location of functions. list of directories, separated by a `:`.

### `export`

Add a variable to the environment. Set using export, a variable is available to subsequent commands or child processes.

### `unset`

Remove a variable from the environment.

### `$`

Expands the value of an environment variable.

### `$?`

A variable that holds the value of the exit status of the last exicuted command.

**0** = Success, **1-127** = Various errors, **128+** = Used by signals

<br />


### Environment Examples

```bash
  # Print all environment variables
  env

  # Add environment variable MY_VAR
  export MY_VAR=0

  # Print MY_VAR
  echo $MY_VAR

  # Run utility with new temp value of MY_VAR
  env MY_VAR=123 echo $MY_VAR

  # Remove MY_VAR
  unset MY_VAR

  # Print status of last command
  echo $?
```

<br />


## Pipe

Connect the output of one command to the input of another. By default, pipe sends `stdout(1)` to `stdin(0)`.

### Pipe Examples

```bash
  # Word count
  ls -l | wc -l
  cat document | grep text | wc -l

  # Sort
  echo -e $'banana\napple\norange' | sort
```

<br />


## Built-ins

### `echo`

Display text in terminal.
`-n` Do not print the trailing newline character.


### `pwd`

*"print working directory"*, print the absolute path to the current working directory.

> **Absolute path** location of a file or directory from the root directory.

> **Relative path** location of a file or directory relative to the current working directory.


### `cd`

Change the current working directory.

### (CD) Command Directory Example

```bash
  # Jump to root
  cd ~
  cd ~ Desktop/Codam

  # Move up/back
  cd ..
  cd -

  # Relative path
  # /home/user/Desktop/File
  cd Desktop/Codam

  # Absolute path
  # /Desktop/file
  cd /Desktop/Codam
```

<br />

## Quotes

### Single `''`

All characters are treated literally, and no variable expansion or command substitution occurs.


### Double `""`

Variables are expanded. Use only `$`.

### Quotes Example

```bash
  # Single
  echo 'Hello, $USER' # Output: Hello, $USER

  # Double
  echo "Hello, $USER" # Output: Hello, qbeukelm

  # Multiple
  GREETING="Hello"
  TARGET="world"
  echo "${GREETING}, ${TARGET}! Today is $(date '+%A')."
  # Output: Hello, world! Today is Tuesday.
```

<br />


## Redirects

### Redirect output `>`

Redirect the standard output of a command to a file. If the file does not exist, it is created. If the file does exist, contents are overwritten.

```bash
  command > output.txt
  echo "" > output.txt # Clear contents of input.txt
```

<br />


### (Append to file) `>>`

Include multiple lines of input in a command. Given a `delimiter`, read the input until a line containing the delimiter is seen.

> **!** Doesn’t have to update the history

```bash
  command >> output.txt
  echo "Append to end of output.txt" >> output.txt
```

<br />

### Redirect input `<`

Redirect the standard input of a command from a file. It takes the contents of the file and proviedes the as an input for the command.

```bash
  command < input.txt
```

<br />



### (Here doc) `<<`

Redirect the standard output of a command to a file, appended to the end of the contents of the file. No overwriting.

```bash
  # END is delimiter
  cat << END > output.txt
  This is line 1.
  This is line 2.
  END
```
`Cat` is reading from the **here document**, which is the block of text between `<< END` and `END`. The here document provides input to the cat command.

```bash
  # END is delimiter
  cat input.txt << END > output.txt
```
`Cat` is reading from **input.txt**, up to `END` and appends to **output.txt**.


<br />


## Exit

Terminate the current shell or script.

```bash
  # Exit with status code
  exit 0 # Success
  exit 255 # Errors

  # Exit with status of last command
  exit $?
```

<br />
