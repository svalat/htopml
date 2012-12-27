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

######################################################
"""
This class provide management of numbering interval. In min and max have same value it represent a single value.
This is to manage hostname range into slurm job allocation.
"""
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

######################################################
"""
This class represent a slurm job, mainly a job name, a base hostname and a range
of hosts ids.
"""
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

######################################################
"""
This class provide the GUI interface in curses mode to swtich between jobs and
hosts in job.
"""
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
	proxy = None

	def __init__(self,proxy,interactiveNode,remoteUser):
		self.interactiveNode = interactiveNode
		self.remoteUser = remoteUser
		self.getOutputLines()
		self.screen = curses.initscr()
		self.proxy = proxy
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
			elif '%c' % (c,) == 'q':
				self.exit()
			elif '%c' % (c,) == 'r':
				self.proxy.errors += ">> Refresh job list\n"
				self.getOutputLines()
			else:
				self.proxy.errors += "%c => %d\n" % (c,c,)

	def selectPrevNextHost(self,delta):
		if self.highlightLineNum != -1 and self.nOutputLines > 0:
			self.outputLines[self.highlightLineNum].moveSelected(delta)
			#self.updateProxyRedirection(self.outputLines[self.activeEntry])

	def markLine(self):
		self.activeEntry = self.topLineNum + self.highlightLineNum
		self.updateProxyRedirection(self.outputLines[self.activeEntry])

	def updateProxyRedirection(self,slurmHost):
		if slurmHost.selected == -1:
			hostname = slurmHost.baseHostname
		else:
			hostname = "%s%d" % (slurmHost.baseHostname,slurmHost.selected,)
		self.proxy.update(hostname,8080)

	def getOutputLines(self):
		### !!!
		### This is where you would write a function to parse lines into rows
		### and columns. For this demo, I'll just create a bunch of random ints
		### !!!
		self.outputLines = list()
		# gen squeue command
		if self.interactiveNode == 'localhost':
			cmd = ['squeue','-u',remoteUser]
		else:
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
		bottom = self.topLineNum+curses.LINES - 10
		cols = curses.COLS

		#setup title bar
		title = "htopml-slurm-proxy - http://localhost:8080 -> http://%s:%d" % (self.proxy.targetHost,self.proxy.targetPort,)
		title = title.center(cols,' ')
		self.screen.addstr(0, 0, title, curses.A_REVERSE)

		#setup bottom bar
		helpText = "Refresh : R  |  Select job : UP/DOWN  |  Select node in job : LEFT/RIGHT  |  Switch : SPACE  |  Exit : ESC/Q"
		helpText = helpText.center(cols,' ')
		self.screen.addstr(curses.LINES - 2,0,helpText,curses.A_REVERSE)

		#setup col index
		line = '%s %-6s %-15s %-20s %-10s %-5s  %-5s  %s' % (self.PREFIX_DESELECTED,"ID","Part.","Exe","State","Time","Cores","Hosts",)
		self.screen.addstr(2,0,line)
		self.screen.addstr(3,0,"".ljust(cols,'-'))

		#print error area
		lines = self.proxy.errors.splitlines()
		errorText=''
		for i in range(0,4):
			if 4-i <= len(lines):
				errorText = errorText + lines[-4+i] + "\n"
		self.screen.addstr(curses.LINES - 6,0,errorText)

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

######################################################
class Proxy:
	#default members
	targetHost = "unknown"
	targetPort = 0
	localPort = 0
	errors = ''

	def __init__(self,localPort):
		self.localPort = localPort

