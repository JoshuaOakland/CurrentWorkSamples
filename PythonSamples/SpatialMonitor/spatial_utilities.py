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
def strip_comments(config):
	filtered_lines = []
	raw_lines = config
#	print(raw_lines)
	for line in raw_lines:
		if line[0] != '#' and line[0] != '\n':
			filtered_lines.append(line.strip().split())
#	print("\n\n\n\n\n\n\n\n\n")
#	print(filtered_lines)
	return filtered_lines

def get_argument(config,target):
	for argument in config:
		if target == argument[0]:
			return argument[1]
def get_boolean(raw_text):
	if raw_text == "True":
		return True
	if raw_text == "False":
		return False
def get_integer(raw_text):
	return int(raw_text)

