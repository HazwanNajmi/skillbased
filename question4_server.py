import socket
import threading
import random


quotes = [
    "Believe you can and you're halfway there. - Theodore Roosevelt",
    "The only limit to our realization of tomorrow will be our doubts of today. - Franklin D. Roosevelt",
    "You miss 100% of the shots you don't take. - Wayne Gretzky",
    "The only way to do great work is to love what you do. - Steve Jobs",
    "Life is 10% what happens to us and 90% how we react to it. - Charles R. Swindoll",   
    "Be yourself; everyone else is already taken. - Oscar Wilde",
    "In three words I can sum up everything I've learned about life: it goes on. - Robert Frost",
    "The best way to predict the future is to create it. - Peter Drucker",
    "The only thing standing between you and your goal is the story you keep telling yourself as to why you can't achieve it. - Jordan Belfort",
    "Life is 10% what happens to us and 90% how we react to it. - Charles R. Swindoll"]

def handle_c(c_socket):
    quote = random.choice(quotes)
    c_socket.send(quote.encode())
    c_socket.close()

def main():
    s_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s_host = '192.168.65.134'  
    s_port = 8888

    s_socket.bind((s_host, s_port))
    s_socket.listen(5)

    print("Server is listening on port", s_port)

    while True:
        c_socket, c_address = s_socket.accept()
        print("Connected to client of:", c_address)

        c_thread = threading.Thread(target=handle_c, args=(c_socket,))
        c_thread.start()

if __name__ == "__main__":
    main()

