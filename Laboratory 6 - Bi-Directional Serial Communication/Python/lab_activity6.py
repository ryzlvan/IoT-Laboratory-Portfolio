import serial
import time
import sys

# === Configuration ===
# UPDATE THIS PORT to match your system (e.g., COM3, COM7, /dev/ttyUSB0)
arduino_port = "COM3" 
baud_rate = 9600

# === Connection Setup ===
# We keep this initial check to ensure the connection starts correctly
try:
    arduino = serial.Serial(arduino_port, baud_rate, timeout=1)
    time.sleep(2)  # Allow time for Arduino to reset after connection
    print(f"Connected to {arduino_port}. Listening for Button Presses...")

except serial.SerialException:
    print(f"Error: Could not open port {arduino_port}. Check your connection.")
    sys.exit()

def send_command(command):
    """
    Sends a command to Arduino with the required newline character.
    """
    full_command = command + '\n'
    arduino.write(full_command.encode())
    arduino.flush()

# === Main Automated Relay Loop ===
# This loop is now completely infinite. 
# It has no code to handle exiting; it will run until the window is closed.
while True:
    # Check if data is waiting in the buffer
    if arduino.in_waiting > 0:
        try:
            # readline() reads until it finds '\n'
            data = arduino.readline().decode('utf-8').strip()

            if not data:
                continue

            # === Round Trip Logic ===
            if data == 'R':
                print("Received 'R' (Btn 1) -> Sending '1' (Toggle Red)")
                send_command('1')

            elif data == 'G':
                print("Received 'G' (Btn 2) -> Sending '2' (Toggle Green)")
                send_command('2')

            elif data == 'B':
                print("Received 'B' (Btn 3) -> Sending '3' (Toggle Blue)")
                send_command('3')

        except UnicodeDecodeError:
            print("Error decoding serial data. Skipping...")
            continue

    # Short delay to reduce CPU usage
    time.sleep(0.1)