######################################################
class SshNativeProxy(Proxy):
	#default members
	ssh = None
	remoteUser = None
	interactiveNode = None

	def __init__(self,localPort,interactiveNode,remoteUser,useHopToNode = False,skipHostKey = False):
		#setup parent class
		Proxy.__init__(self,localPort)

		#setup local args
		self.interactiveNode = interactiveNode
		self.remoteUser = remoteUser
		self.useHopToNode = useHopToNode
		self.skipHostKey = skipHostKey
		
	def genCmdNoHop(self):
		return ['ssh','-l',self.remoteUser,self.interactiveNode,'-L%d:%s:%d' % (self.localPort,self.targetHost,self.targetPort)]

	def genCmdHop(self):
		if self.skipHostKey:
			return ['ssh','-l',self.remoteUser,self.targetHost,'-L%d:localhost:%d' % (self.localPort,self.targetPort),'-o','ProxyCommand=ssh %s nc %s 22' % (self.interactiveNode,self.targetHost),'-o','UserKnownHostsFile=/dev/null','-o','StrictHostKeyChecking=no']
		else:
			return ['ssh','-l',self.remoteUser,self.targetHost,'-L%d:localhost:%d' % (self.localPort,self.targetPort),'-o','ProxyCommand=ssh %s nc %s 22' % (self.interactiveNode,self.targetHost)]
	
	def update(self,targetHost,targetPort):
		#if same
		#self.errors += "Check if need to update\n"
		#if self.targetHost == targetHost and self.targetPort == targetPort:
		#	return
		
		#update current params
		self.targetHost = targetHost
		self.targetPort = targetPort

		#close current connection
		if self.ssh != None:
			self.ssh.stdin.close()
			self.ssh.wait()

		#start a new one
		try:
			if self.useHopToNode:
				cmd = self.genCmdHop()
			else:
				cmd = self.genCmdNoHop()
			self.errors += ">> " + ' '.join(cmd) + "\n"
			self.ssh = subprocess.Popen(cmd,stdout=subprocess.PIPE,stdin=subprocess.PIPE,stderr=subprocess.PIPE)
		except ValueError:
			self.errors += ValueError
			self.ssh = None

######################################################
class SshEmulatedProxy(Proxy):
	#default members
	ssh = None
	bounce = None

	def __init__(self,localPort,interactiveNode,remoteUser):
		#setup parent class
		Proxy.__init__(self,localPort)

		#setup loal args
		self.bounce = interactiveNode
		self.remoteUser = remoteUser

	def update(self,targetHost,targetPort):
		#if same
		#self.errors += "Check if need to update\n"
		#if self.targetHost == targetHost and self.targetPort == targetPort:
		#	return

		#update current params
		self.targetHost = targetHost
		self.targetPort = targetPort

		#close current connection
		if self.ssh != None:
			self.ssh.stdin.close()
			self.ssh.wait()

		#start a new one
		try:
			cmd = [sys.argv[0],'ssh-emulated-local',self.bounce,targetHost,'%s'%(targetPort,)]
			self.errors += ">> " + ' '.join(cmd) + "\n"
			self.ssh = subprocess.Popen(cmd,stdout=subprocess.PIPE,stdin=subprocess.PIPE,stderr=subprocess.PIPE)
		except ValueError:
			self.errors += ValueError
			self.ssh = None

######################################################
class LocalProxy(Proxy):
	def __init__(self,localPort):
		#setup parent class
		Proxy.__init__(self,localPort)
		self.start()

	def update(self,targetHost,targetPort):
		if self.targetHost == targetHost and self.targetPort == targetPort:
			return
		else:
			self.targetHost = targetHost
			self.targetPort = targetPort
			self.errors += ">> Update redirection to %d -> %s:%d\n" % (self.localPort,targetHost,targetPort,)

	def start(self):
		thread.start_new_thread(server, (self,))

def forward(source, destination):
	string = ' '
	while string:
		string = source.recv(1024)
		if string:
			destination.sendall(string)
		else:
			#source.shutdown(socket.SHUT_RD)
			destination.shutdown(socket.SHUT_WR)

def server(*proxy):
	try:
		dock_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		dock_socket.bind(('localhost', proxy[0].localPort))
		dock_socket.listen(5)
		#print target[0].hostname
		while True:
			try:
				client_socket = dock_socket.accept()[0]
				server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
				server_socket.connect((proxy[0].targetHost, proxy[0].targetPort))
				thread.start_new_thread(forward, (client_socket, server_socket))
				thread.start_new_thread(forward, (server_socket, client_socket))
			except ValueError:
				self.errors += ValueError
	finally:
		dock_socket.close()

