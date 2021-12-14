* to start memcached
$sudo systemctl start memcached

* to start memcached on different port
$memcached -p 11111 -U 11111 -u user -d

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


