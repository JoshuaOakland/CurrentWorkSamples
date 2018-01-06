"""
	Author: Joshua Louch

	Purpose: Alert configurable person's of interest in the event a target disk or disks is/are 			approaching a threshold. Target Platform Linux OS supporting df command and python 2.7+

	Date: 01-08-2018

	License: 

Copyright (c) 2018 Joshua Louch

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
"""

class SpatialAlert():
	def __init__(self, notification = 'Something bad has happened', recipient_list = []):
		self.message = notification
		self.recipients = recipient_list
	def __str__(self):
		return("{0} {1}".format(self.message,self.recipients))
	def __repr__(self):
		return self.__str__()

class SpatialSubscriber():
	def __init__(self, address = "admin@example.com", delivery_method = "email"):
		self.address = address
		self.delivery_method = delivery_method
	def __str__(self):
		return("Subscriber: {0} Delivery Method: {1}".format(self.address,self.delivery_method))
	def __repr__(self):
		return self.__str__()

class SpatialConfiguration():
	def __init__(self, logging = False, dumbfire = True, pollrate = 10, lifetime = 0):
		self.logging = logging
		self.dumbfire = dumbfire
		self.pollrate = pollrate
		self.lifetime = lifetime

class SpatialEmailConfiguration():
	def __init__(self, server_address = "smtp.example.com", server_port = 587, spatial_bot_address = "spatialbot@example.com", spatial_bot_password = "1234"):
		self.server_address = server_address
		self.server_port = server_port
		self.spatial_bot_address = spatial_bot_address
		self.spatial_bot_password = spatial_bot_password
