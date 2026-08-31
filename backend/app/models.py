from datetime import datetime
from typing import Literal

from pydantic import BaseModel, ConfigDict, Field


class SensorHealth(BaseModel):
    model_config = ConfigDict(extra="forbid")

    initialized: bool
    valid: bool
    stale: bool
    consecutive_failures: int = Field(ge=0)
    total_failures: int = Field(ge=0)


class Environment(BaseModel):
    model_config = ConfigDict(extra="forbid")

    temperature_c: float | None
    humidity_percent: float | None
    pressure_hpa: float | None
    light_lux: float | None
    uv_index: float | None


class Particulate(BaseModel):
    model_config = ConfigDict(extra="forbid")

    pm1_ugm3: float | None
    pm25_ugm3: float | None
    pm10_ugm3: float | None


class Wind(BaseModel):
    model_config = ConfigDict(extra="forbid")

    speed_mps: float | None = Field(default=None, ge=0)
    status: Literal["OK", "CHECK", "TIMEOUT", "STALE", "NOT CONNECTED"] = "NOT CONNECTED"
    last_modbus_result: int | None = Field(default=None, ge=0, le=255)


class Gnss(BaseModel):
    model_config = ConfigDict(extra="forbid")

    state: Literal[
        "NOT CONNECTED",
        "COMMUNICATION OK - NO FIX",
        "FIX VALID",
        "FIX STALE",
    ] = "NOT CONNECTED"
    communication_ok: bool = False
    fix_valid: bool = False
    utc: datetime | None = None
    latitude: float | None = Field(default=None, ge=-90, le=90)
    longitude: float | None = Field(default=None, ge=-180, le=180)
    altitude_m: float | None = None
    satellites: int | None = Field(default=None, ge=0)
    speed_kmph: float | None = Field(default=None, ge=0)
    course_deg: float | None = Field(default=None, ge=0, le=360)
    mode: str | None = Field(default=None, max_length=40)
    last_successful_fix_ms: int | None = Field(default=None, ge=0)


class Health(BaseModel):
    model_config = ConfigDict(extra="forbid")

    sht4x: SensorHealth
    bmp180: SensorHealth
    bh1750: SensorHealth
    ltr390: SensorHealth
    pms7003: SensorHealth
    wind_speed: SensorHealth = Field(default_factory=lambda: SensorHealth(
        initialized=False,
        valid=False,
        stale=True,
        consecutive_failures=0,
        total_failures=0,
    ))


class Measurement(BaseModel):
    model_config = ConfigDict(extra="forbid")

    schema_version: str = Field(pattern=r"^weather\.measurement\.v1$")
    station_id: str = Field(min_length=1, max_length=80)
    firmware_version: str = Field(min_length=1, max_length=40)
    uptime_ms: int = Field(ge=0)
    device_timestamp: datetime | None = None
    environment: Environment
    particulate: Particulate
    wind: Wind = Field(default_factory=Wind)
    gnss: Gnss = Field(default_factory=Gnss)
    health: Health
