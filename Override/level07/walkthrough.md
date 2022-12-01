# Level 07

Level 07's program is a number storer/reader.
It stores the numbers in an `char v6[400]` but it doesn't do bounds checking, so we have to take advantage of that.

It does do some checking, namely if the index is divisible by 3 or if HIBYTE(index) == 183 we are not allowed to write there.
But we can bypass that by giving indices which are bigger than INT_MAX.

```shell
(gdb) b read_number 
Breakpoint 1 at 0x80486dd
(gdb) r
[...]
(gdb) x/x $ebp + 0x8
0xffffd5b0:	0xffffd5d4
# 0xffffd5d4 is the value of the passed argument,
# 0xffffd5b0 is where it is being stored inside `read_number`
```

By trial and error, we find that the saved EIP is at index 114.
Trying to store a number at 114 tells us the index is reserved for Wil, so using [bitwiseCMD](https://bitwisecmd.com/) (`MIN_INT | 114`) we get index -2147483534.
Storing an integer at that index lets us overwrite the EIP.
Now we just need to store our Ret2Libc attack on indices 114, 115 and 116.