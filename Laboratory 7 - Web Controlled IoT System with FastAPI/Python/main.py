from fastapi import FastAPI, HTTPException
from fastapi.middleware.cors import CORSMiddleware
import serial
import time
import sys

app = FastAPI()

# --- CONFIGURATION ---
# UPDATE THIS PORT! (Check Arduino IDE > Tools > Port)
SERIAL_PORT = 'COM7'  # Windows example: 'COM3', Mac/Linux: '/dev/ttyUSB0'
BAUD_RATE = 9600

app = FastAPI()
arduino = None

# --- LIFECYCLE EVENTS ---
@app.on_event("startup")
async def startup_event():
    """
    Initializes the Serial connection when the server starts.
    We verify the connection to ensure the system is ready.
    """
    global arduino
    try:
        arduino = serial.Serial(port=SERIAL_PORT, baudrate=BAUD_RATE, timeout=1)
        # Wait a moment for Arduino to reset after connection
        time.sleep(2) 
        print(f"Connected to Arduino on {SERIAL_PORT}")
    except serial.SerialException as e:
        print(f"Failed to connect to Arduino: {e}")
        print("Please check your port settings in the code.")
        sys.exit(1)

@app.on_event("shutdown")
async def shutdown_event():
    """Closes the serial connection when the server stops."""
    if arduino and arduino.is_open:
        arduino.close()
        print("Serial connection closed.")

# --- API ENDPOINTS ---

@app.get("/")
def read_root():
    return {"message": "Arduino LED Controller API is running."}

@app.get("/led/on")
def turn_all_on():
    """Turns all LEDs ON."""
    if arduino:
        arduino.write(b'9') # Sends '9' to Arduino (Our helper command for All ON)
        return {"status": "All LEDs turned ON"}
    raise HTTPException(status_code=500, detail="Arduino not connected")

@app.get("/led/off")
def turn_all_off():
    """Turns all LEDs OFF."""
    if arduino:
        arduino.write(b'0') # Sends '0' to Arduino (Our helper command for All OFF)
        return {"status": "All LEDs turned OFF"}
    raise HTTPException(status_code=500, detail="Arduino not connected")

@app.get("/led/{color}")
def control_led(color: str):
    """
    Controls specific LEDs.
    color: 'red', 'green', or 'blue'
    """
    if not arduino:
        raise HTTPException(status_code=500, detail="Arduino not connected")

    # Normalize input to lowercase to ensure case-insensitivity
    color = color.lower()

    if color == "red":
        arduino.write(b'1') # Sends '1' to Arduino
        return {"status": "Red LED toggled", "command_sent": "1"}
    elif color == "green":
        arduino.write(b'2') # Sends '2' to Arduino
        return {"status": "Green LED toggled", "command_sent": "2"}
    elif color == "blue":
        arduino.write(b'3') # Sends '3' to Arduino
        return {"status": "Blue LED toggled", "command_sent": "3"}
    else:
        raise HTTPException(status_code=400, detail="Invalid color. Use red, green, or blue.")
    
app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],  # Allows all origins
    allow_credentials=True,
    allow_methods=["*"],  # Allows all methods (GET, POST, etc.)
    allow_headers=["*"],
)
