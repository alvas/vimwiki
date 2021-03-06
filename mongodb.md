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


* to query data from collection:
>db.mycol.find.pretty()


* to return only one document from query:
>db.mycol.findOne().pretty()


* RDBMS Where Clause Equivalents in MongoDB
    - Equality, db.mycol.find({"by": "tutorials point"}).pretty() 
    - Less Than, db.mycol.find({"likes": {$lt:50}}).pretty() 
    - Less Than Equals, db.mycol.find({"likes": {$lte:50}}).pretty() 
    - Greater Than, db.mycol.find({"likes": {$gt:50}}).pretty() 
    - Greater Than Equals, db.mycol.find({"likes": {$gte:50}}).pretty() 
    - Not Equals, db.mycol.find({"likes": {$ne:50}}).pretty()


* AND
>db.mycol.find({$and:[{"by":"tutorials point"},{"title": "MongoDB Overview"}]}).pretty()


* OR
>db.mycol.find({$or:[{"by":"tutorials point"},{"title": "MongoDB Overview"}]}).pretty()


* AND and OR together
```
db.mycol.find({"likes": {$gt:10}, $or: [{"by": "tutorials point"}, {"title": "MongoDB Overview"}]}).pretty()
```


* to update document, update() updates the values in the existing document 
>db.mycol.update({'title':'MongoDB Overview'},{$set:{'title':'New MongoDB Tutorial'}})


* to update multiple documents:
>db.mycol.update({'title':'MongoDB Overview'}, {$set:{'title':'New MongoDB Tutorial'}},{multi:true})


* save() replaces the existing document with the document passed in save() method
>db.mycol.save({ "_id" : ObjectId(5983548781331adf45ec5), "title":"Tutorials Point New Topic", "by":"Tutorials Point" })


* to delete document:
>db.mycol.remove({'title':'MongoDB Overview'})


* to remove only one:
>db.mycol.remove({'title':'MongoDB Overview'}, 1)


* remove all documents:
>db.mycol.remove({})


* projection means selecting only the necessary data rather than selecting whole of the data of a document:
>db.mycol.find({},{"title":1,_id:0})


* to limit records returning from query:
>db.mycol.find({},{"title":1,_id:0}).limit(2)


* to skip first n records returning from query:
>db.mycol.find({},{"title":1,_id:0}).limit(1).skip(1)


* to sort query:
>db.mycol.find({},{"title":1,_id:0}).sort({"title":-1})


* to create index:
>db.mycol.ensureIndex({"title":1})


* to create index on multiple fields:
>db.mycol.ensureIndex({"title":1,"description":-1})


* Aggregation operations group values from multiple documents together, and can perform a variety of operations on the grouped data to return a single result. In SQL count(*) and with group by is an equivalent of mongodb aggregation:
```
db.mycol.aggregate([{$group : {_id : "$by_user", num_tutorial : {$sum : 1}}}])
```


+ aggregation expressions:
    - $sum
    ```
    db.mycol.aggregate([{$group : {_id : "$by_user", num_tutorial : {sum : "$likes"}}})
    ```
    - $avg
    ```
    db.mycol.aggregate([{$group : {_id : "$by_user", num_tutorial : {$avg : "$likes"}}}])
    ```
    - $min
    ```
    db.mycol.aggregate([{$group : {_id : "$by_user", num_tutorial : {$min : "$likes"}}}])
    ```
    - $max
    ```
    db.mycol.aggregate([{$group : {_id : "$by_user", num_tutorial : {$max : "$likes"}}}])
    ```
    - $push, inserts the value to an array in the resulting document.
    ```
    db.mycol.aggregate([{$group : {_id : "$by_user", url : {$push: "$url"}}}])
    ```
    - $addToSet, inserts the value to an array in the resulting document but does not create duplicates.
    ```
    db.mycol.aggregate([{$group : {_id : "$by_user", url : {$addToSet : "$url"}}}])
    ```
    - $first, gets the first document from the source documents according to the grouping. 
    ```
    db.mycol.aggregate([{$group : {_id : "$by_user", first_url : {$first : "$url"}}}])
    ```
    - $last, gets the last document from the source documents according to the grouping.
    ```
    db.mycol.aggregate([{$group : {_id : "$by_user", last_url : {$last : "$url"}}}])
    ```
    
    
