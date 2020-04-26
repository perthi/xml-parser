// -*- mode: c++ -*-

#pragma once

/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
***************************************************/

#include <string>
using std::string;

#include "GPrintable.h"
#include "GDefinitions.h"


class  GXmlEntity : public GPrintable
{
public:
	API GXmlEntity();
	virtual API ~GXmlEntity();
	virtual  string API str() const override = 0;


};

