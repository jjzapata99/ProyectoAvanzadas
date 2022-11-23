from pymongo import MongoClient
import pandas as pd
import datetime

client = MongoClient('mongodb://0.0.0.0:8801/')
db_scan= client['scan']
c_temperature= db_scan['temperature']
c_address = db_scan['address']
def exist(ip):
    query={'_id':ip}
    dt_q=pd.DataFrame(list(c_address.find(query)))
    return  len(dt_q)

def updateIp(ip='0.0.0.0'):
    ex =exist(ip)
    if(ex==0):
        c_address.insert_one({ "_id": ip ,"nombre": "Juan", "direccion": "C/ Mayor 1" })
def deleteIp(ip='0.0.0.0'):
    ex =exist(ip)
    if(ex>0):
        c_address.delete_one({'_id': ip})

def sensor(degree= 0):
    c_temperature.insert_one({'createAt':datetime.datetime.now(), 'temperature': degree})
