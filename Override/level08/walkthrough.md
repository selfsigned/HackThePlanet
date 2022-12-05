# Level 08

This one is more of a snow-crash type exploit as we don't actually override anything.
One thing we can note in the sourcefile is that our argv[1] gets used twice. Once as an absolute path, and one copied right after `./backups`.


Where it gets used as an absolute path, it is being read (`fopen(argv[1], "r")`).

And on line 44-46, we can see it is being used as `"./backups/${argv[1]}"`.

So if we can ensure that in our current working directory this last path exists, and argv[1] exists also as an absolute value, we can force the program to read from that file, and write its content into the backups folder, allowing us to read the contents of it.

## So...

What I did was the following:
```shell
cd /tmp
level08@OverRide:/tmp$ mkdir -p ./backups/home/users/level09/
level08@OverRide:/tmp$ ~/level08 /home/users/level09/.pass
level08@OverRide:/tmp$ cat backups/home/users/level09/.pass
[redacted]
```
