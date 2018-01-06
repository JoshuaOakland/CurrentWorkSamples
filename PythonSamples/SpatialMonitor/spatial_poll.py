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

from os import popen
from spatial_datatypes import SpatialAlert

def poll_space(target):
	'check target for % of space in usage'
	pollset = get_target_pair(target)#.split())
	dataset = popen('df','r')
	data = dataset.readlines()
	dataset.close()
	current_usage = data[5].split()[4]
	current_usage_as_float = float(current_usage.split("%")[0])
	return current_usage_as_float if current_usage_as_float >= pollset[1] else 0

def get_disk(target):
	'grab disk name from target'
	return target[0]

def get_threshold(target):
	'grab acceptable percentage from target disk'
	return float(target[1].split('%')[0])

def get_target_pair(target):
	diskname = get_disk(target)
	threshold = get_threshold(target)
	return (diskname,threshold)

def get_hostname():
	formatted_data = ''
	hostdataset = popen('hostname -s','r')
	data = hostdataset.readlines()
	hostdataset.close()
	for item in data:
		formatted_data += item
	ipdataset = popen('hostname -i','r')
	data = ipdataset.readlines()
	ipdataset.close()
	for item in data:
		formatted_data += item
	return formatted_data.split()

def create_spatial_alert(monitor_target, alert, recipients):
	target_data = get_target_pair(monitor_target)#.split())
	alert = SpatialAlert(notification = "Target {0} has reached a threshold of {1}% usage on system {2}".format(target_data[0].strip(), alert, get_hostname()),recipient_list = recipients)
	return alert

def get_spatial_alerts(monitor_targets,recipients):
	alerts = []
	for monitor_target in monitor_targets:
		alert = poll_space(monitor_target)
		if (alert):
			spatial_alert = create_spatial_alert(monitor_target, alert, recipients)
			alerts.append(spatial_alert)
	return alerts

