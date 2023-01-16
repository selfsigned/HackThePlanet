# Stored XSS
## Exploit
Here we supposedly have an XSS on the feedback, except not really because this subject is dumb and a waste of time, just typing `script` in any of the fields and pressing submit gives the flag. Here with a real XSS exploit the browser would assume that the user inputted`<script>` tag is part of the page upon loading and execute it happily.

## Fix
XSS vulnerabilities allow full control over the website and the theft of any sensitive information in the user session. To prevent XSS bugs developers should use whatever escaping feature their framework provide.
