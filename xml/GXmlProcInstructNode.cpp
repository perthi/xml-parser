// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/


#include "GXmlProcInstructNode.h"
#include "GXmlEnum2String.h"


GXmlProcInstructNode::GXmlProcInstructNode(const std::string& target, const std::string& content)
	: GXmlNodeImpl(target, content)
{
}


eXML_NODETYPE 
GXmlProcInstructNode::GetType() const
{
	return eXML_NODETYPE::EProcInstrNode;
}


string 
GXmlProcInstructNode::GetTypeS() const
{
	return GXmlEnum2String::Enum2String( eXML_NODETYPE::EProcInstrNode);
}

