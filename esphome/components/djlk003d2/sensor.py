import esphome.codegen as cg
from esphome.components import sensor, uart
from esphome.const import (
    STATE_CLASS_MEASUREMENT,
    UNIT_METER,
    ICON_ARROW_EXPAND_VERTICAL,
    DEVICE_CLASS_DISTANCE,
)

DEPENDENCIES = ["uart"]

djlk003d2_ns = cg.esphome_ns.namespace("djlk003d2")
Djlk003d2Component = djlk003d2_ns.class_(
    "Djlk003d2Component", sensor.Sensor, cg.Component, uart.UARTDevice
)

CONFIG_SCHEMA = sensor.sensor_schema(
    Djlk003d2Component,
    unit_of_measurement=UNIT_METER,
    icon=ICON_ARROW_EXPAND_VERTICAL,
    accuracy_decimals=3,
    state_class=STATE_CLASS_MEASUREMENT,
    device_class=DEVICE_CLASS_DISTANCE,
).extend(uart.UART_DEVICE_SCHEMA)

FINAL_VALIDATE_SCHEMA = uart.final_validate_device_schema(
    "djlk003d2",
    baud_rate=9600,
    require_tx=False,
    require_rx=True,
    data_bits=8,
    parity=None,
    stop_bits=1,
)


async def to_code(config):
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)
