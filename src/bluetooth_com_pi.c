import asyncio
from bleak import BleakClient, BleakScanner

ESP32_BLE_NAME = "ESP32-S3 BLE"  # Must match the ESP32-S3 advertisement name
SERVICE_UUID = "12345678-1234-5678-1234-56789abcdef0"
CHARACTERISTIC_UUID = "87654321-4321-6789-4321-abcdef987654"

async def find_esp32():
    print("Scanning for ESP32-S3 BLE device...")
    devices = await BleakScanner.discover()
    for device in devices:
        if ESP32_BLE_NAME in device.name:
            print(f"Found ESP32-S3: {device.address}")
            return device.address
    print("ESP32-S3 not found.")
    return None

async def connect_and_listen(address):
    async with BleakClient(address) as client:
        print("Connected to ESP32-S3 BLE!")

        def notification_handler(sender, data):
            print(f"Received from ESP32-S3: {data.decode()}")

        await client.start_notify(CHARACTERISTIC_UUID, notification_handler)

        while True:
            await asyncio.sleep(1)  # Keep listening

async def main():
    address = await find_esp32()
    if address:
        await connect_and_listen(address)

if __name__ == "__main__":
    asyncio.run(main())

