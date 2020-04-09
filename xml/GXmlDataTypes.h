// -*- mode: c++ -*-

#pragma once

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include <utilities/GDefinitions.h>
#include <utilities/MBDataTypes.h> 


class XMLFile_t  : public MBDataType<string> 
{ 
public:
    XMLFile_t ( ) : MBDataType("") {};
    XMLFile_t ( string val) : MBDataType(val) {};
};

class XSDFile_t  : public MBDataType<string> 
{ 
public:
    XSDFile_t ( ) : MBDataType("") {};
    XSDFile_t ( string val) : MBDataType(val) {};
};
