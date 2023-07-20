import socket
def main ():
    s_host = '192.168.65.134'  
    s_port = 8443
    c_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)     
    c_socket.connect((s_host, s_port))

    try:
        press_bar = float (input("Please enter pressure value in bar: "))
        c_socket.send(str(press_bar).encode())

        atmosphere_standard = c_socket.recv(1024).decode()
        print("The Atmosphere-Standard Value is: ", atmosphere_standard)

    except ValueError:
        print("You have entered wrong input. Please enter a valid pressure value in bar.")

    c_socket.close()

if __name__ == "__main__":
    main()

