# Abitrary redirect

## Exploit
The redirect mechanism takes an user-specified input, making it possible for an attacker to scam users via a phising attack exploiting the legitimacy of the domain that's redirecting.
Here it's only a matter of editing the `site` parameter of `${URL}/?page=redirect`, for instance:
```shell
curl -s 'http://localhost/?page=redirect&site=example.com' | grep flag
```

## Fix
Explicitely declare the URl to redirect to in the code instead of letting the user specify it.
