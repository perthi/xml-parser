


## ifneq (ARM, $(TARGET))
LIBNAME_SO:=libxml-embc.so	
## endif	

LIBNAME_A:=libxml-embc.a


SRCCPP+= GXmlAttribute.cpp \
	GXmlClassFactory.cpp \
	GXmlDocTypeNode.cpp \
	GXmlProcInstructNode.cpp \
	GXmlStreamReaderSp.cpp \
	GXmlTagNode.cpp \
	GXmlValidator.cpp \
	GXmlCDataNode.cpp \
	GXmlCommentNode.cpp \
	GXmlNodeImpl.cpp \
	GXmlStreamReaderImpl.cpp \
	GXmlStreamWriterImpl.cpp \
	GXmlTextNode.cpp \
	GXmlValidatorImpl.cpp \
	GTextXml.cpp \
	GPrintable.cpp \
	GCommonXML.cpp \
	GXmlParser.cpp \
	GString2Number.cpp \
	GXmlEntity.cpp \
	GXmlEnum2String.cpp


INCLUDES+=$(XML_INCLUDES)
include ../../common.mk
