# OOD

SOLID principles:

* S — Single responsibility principle
A Class should be responsible for a single task or a class must have a specific purpose.

* O — Open-closed principle
This principle states that Objects or entities should be open for extension, but closed for modification. This simply means that a class should be easily extendable without modifying the class itself
 
* L — Liskov substitution principle
Liskov substitution principle says every class that inherit from a parent class, must not replicate functionality already implemented in the parent class.
Then the parent class should be able to be replaced by any of its subclasses in any region of the code.

* I — Interface segregation principle
Interface segregation principle states that many specialized interfaces are better than one universal. In other words we can say this also that client must not be forced to implement an interface that it doesn’t use. So the main purpose is to divide the interfaces so that they are more specific.

* D — Dependency Inversion Principle
Dependency inversion principle states that: 1. High level modules should not depend on low-level modules, both should depend on abstractions. 2. Abstractions should not depend on details. Details should depend on abstractions. Or it can be rephrases as “the dependencies should be based on abstractions, not details.”


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



# Dynamo: How to Design a Key-value Store

# Cassandra: How to Desing a Wide-column NoSQL Database

# Kafka: How to Design a Distributed Messaging System

# Chubby: How to Design a Distributed Locking Service

# GFS: How to Design a Distributed File Storage System

# HDFS: How to Design a Distributed File Storage System

# BitTable: How to Design a Wide-column Storage System




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
249 Count of Smaller Number Before itself


575 Decode String
363 Trapping Rain Water
12 Min Stack
360 Sliding Window Median
364 Trapping Rain Water II
510 Maximal Rectangle
126 Max Tree
122 Largest Rectangle in Histogram
81 Find Median from Data Stream
475 Binary Tree Maximum Path Sum II
370 Convert Expression to Reverse Polish Notation
369 Convert Expression to Polish Notation
130 Heapify
40 Implement Queue by Two Stacks
623 K Edit Distance
367 Expression Tree Build
368 Expression Evaluation


141 Sqrt
586 Sqrt(x) II
183 Wood Cut
437 Copy Books
438 Copy Books II
633 Find the Duplicate Number
617 Maximum Average Subarray II
919 Meeting Rooms II
591 Number of Airplanes in the Sky
414 Divide Two Integers
75 Find Peak Element
390 Find Peak Element II
362 Sliding Window Maximum
821 Time Intersection
74 First Bad Version
600 Smallest Rectangle Enclosing Black Pixels
131 The Skyline Problem
920 Meeting Rooms
868 Maximum Average Subarray


453 Flatten Binary Tree to Linked List
22 Flatten List
138 Subarray Sum
404 Subarray Sum II
139 Subarray Sum Closest
405 Submatrix Sum
404 Subarray Sum II
406 Minimum Size Subarray Sum
528 Flatten Nested List Iterator
399 Nuts & Bolts Problem
402 Continuous Subarray Sum
403 Continuous Subarray Sum II
400 Maximum Gap
401 Kth Smallest Number in Sorted Matrix
75 Find Peak Element
588 Sliding Window Matrix Maximum
86 Binary Search Tree Iterator
551 Nested List Weight Sum
601 Flatten 2D Vector
553 Bomb Enemy
541 Zigzag Iterator II
540 Zigzag iterator
574 Build Post Office
573 Build Post Office II
390 Find Peak Eelement II



```
