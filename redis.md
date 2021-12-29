* install redis:
 
$sudo apt install redis-server

* start redis:

$redis-server


* start redist client:
 
$redis-cli


* configuration

redis>CONFIG GET CONFIG_SETTING_NAME

redis>CONFIG GET loglevel

redis>CONFIG GET *


* to update config, you can edit redis.conf file, or via CONFIG SET command

redis>CONFIG SET CONFIG_SETTING_NAME NEW_CONFIG_VALUE

redis>CONFIG SET loglevel "notice" 

* redis data types

** Strings

redis>SET name "tutorialpoint"

redis>GET name

** Hashes

redis>HMSET user:1 username tutorialspoint password tutorialspoint points 200

redis>HGETALL user:1  

** Lists

reids>lpush tutoriallist redis

redis>lpush tutoriallist mongodb 

redis>lpush tutoriallist rabitmq

redis>lrange tutoriallist 0 10 

** Sets

redis>sadd tutoriallist redis 

redis>sadd tutoriallist mongodb 

redis>sadd tutoriallist rabitmq

redis>sadd tutoriallist rabitmq 

redis>smembers tutoriallist  


** Sorted Sets

redis>zadd tutoriallist 0 redis 

redis>zadd tutoriallist 0 mongodb

redis>zadd tutoriallist 0 rabitmq 

redis>ZRANGEBYSCORE tutoriallist 0 1000  


* commands

redis>PING


* run commands on remote server
 
$redis-cli -h host -p port -a password

$redis-cli -h 127.0.0.1 -p 6379 -a "mypass" 


* keys

redis>COMMAND KEY_NAME

redis>SET tutorialspoint redis 

redis>DEL tutorialspoint 


* key commands

1. DEL key This command deletes the key, if it exists.

2. DUMP key This command returns a serialized version of the value stored at the specified key.

3. EXISTS key This command checks whether the key exists or not.

4. EXPIRE key seconds Sets the expiry of the key after the specified time.

5. EXPIREAT key timestamp Sets the expiry of the key after the specified time. Here time is in Unix timestamp format.

6. PEXPIRE key milliseconds Set the expiry of key in milliseconds.

7. PEXPIREAT key milliseconds-timestamp Sets the expiry of the key in Unix timestamp specified as milliseconds.

8. KEYS pattern Finds all keys matching the specified pattern.

9. MOVE key db Moves a key to another database.

10. PERSIST key Removes the expiration from the key.

11.	PTTL key Gets the remaining time in keys expiry in milliseconds.

12. TTL key Gets the remaining time in keys expiry.

13. RANDOMKEY Returns a random key from Redis.

14. RENAME key newkey Changes the key name.

15. RENAMENX key newkey Renames the key, if a new key doesn't exist.

16. TYPE key Returns the data type of the value stored in the key.


* string commands

1. SET key value This command sets the value at the specified key.

2. GET key Gets the value of a key.

3. GETRANGE key start end Gets a substring of the string stored at a key.

4. GETSET key value Sets the string value of a key and return its old value.

5. GETBIT key offset Returns the bit value at the offset in the string value stored at the key.

6. MGET key1 [key2..] Gets the values of all the given keys

7. SETBIT key offset value Sets or clears the bit at the offset in the string value stored at the key

8. SETEX key seconds value Sets the value with the expiry of a key

9. SETNX key value Sets the value of a key, only if the key does not exist

10. SETRANGE key offset value Overwrites the part of a string at the key starting at the specified offset

11. STRLEN key Gets the length of the value stored in a key

12. MSET key value [key value ...] Sets multiple keys to multiple values

13. MSETNX key value [key value ...] Sets multiple keys to multiple values, only if none of the keys exist

14. PSETEX key milliseconds value Sets the value and expiration in milliseconds of a key

15. INCR key Increments the integer value of a key by one

16. INCRBY key increment Increments the integer value of a key by the given amount

17. INCRBYFLOAT key increment Increments the float value of a key by the given amount

18. DECR key Decrements the integer value of a key by one

19. DECRBY key decrement Decrements the integer value of a key by the given number


* hash commands

1. HDEL key field2 [field2] Deletes one or more hash fields.

2. HEXISTS key field Determines whether a hash field exists or not.

3. HGET key field Gets the value of a hash field stored at the specified key.

4. HGETALL key Gets all the fields and values stored in a hash at the specified key

5. HINCRBY key field increment Increments the integer value of a hash field by the given number

6. HINCRBYFLOAT key field increment Increments the float value of a hash field by the given amount

7. HKEYS key Gets all the fields in a hash

8. HLEN key Gets the number of fields in a hash

9. HMGET key field1 [field2] Gets the values of all the given hash fields

10. HMSET key field1 value1 [field2 value2 ] Sets multiple hash fields to multiple values

11. HSET key field value Sets the string value of a hash field

12. HSETNX key field value Sets the value of a hash field, only if the field does not exist

13. HVALS key Gets all the values in a hash

14. HSCAN key cursor [MATCH pattern] [COUNT count] Incrementally iterates hash fields and associated values


* list commands

1. BLPOP key1 [key2 ] timeout Removes and gets the first element in a list, or blocks until one is available

