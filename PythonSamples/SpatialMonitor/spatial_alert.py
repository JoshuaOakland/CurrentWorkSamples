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
#import necessary libraries
#tick @ frequency
#poll disk space within tick
#set sanity limit on frequency of pings to restrict any kind of massive cpu consumption
#if space low notify relevant parties
#likely imports smtp, os

valid_alert_methods = ['email']

import smtplib
from email.mime.text import MIMEText
from os import popen
from spatial_datatypes import SpatialSubscriber
from spatial_utilities import get_argument, get_integer, get_boolean, strip_comments

def alert_monitor(monitor, alert):
	'alert appropriate entity'
	print("Subscribed Monitor {0} is receiving alert {1}".format(monitor,alert))

def broadcast_alert(monitors, alert = "Disk low on space"):
	'notify every listener of event'
	for monitor in monitors:
		alert_monitor(monitor, alert)
		print("{0} {1}".format(monitor, alert))

def get_monitor(target):
	return target[0]

def get_method(target):
	return target[1]

def get_monitor_pair(target):
	return (get_monitor(target),get_method(target))


def tick():
	'get monitoring entities'
	spatial_subscribed_entities = open('monitoring_subscribers.conf','r')
	subscribed_entities = spatial_subscribed_entities.readlines()
	spatial_subscribed_entities.close()
	cycle_targets(monitor_targets,subscribed_entities)

def create_subscriber(subscriber):
	return SpatialSubscriber(address = subscriber[0], delivery_method = subscriber[1])

def get_spatial_subscribers(subscribers):
	subs = []
	for subscriber in subscribers:
		subs.append(create_subscriber(subscriber))#.split()))
	return subs

def generate_email_server_connection(host = 'smtp.example.com', port = 587):
	return smtplib.SMTP(host,port)

def authenticate_against_email_server(server, username = 'spatialbot@example.com', password = '1234'):
	server.ehlo()
	server.starttls()
	server.ehlo()
	server.login(username,password)
	return server

def send_alert(alert, alert_configuration):
	server_address = alert_configuration.server_address
	message = alert.message
	recipients = alert.recipients
	smtpServer = authenticate_against_email_server(
			generate_email_server_connection(
				alert_configuration.server_address,
				alert_configuration.server_port
				),
			alert_configuration.spatial_bot_address,
			alert_configuration.spatial_bot_password
			)
	for recipient in recipients:
#		print("Alerting: {0} that {1}".format(recipient,message))
		if recipient.delivery_method == 'email':
			send_email(message,recipient.address,smtpServer,alert_configuration.spatial_bot_address)
	smtpServer.quit()

def send_email(message, recipient,smtpServer, from_address = "spatialbot@example.com"):
	msg = MIMEText(message)
	msg['Subject'] = message
	msg['From'] = from_address
	msg['To'] = recipient
	smtpServer.sendmail(from_address,[recipient],msg.as_string())
