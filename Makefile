# -*- mode: makefile-gmake -*-


########################################
## MAKEFILE FOR FERROTECH
## AUTHOR: Per Thomas Hille pth@embc.no
## COPYRIGHT: Embedded Consulting A/S
########################################


##########################################################################
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <https://www.gnu.org/licenses/>.
##########################################################################

# This Makefile has two primary build targets: 'x86' and 'arm'
# When building each of these the Makefile will call itself with
# the TARGET variable set accordingly, but with no goals. For example:
# "make TARGET=arm". The TARGET variable is responsible for setting
# the value of the "all-src" list which contains all directories that
# shall be built for the given target.


export BUILDDIR=$(CURDIR)/build
export BINDIR=$(BUILDDIR)/$(TARGET)/bin
export LIBLOCAL=$(BUILDDIR)/$(TARGET)/lib
export INSTALLDIRS=$(BUILDDIR) $(BUILDDIR)/$(TARGET)  $(BUILDDIR)/$(TARGET)/bin  $(BUILDDIR)/$(TARGET)/lib

export COMMON_FLAGS:= -fPIC -std=c++17  -g
export PEDANTIC_FLAGS:= -Weffc++ -Wshadow -Wall -Wextra -Wpedantic -Wno-unknown-pragmas -Wswitch-enum -Wimplicit-fallthrough -Wignored-qualifiers 

export CPPFLAGS:=           $(COMMON_FLAGS) $(PEDANTIC_FLAGS)
export CPPFLAGS_RELAXED:=   $(COMMON_FLAGS) $(PEDANTIC_FLAGS)

export XML_DIR:=$(CURDIR)/xml/3rd-party/
export XML_INCLUDES:= -I $(XML_DIR)

export LIBFLAGS:= -shared


INCLUDES:= -I $(CURDIR)/include/
GTEST_INCLUDES:= -isystem $(CURDIR)/
LIBS= -L $(CURDIR)/build/$(TARGET)/lib  -lm


export UNIT_TEST_LIBS:= -lgtest -lpthread 

gtest-embc:=         gtest-embc/$(TARGET)

xml:=                 xml/$(TARGET)
xml-unittest:=        xml/unit-tests/commit/$(TARGET)
xml-example1:=        xml/examples/xml-example1/$(TARGET)
xml-validator:=       xml/xml-validator/$(TARGET)


unittests:= $(xml-unittest)


src-lib:= $(gtest-embc) \
	      $(xml)


src-exe:=$(unittests) \
	 $(xml-example1) \
	 $(xml-validator) 



arm-src:=$(src-lib) $(src-exe)
x86-src:=$(src-lib) $(src-exe) $(version-info)


ifeq (x86, $(TARGET))
src-lib+=$(xml)
all-src:=$(x86-src) 
endif


ifeq (arm, $(TARGET))
LIBS+=-L  $(CURDIR)/arm-extras
all-src:=$(arm-src)
endif


#default target is x86, we define it here to avoid cheking for the arm compiler if
#compiling just for x86
export TARGET=x86

## Set compiler and archive builder to toolchain.
##ifeq ($(strip $(ARCH)),)
ifeq (x86, $(TARGET))
CCLOCAL:=c++   -std=c++17
ARLOCAL:=ar
else
CCLOCAL:=arm-linux-gnueabihf-g++   -std=c++17 -DARM
ARLOCAL:=arm-linux-gnueabihf-ar
endif


ifdef CC-CROSS
CCLOCAL:=$(CC-CROSS)
endif


export


.PHONY: all $(all-src)
all: $(all-src)


all-clean:=$(x86-src)
unittest-common =  $(testlib)  $(support-modules)  $(gtest-embc)

$(src-exe) : $(src-lib)



$(all-src): 
	$(MAKE) --directory=$@ all


.PHONY: check-compiler
check-compiler:
	$(CCLOCAL) --version /dev/null;



$(INSTALLDIRS):
	mkdir -p $@


x86:
	@$(MAKE) TARGET=x86


arm:
	#@$(MAKE) TARGET=arm



.PHONY: clean
clean:  clean-x86
	@find -name *.d -exec rm {} \;
	@find -name *.gdb -exec rm {} \;
	@find -name *.o -exec rm {} \;
	@rm -rf `find -name "SvnInfo*" | grep -v .svn`

.PHONY: clean-exe
clean-exe:
	@for d in $(src-exe); \
	do \
	    $(MAKE)  --directory=$$d/x86  --no-print-directory clean-exe TARGET=x86; \
	done
#	@rm -f build/x86/bin/*



.PHONY: clean-x86
clean-x86:
	@for d in $(x86-src); \
	do \
	    $(MAKE)  --directory=$$d/x86  --no-print-directory clean TARGET=x86; \
	done
	@rm -rf build/x86


.PHONY: distclean
distclean: clean
	@-$(RM) -r build
	@-$(RM) `find -name "SvnInfo*" | grep -v .svn`
	@find -name *.so    |  egrep  -v  '^\./3rd-party/'  |  egrep -v   '^\./arm-lib-dep/' |  xargs rm -f
	@find -name *.so.*  |  egrep  -v  '^\./3rd-party/'  |  egrep -v   '^\./arm-lib-dep/' |  xargs rm -f
	@find -name *.a     |  egrep  -v  '^\./3rd-party/'  |   xargs rm -f
	@find -name *~ -exec rm {} \;
	@find -name tmp.cpp | xargs rm -f;

.PHONY: doc
doc:
	doxygen Doxyfile

