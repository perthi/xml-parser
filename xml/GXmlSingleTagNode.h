// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once
#include "GXmlTagNode.h"
#include "GXmlEnums.h"
#include "GXmlEnum2String.h"

class GXmlSingleTagNode : public GXmlTagNode
{
public:
	using GXmlTagNode::GXmlTagNode;
	virtual eXML_NODETYPE GetType() const override { return eXML_NODETYPE::ESingleTagNode; }
	virtual string GetTypeS() const override { return  GXmlEnum2String::Enum2String ( eXML_NODETYPE::ESingleTagNode ); }

};