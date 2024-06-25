import socket, time
udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
udp_socket.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 2)
i=0

while True:
    udp_socket.sendto(bytes(1010), ('227.77.77.7', 12345))
    time.sleep(0.25)

udp_socket.close()