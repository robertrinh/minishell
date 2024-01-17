# Tasks

## Schedules:
Availability Robert:
Normal times @ codam = wednesday to friday

---


## Availablilty Quinten:
Normal times @ codam = thursday + friday

---

## Notes
Join quote into one token

Based on outer quote, expand

Tokenizing based on operators

if first occurance from input is a command -> afterwards arguments, tokens until you encounter a specific symbol 
example: cat sources/minishell.c | grep "include" --> gives include line

Need to splite allocate_strings into 2 functions for the norm

---

## Tests

`echo "test"` -> segfaults when quotes are 1 token

`token ">> more"` -> no space after heredoc

`test "another |more"` -> works?

`token "   more tokens"` -> skips first spaces

`token "token   >>   more"` -> skips spaces

to consider: retraverse the token; add spaces back?

so "lets try" --> extra token at the end. check


---


## Documentation and Links: 

[42 Docs: Minishell](https://harm-smits.github.io/42docs/projects/minishell)

[Markdown: Basic Syntax](https://www.markdownguide.org/basic-syntax/)

[readline(3) - Linux manual page](https://man7.org/linux/man-pages/man3/readline.3.html)
