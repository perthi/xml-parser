// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "GXmlCDataNode.h"
#include "GXmlEnum2String.h"

GXmlCDataNode::GXmlCDataNode(const std::string& value)
	: GXmlNodeImpl("", value)
{
}


eXML_NODETYPE  
GXmlCDataNode::GetType() const
{
	return eXML_NODETYPE::ECDataNode;
}


string  
GXmlCDataNode::GetTypeS() const
{
	return  GXmlEnum2String::Enum2String (eXML_NODETYPE::ECDataNode );
}
