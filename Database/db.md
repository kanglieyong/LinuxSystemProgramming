### HOW TO CREATE A DB INSTANCE
1. login MySQL
```
  $ mysql -u root -p
```
2. the password is `1`

3. create a account
```
 mysql> GRANT ALL ON *.* TO kly@localhost IDENTIFIED BY '1';
 mysql> \q
```

4. log in with new account
```
  $ mysql -u kly -p
```
5. create a new db instance
```
 mysql> CREATE DATABASE foo;
 mysql> \q
```
