# Level 6

In the source, we see two functions m and n.
In the main there is a function pointer being set to m which just prints "Nope". But n would print out the flag for us.
If only we could call it!

In comes strcpy to save the day.
Because the `char* dest` is located before our function pointer in memory, we can override it by overflowing the buffer.

As we can see, the strcpy copies over the entire argv[1].

```shell
level6@RainFall:~$ ./level6 $(python -c 'print 72 * "A" + "\x54\x84\x04\x08"')
[...]
```
I just don't yet understand why I can't print 64 A's, why it has to be 72. Probably padding but that is just my guess unless im missing something.
