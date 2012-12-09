#!/usr/bin/env python
######################################################
#            PROJECT  : htopml                       #
#            VERSION  : 0.1.0-dev                    #
#            DATE     : 11/2012                      #
#            AUTHOR   : Valat Sebastien              #
#            LICENSE  : CeCILL-C                     #
######################################################
"""
Inspired from git://github.com/LyleScott/Python-curses-Scrolling-Example.git for the GUI interface implementation
and from http://www.linux-support.com/cms/forward-network-connections-with-python/ for the port redirection
"""

#For interface :
import curses
import sys
import random
import time
import socket
import sys
import thread
import time
import os
import subprocess

interactiveNode='unknown'
localPort=8080
remoteUser=os.getlogin()

class HostTarget:
	name = "localhost"
	hostname = "localhost"
	port = 8080

class Interval:
	min = 0
	max = 0

	def __init__(self,slurmInterval):
		tmp = slurmInterval.partition('-')
		self.min = int(tmp[0])
		if tmp[1] == '-':
			self.max = int(tmp[2])
		else:
			self.max = self.min

	def convertToString(self,selected = -1):
		leftMin = -1
		leftMax = -1
		rightMin = -1
		rightMax = -1

		if selected == -1:
			return self.simpleIntervalToString(self.min,self.max)

		if selected == -1:
			leftMin = self.min
			leftMax = self.max
		elif selected == self.min and selected == self.max:
			leftMin = -1
			leftMax = -1
		elif selected == self.min:
			rightMin = self.min + 1
			rightMax = self.max
		elif selected == self.max:
			leftMin = self.min
			leftMax = self.max-1
		elif selected >= self.min and selected <= self.max:
			leftMin = self.min
			leftMax = selected - 1
			rightMin = selected + 1
			rightMax = self.max
		else:
			selected = -1
			leftMin = self.min
			leftMax = self.max

		res = self.simpleIntervalToString(leftMin,leftMax)
		if res != "" and selected != -1:
			res += ","
		if selected != -1:
			res += " ->(%d)<- " % (selected,)
		if res != "" and rightMin != -1:
			res += ","
		res += self.simpleIntervalToString(rightMin,rightMax)

		return res;

	def simpleIntervalToString(self,min,max):
		if min == -1 and max == -1:
			return ""
		elif min == max:
			return '%d' % (min,)
		else:
			return '%d-%d' % (min,max,)

class SlurmJob:
	jobId = 0
	partition = "unknown"
	exeName = "none"
	user = "valats"
	status = "U"
	runtime = "0:00"
	hosts = "unknown0"
	cores = 0
	baseHostname = "unknown"
	slurmLine = "..."
	intervals = list()
	selected = -1

	def __init__(self,slurmSqueueLine):
		self.slurmLine = slurmSqueueLine.rstrip()
		parts = slurmSqueueLine.split()
		self.jobId = int(parts[0])
		self.partition = parts[1]
		self.exeName = parts[2]
		self.user = parts[3]
		self.status = parts[4]
		self.runtime = parts[5]
		self.cores = int(parts[6])
		self.hosts = parts[7]
		self.parseHosts(self.hosts)

	def parseHosts(self,hosts):
		self.intervals = list()
		tmp = hosts.partition('[')
		self.baseHostname = tmp[0]
		if tmp[1] == '[':
			tmp = tmp[2].replace(']','').split(',')
			for entry in tmp:
				self.intervals.append(Interval(entry))

	def getStringInterval(self,selected=-1):
		tmp = ""
		for interval in self.intervals:
			if tmp != "":
				tmp = tmp + ","
			tmp += interval.convertToString(selected)
		return tmp

	def getPrevOrCurInterval(self,pos):
		res = self.intervals[0]
		for interval in self.intervals:
			if interval.max <= pos or interval.min <= pos:
				res = interval
		return res

	def getNextInterval(self,interval):
		prev = None
		for tmp in self.intervals:
			if prev != None and prev.max == interval.max and prev.min == interval.min:
				return tmp
			prev = tmp
		return self.intervals[-1]

	def moveSelected(self,delta):
		if len(self.intervals) > 0:
			self.selected += delta
			res = self.getPrevOrCurInterval(self.selected)
			if self.intervals[-1].max < self.selected:
				self.selected = self.intervals[-1].max
			elif res.max < self.selected and delta <= 0:
				self.selected = res.max
			elif res.max < self.selected and delta > 0:
				self.selected = self.getNextInterval(res).min
			elif res.min > self.selected:
				self.selected = res.min

