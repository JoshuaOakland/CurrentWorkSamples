The purpose of spatial_monitor is the continuous automation of a redundant system administration task. Feel free to go about your day knowing that the disks that keep your mission critical systems up and running are being consistently monitored. (You still need to look at your emails though, no luck there.)

You may daemonize this small application to run at scheduled intervals or you may dumbfire the application
and set configurable lifetime and poll frequency.

To properly run the dumbfire version of this application you probably want to disown the process so that
it can run in the background.

i.e. python spatial_monitor.py & disown

This application assumes the existence of df within your os path and obviously a python interpreter(2.7+ to be safe).

You do not need to be root to execute this application, though you may find it useful to do so if you want
to restrict the read / write access of the config files which will contain plain-text password and acct
information.

There are more elegant and secure ways of loading that information, however that is beyond the scope of this exercise.

There is also little to no error checking, redundancy, or performance consideration. Though this should be a solid start and easily remedied. Also it should be noted that if properly daemonized application failures will have less effect. (These can be symptoms of timeouts, connection refusals etc.)

I hope you find this useful

- Josh

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

