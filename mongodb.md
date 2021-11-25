| RDBMS       | MongoDB                                         |
| ---         | ---                                             |
| Database    | Database                                        |
| Table       | Collection                                      |
| Tuple/Row   | Document                                        |
| Column      | Field                                           |
| Table Join  | Embedded Documents                              |
| Primary Key | Primary Key(Default key_id provided by mongodb) |

* to use mongodb: mongo

* help: db.help()

* statistics: db.stats()

* to create/use database: use mydb

* to check current selected db: db

* to check db list: show dbs

* insert one document to db: db.movie.insert({"name": "tutorials [points](poits)"})

* to delete a db: db.dropDatabase()

* to create collection: db.createCollection(name, options)
>use test
>db.createCollection("mycollection")
>db.createCollection("mycol", {capped: true, autoIndexId: true, size: 6142800, max: 10000})
>db.tutorialspoint.insert({"name": "tutorialspoint"})

* to check collection list: show collections
 
* to drop collection: db.collection.drop()
>db.mycollection.drop()

* _id: ObjectId(4 bytes timestamp, 3 bytes machine id, 2 bytes process id, 3 bytes incrementer)

* datatype
    - string
    - integer
    - boolean
    - double
    - min/max keys
    - arrays
    - timestamp
    - object
    - null
    - symbol
    - date
    - object id
    - binary data
    - code
    - regular expression


* to insert document: 
>db.post.insert({
title: 'MongoDB Overview', 
description: 'MongoDB is no sql database',
by: 'tutorials point',
url: 'http://www.tutorialspoint.com',
tags: ['mongodb', 'database', 'NoSQL'],
likes: 100
})


* another way to insert document:
>db.post.save(document)


