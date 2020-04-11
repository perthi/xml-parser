// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#ifndef GXMLVALIDATORIMPL_H
#define GXMLVALIDATORIMPL_H

#include <string>
#include <libxml/xmlerror.h>
#include <xml/GDefinitions.h>

#include "LEnums.h"

class GXmlValidatorImpl
{
public:
	static bool  API  IsValid(std::string xmlFilename, std::string xsdFilename);
	static void  API  SetError(const bool err);
	static bool  API  HasError();
	static eLOGLEVEL  ErrorLevel2Loglevel(const int level);

private:
	static void  DoError(void *ctx, const char *msg, ...);
	static void  DoWarning(void *ctx, const char *msg, ...);

	static bool fHasError;

};

#endif // !GXMLVALIDATORIMPL_H
