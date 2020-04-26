// -*- mode: c++ -*-

/*****************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                       ****
******************************************************************************/

/*****************************************************************************
******************************************************************************
*** This file is part of logmaster.                                        ***
*** Copyright (C) 2018 Per Thomas Hille <pth@embc.no> http:///www.embc.no  ***
*** all rights reserved                                                    ***
***                                                                        ***
*** logmaster is free software: you can redistribute it and/or modify      ***
*** it under the terms of the Lesser GNU General Public License (LGPL)     ***
*** as published by the Free Software Foundation, either version 3 of the  ***
*** License, or (at your option) any later version.                        ***
***                                                                        ***
*** logmaster is distributed in the hope that it will be useful,           ***
*** but WITHOUT ANY WARRANTY; without even the implied warranty of         ***
*** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          ***
*** GNU General Public License for more details.                           ***
***                                                                        ***
*** You should have received a copy of the Lesser GNU General Public       ***
*** License along with logmaster in the README file in the source code     ***
*** directory. If not, see <http://www.gnu.org/licenses/>.                 ***
******************************************************************************
******************************************************************************/

#include  "GCommonXML.h"
#include  "GDefinitions.h"


#ifdef HAS_LOGGING
#include <logging/LLogApi.h>
#include <utilities/GLocation.h>
#include <xml/GLocationXml.h>
#include <exception/GException.h>
using namespace LOGMASTER;
#else
#include "GLocationXml.h"
#endif

#include <iostream>
using std::cout;
using std::endl;
using std::cerr;



GCommonXML * g_common_xml()
{
	static GCommonXML *instance = new GCommonXML();
	return instance;
}




#ifdef HAS_LOGGING
void
GCommonXML::HandleError(const string message, const GLocationXml  l_xml,   const bool   disable_exception  )
{
    GLocation l(  l_xml.fFileName, l_xml.fLineNo, l_xml.fFunctName  );

    if ( disable_exception == false)
    {
        FORCE_DEBUG("l = %s", l.c_str()  );
        throw_exception(   GException(l.fFileName, l.fFunctName, l.fLineNo, eMSGSYSTEM::SYS_EX, "%s", message.c_str( ))  )  ;
    }
    else
    {
        FORCE_DEBUG("l = %s", l.c_str()  ); 
        XML_ERROR( (message  + string ( l.c_str() ) ).c_str()  );
    }
}

#else

void
GCommonXML::HandleError(const string message, const GLocationXml l, const bool   disable_exception  )
{
    if ( disable_exception == false)
    {
    #ifdef _WIN32
		throw( std::exception(message.c_str() ) );
	#else
		throw(std::invalid_argument( message.c_str() ));
	#endif
    }
    else
    {
        cout << l.fFileName << "::" << l.fFunctName << ", line " << l.fLineNo << ";" << message << std::endl;
    }
}

#endif



