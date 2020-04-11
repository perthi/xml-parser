// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#pragma once
#include "GXmlNodeImpl.h"
#include "GXmlEnums.h"

#include <string>
using std::string;

class GXmlCDataNode : public GXmlNodeImpl
{
public:
	GXmlCDataNode(const string& value);
	virtual eXML_NODETYPE GetType() const override;
	virtual string GetTypeS() const override;
};