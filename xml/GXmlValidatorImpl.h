// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#ifndef GXMLVALIDATORIMPL_H
#define GXMLVALIDATORIMPL_H

#include  "GDefinitions.h"
#include  "LEnums.h"

#include <string>
using std::string;

#include <libxml/xmlerror.h>

class GXmlValidatorImpl
{
public:
	static bool  API  IsValid( string xmlFilename,  string xsdFilename);
	static void  API  SetError(const bool err);
	static bool  API  HasError();
	static eLOGLEVEL  ErrorLevel2Loglevel(const int level);

private:
	static void  DoError(void *ctx, const char *msg, ...);
	static void  DoWarning(void *ctx, const char *msg, ...);

	static bool DoExistFile( const string fname );

	static bool fHasError2;

};

#endif // !GXMLVALIDATORIMPL_H
