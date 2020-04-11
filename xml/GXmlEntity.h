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

#include <utilities/GPrintable.h>
#include <utilities/GDefinitions.h>


struct  GXmlEntity : public GPrintable
{
	API GXmlEntity();
	virtual API ~GXmlEntity();
	virtual  string API str() const override = 0;


};