class CursesMenuList:
	DOWN = 1
	UP = -1
	SPACE_KEY = 32
	ESC_KEY = 27

	PREFIX_SELECTED   = '  =>   '
	PREFIX_DESELECTED = '       '

	outputLines = []
	screen = None
	redirection = None

	def __init__(self,target):
		self.getOutputLines()
		self.screen = curses.initscr()
		self.target = target
		curses.noecho()
		curses.cbreak()
		self.screen.keypad(1)
		self.screen.border(0)
		self.topLineNum = 0
		self.highlightLineNum = 0
		self.activeEntry = -1
		#if self.nOutputLines > 0:
			#self.markLine()
		self.run()

	def run(self):
		while True:
			self.displayScreen()
			# get user command
			c = self.screen.getch()
			if c == curses.KEY_UP:
				self.updown(self.UP)
			elif c == curses.KEY_DOWN:
				self.updown(self.DOWN)
			elif c == curses.KEY_LEFT:
				self.selectPrevNextHost(-1)
			elif c == curses.KEY_RIGHT:
				self.selectPrevNextHost(1)
			elif c == self.SPACE_KEY:
				self.markLine()
			elif c == self.ESC_KEY:
				self.exit()

	def selectPrevNextHost(self,delta):
		if self.highlightLineNum != -1 and self.nOutputLines > 0:
			self.outputLines[self.highlightLineNum].moveSelected(delta)
			#self.updateProxyRedirection(self.outputLines[self.activeEntry])

	def markLine(self):
		self.activeEntry = self.topLineNum + self.highlightLineNum
		self.updateProxyRedirection(self.outputLines[self.activeEntry])

	def updateProxyRedirection(self,slurmHost):
		if slurmHost.selected == -1:
			self.target.hostname = slurmHost.baseHostname
		else:
			self.target.hostname = "%s%d" % (slurmHost.baseHostname,slurmHost.selected,)
		if self.redirection != None:
			self.redirection.stdin.close()
			self.redirection.wait()
		try:
			self.redirection = subprocess.Popen(['ssh',interactiveNode,'-L%d:%s:%d' % (localPort,self.target.hostname,self.target.port)],stdout=subprocess.PIPE,stdin=subprocess.PIPE,stderr=subprocess.PIPE)
		except ValueError:
			self.restoreScreen()
			print ValueError
			sys.exit(1)

	def getOutputLines(self):
		### !!!
		### This is where you would write a function to parse lines into rows
		### and columns. For this demo, I'll just create a bunch of random ints
		### !!!
		self.outputLines = list()
		# gen squeue command
		#cmd = ['squeue','-u',os.getlogin()]
		cmd = ['ssh',interactiveNode,'squeue','-u',remoteUser]
		#cmd = ['cat','lines.txt']
		try:
			fd = subprocess.Popen(cmd,stdout=subprocess.PIPE).stdout
		except:
			sys.stderr.write("Failed to execute command %s \n" % (cmd))
			sys.exit(1)
		firstLine=True
		for line in fd:
			if firstLine == False:
				self.outputLines.append(SlurmJob(line))
				self.outputLines[-1].moveSelected(1)
			else:
				firstLine = False
		self.nOutputLines = len(self.outputLines)

	def displayScreen(self):
		# clear screen
		self.screen.clear()

		# now paint the rows
		top = self.topLineNum
		bottom = self.topLineNum+curses.LINES - 6
		cols = curses.COLS

		#setup title bar
		title = "htopml-proxy - http://localhost:8080 -> http://%s:%d" % (self.target.hostname,self.target.port,)
		title = title.center(cols,' ')
		self.screen.addstr(0, 0, title, curses.A_REVERSE)

		#setup bottom bar
		helpText = "Select job : UP/DOWN   -   Select node in job : LEFT/RIGHT   -   Exit : ESC"
		helpText = helpText.center(cols,' ')
		self.screen.addstr(curses.LINES - 2,0,helpText,curses.A_REVERSE)

		#setup col index
		line = '%s %-6s %-15s %-20s %-10s %-5s  %-5s  %s' % (self.PREFIX_DESELECTED,"ID","Part.","Exe","State","Time","Cores","Hosts",)
		self.screen.addstr(2,0,line)
		self.screen.addstr(3,0,"".ljust(cols,'-'))

		# paint list
		for (index,line,) in enumerate(self.outputLines[top:bottom]):
			linenum = self.topLineNum + index
			if linenum == self.activeEntry:
				prefix = self.PREFIX_SELECTED
			else:
				prefix = self.PREFIX_DESELECTED

			#                       ;       ;     ;
			line = '%s %-6d %-15s %-20s %-10s %-5s  %-5d  %s[%s]' % (prefix,line.jobId,line.partition,line.exeName,line.status,line.runtime,line.cores,line.baseHostname,line.getStringInterval(line.selected),)
			line = line.ljust(cols,' ')

			# highlight current line
			if index != self.highlightLineNum:
				self.screen.addstr(index + 4, 0, line)
			else:
				self.screen.addstr(index + 4, 0, line, curses.A_REVERSE)
		self.screen.refresh()

	# move highlight up/down one line
	def updown(self, increment):
		nextLineNum = self.highlightLineNum + increment

		# paging
		if increment == self.UP and self.highlightLineNum == 0 and self.topLineNum != 0:
			self.topLineNum += self.UP
			return
		elif increment == self.DOWN and nextLineNum == curses.LINES and (self.topLineNum+curses.LINES) != self.nOutputLines:
			self.topLineNum += self.DOWN
			return

		# scroll highlight line
		if increment == self.UP and (self.topLineNum != 0 or self.highlightLineNum != 0):
			self.highlightLineNum = nextLineNum
		elif increment == self.DOWN and (self.topLineNum+self.highlightLineNum+1) != self.nOutputLines and self.highlightLineNum != curses.LINES:
			self.highlightLineNum = nextLineNum

		#self.markLine()

	def restoreScreen(self):
		curses.initscr()
		curses.nocbreak()
		curses.echo()
		curses.endwin()

	# catch any weird termination situations
	def __del__(self):
		self.restoreScreen()

def forward(source, destination):
	string = ' '
	while string:
		string = source.recv(1024)
		if string:
			destination.sendall(string)
		else:
			#source.shutdown(socket.SHUT_RD)
			destination.shutdown(socket.SHUT_WR)

def server(*target):
	try:
		dock_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		dock_socket.bind(('', 8090))
		dock_socket.listen(5)
		#print target[0].hostname
		while True:
			client_socket = dock_socket.accept()[0]
			server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
			server_socket.connect((target[0].hostname, target[0].port))
			thread.start_new_thread(forward, (client_socket, server_socket))
			thread.start_new_thread(forward, (server_socket, client_socket))
	finally:
		dock_socket.close()

if __name__ == '__main__':
	if len(sys.argv) < 2:
		sys.stderr.write("Missing arguments, usage : {interactive_node_hostaname} [remote_username]")
	interactiveNode = sys.argv[1]
	if len(sys.argv) > 2:
		remoteUser = sys.argv[2]
	target = HostTarget()
	#thread.start_new_thread(server, (target,))
	ih = CursesMenuList(target)
	while True:
		time.sleep(60)
