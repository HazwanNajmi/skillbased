import socket

def main():
    c_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s_host = '192.168.65.134'  
    s_port = 8888

    c_socket.connect((s_host, s_port))

    received_data = c_socket.recv(1024).decode()
    print("Quote of the Day:", received_data)

    c_socket.close()

if __name__ == "__main__":
    main()

