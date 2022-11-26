# Level 3

Here we can see that the function `test()` is called with two parameters, if `322424845` minus our input equals 1 to 21 the `decrypt()` function is called with that value. Otherwise it's called with a random number.

The function `decrypt` then XOR it's input with "Q}|u`sfg~sf{}|a3" and returns a shell if the results is equal to "Congratulations!"

But nevermind that, let's bruteforce the 21 possible numbers
```shell
level03@OverRide:~$ for i in {0..21};do ./level03 < <(echo $((322424845-i))) | tr -d '\n' | grep -v 'Invalid' && echo $((322424845-i)) ; done                                                                                  
************************************            level03         *************************************Password:
322424827
level03@OverRide:~$ ./level03 
***********************************
*               level03         **
***********************************
Password:322424827
$ whoami
level04
```
