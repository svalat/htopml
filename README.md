Htopml
======

What it is
----------

Htopml is a mix between htop and html as it provide ways to watch the system or you app in html with a lightweigt server.
The main idea is to provide a light framework to spy some values of your application in a nice way thanks to
the nice rending we can to with html/js/svg. 

Currently it a more a prototype than a finished product.

Some screenshots
----------------

Example on CPU usage :

![CPU usage](./screens/top.png?raw=true "Example of CPU usage")

Example looking on thread bindings thanks to patched hwloc :

![Thread binding](./screens/thread-binding.png?raw=true "Thread binding")

Compile and install
-------------------

If you want to get some nice view of the threads running on the CPUs you can install then patched hwloc (optional) : 

```sh
	wget http://www.open-mpi.org/software/hwloc/v1.7/downloads/hwloc-1.7.2.tar.gz
	tar -xvf hwloc-1.7.2.tar.gz
	cd hwloc-1.7.2
	patch -p1 < ../extern-deps/hwloc-1.7.2-0001-Add-native-svg-support.patch
	./configure --prefix=$HOME/usr
	make
	make install
	#put it in your .bashrc if you want to keep it
	export PATH=$HOME/usr/bin:$PATH
```

First you need to compile and install

```sh
	mkdir build
	cd build
	../configure --prefix=$HOME/usr --with-hwloc=$HOME/usr
	make
	make install
```

or using directly cmake :

```sh
	mkdir build
	cd build
	cmake .. -DCMAKE_INSTALL_PREFIX=$HOME/usr -DHWLOC_PREFIX=/home/sebv/usr
	make
	make install
```

Usage as daemon
---------------

You can use htopml as daemon to watch the system :

```sh
	htopmld
	#then connect with your browser onto http://localhost:8080
```

Load into app
-------------

If you wanto to watch a particular application for example to track its memory usage over time you can use :

```sh
	htopml [htopml-options] my_app [app-options]
	#then connect with your browser onto http://localhost:8080
```

Using plugins
-------------

You can create your own plugins or see some examples into `plugins` directory. Htopml provide a small kind of DSL
to define your plugins and generate the C++/html/js code for you for some basic cases, see the examples to
get the semantic of the files.

To build a plugin :

```sh
	htopml-generate my_plugin.xml
	make
```

Then you use it at runtime with :

```sh
	htopml --plugins=./libmyplugins.so my_app
```

Usage of proxy
--------------

If you use slurm, you can use the `htopml-slurm-proxy` command to select which process you want to look on, it will automatically setup and ssh
relay with port forwarding to look on it and you can switch from one to another into the console (need to push it into the web GUI).

Licence & status
----------------

It is currently a draft prototype so expect miracles.

It is distributed under CeCILL-C lincence. But CAUTION, the web GUI used http://www.highcharts.com/ for the charts and this library
is OpenSource (CC) only for personal and non-commercial use, in other cases, look on their site.

