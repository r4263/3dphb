import socket

multicast_group = '227.77.77.7'
port = 12345

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
group = socket.inet_aton(multicast_group)

sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, group + socket.inet_aton('10.0.0.249'))

print(f"Juntou-se ao grupo multicast {multicast_group} na porta {port}")

input("Pressione Enter para sair...")
sock.close()
