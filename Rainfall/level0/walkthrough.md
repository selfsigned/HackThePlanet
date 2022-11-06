# Level 0
### The start of it all

We see that an input is expected and then sent to atoi, and then compared with a number
```
0x08048ed4      e837080000     call sym.atoi               ; int atoi(const char *str)
0x08048ed9      3da7010000     cmp eax, 0x1a7              ; 423
0x08048ede      7578           jne 0x8048f58
```

Converting `0x1a7` in decimal gives us `423`

```
level0@RainFall:~$ ./level0 423
$ cat /home/user/level1/.pass
1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
```
Hooray!
