# Level 00

Now that's a tough one! 
The program compares the value we input to a number and gives us a shell if it matches
```ASM
0x080484e7 <+83>:    cmp    $0x149c,%eax
0x080484ec <+88>:    jne    0x804850d <main+121>
```

let's input `5276`
```shell
level00@OverRide:~$ ./level00
***********************************
*            -Level00 -           *
***********************************
Password:5276

Authenticated!
$ whoami
level01
```
yeah...
