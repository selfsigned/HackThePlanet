# Robots and folders

## Exploit
An interesting URL to explore to gather some intel on a website is `/robots.txt`. It's purpose is to tell well-behaving robots which paths not to crawl or index.
Within this website's robots.txt we notice the presence of `${URL}/.hidden`, exploring it seems like a mess of folder. Thankfully we can use some trusty shell commands to find the needle in the haystack:
```shell
$ wget  --mirror --no-parent --execute robots=off http://${URL}/.hidden/ #recursively download the whole folder
$ cd ${URL}/.hidden
$ find . -name "*README" | xargs cat | sort | uniq #read all README files, sort them, and delete duplicated lines
[REDACTED]
Demande à ton voisin de droite
Demande à ton voisin de gauche
Demande à ton voisin du dessous
Demande à ton voisin du dessus
Non ce n'est toujours pas bon ...
Toujours pas tu vas craquer non ?
Tu veux de l'aide ? Moi aussi !
```
No need to code a fancy script.
