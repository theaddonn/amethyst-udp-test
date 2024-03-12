# Amethyst UDP Test

This a repo containing example code for amethyst to impl a udp connection to an extern server and send messages.

**This is just a TEST!**

No Production/Ready to use code is provided here, this is just code to show how networking with amethyst can be done.

## How does it work?

Minecraft Bedrock Edition is an uwp (Universal Windows Platform) app, that means it is mostly sandboxed and doesn't have access to most windows apis.

We normally use a windows lib like `winsock` for windows to connected to/create servers.

But due to it being an uwp app, we need to use the winrt.

## How do I test it?

*Install [Amethyst](https://github.com/FrederoxDev/Amethyst) if not done already*

1. Start a UDP server on 127.0.0.1:12345
   (My Python Server as an example) 
    ```python
    import socket

    # Define server IP address and port
    SERVER_IP = "127.0.0.1"
    SERVER_PORT = 12345
    
    # Create a UDP socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    
    # Bind the socket to the server address
    server_socket.bind((SERVER_IP, SERVER_PORT))
    
    print(f"UDP server is listening on {SERVER_IP}:{SERVER_PORT} ...")
    
    while True:
    # Receive data from the client
    data, client_address = server_socket.recvfrom(1024)
    
        # Decode the received data
        received_message = data.decode('utf-8')
    
        # Print the received message and client address
        print(f"Received message from {client_address}: {received_message}")
    ```
2. Launch the Mods using Amethyst and join your world.
3. You should recieve certain send messages like in my example these:
   ```
   UDP server is listening on 127.0.0.1:12345 ...
   Received message from ('127.0.0.1', 53583): Mod init
   Received message from ('127.0.0.1', 53583): Player joined world!
   Received message from ('127.0.0.1', 53583): Player left world!
   ```
   
   
