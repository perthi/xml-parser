// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "GXmlClassFactory.h"
#include "GXmlStreamWriterImpl.h"
#include "GXmlMacros.h"
#include "GLocationXml.h"


#define MY_ENCODING "UTF-8"

/// #define XML(s,m) G_ASSERT_EXCEPTION(s >= 0, m)





GXmlStreamWriterImpl::~GXmlStreamWriterImpl()
{
	XML(xmlTextWriterEndDocument(fWriter), GLOCATION_SRC, "xmlTextWriterEndDocument: Error at xmlTextWriterStartDocument");
	xmlFreeTextWriter(fWriter);
}

GXmlStreamWriterImpl::GXmlStreamWriterImpl()
{
}

GXmlStreamWriterImpl::GXmlStreamWriterImpl(std::string fileName)
{
	/* Create a new XmlWriter for uri, with no compression. */
	fWriter = xmlNewTextWriterFilename(fileName.c_str(), 0);

	if( fWriter == nullptr  )
	{
		g_common_xml()->HandleError(  "xmlNewTextWriterFilename failed", GLOCATION_SRC, THROW_EXCEPTION );
	}

	XML(xmlTextWriterSetIndent(fWriter, 1), GLOCATION_SRC, "testXmlwriterFilename: Error at xmlTextWriterSetIndent");
	XML(xmlTextWriterSetIndentString(fWriter,  BAD_CAST "\t"),  GLOCATION_SRC,"Error setting xmlTextWriterSetIndentString");
	XML(xmlTextWriterStartDocument(fWriter, NULL, MY_ENCODING, NULL), GLOCATION_SRC, "testXmlwriterFilename: Error at xmlTextWriterStartDocument\n");
}

void GXmlStreamWriterImpl::WriteSingleTag(std::string tag)
{
	XML(xmlTextWriterStartElement(fWriter, BAD_CAST tag.c_str()), GLOCATION_SRC,"Error writing xmlTextWriterStartDocument");
	XML(xmlTextWriterEndElement(fWriter), GLOCATION_SRC,"Error writing xmlTextWriterEndElement");
}

void GXmlStreamWriterImpl::WriteSingleTag(std::string tag, std::vector<GXmlAttribute> attributes)
{
	XML(xmlTextWriterStartElement(fWriter, BAD_CAST tag.c_str()), GLOCATION_SRC,"Error writing xmlTextWriterStartDocument");
	for (size_t n = 0; n < attributes.size(); n++)
	{
		XML(xmlTextWriterWriteAttribute(fWriter, BAD_CAST attributes.at(n).GetName().c_str(), BAD_CAST attributes.at(n).GetValue().c_str()), GLOCATION_SRC, "Error writing xmlTextWriterWriteAttribute");
	}
	XML(xmlTextWriterEndElement(fWriter), GLOCATION_SRC, "Error writing xmlTextWriterEndElement");
}

void GXmlStreamWriterImpl::WriteStartTag(std::string tag)
{
	XML(xmlTextWriterStartElement(fWriter, BAD_CAST tag.c_str()), GLOCATION_SRC,"Error writing xmlTextWriterStartDocument");
}

void GXmlStreamWriterImpl::WriteStartTag(std::string tag, std::vector<GXmlAttribute> attributes)
{
	XML(xmlTextWriterStartElement(fWriter, BAD_CAST tag.c_str()), GLOCATION_SRC, "Error writing xmlTextWriterStartDocument");
	for (size_t n = 0; n < attributes.size(); n++)
	{
		XML(xmlTextWriterWriteAttribute(fWriter, BAD_CAST attributes.at(n).GetName().c_str(), BAD_CAST attributes.at(n).GetValue().c_str()), GLOCATION_SRC, "Error writing xmlTextWriterWriteAttribute");
	}
}

void GXmlStreamWriterImpl::WriteEndTag()
{
	XML(xmlTextWriterEndElement(fWriter), GLOCATION_SRC, "Error writing xmlTextWriterEndElement");
}

void GXmlStreamWriterImpl::WriteValueTag(std::string tag, std::string value)
{
	XML(xmlTextWriterWriteElement(fWriter, BAD_CAST tag.c_str(), BAD_CAST value.c_str()), GLOCATION_SRC, "Error writing xmlTextWriterWriteElement");
}

void GXmlStreamWriterImpl::WriteValueTag(std::string tag, std::vector<GXmlAttribute> attributes, std::string value)
{
	XML(xmlTextWriterStartElement(fWriter, BAD_CAST tag.c_str()), GLOCATION_SRC, "Error writing xmlTextWriterStartDocument");
	for (size_t n = 0; n < attributes.size(); n++)
	{
		XML(xmlTextWriterWriteAttribute(fWriter, BAD_CAST attributes.at(n).GetName().c_str(), BAD_CAST attributes.at(n).GetValue().c_str()), GLOCATION_SRC, "Error writing xmlTextWriterWriteAttribute");
	}
	XML(xmlTextWriterWriteString(fWriter, BAD_CAST value.c_str()), GLOCATION_SRC, "Error writing xmlTextWriterWriteString");
	XML(xmlTextWriterEndElement(fWriter), GLOCATION_SRC, "Error writing xmlTextWriterEndElement");
}

void GXmlStreamWriterImpl::WriteComment(std::string comment)
{
	XML(xmlTextWriterWriteComment(fWriter, BAD_CAST comment.c_str()), GLOCATION_SRC, "Error writing xmlTextWriterWriteComment");
}
