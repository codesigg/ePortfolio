from pymongo import MongoClient
from bson.objectid import ObjectId
    
class AnimalShelter(object):
    """ CRUD operations for Animal collection in MongoDB """
    
    def __init__(self, username, password):
        # Initializing the MongoClient. This helps to 
        # access the MongoDB databases and collections. 
        USER = username
        PASS = password
        HOST = 'nv-desktop-services.apporto.com'
        PORT = 30405
        DB ='aac'
        COL = 'animals'
        self.client = MongoClient('mongodb://%s:%s@%s:%d' %(USER,PASS,HOST,PORT))
        self.database = self.client['%s' % (DB)]
        self.collection = self.database['%s' % (COL)]
        
    # Complete this create method to implement the C in CRUD
    def create(self, data):
        if data is not None:
            self.database.animals.insert_one(data)  # data should be dictionary
            return True    
        else:
            print("Nothing to save, because data parameter is empty")
            return False
            
            
    # Complete this create method to implement the R in CRUD
    def read(self, criteria=None):
        if criteria is not None:
            return self.database.animals.find(criteria)
            #for document in data:
            #    print(document)
            
        else:
            return False
        #return data
    
    #Create method to implement the U the CRUD.
    def update(self, searchData, updateData):
        if searchData is not None:
            result = self.database.animals.update_many(searchData, { "$set": updateData })
        else:
            return "{}"
        #Return the dataset else let the error flow up
        return result.raw_result
    
    #Create method to implement the D in CRUD.
    def delete(self, deleteData):
        if deleteData is not None:
            result = self.database.animals.delete_many(deleteData)
        else:
            return "{}"
        #Return the dataset else let the error flow up
        return result.raw_result
