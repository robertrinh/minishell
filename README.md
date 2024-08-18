# minishell

## Linux

```
# install readline
sudo apt install libreadline-dev

# run valgrind
make valgrind

# show reachable blocks
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes  ./minishell
```