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

* create database: use mydb

* to check current selected db: db

* to check db list: show dbs

* insert one document to db: db.movie.insert({"name": "tutorials [points](poits)"})

* to delete a db: db.dropDatabase()

* to create collection: db.createCollection(name, options)
    >use test
    >db.createCollection("mycollection")
    >db.createCollection("mycol", {capped: true, autoIndexId: true, size: 6142800, max: 10000})
    >db.tutorialspoint.insert({"name": "tutorialspoint"})

* to drop collection: db.collection.drop()
    >db.mycollection.drop()



