from microbit import *
import bluetooth


def on_data_received():
    data = bluetooth.read()
    if data:
        display.scroll(data)


def on_connected():
    display.show(Image.HAPPY)


def on_disconnected():
    display.show(Image.SAD)


def scan_and_connect():
    display.show(Image.HEART)
    while True:
        devices = bluetooth.scan(5)
        for device in devices:
            if "keyboard" in device[1]:
                display.show(Image.ARROW_W)
                bluetooth.connect(device[0])
                return
        display.show(Image.HEART)


bluetooth.on_data_received(on_data_received)
bluetooth.on_connected(on_connected)
bluetooth.on_disconnected(on_disconnected)

scan_and_connect()
