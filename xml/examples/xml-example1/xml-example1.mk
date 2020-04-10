
PROGRAM:=xml-example1


SRCCPP:=xml-example1.cpp


LIBS+=  -lxml-embc   -lxml2 
CPPFLAGS:=$(CPPFLAGS_RELAXED)
INCLUDES+=$(XML_INCLUDES)


include ../../../../common.mk

