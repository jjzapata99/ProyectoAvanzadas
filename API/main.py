from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from back import *
from fastapi.responses import JSONResponse
from fastapi.encoders import jsonable_encoder
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
@app.get('/address/on')
async def get(ip : str ):
    updateIp(ip)
@app.get('/address/off')
async def get(ip : str ):
    deleteIp(ip)
@app.get('/temperature')
async def get(degrees : str):
    sensor(degrees)
@app.get('/getPcs')
async def get():
    json_compatible_item_data = jsonable_encoder(getScan())
    return JSONResponse(content=json_compatible_item_data)