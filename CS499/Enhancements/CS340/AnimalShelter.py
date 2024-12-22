from pymongo import MongoClient
from bson.objectid import ObjectId


class AnimalShelter(object):
    """CRUD operations for Animal collection in MongoDB"""

    def __init__(self, username, password):
        USER = username
        PASS = password
        HOST = "localhost"
        PORT = 27017
        DB = "dog_shelters"
        COL = "animals"
        self.client = MongoClient("mongodb://%s:%s@%s:%d" % (USER, PASS, HOST, PORT))
        self.database = self.client[DB]
        self.collection = self.database[COL]

    # Create method to implement the C in CRUD
    def create(self, data):
        if data is not None:
            self.database.animals.insert_one(data)
            return True
        else:
            print("Nothing to save, because data parameter is empty")
            return False

    # Read method to implement the R in CRUD
    def read(self, criteria=None):
        if criteria is not None:
            results = self.database.animals.find(criteria)
            # Convert ObjectId fields to strings
            data = []
            for item in results:
                item["_id"] = str(item["_id"])
                data.append(item)
            return data
        else:
            return []

    # Update method to implement the U in CRUD
    def update(self, searchData, updateData):
        if searchData is not None:
            result = self.database.animals.update_many(searchData, {"$set": updateData})
            return result.raw_result
        else:
            return "{}"

    # Delete method to implement the D in CRUD
    def delete(self, deleteData):
        if deleteData is not None:
            result = self.database.animals.delete_many(deleteData)
            return result.raw_result
        else:
            return "{}"
