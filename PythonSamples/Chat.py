import Framework.Lang
import threading
import socket

class Chat_Client():
	'Send and receive chat messages'
	def __init__(self, ip_address, port = 8787):
		'Default port dynamic address'
		self.c_socket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
		self.c_socket.bind((ip_address,port))
		self.outgoing_messages = []
		self.port_open = False
	def connect_to_chat_server(self,address):
		self.c_server = address
	def get_chat_message(self):
		message = input(">>")
		self.outgoing_messages.append(message.encode('utf-8'))
	def send(self,message):
		self.c_socket.sendto(message,self.c_server)
	def receive(self):
		self.port_open = True
		self.filter_message(self.c_socket.recvfrom(512))
		self.port_open = False
	def parse_message(self,message):
		commands = message.split(Lang.sep)
		command_type = commands[0]
		if (command_type == Lang.connect_to_server):
			ip_address = commands[1].decode('utf-8')
			port = int(commands[2].decode('utf-8'))
			server_address = (ip_address,port)
			self.connect_to_chat_server(server_address)
		elif (command_type == Lang.chat_message):
			chat_message = commands[1].decode('utf-8')
			print(chat_message)#Nothing else for now.
	def filter_message(self,message):
		return(True)#Add security for chat and validation
	def run_threaded(self):
		while (self.listening):
			if(not self.port_open):
				threading.Thread(group = None, target = self.receive).start()
			if(self.outgoing_messages):
				threading.Thread(group = None, target = self.send, args = (self.outgoing_messages.pop(),)).start()
	
class Chat_Server():
	'Relay and filter for Clients, basically a bytestring proxy'
	def __init__(self,ip_address,port):
		self.address = (ip_address,port)
		self.sender = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
		self.receiver = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
		self.receiver.bind(self.address)
		self.clients = set()#addresses
		self.client_names = dict()#[client_address] = name
		self.port_open = False
		self.listening = True
		self.main_server = ''
	def add_as_server(self,server_address):
		self.main_server = server_address
	def add_client(self,client,name):
		self.client_names[client] = name
		self.clients.add(client)
	def remove_client(self,client):
		self.clients.remove(client)
		self.client_names.pop(client)
	def send(self, message, client):
		self.sender.sendto(message,client)
	def broadcast(self,message):
		for client in self.clients:
			self.send(message,client)
	def receive(self):
		self.port_open = True
		self.filter(self.receiver.recvfrom(512))
		self.port_open = False
	def parse_client_command(self, message):
		commands = message.split(Lang.sep)
		command_type = commands[0]
		name = commands[1]
		ip_address = commands[2].decode('utf-8')
		port = int(commands[3].decode('utf-8'))
		client = (ip_address,port)
		if (command_type == Lang.add_chat_client):
			self.add_client(client,name)
		elif (command_type == Lang.remove_chat_client):
			self.remove_client(client)
	def filter(self, message):
		client = message[1]
		if(client not in self.clients):
			return(False)
		elif(client is self.main_server):
			self.parse_client_command(message[0])
			return(True)
		else:
			self.add_message_to_updates(message)
			return(True)
	def add_message_to_updates(self, message):
		name = self.client_names.get(message[1])
		content = message[0]
		update = name+b' says: '+content
		self.updates.append(update)
	def run_threaded(self):
		while(self.listening):
			if(not self.port_open):
				threading.Thread(group = None, target = self.receive).start()
			if(self.updates):
				threading.Thread(group = None, target = self.broadcast, args = (self.updates.pop(),)).start()

