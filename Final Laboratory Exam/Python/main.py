import serial
import requests
import time
import sys

# ===== CONFIG =====
SERIAL_PORT = "COM7"      # Change to your Arduino port (e.g., /dev/ttyUSB0 for Linux)
BAUD_RATE = 9600
BASE_URL = "http://172.20.10.3:8000"  # Replace with instructor's API base URL

print("Starting Arduino-to-API Client...")
print("Listening on serial port:", SERIAL_PORT)

try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    time.sleep(2)
except:
    print("ERROR: Could not open serial port.")
    sys.exit()

while True:
    try:
        if ser.in_waiting > 0:
            raw_data = ser.readline().decode('utf-8').strip()

            if raw_data.isdigit():
                group_number = raw_data.lower().strip()
                endpoint = f"/led/group/{group_number}/toggle"
                full_url = BASE_URL + endpoint

                print("\nGroup Received:", group_number)
                print("Calling Endpoint:", endpoint)

                try:
                    response = requests.get(full_url)
                    if response.status_code == 200:
                        print("API Response: SUCCESS")
                        print("Server Message:", response.text)
                    else:
                        print("API Response: ERROR", response.status_code)
                        print("Server Message:", response.text)

                except requests.exceptions.RequestException as e:
                    print("API Connection Error:", e)

            else:
                print("Invalid Serial Input:", raw_data)

    except KeyboardInterrupt:
        print("\nProgram terminated by user.")
        sys.exit()
        

    except Exception as e:
        print("Unexpected Error:", e)
        ser.close()