# minishell

## Linux

```
# install readline
sudo apt install libreadline-dev

# run valgrind
valgrind --leak-check=full --track-origins=yes  ./minishell
clear && make && valgrind --leak-check=full --track-origins=yes  ./minishell
```