# latency number

| operation                          | time     |
| :--------------------------------: | :------: |
| L1 cache reference                 | 0.5 ns   |
| L2 cache reference                 | 7 ns     |
| Main memory reference              | 100 ns   |
| Disk seek                          | 10 ms    |
| Read sequentially from disk        | 30 MB/s  |
| Read sequentially from 1 Gpbs      | 100 MB/s |
| Read sequentially from SSD         | 1 GB/s   |
| Read sequentially from main memory | 4 GB/s   |
| 6 - 7 world-wide round trips       | 1 s      |
| 200 round trips within data center | 1 s      |


# QPS

Single web server, 1k
SQL database, 1k
NoSQL database, 10k
NoSQL database(memcached), 1m


# rate limiting algorithm
* Token bucket
* Leaking bucket
* Fixed window counter
* Sliding window log
* Sliding window counter


# consistent hashing
* hash space/ring
* hash server
* hash key
* virtual nodes

# key-value pair

Versioning and vector clocks are used to solve inconsistency problems.

A vector clock is a [server, version] pair associated with a data item.

* conflict resolution, replication, failure detection, failure repair mechanism 

Sorted-string table(SSTable) is a sorted list of <key, value> pairs.


# unique id generator

UUID is a 128-bit number used to identify information in computer systems. 

snowflake id generator: 0(1 bit) + timestamp(41 bits) + datacenter id(5 bits) + machine id(5 bits) + sequence number(12 bits)



```
5  Kth Largest Element
461  Kth Smallest Numbers in Unsorted Array
543  Kth Largest in N Arrays
401  Kth Smallest Number in Sorted Matrix
465  Kth Smallest Sum In Two Sorted Arrays
406  Minimum Size Subarray Sum
32  Minimum Window Substring
384  Longest Substring Without Repeating Characters
386  Longest Substring with At Most K Distinct Characters
609  Two Sum - Less than or equal to target
382  Triangle Count


589 Connecting Graph
590 Connecting Graph II
591 Connecting Graph III
434 Number of Islands II
178 Graph Valid Tree
1070 Accounts Merge
1396 Set Union
434 Nmber of Island II
431 Connected Component in Undirected Graph
432 Find the Weak Connected Component in the Directed Graph
559 Trie Service
629 Minimum Spanning Tree
805 Maximum Association Set
442 Implement Trie (Prefix Tree)
473 Add and Search Word - Data structure design
132 Word Search II
477 Surrunded Regions
635 Boggle Game
634 Word Squares


202 Segment Tree Query
247 Segment Tree Query II
201 Segment Tree Build
439 Segment Tree Build II
203 Segment Tree Modify
205 Interval Minimum Number
206 Interval Sum
207 Interval Sum II
248 Count of Smaller Number
249 Count of Smaller Number Before itself249 Count of Smaller Number Before itself


```
