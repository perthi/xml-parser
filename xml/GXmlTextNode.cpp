// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "GXmlTextNode.h"
#include "GXmlEnum2String.h"

GXmlTextNode::GXmlTextNode(const std::string& text)
	: GXmlNodeImpl("", text)
{
}

eXML_NODETYPE GXmlTextNode::GetType() const
{
	return eXML_NODETYPE::ETextNode;
}


string GXmlTextNode::GetTypeS() const
{
	return  GXmlEnum2String::Enum2String ( eXML_NODETYPE::ETextNode );
}
