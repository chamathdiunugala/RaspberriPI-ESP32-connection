import serial
import time

def setup_uart():
    """
    Set up UART communication with ESP32-S3
    
    Note: Disable serial console before using UART
    Use 'sudo raspi-config' -> Interfacing Options -> Serial
    Disable serial login shell, keep serial interface enabled
    """
    try:
        # Open serial port (/dev/ttyAMA0 or /dev/ttyS0 depending on Raspberry Pi model)
        ser = serial.Serial(
            port='/dev/ttyS0', 
            baudrate=115200,
            bytesize=serial.EIGHTBITS,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            timeout=1
        )
        return ser
    except Exception as e:
        print(f"Error setting up UART: {e}")
        return None

def main():
    # Set up UART
    ser = setup_uart()
    if not ser:
        return
    
    try:
        while True:
            # Send message to ESP32
            message = "Hello from Raspberry Pi!"
            ser.write((message + '\n').encode('utf-8'))
            print(f"Sent: {message}")
            
            # Check for incoming messages
            if ser.in_waiting:
                received = ser.readline().decode('utf-8').strip()
                print(f"Received: {received}")
            
            time.sleep(2)
    
    except KeyboardInterrupt:
        print("Communication stopped")
    
    finally:
        # Close the serial port
        if ser:
            ser.close()

if __name__ == "__main__":
    main()
