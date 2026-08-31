import os
from datetime import datetime
from pathlib import Path

from fastapi import FastAPI, HTTPException, Query
from fastapi.responses import FileResponse
from fastapi.staticfiles import StaticFiles

from .database import Database, to_utc_text
from .models import Measurement


APP_DIR = Path(__file__).parent
STATIC_DIR = APP_DIR / "static"


def create_app(database_path: str | Path | None = None) -> FastAPI:
    db_path = database_path or os.getenv("WEATHER_DB_PATH", APP_DIR.parent / "weather.db")
    database = Database(db_path)
    database.initialize()

    application = FastAPI(title="Solar Weather Station API", version="0.4.0")
    application.state.database = database
    application.mount("/static", StaticFiles(directory=STATIC_DIR), name="static")

    @application.get("/", include_in_schema=False)
    def dashboard():
        return FileResponse(STATIC_DIR / "index.html")

    @application.post("/api/v1/measurements", status_code=201)
    def post_measurement(measurement: Measurement):
        result = database.insert(measurement)
        return {"status": "stored", **result}

    @application.get("/api/v1/measurements/latest")
    def get_latest(station: str | None = Query(default=None, max_length=80)):
        measurement = database.latest(station)
        if measurement is None:
            raise HTTPException(status_code=404, detail="no measurements found")
        return measurement

    @application.get("/api/v1/measurements")
    def get_history(
        station: str | None = Query(default=None, max_length=80),
        start: datetime | None = None,
        end: datetime | None = None,
        limit: int = Query(default=1000, ge=1, le=20000),
    ):
        if start and end and to_utc_text(start) > to_utc_text(end):
            raise HTTPException(status_code=400, detail="start must not be after end")
        return database.history(station, start, end, limit)

    return application


app = create_app()
