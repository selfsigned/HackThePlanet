# Survey

## Exploit
We make our way to the survey page `${URL}?page=survey`. We can grade users there via a form from 1 to 10, easily bypassed by modifying the value property in the html, or alternatively with cURL
```shell
$ curl -s -X POST --data "sujet=2&valeur=666" "${URL}/localhost/?page=survey" | grep flag
```
## Fix
Always validate user input, here a simple boundary check of i >= 1 and i <= 10 would have worked. It's worth noting that to implement a user survey you most likely should have an identity verification mechanism, otherwise it's all too trivial to make the results worthless.
