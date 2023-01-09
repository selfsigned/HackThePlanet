# False-ly secure

## Exploit
Checking the cookies on the website we can see a curious key called `i_am_admin` with a value of `68934a3e9455fa72420237eb05902327`. Sure looks like md5, let's get to cracking with john the ripper:
```shell
$ echo "dummy:68934a3e9455fa72420237eb05902327" > pw.txt
$ john --format=raw-md5 --show pw.txt
dummy:false

1 password hash cracked, 0 left
```
So the admin authentification cookie... is just a boolean. Let's change it to `true` converted to md5
```shell
$ echo -n "true" | md5sum
b326b5062b2f0e69046810717534cb09  -
```
We replace it in the browser and as soon as we reload the page we get the flag.

## Fix
Several things went wrong here:
- The password wasn't even one, making it incredibly weak and easy to bruteforce, using a better one would've helped
- md5 [was already considered broken in 2010](https://www.kb.cert.org/vuls/id/836068)
- A possible fix would be to maybe use's nginx `auth_basic` over HTTPS instead of re-inventing the wheel
- On top of this, the cookie is vulnerable  to MiTM attacks as it doesn't have the secure flag, allowing HTTP connections. It would be trivial for a public wifi operator to harvest the cookie from the cleartext traffic.
