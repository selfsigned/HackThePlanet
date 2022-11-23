# Level 8

We have a big main and 2 global variables: `auth` and `service`.
The main continuously asks for input, with the valid commands being: `auth `(notice the space), `service`, `reset` and `login`.

It took some time here to figure out that auth wasn't a `char*`, but probably an `int*`. I got this because on dogbolt.org when you decompile with BinaryNinja, it showed an offset of 32 instead of 8 on line 33 of the source.c.
That would be because a char is 1 byte, and an int 4 bytes.

All we need to do is run the `auth ` command once, to initialize it with an address, and then run `service` twice, so that 32 bytes after the start of auth there are nonzero bytes (from the strdup() call on line 30) and finish it off with `login`.

```shell
level8@RainFall:~$ ./level8 
(nil), (nil) 
auth space
0x804a008, (nil) 
service
0x804a008, 0x804a018 
service
0x804a008, 0x804a028 
login
$ cat /home/user/level9/.pass
[redacted]
$ 
```
