# Level 6

Here we have a function `auth` that has several rounds of checks to pass before getting a shell.

### Login length

First we need to make sure our login is at least six characters long or the function will just exit.

### No tampering pls!

Now the program is trying to prevent us from debugging with gdb, let's outsmart it.

`0x080487bd      752e           jne 0x80487ed` is preventing us to debug the program, let's replace the `jne` with a `je`, opcode 0x74 in x86 ASM
```shell
// 0x74 
level06@OverRide:~$ gdb -q ./level06 
Reading symbols from /home/users/level06/level06...(no debugging symbols found)...done.
(gdb) def hook-stop
Type commands for definition of "hook-stop".
End with a line saying just "end".
>set *(unsigned char*)0x080487bd = 0x74
>end
(gdb) b main
Breakpoint 1 at 0x804887c
(gdb) r
Breakpoint 1, 0x0804887c in main ()
(gdb) c
Continuing.
***********************************
*               level06           *
***********************************
-> Enter Login: aaaaaa
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: aaaaaa
[Inferior 1 (process 1844) exited with code 01]
```
😈
### No peeking

Let's take a look at what our input is compared to now shall we?

```shell
(gdb) b *0x08048869                                                  
Breakpoint 2 at 0x8048869                                            
(gdb) r                                                              
Starting program: /home/users/level06/level06      
                                                                     
Breakpoint 1, 0x0804887c in main ()             
(gdb) c                                                              
Continuing.                                                          
***********************************                   
*               level06           *            
***********************************                
-> Enter Login: bazinga                                              
***********************************               
***** NEW ACCOUNT DETECTED ********       
***********************************     
-> Enter Serial: 42                                                  
```
                                                                     
Okay, let's now put a breakpoint inside the check we want to pass and check the value of each arguments
```shell
Breakpoint 2, 0x08048869 in auth ()     
[...]
   0x08048863 <+283>:   mov    0xc(%ebp),%eax
   0x08048866 <+286>:   cmp    -0x10(%ebp),%eax
=> 0x08048869 <+289>:   je     0x8048872 <auth+298>
[...]
(gdb) x/d $ebp+0xc
0xffffd6c4:     42
(gdb) x/d $ebp-0x10
0xffffd6a8:     6233784
```
### The final countdown
We could see our argument `42` and another value it's compared to, `6233784`. Let's run our program outside of gdb with the same user and that value and see what happens.

```shell
level06@OverRide:~$ ./level06 
***********************************
*               level06           *
***********************************
-> Enter Login: bazinga
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6233784
Authenticated!
$ whoami
level07
```

Bazinga.
