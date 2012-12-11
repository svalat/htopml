######################################################
CXX=g++
LDFLAGS=-fPIC -shared -g
HTOPML_PREFIX=`which htopml-generate | xargs dirname`/../
HTOPML_GENERATE=$(HTOPML_PREFIX)/bin/htopml-generate

######################################################
all: liball.so alld

######################################################
openedfiles/Makefile: openedfiles/openedfiles.xml
	cd openedfiles/ && $(HTOPML_GENERATE) openedfiles.xml

statm/Makefile: statm/statm.xml
	cd statm/ && $(HTOPML_GENERATE) statm.xml

sysinfo/Makefile: sysinfo/sysinfo.xml
	cd sysinfo/ && $(HTOPML_GENERATE) sysinfo.xml

environ/Makefile: environ/environ.xml
	cd environ/ && $(HTOPML_GENERATE) environ.xml

malloc/Makefile: malloc/malloc.xml
	cd malloc/ && $(HTOPML_GENERATE) malloc.xml

######################################################
openedfiles/libopenedfiles.so: openedfiles/Makefile
	cd openedfiles && make

statm/libstatm.so: statm/Makefile
	cd statm && make

environ/libenviron.so: environ/Makefile
	cd environ && make

malloc/libmalloc.so: malloc/Makefile
	cd malloc && make

sysinfo/libsysinfo.so: sysinfo/Makefile
	cd sysinfo && make

######################################################
liball.so: openedfiles/libopenedfiles.so statm/libstatm.so environ/libenviron.so malloc/libmalloc.so sysinfo/libsysinfo.so
	ln -sf openedfiles/libopenedfiles.so .
	ln -sf statm/libstatm.so .
	ln -sf environ/libenviron.so .
	ln -sf malloc/libmalloc.so
	ln -sf sysinfo/libsysinfo.so
	$(CXX) $(LDFLAGS) -o $@ -Wl,-rpath=$(PWD) -L. -lopenedfiles -lstatm -lenviron -lmalloc -lsysinfo

alld: liball.so
	$(CXX) -g -o $@ $(HTOPML_PREFIX)/share/htopml/templates/main.cpp $^ -Wl,-rpath=$(PWD)

clean:
	$(RM) alld liball.so libopenedfiles.so libstatm.so libenviron.so libmalloc.so libsysinfo.so
	make -C openedfiles clean
	make -C statm clean
	make -C environ clean
	make -C malloc clean
	make -C sysinfo clean

distclean:
	$(RM) alld liball.so libopenedfiles.so libstatm.so libenviron.so libmalloc.so libsysinfo.so
	make -C openedfiles distclean
	make -C statm distclean
	make -C environ distclean
	make -C malloc distclean
	make -C sysinfo distclean
