import serial
import time
import os
import sys

arduino_port = "COM5"

def clear_screen():
    os.system('cls' if os.name == 'nt' else 'clear')
    

def main():
    
    # 1. Setup and Checking Serial Connection
    try:
        arduino = serial.Serial(arduino_port, 9600)
        time.sleep(2) 

    except serial.SerialException:
        print(f"Error: Could not connect to {arduino_port}.")
        print("Please check your cable,, and ensure that the Arduino IDE is closed.")
        sys.exit()

    while True:
        # 2. Clear Screen and Print Menu (Nice to Have)
        clear_screen()
        print("[R] Red ON/OFF")
        print("[G] Green ON/OFF")
        print("[B] Blue ON/OFF")
        print("[A] All ON")
        print("[O] All OFF")
        print("[X] Exit")

        # 3. Get User Input
        choice = input("Enter selection: ").strip().upper()

        if choice == 'X':
            print("Terminating application...")
            arduino.close()
            sys.exit()

        # 4. Handle Valid Commands
        if choice in ['R', 'G', 'B', 'A', 'O']:
            command = choice + '\n'
            arduino.write(command.encode('utf-8'))
        else:
            print("Invalid input! Please select from the menu.")
            time.sleep(0.5)

if __name__ == "__main__":
    main()