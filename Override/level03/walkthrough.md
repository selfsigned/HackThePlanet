# Level 3

Here we can see that the function `test()` is called with two parameters, if `322424845` minus our input equals between 1 and 21, the `decrypt()` function is called with that value. Otherwise it's called with a random number.

The function `decrypt` then XOR it's input with "Q}|u`sfg~sf{}|a3" and returns a shell if the results is equal to "Congratulations!"

Q's Ascii value is 81, C's ascii value is 67.
If we calculate `81 ^ 67`, we get `18`.

Let's try that then, shall we?

```shell
level03@OverRide:~$ python -c 'print 322424845 - 18'
322424827
level03@OverRide:~$ ./level03 
***********************************
*		level03		**
***********************************
Password:322424827
$ whoami          
level04
```
