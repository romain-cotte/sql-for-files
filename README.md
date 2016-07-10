Sql for files
=============

[![Build Status](https://img.shields.io/travis/LilMeyer/sql-for-files/master.svg?style=flat-square)](https://travis-ci.org/LilMeyer/sql-for-files)

# Objective

The purpose of this tool is to query data files with SQL language. Given an
input file :

`data.csv`
```
1;2;3
4;5;6
7;8;9
10;11;12
```

and this query:
```
SELECT 1, 3 FROM data.csv DELIMITER ';';
```

the command:
```
sql-file query.txt
```

will output:
```
1;3
4;6
7;9
10;12
```

# Backlog

 * [ ] Support path in the filename
 * [ ] Add ORDER BY option
 * [ ] Add JOIN operation
 * [ ] Add the possibility to give an alias to a filename
 * [ ] Support multiple SELECT

# Contribute

Don't hesitate to contibute !
