# Raspberry Pi Server Code (Python)
import socket
import time
from datetime import datetime

# Server configuration
HOST = '0.0.0.0'  # Listen on all available interfaces
PORT = 12345      # Port to listen on

def start_server():
    # Create a TCP/IP socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    # Allow reuse of address
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
    # Bind the socket to the port
    server_socket.bind((HOST, PORT))
    
    # Listen for incoming connections
    server_socket.listen(1)
    
    print(f"Server started on {HOST}:{PORT}")
    
    try:
        while True:
            # Wait for a connection
            print("Waiting for connection...")
            client_socket, client_address = server_socket.accept()
            
            try:
                print(f"Connected to {client_address}")
                
                # Receive data
                data = client_socket.recv(1024).decode('utf-8').strip()
                if data:
                    print(f"Received: {data}")
                    
                    # Send response
                    timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
                    response = f"Message received by Raspberry Pi at {timestamp}\n"
                    client_socket.sendall(response.encode('utf-8'))
                    print(f"Sent: {response}")
            
            finally:
                # Clean up the connection
                client_socket.close()
                print("Connection closed")
    
    except KeyboardInterrupt:
        print("\nShutting down server...")
    
    finally:
        server_socket.close()
        print("Server closed")

if __name__ == "__main__":
    start_server()