######################################################
class EmulateSshProxyOption:
	REMOTE_SERVER = 1
	LOCAL_SERVER = 2
	mode = None
	bounce = None
	bounceUser = None
	targetHost = None
	targetPort = 8080
	localPort = 8080

	def __init__(self,mode,localPort,bounce,targetHost,targetPort):
		self.mode = mode
		self.localPort = localPort
		self.bounce = bounce
		self.targetHost = targetHost
		self.targetPort = targetPort

	def proxyDebug(self,message):
		#sys.stderr.write(message+"\n")
		message = None

	def proxySocketRecvAllHttpReq(self,remote_socket):
		tot=''
		buf=' '
		while buf:
			buf = remote_socket.recv(1)
			if buf:
				tot+=buf
			if "\r\n\r\n" in tot:
				break
		return tot

	def proxySocketRecvAll(self,remote_socket):
		tot=''
		buf=' '
		while buf:
			buf = remote_socket.recv(1024)
			if buf:
				tot+=buf
		return tot

	def proxySendOnSsh(self,fd,category,message):
		fd.write(category)
		fd.write('%010d'%(len(message),))
		fd.write(message)
		fd.flush()

	def proxyReadOnSsh(self,fd,expectedCategory):
		#wait category
		cat = fd.read(1)
		#check cat
		if cat != expectedCategory:
			sys.stderr.write("Invalid categrory received from remote proxy : '%s', expect '%s'\n" % (cat,expectedCategory,))
			sys.exit(1)
		#read size
		self.proxyDebug("Cat is OK")
		size = fd.read(10)
		size = int(size)
		self.proxyDebug("Size is %d" % (size,))
		#read message
		self.proxyDebug("Read message")
		message = fd.read(size)
		self.proxyDebug("Read message OK")
		if len(message) != size:
			sys.stderr.write("Get an invalid size, read %d bu expect %d\n"% (len(message),size,))
			sys.exit(1)
		return message

	def localServer(self):
		client_socket=None
		#open listen port
		print 'Open listen port'
		dock_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		dock_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
		dock_socket.bind(('localhost', self.localPort))
		dock_socket.listen(5)
		print 'Now listening on http://localhost:%d => %s:%d throw ssh://%s' % (self.localPort,self.targetHost,self.targetPort,self.bounce,)
		try:
			#Open ssh proxy
			cmd = ['ssh','-C',self.bounce,'htopml-slurm-proxy','ssh-emulated-remote',self.bounce,self.targetHost,'%d'%(self.targetPort,)]
			self.proxyDebug(" ".join(cmd))
			ssh = subprocess.Popen(cmd,stdout=subprocess.PIPE,stdin=subprocess.PIPE)
			#Wait clients
			while True:
				client_socket = dock_socket.accept()[0]
				#read client request
				request = self.proxySocketRecvAllHttpReq(client_socket)
				self.proxyDebug("================== REQUEST ===================")
				self.proxyDebug(request)
				self.proxyDebug("==============================================")
				#transmit to remote proxy
				self.proxySendOnSsh(ssh.stdin,'R',request)
				#wait answer from remote proxy
				answer = self.proxyReadOnSsh(ssh.stdout,'A')
				#transmit to client
				self.proxyDebug("Send message")
				self.proxyDebug("================= ANSWER =====================")
				self.proxyDebug(answer)
				self.proxyDebug("==============================================")
				client_socket.sendall(answer)
				#close client and go to next one
				client_socket.close()
		except KeyboardInterrupt:
			self.proxyDebug("Bye bye")
		finally:
			self.proxyDebug("Close socket")
			if client_socket != None:
				client_socket.close()
			dock_socket.close()

	def remoteServer(self):
		server_socket = None
		while True:
			#read on stdin to get request
			self.proxyDebug("Wait messages on reamote")
			request = self.proxyReadOnSsh(sys.stdin,'R')
			answer = ''
			try:
				#connect to target
				server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
				server_socket.connect((self.targetHost, self.targetPort))
				#forward to client
				server_socket.sendall(request)
				server_socket.shutdown(socket.SHUT_WR)
				#read answer
				answer = self.proxySocketRecvAll(server_socket)
			except:
				self.proxyDebug("Get an error while connecting to target on remote")
			finally:
				#return awser via ssh
				self.proxyDebug("forward in SSH")
				self.proxySendOnSsh(sys.stdout,'A',answer)
				server_socket.close()

	def run(self):
		if self.mode == self.REMOTE_SERVER:
			self.remoteServer()
		elif self.mode == self.LOCAL_SERVER:
			self.localServer()
		else:
			sys.stderr.write("Invalid mode : %d.",self.mode)
			sys.exit(1)

