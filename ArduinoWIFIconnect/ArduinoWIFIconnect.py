import socket
import curses
# import argparse
from curses import wrapper

hello_msg = """
=============(Arduino WifiConnect)============
Welcome to Arduino WifiConnect!!!
To get the necessary module data, enter the
required commands.
==============================================
"""

desc = """
This programm connects to my Wi-Fi module that works with arduino.
You can change host and port to connect to the module
(by default: host = 192.168.4.1, port = 8091)
"""

def main(stdscr):

    stdscr.scrollok(1)
    stdscr.addstr(hello_msg)
    curses.echo()

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind(("0.0.0.0", 8090))
    sock.connect(("192.168.4.1", 8091))

    while True:
        stdscr.addstr("(^-^) ")
        data = stdscr.getstr()

        if data == b"exit" or data == b"q":
            break

        sock.send(data)

        if data == b"trace":

            curses.noecho()
            stdscr.nodelay(True)

            while stdscr.getch() != ord('q'):
                data = sock.recv(1024)
                stdscr.addstr("\n=====")
                stdscr.addstr("\n{}\n".format(data.decode('utf-8')))
                stdscr.addstr("=====\n")

            curses.echo()
            stdscr.nodelay(False)
            sock.send(b"quit")

        else:
            data = sock.recv(1024)
            stdscr.addstr("\n{}\n\n".format(data.decode('utf-8')))

    stdscr.addstr("\nClose connection ...")
    sock.close()


wrapper(main)
