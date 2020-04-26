// -*- mode: c++ -*-
#ifndef GXMLENUM2STRING_H
#define GXMLENUM2STRING_H


#include "GXmlEnums.h"
#include <string>

using std::string;


class  GXmlEnum2String
{
	public:
	   GXmlEnum2String();
	   virtual ~GXmlEnum2String();
	   static string  Enum2String( eXML_NODETYPE );
};

#endif
