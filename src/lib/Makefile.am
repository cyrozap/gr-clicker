#
# Copyright 2009 Jordan Riggs                                                                                                    
# Copyright 2005, 2006 Free Software Foundation, Inc.
# 
# This file is part of gr-clicker
# 
# gr-clicker is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
# 
# gr-clicker is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with gr-clicker; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

include $(top_srcdir)/Makefile.common

# Install this stuff so that it ends up as the gnuradio.howto module
# This usually ends up at:
#   ${prefix}/lib/python${python_version}/site-packages/gnuradio

ourpythondir = $(grpythondir)
ourlibdir    = $(grpyexecdir)

INCLUDES = $(STD_DEFINES_AND_INCLUDES) $(PYTHON_CPPFLAGS)

SWIGPYTHONARGS = $(SWIGPYTHONFLAGS) $(SWIGGRFLAGS)

ALL_IFILES = 				\
	$(LOCAL_IFILES)			\
	$(NON_LOCAL_IFILES)		

NON_LOCAL_IFILES =			\
	$(GNURADIO_CORE_INCLUDEDIR)/swig/gnuradio.i


LOCAL_IFILES = 				\
	$(top_srcdir)/src/lib/clicker.i				

# These files are built by SWIG.  The first is the C++ glue.
# The second is the python wrapper that loads the _howto shared library
# and knows how to call our extensions.

BUILT_SOURCES = 			\
	clicker.cc			\
	clicker.py				

# This gets howto.py installed in the right place
ourpython_PYTHON =			\
	clicker.py

ourlib_LTLIBRARIES = _clicker.la

# These are the source files that go into the shared library
_clicker_la_SOURCES = 		\
	clicker.cc				\
	clicker_packet.cc		\
	clicker_sniffer.cc		

# magic flags
_clicker_la_LDFLAGS = $(NO_UNDEFINED) -module -avoid-version

# link the library against some comon swig runtime code and the 
# c++ standard library
_clicker_la_LIBADD = 			\
	$(PYTHON_LDFLAGS)		\
	-lstdc++	                	

clicker.cc clicker.py: $(LOCAL_IFILES) $(ALL_IFILES)
	$(SWIG) $(SWIGPYTHONARGS) -module clicker -o clicker.cc $(LOCAL_IFILES)

# These headers get installed in ${prefix}/include/gnuradio
grinclude_HEADERS =			\
	clicker_packet.h		\
	clicker_sniffer.h		


# These swig headers get installed in ${prefix}/include/gnuradio/swig
swiginclude_HEADERS = 			\
	$(LOCAL_IFILES)

MOSTLYCLEANFILES = $(BUILT_SOURCES) *.pyc

# Don't distribute output of swig
dist-hook:
	@for file in $(BUILT_SOURCES); do echo $(RM) $(distdir)/$$file; done
	@for file in $(BUILT_SOURCES); do $(RM) $(distdir)/$$file; done
