# Robots and folders

## Exploit
An interesting URL to explore to gather some intel on a website is `/robots.txt`. It's purpose is to tell well-behaving robots which paths not to crawl or index.
Within this website's robots.txt we notice the presence of `${URL}/whatever`, exploring it we can see an `.htpasswd` file that contains the admin password, in md5.

This time john can't decrypt it with the default wordlist, using [dcode](https://www.dcode.fr/md5-hash) instead we get `dragon`.

We can now login on the admin page `http://${URL}/admin` using `root:dragon` and get the flag

## Fix
To fix this you'd want to protect the `.htpasswd` folder, you should also never use MD5 and always select strong passwords that realistically can't be bruteforced.