2. BRPOP key1 [key2 ] timeout Removes and gets the last element in a list, or blocks until one is available

3. BRPOPLPUSH source destination timeout Pops a value from a list, pushes it to another list and returns it; or blocks until one is available

4. LINDEX key index Gets an element from a list by its index

5. LINSERT key BEFORE|AFTER pivot value Inserts an element before or after another element in a list

6. LLEN key Gets the length of a list

7. LPOP key Removes and gets the first element in a list

8. LPUSH key value1 [value2] Prepends one or multiple values to a list

9. LPUSHX key value Prepends a value to a list, only if the list exists

10. LRANGE key start stop Gets a range of elements from a list

11. LREM key count value Removes elements from a list

12. LSET key index value Sets the value of an element in a list by its index

13. LTRIM key start stop Trims a list to the specified range

14. RPOP key Removes and gets the last element in a list

15. RPOPLPUSH source destination Removes the last element in a list, appends it to another list and returns it

16. RPUSH key value1 [value2] Appends one or multiple values to a list

17. RPUSHX key value Appends a value to a list, only if the list exists


* set commands

1. SADD key member1 [member2] Adds one or more members to a set

2. SCARD key Gets the number of members in a set

3. SDIFF key1 [key2] Subtracts multiple sets

4. SDIFFSTORE destination key1 [key2] Subtracts multiple sets and stores the resulting set in a key

5. SINTER key1 [key2] Intersects multiple sets

6. SINTERSTORE destination key1 [key2] Intersects multiple sets and stores the resulting set in a key

7. SISMEMBER key member Determines if a given value is a member of a set

8. SMEMBERS key Gets all the members in a set

9. SMOVE source destination member Moves a member from one set to another

10. SPOP key Removes and returns a random member from a set

11. SRANDMEMBER key [count] Gets one or multiple random members from a set

12. SREM key member1 [member2] Removes one or more members from a set

13. SUNION key1 [key2] Adds multiple sets

14. SUNIONSTORE destination key1 [key2] Adds multiple sets and stores the resulting set in a key

15. SSCAN key cursor [MATCH pattern] [COUNT count] Incrementally iterates set elements


* sorted set commands

1. ZADD key score1 member1 [score2 member2] Adds one or more members to a sorted set, or updates its score, if it already exists

2. ZCARD key Gets the number of members in a sorted set

3. ZCOUNT key min max Counts the members in a sorted set with scores within the given values

4. ZINCRBY key increment member Increments the score of a member in a sorted set

5. ZINTERSTORE destination numkeys key [key ...] Intersects multiple sorted sets and stores the resulting sorted set in a new key

6. ZLEXCOUNT key min max Counts the number of members in a sorted set between a given lexicographical range

7. ZRANGE key start stop [WITHSCORES] Returns a range of members in a sorted set, by index

8. ZRANGEBYLEX key min max [LIMIT offset count] Returns a range of members in a sorted set, by lexicographical range

9. ZRANGEBYSCORE key min max [WITHSCORES] [LIMIT] Returns a range of members in a sorted set, by score

10. ZRANK key member Determines the index of a member in a sorted set

11. ZREM key member [member ...] Removes one or more members from a sorted set

12. ZREMRANGEBYLEX key min max Removes all members in a sorted set between the given lexicographical range

13. ZREMRANGEBYRANK key start stop Removes all members in a sorted set within the given indexes

14. ZREMRANGEBYSCORE key min max Removes all members in a sorted set within the given scores

15. ZREVRANGE key start stop [WITHSCORES] Returns a range of members in a sorted set, by index, with scores ordered from high to low

16. ZREVRANGEBYSCORE key max min [WITHSCORES] Returns a range of members in a sorted set, by score, with scores ordered from high to low

17. ZREVRANK key member Determines the index of a member in a sorted set, with scores ordered from high to low

18. ZSCORE key member Gets the score associated with the given member in a sorted set

19. ZUNIONSTORE destination numkeys key [key ...] Adds multiple sorted sets and stores the resulting sorted set in a new key

20. ZSCAN key cursor [MATCH pattern] [COUNT count] Incrementally iterates sorted sets elements and associated scores


* HyperLogLog commands

1. PFADD key element [element ...] Adds the specified elements to the specified HyperLogLog.

2. PFCOUNT key [key ...] Returns the approximated cardinality of the set(s) observed by the HyperLogLog at key(s).

3. PFMERGE destkey sourcekey [sourcekey ...] Merges N different HyperLogLogs into a single one.


* Publish Subscribe commands

1. PSUBSCRIBE pattern [pattern ...] Subscribes to channels matching the given patterns.

2. PUBSUB subcommand [argument [argument ...]] Tells the state of Pub/Sub system. For example, which clients are active on the server.

3. PUBLISH channel message Posts a message to a channel.

4. PUNSUBSCRIBE [pattern [pattern ...]] Stops listening for messages posted to channels matching the given patterns.

5. SUBSCRIBE channel [channel ...] Listens for messages published to the given channels.

6. UNSUBSCRIBE [channel [channel ...]] Stops listening for messages posted to the given channels.



