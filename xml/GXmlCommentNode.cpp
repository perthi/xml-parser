// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "GXmlCommentNode.h"
#include "GXmlEnum2String.h"

GXmlCommentNode::GXmlCommentNode(const std::string& comment) : GXmlNodeImpl("", comment)
{

}


eXML_NODETYPE GXmlCommentNode::GetType() const
{
	return eXML_NODETYPE::ECommentNode;
}

string GXmlCommentNode::GetTypeS() const
{
	return  GXmlEnum2String::Enum2String(eXML_NODETYPE::ECommentNode);
}
