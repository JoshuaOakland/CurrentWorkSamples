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


import spatial_poll
import spatial_alert
from spatial_utilities import get_argument, get_integer, get_boolean, strip_comments
from spatial_datatypes import SpatialEmailConfiguration
logging = False

def log_event(event, log = "spatial_log.txt"):
	'put event into a log for inspection at a later date'
	output = open(log,'a')
	output.write('\n'+str(event)+'\n')
	output.close()
#	print("Logging Event {0} in log {1}".format(event,log))

def cycle_targets(monitor_targets, subscribed_entities,alert_configuration):
	subscribers = spatial_alert.get_spatial_subscribers(subscribed_entities)
	alerts = spatial_poll.get_spatial_alerts(monitor_targets, subscribers)
	if(len(alerts) > 0 and len(subscribers) > 0):
		for alert in alerts:
			if(logging):
				log_event(alert)
			spatial_alert.send_alert(alert,alert_configuration)
	else:
		if len(monitor_targets) < 1:
			print("Warning, you have no targets being monitored. Perhaps you should check the config file monitoring_targets.conf an example entry is /dev/sda1 90% to warn subscribers when ")
		if len(subscribed_entities) < 1 and not logging:
			print("Warning, there are currently no subscribers for the monitoring system. Maybe you should check the config file monitoring_subscribers.conf this warning is ignored if you are logging, but that is currently set to false an example entry is admin@example.com email")

def tick(alert_configuration):
#get spatial targets
	spatial_monitor_targets = open('monitoring_targets.conf','r')
	monitor_targets = strip_comments(spatial_monitor_targets.readlines())
	spatial_monitor_targets.close()
#get monitoring entities
	spatial_subscribed_entities = open('monitoring_subscribers.conf','r')
	subscribed_entities = strip_comments(spatial_subscribed_entities.readlines())
	spatial_subscribed_entities.close()
	cycle_targets(monitor_targets,subscribed_entities,alert_configuration)
			
import time

def main(): 
	'System Space Monitor and Early Warning System Entry Point'
	configuration = open('monitor.conf','r')
	config = configuration.readlines()
	configuration.close()
	config = strip_comments(config)
	global logging
	logging = get_boolean(get_argument(config,'logging'))
	alert_configuration = SpatialEmailConfiguration(get_argument(config,'server_address'),
							get_integer(get_argument(config,'server_port')),
							get_argument(config,'alert_account'),
							get_argument(config,'alert_account_password')
							)
	if(get_boolean(get_argument(config,'dumbfire'))):
		pollrate = get_integer(get_argument(config,'pollrate'))*60#converting to minutes
		if(pollrate < 1):
			print("pollrate cannot be more frequent than once per minute.")
			exit(1)
		iterations = (get_integer(get_argument(config,'lifetime'))*60*60)/pollrate
		if(iterations != 0):
			while iterations > 0:
				tick(alert_configuration)
				time.sleep(pollrate)
				iterations -= 1
		else:
			while(True):
				tick(alert_configuration)
				time.sleep(pollrate)
	else:#this means you are running this as a scheduled service
		print("Running once")
		tick(alert_configuration)

if __name__ == "__main__":
	main()
