# minishell

## Linux

```
# install readline
sudo apt install libreadline-dev

# run valgrind
valgrind --leak-check=full --track-origins=yes  ./minishell
clear && make re && valgrind --leak-check=full --track-origins=yes  ./minishell

# show reachable blocks
clear && make re && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes  ./minishell
```