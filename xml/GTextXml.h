// -*- mode: c++ -*-

#pragma once

/****************************************************************************
*** Copyright(C) 2015  Per Thomas Hille, pth@embc.no                     ***
*** This file is part of logmaster. logmaster is free software : you can ***
*** redistribute it and / or modify it under the terms of the Lesser GNU ***
*** General Public License (LGPL) V3 or later. See .cpp file for details ***
*****************************************************************************/

#include  "GDefinitions.h"
#include  "GPrintable.h"

#include <string>
using std::string;
#include <stdint.h>

/** @brief Generate a text object using printf formatting */
class GTextXml : public GPrintable
{
public:
   API GTextXml (const char * fmt, ... );
   ///API GTextXml (char *message, const int n, const char * fmt, ...);
   API GTextXml (const string s );
   string             API    str() const  override;
   int64_t            API    size() const;
   const              API    char *    what() const;
   const char         API  * c_str() const;
   void               API    SetGTextXml(const char *txt);
  
   GTextXml &  operator  = (const char *rhs);
   void                SetGTextXml(const char *fmt, va_list ap);

private:
  
    GTextXml() : fText("") {};
    string fText;
};


inline string operator  + (const GTextXml &lhs, const string &rhs);
inline string operator  + (const string &lhs, const GTextXml &rhs);
inline bool operator  == (const GTextXml &lhs, const string &rhs);
inline bool operator  == (const string &lhs, const GTextXml &rhs);
inline bool operator  != (const GTextXml &lhs, const string &rhs);
inline bool operator  != (const string &lhs, const GTextXml &rhs);



inline string operator  + (const GTextXml &lhs, const string &rhs)
{
    return  lhs.str() + rhs;
}


inline string operator  + (const string &lhs, const GTextXml &rhs)
{
    return  lhs + rhs.str();
}


inline bool operator  == (const GTextXml &lhs, const string &rhs)
{
    if (lhs.str() == rhs)
    {
        return true;
    }
    else
    {
        return false;
    }
}


inline bool operator  == (const string &lhs, const GTextXml &rhs)
{
    if (rhs.str() == lhs)
    {
        return true;
    }
    else
    {
        return false;
    }
}


inline bool operator  != (const GTextXml &lhs, const string &rhs)
{
    if (lhs.str() == rhs)
    {
        return  false;
    }
    else
    {
        return true;
    }
}


inline bool operator  != (const string &lhs, const GTextXml &rhs)
{
    if (rhs.str() == lhs)
    {
        return false;
    }
    else
    {
        return true;
    }
}