* There is a set of possible stages and each of those is taken as a set of documents as an input and produces a resulting set of documents 
```
    - $project
    - $match
    - group
    - $sort
    - $skip
    - $limit
    - $unwind

```


* setup a replica set
$mongod --port 27017 --dbpath "/var/lib/mongodb" --replSet rs0 --quiet

    + in Mongo client, issue the command rs.initiate() to initiate a new replica set
    + to check replica set configuration, issue the command rs.conf()
    + to check the status of replica set, issue the command rs.status()


* to add member to replica set:
>rs.add("192.168.1.51:27017")


* to create backup:
$mongodump


* to restore from backup:
$mongorestore


* deployment
    + mongostat
    + mongotop


* relationship
Relationships in MongoDB represent how various documents are logically related to each other. Relationships can be modeled via Embedded and Referenced approaches. Such relationships can be either 1:1, 1:N, N:1 or N:N.


* references
    + DBRefs 
        - $ref
        - $id
        - $db
    + Manual References


* covered query 
>db.users.ensureIndex({gender:1,user_name:1})


* analyzing quey 
Analyzing queries is a very important aspect of measuring how effective the database and indexing design is. 

>db.users.find({gender:"M"},{user_name:1,_id:0}).explain()

>db.users.find({gender:"M"},{user_name:1,_id:0}).hint({gender:1,user_name:1})


* atomic operation

```
>db.products.findAndModify({ 
   query:{_id:2,product_available:{$gt:0}}, 
   update:{ 
      $inc:{product_available:-1}, 
      $push:{product_bought_by:{customer:"rob",date:"9-Jan-2014"}} 
   }    
})
```

* advanced indexing
```
{
   "address": {
      "city": "Los Angeles",
      "state": "California",
      "pincode": "123"
   },
   "tags": [
      "music",
      "cricket",
      "blogs"
   ],
   "name": "Tom Benzamin"
}
```

* indexing array fields:
 
>db.users.ensureIndex({"tags":1})
>db.users.find({tags:"cricket"})

* indexing sub-document fields:
>db.users.ensureIndex({"address.city":1,"address.state":1,"address.pincode":1})
>db.users.find({"address.city":"Los Angeles"})   


* ObjectId
An ObjectId is a 12-byte BSON type having the following structure:
+ The first 4 bytes representing the seconds since the unix epoch
+ The next 3 bytes are the machine identifier
+ The next 2 bytes consists of process id
+ The last 3 bytes are a random counter value


* to generate a new ObjectId:
>newObjectId = ObjectId()


* to provide an ObjectId:
>myObjectId = ObjectId("5349b4ddd2781d08c09890f4")


* fetch creation time of a document:
>ObjectId("5349b4ddd2781d08c09890f4").getTimestamp()


* to convert ObjectId to string:
>newObjectId.str


* map reduce:
```
>db.collection.mapReduce(
   function() {emit(key,value);},  //map function
   function(key,values) {return reduceFunction}, {   //reduce function
      out: collection,
      query: document,
      sort: document,
      limit: number
   }
)

>db.posts.mapReduce( 
   function() { emit(this.user_id,1); }, 
	
   function(key, values) {return Array.sum(values)}, {  
      query:{status:"active"},  
      out:"post_total" 
   }
)
```

* text search
```
{
   "post_text": "enjoy the mongodb articles on tutorialspoint",
   "tags": [
      "mongodb",
      "tutorialspoint"
   ]
}
```

* to create text index on post_text field:
>db.posts.ensureIndex({post_text:"text"})


* to use text index:
>db.posts.find({$text:{$search:"tutorialspoint"}})


* to find name of text index:
>db.posts.getIndexes()


* to delete text index:
>db.posts.dropIndex("post_text_text")


* to use regex expression
>db.posts.find({post_text:{$regex:"tutorialspoint"}})
>db.posts.find({post_text:/tutorialspoint/})


* to use regex expression with case insensitive
>db.posts.find({post_text:{$regex:"tutorialspoint",$options:"$i"}})


* to use regex expression for array element
>db.posts.find({tags:{$regex:"tutorial"}})


* to store an mp3 file using GridFS
>mongofiles.exe -d gridfs put song.mp3

gridfs is database name, song.mp3 is file name

* to see file's document in database
>db.fs.files.find()


* to see fs.chunk of the file
>db.fs.chunks.find({files_id:ObjectId('534a811bf8b4aa4d33fdf94d')})




