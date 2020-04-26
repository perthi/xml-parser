// -*- mode: c++ -*-


/*****************************************************************************
***          Author: Per Thomas Hille <pth@embc.no>                       ****
******************************************************************************/

/*****************************************************************************
******************************************************************************
*** This file is part of logmaster.                                        ***
*** Copyright (C) Per Thomas Hille <pth@embc.no>  http:///www.embc.no      ***
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

#include "GTextXml.h"
#include <cstdarg>

#define GTextXml_MAX_SIZE 4096


GTextXml::GTextXml(const char * fmt, ...) : fText("")
{
    va_list ap;
    va_start(ap, fmt);
    SetGTextXml(fmt, ap);
    va_end(ap);
 }


// GTextXml::GTextXml(char *message, const int n, const char * fmt, ...) : fText("")
// {
//     va_list ap;
//     va_start(ap, fmt);
//     vsnprintf(message, n-1 , fmt, ap);
//     SetGTextXml(fmt, ap);
//     va_end(ap);
// }


GTextXml::GTextXml(const string s ) : fText("")
{   
   fText = s;
}


void
GTextXml::SetGTextXml(const char *fmt, va_list ap)
{
    static char msg[GTextXml_MAX_SIZE]; // CRAP PTH
    vsnprintf(msg, sizeof(msg) -1, fmt, ap);
    fText = string(msg);
}



GTextXml & 
GTextXml::operator  = (const char *rhs)
{
    this->SetGTextXml(rhs);
    return *this;
}


void 
GTextXml::SetGTextXml(const char *txt)
{
    fText =  string(txt);
}




string    
GTextXml::str() const 
{ 
    return fText; 

}


int64_t  
GTextXml::size() const
{
    return fText.size();
}


const char *  
GTextXml::c_str() const 
{ 
    return fText.c_str(); 
}


const char *
GTextXml::what() const
{ 
    return fText.c_str(); 
}

