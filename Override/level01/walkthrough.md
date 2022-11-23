# Level 1

Before us we have a binary which represents an admin login prompt.
First, it asks us for the username which it `fgets` into a global variable called `a_user_name`, and if it matches `dat_wil`, we can input the password.
The password would then be read into a 64 byte buffer with `fgets`, but here fgets will read up to 256 bytes, so we can overflow.

Using our trusted [pattern generator](https://wiremask.eu/tools/buffer-overflow-pattern-generator/), we find that the offset is 80.


Because NX (No eXecute) is enabled, we can't just store shellcode in our environment variables and execute it, so we have to build our own ret2libc attack, but this I will do tomorrow or something.
