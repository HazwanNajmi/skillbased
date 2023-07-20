import socket
def bar_to_atmosphere(press_bar):
    return press_bar * 0.986923

def main():
    s_host = '192.168.65.134'  
    s_port = 8443
    s_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s_socket.bind((s_host, s_port))
    s_socket.listen(1)

    print("Server is waiting for a connection...")

    connection, address = s_socket.accept()
    print("Connected to client with IP address of:", address)

    while True:
        try:
            data = connection.recv(1024)
            if not data:
                break

            press_bar = float(data.decode())
            atmosphere_standard = bar_to_atmosphere(press_bar)
            connection.send(str(atmosphere_standard).encode())

        except ValueError:
            connection.send(b"You have entered wrong input. Please enter a valid pressure value in bar.")

    connection.close()
    s_socket.close()

if __name__ == "__main__":
    main()

