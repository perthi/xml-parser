
PROGRAM:=xml-example1


SRCCPP:=xml-example1.cpp
LIBS+=  -lxml-embc   -lxml2 
INCLUDES+=$(XML_INCLUDES)


include ../../../../common.mk

