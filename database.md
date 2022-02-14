# SQL

We cannot avoid partition in a distributed system, therefore, according to the CAP theorem, a distributed system should choose between consistency or availability. ACID (Atomicity, Consistency, Isolation, Durability) databases, such as RDBMSs like MySQL, Oracle, and Microsoft SQL Server, chose consistency (refuse response if it cannot check with peers), while BASE (Basically Available, Soft-state, Eventually consistent) databases, such as NoSQL databases like MongoDB, Cassandra, and Redis, chose availability (respond with local data without ensuring it is the latest with its peers).

```
SELECT column1, column2....columnN
FROM   table_name;


SELECT DISTINCT column1, column2....columnN
FROM   table_name;


SELECT column1, column2....columnN
FROM   table_name
WHERE  CONDITION;


SELECT column1, column2....columnN
FROM   table_name
WHERE  CONDITION-1 {AND|OR} CONDITION-2;


SELECT column1, column2....columnN
FROM   table_name
WHERE  column_name IN (val-1, val-2,...val-N);


SELECT column1, column2....columnN
FROM   table_name
WHERE  column_name BETWEEN val-1 AND val-2;


SELECT column1, column2....columnN
FROM   table_name
WHERE  column_name LIKE { PATTERN };


SELECT column1, column2....columnN
FROM   table_name
WHERE  CONDITION
ORDER BY column_name {ASC|DESC};


SELECT SUM(column_name)
FROM   table_name
WHERE  CONDITION
GROUP BY column_name;


SELECT COUNT(column_name)
FROM   table_name
WHERE  CONDITION;


SELECT SUM(column_name)
FROM   table_name
WHERE  CONDITION
GROUP BY column_name
HAVING (arithematic function condition);


CREATE TABLE table_name(
column1 datatype,
column2 datatype,
column3 datatype,
.....
columnN datatype,
PRIMARY KEY( one or more columns )
);


DROP TABLE table_name;


CREATE UNIQUE INDEX index_name
ON table_name ( column1, column2,...columnN);


ALTER TABLE table_name
DROP INDEX index_name;


DESC table_name;


TRUNCATE TABLE table_name;


ALTER TABLE table_name {ADD|DROP|MODIFY} column_name {data_type};


ALTER TABLE table_name RENAME TO new_table_name;


INSERT INTO table_name( column1, column2....columnN)
VALUES ( value1, value2....valueN);


UPDATE table_name
SET column1 = value1, column2 = value2....columnN=valueN
[ WHERE  CONDITION ];


DELETE FROM table_name
WHERE  {CONDITION};


CREATE DATABASE database_name;


DROP DATABASE database_name;


USE database_name;


COMMIT;


ROLLBACK;


```
