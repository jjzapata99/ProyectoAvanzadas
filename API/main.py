from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from back import *
app = FastAPI(
    title= 'Monitoreo', description= 'Api para la carga de datos de monitoreo', version= '1.1.0'
)
origins = [
    "http://localhost",
    "http://localhost:4200",
    "http://localhost:4200/*",
    "https://web.postman.co/*"
]
app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)
@app.post('/address/on')
async def post(ip : str ):
    updateIp(ip)
@app.post('/address/off')
async def post(ip : str ):
    deleteIp(ip)
@app.post('/temperature')
async def post(degrees : int ):
    sensor(degrees)
