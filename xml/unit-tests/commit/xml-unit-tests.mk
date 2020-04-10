
PROGRAM:=xml-unit-tests


SRCCPP += xml-unit-tests.cpp \
	TestGXmlClassFactory.cpp \
	TestGXmlValidatorImpl.cpp 

include ../../../../common.mk
include ../../../../unittest-common.mk

LIBS+=  -lreadline -lxml-embc  -lxml2
INCLUDES+=$(GTEST_INCLUDES)
