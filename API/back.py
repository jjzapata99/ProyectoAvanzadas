from pymongo import MongoClient
import pandas as pd
import datetime
import pytz

client = MongoClient('mongodb://200.126.14.228:8801/')
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
        c_address.insert_one({ "_id": ip ,"sensedAt": datetime.datetime.now(pytz.utc) })
def deleteIp(ip='0.0.0.0'):
    ex =exist(ip)
    if(ex>0):
        c_address.delete_one({'_id': ip})

def sensor(degree='0'):
    c_temperature.insert_one({'createAt':datetime.datetime.now(pytz.utc), 'temperature': degree})


def getScanPc():
    dt_pcs= pd.DataFrame(list(c_address.find()))
    return dt_pcs
def getScanSensor(init_date, end_date):
    query= {'createAt':{'$gte': datetime.datetime.strptime(init_date, '%d/%m/%Y'), '$lt': datetime.datetime.strptime(end_date+  " 23:59:59", '%d/%m/%Y %H:%M:%S')}}

    dt_sensor= pd.DataFrame(list(c_temperature.find(query)))
    dt_sensor['_id'] = dt_sensor['_id'].astype('|S')
    return dt_sensor[["temperature","createAt","_id"]].to_dict(orient='records')



