// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once

#include "GXmlTagNode.h"
#include "GXmlEnum2String.h"

class GXmlOpenTagNode : public GXmlTagNode
{
public:
	using GXmlTagNode::GXmlTagNode;
	virtual eXML_NODETYPE GetType() const override { return eXML_NODETYPE::EOpenTagNode; }
	virtual string GetTypeS() const override { return  GXmlEnum2String::Enum2String(  eXML_NODETYPE::EOpenTagNode ); }
};