

PROGRAM:=xml-validator

SRCCPP+=../xml-validator.cpp \
	GVersion.cpp \
	GVersionMenu.cpp


LIBS+= -lxml-embc  -lxml2 -llogmaster -lutilities  -lcmdline  -lexception -lreadline


include ../../../common.mk
