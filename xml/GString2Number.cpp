// -*- mode: c++ -*-


#include "GString2Number.h"
#include "GXmlMacros.h"
#include <xml/GLocationXml.h>

#include <iostream> 
#include <string>


GString2Number::GString2Number()
{

}

GString2Number::~GString2Number()
{

}


double 
GString2Number::ToNumber( const string num )
{
    std::string::size_type sz = 0;
    double d = -9999;

    try
    {
        d = std::stoi(num, &sz);

        if (sz > 0)
        {
            return d;
        }
        else
        {
            d = std::stod(num, &sz);
        
             if (sz > 0)
            {
                return d;
            } 
        
        }
    }
    catch (const std::exception &e)
    {
        g_common_xml()->HandleError( GTextXml("exection caught trying to convert \"%s\" to a number ", num.c_str()  ).str() , GLOCATION_XML, THROW_EXCEPTION );
        return d;
    
    }

    return d;

}