######################################################
def showHelpAndQuit():
	sys.stderr.write("Missing arguments, usage : \n    -> %s local\n    -> %s {ssh|ssh-hop|ssh-hop-no-check|ssh-emulated} {interactive_node} [remote_username]\nThis is more for internal self recall but also :\n    -> {ssh-emulated-local|ssh-emulated-remote} {bounce node} {target host} {target port} [bounce user]\n" % (sys.argv[0],sys.argv[0]))
	sys.exit(1)

######################################################
def runProxyInterface(proxy,interactiveNode,remoteUser):
	ih = CursesMenuList(proxy,interactiveNode,remoteUser)
	while True:
		time.sleep(60)

######################################################
def runEmulatedProxyThread(proxy):
	proxy.run()

######################################################
def runEmulatedProxy(mode):
	bounce = sys.argv[2]
	target = sys.argv[3]
	port = int(sys.argv[4])
	proxy = EmulateSshProxyOption(mode,port,bounce,target,port)
	if mode == EmulateSshProxyOption.LOCAL_SERVER:
		thread.start_new_thread(runEmulatedProxyThread, (proxy,))
		sys.stderr.write("Wait press enter to exit")
		sys.stdin.readline()
	else:
		proxy.run()

######################################################
if __name__ == '__main__':
	#check if we have mode
	if len(sys.argv) < 2:
		showHelpAndQuit()

	#extract it
	mode = sys.argv[1]

	#check missing args
	if mode == 'local' and len(sys.argv) != 2:
		showHelpAndQuit()
	elif mode == 'ssh' and len(sys.argv) < 3:
		showHelpAndQuit()
	elif mode == 'ssh-hop' and len(sys.argv) < 3:
		showHelpAndQuit()
	elif mode == 'ssh-hop-no-check' and len(sys.argv) < 3:
		showHelpAndQuit()
	elif mode == 'ssh-emulated' and len(sys.argv) < 3:
		showHelpAndQuit()
	elif mode == 'ssh-emulated-local' and len(sys.argv) < 5:
		showHelpAndQuit()
	elif mode == 'ssh-emulated-remote' and len(sys.argv) < 5:
		showHelpAndQuit()

	#swtich between modes
	if mode == 'local':
		interactiveNode = 'localhost'
		remoteUser = os.getlogin()
		runProxyInterface(LocalProxy(8080),interactiveNode,remoteUser)
	elif mode == 'ssh' or mode == 'ssh-hop' or mode == 'ssh-hop-no-check':
		interactiveNode = sys.argv[2]
		if len(sys.argv) >= 4:
			remoteUser = sys.argv[3]
		else:
			remoteUser = os.getlogin()
		if mode == 'ssh':
			runProxyInterface(SshNativeProxy(8080,interactiveNode,remoteUser),interactiveNode,remoteUser)
		elif mode == 'ssh-hop':
			runProxyInterface(SshNativeProxy(8080,interactiveNode,remoteUser,True),interactiveNode,remoteUser)
		elif mode == 'ssh-hop-no-check':
			runProxyInterface(SshNativeProxy(8080,interactiveNode,remoteUser,True,True),interactiveNode,remoteUser)
	elif mode == 'ssh-emulated':
		interactiveNode = sys.argv[2]
		if len(sys.argv) >= 4:
			remoteUser = sys.argv[3]
		else:
			remoteUser = os.getlogin()
		runProxyInterface(SshEmulatedProxy(8080,interactiveNode,remoteUser),interactiveNode,remoteUser)
	elif mode == 'ssh-emulated-local':
		runEmulatedProxy(EmulateSshProxyOption.LOCAL_SERVER)
	elif mode == 'ssh-emulated-remote':
		runEmulatedProxy(EmulateSshProxyOption.REMOTE_SERVER)
	else:
		showHelpAndQuit()
