// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "GXmlValidatorImpl.h"
//#include "GCommon.h"
//#include "GLocation.h"
//#include "GText.h"
#include "LEnums.h"
#include "GXmlMacros.h"

#include <libxml/xmlschemastypes.h>
#include <libxml/xmlerror.h>
#include <libxml/xmlschemas.h>
#include <libxml/xmlschemastypes.h>
#include <stdio.h>
#include <stdbool.h>
#include <libxml/xmlreader.h>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>

#ifdef HAS_LOGGING
#include <exception/GException.h>
#endif

bool GXmlValidatorImpl::fHasError = false;


#define SETPOS() { location = GLocation(__FILE__, __LINE__, __func__); }

static void schemaParseErrorHandler(void *ctx, xmlErrorPtr error)
{
	eLOGLEVEL loglevel =   GXmlValidatorImpl::ErrorLevel2Loglevel( error->level );
	fprintf(stderr, "filename: %s\n", error->file );

	g_common()->HandleError(  GText(  "Offending file: %s (error code %d) (from %s line[%d])",
	                                  error->message, error->code, __func__, __LINE__  ).str(),   GLocation(error->file, error->line,  "" ), DISABLE_EXCEPTION    );

	g_common()->HandleError(  GText( "%s line %d contains error(s)  !!!!!!!!",  __func__, __LINE__  ).str(),   GLocation(error->file, error->line,  "" ), DISABLE_EXCEPTION    );
	GXmlValidatorImpl::SetError(true);
}



void
GXmlValidatorImpl::SetError(const bool err)
{
	fHasError = err;
}

bool
GXmlValidatorImpl::HasError()
{
	return fHasError;
}

bool
GXmlValidatorImpl::IsValid(std::string xmlFilename, std::string xsdFilename)
{
	int has_schema_errors = 0;

	try
	{
		GLocation location = GLocation(__FILE__, __LINE__, __func__);
		
		FILE *fp = fopen(  xmlFilename.c_str(), "r" );

		if( fp == nullptr)
		{
			g_common()->HandleError( GText(  "Cannot find XML-file %s", xmlFilename.c_str() ).str(), GLOCATION, THROW_EXCEPTION );
		}
		else
		{
			fclose(fp);
		}

		fp = fopen(  xmlFilename.c_str(), "r" );

		if( fp == nullptr)
		{
			g_common()->HandleError( GText(  "Cannot find XSD-file %s", xsdFilename.c_str() ).str(), GLOCATION, THROW_EXCEPTION );
		}
		else
		{
			fclose(fp);
		}

		
		////////::xmlSetGenericErrorFunc(&location, DoError);
		SETPOS(); xmlSchemaParserCtxtPtr schemaTextParser = ::xmlSchemaNewParserCtxt(xsdFilename.c_str());
		
		if( schemaTextParser == nullptr )
		{
			g_common()->HandleError( "Could not create xmlSchemaParserCtxtPtr"   , GLOCATION, THROW_EXCEPTION );	
		}

		
		////////xmlSchemaSetParserErrors(schemaTextParser, DoError, DoWarning, &location);
		xmlSchemaSetParserStructuredErrors( schemaTextParser, schemaParseErrorHandler, &has_schema_errors);
		SETPOS(); xmlSchemaPtr schema = xmlSchemaParse(schemaTextParser);

		if( HasError() == true )
		{
			SetError(false);
			g_common()->HandleError( GText(   "XML file %s contains errors", xsdFilename.c_str()  ).str() , GLOCATION, THROW_EXCEPTION );
		}

		

		XML_ASSERT(schema != nullptr, "Could not parse xmlSchemaPtr", GLOCATION ) ;

		xmlSetGenericErrorFunc(&location, DoError );

		SETPOS(); xmlDocPtr doc = xmlReadFile(xmlFilename.c_str(), nullptr, 0);

	    XML_ASSERT(doc != nullptr,  GText( "Could not parse %s", xmlFilename.c_str() ).str(), GLOCATION );
       

		SETPOS(); xmlSchemaValidCtxtPtr ctxt = xmlSchemaNewValidCtxt(schema);
		xmlSchemaSetValidStructuredErrors(ctxt, schemaParseErrorHandler, &has_schema_errors);
		XML_ASSERT ( has_schema_errors == false, "XML ore XSD contains errors", GLOCATION );
		XML_ASSERT (ctxt != nullptr, "Could not Create", GLOCATION );
		//////	xmlSchemaSetValidErrors(ctxt, DoError, DoWarning, &location);

		SETPOS(); int ret = xmlSchemaValidateDoc(ctxt, doc);

		if( HasError() == true )
		{
			SetError(false);
			g_common()->HandleError( GText( "XML file %s contains errors", xmlFilename.c_str()  ).str() , GLOCATION, THROW_EXCEPTION  );
		}

		xmlSchemaFreeValidCtxt(ctxt);

		xmlFreeDoc(doc);
		XML_ASSERT( ret >= 0,  GText( "%s validation generated an internal error", xmlFilename.c_str() ).str(), GLOCATION  );

		return(ret == 0);
	}
	
	#ifdef HAS_LOGGING
	catch (GException & e)
	{
		g_common()->HandleError(  GText( "%s", e.what() ).str() , GLOCATION, DISABLE_EXCEPTION  );
		return false;
	}
	#endif
	catch( std::exception &e)
	{
		g_common()->HandleError(  GText( "%s", e.what() ).str() , GLOCATION, DISABLE_EXCEPTION  );
		CERR << e.what() << endl;
		return false;
	}
	catch(std::string &e)
	{
		CERR << e << endl;
	}
	catch (...)
	{
		g_common()->HandleError( "Unknown exception caught !!", GLOCATION, DISABLE_EXCEPTION  );
		return false;
	}

	return true;
}



void GXmlValidatorImpl::DoError(void *ctx, const char *msg, ...)
{
///	FORCE_DEBUG("Calling DO ERROR");
	GLocation location = *((GLocation*)ctx);
	char buff[10240];
	va_list ap;
	va_start(ap, msg);

	#ifdef _WIN32
	vsprintf_s(buff, sizeof(buff), msg, ap);
	#else
	vsnprintf (buff, sizeof(buff), msg, ap);
	#endif

	va_end(ap);
	g_common()->HandleError( buff, GLOCATION, DISABLE_EXCEPTION  );
}

void GXmlValidatorImpl::DoWarning(void * ctx, const char * msg, ...)
{
//	FORCE_DEBUG("Calling DO WARNING");
	GLocation location = *((GLocation*)ctx);
	char buff[10240];
	va_list ap;
	va_start(ap, msg);

	#ifdef _WIN32
	vsprintf_s(buff, sizeof(buff), msg, ap);
	#else
	vsnprintf (buff, sizeof(buff), msg, ap);
	#endif

	va_end(ap);
	g_common()->HandleError( buff, GLOCATION, DISABLE_EXCEPTION  );
}



eLOGLEVEL
GXmlValidatorImpl::ErrorLevel2Loglevel(const int level)
{
	switch (level)
	{
	case XML_ERR_NONE:
		 return eLOGLEVEL::LOG_INFO;
		 break;
	case XML_ERR_WARNING:
		 return eLOGLEVEL::LOG_WARNING;
		 break;
	case XML_ERR_ERROR:
		 return eLOGLEVEL::LOG_ERROR;
		 break;
	case XML_ERR_FATAL:
		 return eLOGLEVEL::LOG_FATAL;
		 break;
	default:
		 return eLOGLEVEL::LOG_DEBUG;
		break;
	}

}
