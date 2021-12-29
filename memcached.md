* to start memcached
$sudo systemctl start memcached

* by default memcached is on port 11211

* to start memcached on different port
$memcached -p 11111 -U 11111 -u user -d
$/usr/bin/memcached -m 64 -p 11211 -u memcache -l 127.0.0.1 -P /var/run/memcached/memcached.pid

* to connect to a memcached server
$telnet 192.168.1.54 11111

## set command

Memcached set command is used to set a new value to a new or existing key.

```
set key flags exptime bytes [noreply] 
value 
```

* key − It is the name of the key by which data is stored and retrieved from Memcached.

* flags − It is the 32-bit unsigned integer that the server stores with the data provided by the user, and returns along with the data when the item is retrieved.

* exptime − It is the expiration time in seconds. 0 means no delay. If exptime is more than 30 days, Memcached uses it as UNIX timestamp for expiration.

* bytes − It is the number of bytes in the data block that needs to be stored. This is the length of the data that needs to be stored in Memcached.

* noreply (optional) - It is a parameter that informs the server not to send any reply.

* value − It is the data that needs to be stored. The data needs to be passed on the new line after executing the command with the above options.


## add command

Memcached add command is used to set a value to a new key. If the key already exists, then it gives the output NOT_STORED.

```
add key flags exptime bytes [noreply]
value
```

## replace command

Memcached replace command is used to replace the value of an existing key. If the key does not exist, then it gives the output NOT_STORED.

```
replace key flags exptime bytes [noreply]
value
```


## append command

Memcached append command is used to add some data in an existing key. The data is stored after the existing data of the key.

```
append key flags exptime bytes [noreply]
value
```

## prepend command

Memcached prepend command is used to add some data in an existing key. The data is stored before the existing data of the key.

```
prepend key flags exptime bytes [noreply]
value
```

## CAS command

CAS stands for Check-And-Set or Compare-And-Swap. Memcached CAS command is used to set the data if it is not updated since last fetch. If the key does not exist in Memcached, then it returns NOT_FOUND.

```
cas key flags exptime bytes unique_cas_key [noreply]
value
```

* key − It is the name of the key by which data is stored and retrieved from Memcached.

* flags − It is the 32-bit unsigned integer that the server stores with the data provided by the user, and returns along with the data when the item is retrieved.

* exptime − It is the expiration time in seconds. 0 means no delay. If exptime is more than 30 days, Memcached uses it as a UNIX timestamp for expiration.

* bytes − It is the number of bytes in the data block that needs to be stored. This is the length of the data that needs to be stored in Memcached.

* unique_cas_key − It is the unique key get from gets command.

* noreply (optional) − It is a parameter that informs the server not to send any reply.

* value − It is the data that needs to be stored. Data needs to be passed on new line after executing the command with the above options.


## get command

```
get key
```


## get CAS data

Memcached gets command is used to get the value with CAS token. If the key does not exist in Memcached, then it returns nothing.

```
gets key
```


## delete command

```
delete key [noreply]
```


## increment decrement data

Memcached incr and decr commands are used to increment or decrement the numeric value of an existing key. If the key is not found, then it returns NOT_FOUND. If the key is not numeric, then it returns CLIENT_ERROR cannot increment or decrement non-numeric value. Otherwise, ERROR is returned.

```
incr key increment_value
decr key decrement_value
```


## stats command

Memcached stats command is used to return server statistics such as PID, version, connections, etc.

```
stats
```


## stats items command

Memcached stats items command is used to get items statistics such as count, age, eviction, etc. organized by slabs ID.

```
stats items
```


## stats slabs command

Memcached stats slabs command displays slabs statistics such as size, memory usage, commands, count etc. organized by slabs ID.

```
stats slabs
```


## stats sizes command

Memcached stats sizes command provides information about the sizes and number of items of each size within the cache. The information is returned in two columns. The first column is the size of the item (rounded up to the nearest 32 byte boundary), and the second column is the count of the number of items of that size within the cache.

```
stats sizes
```


## clear data command

Memcached flush_all command is used to delete all data (key-value pairs) from the Memcached server. It accepts an optional parameter called time that sets a time after which the Memcached data is to be cleared.

```
flush_all [time] [noreply]
```


