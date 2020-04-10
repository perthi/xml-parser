
PROGRAM:=xml-unit-tests


SRCCPP += xml-dll-test.cpp \
	TestGXmlClassFactory.cpp \
	TestGXmlValidatorImpl.cpp 

include ../../../../common.mk
include ../../../../unittest-common.mk

LIBS+=  -lreadline -lxml-embc  -lxml2
INCLUDES+=$(GTEST_INCLUDES)
