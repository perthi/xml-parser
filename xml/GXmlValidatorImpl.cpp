// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#include "GXmlValidatorImpl.h"
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

bool GXmlValidatorImpl::fHasError2 = false;


#define SETPOS() { location = GLocation(__FILE__, __LINE__, __func__); }

static void schemaParseErrorHandler(void *  /*ctx*/, xmlErrorPtr error)
{
	///eLOGLEVEL loglevel =   GXmlValidatorImpl::ErrorLevel2Loglevel( error->level );
	fprintf(stderr, "filename: %s\n", error->file );

	// FORCE_DEBUG("msg1 = %s", error->str1 );
	// FORCE_DEBUG("msg2 = %s", error->str2 );
	// FORCE_DEBUG("msg3 = %s", error->str3 );

	g_common_xml()->HandleError(  GTextXml(  "Offending file: %s (error code %d) (from %s line[%d])",
	                                  error->message, error->code, __func__, __LINE__  ).str(),   
									  GLocation(error->file, error->line,  "" ), 
									  DISABLE_EXCEPTION    );

	g_common_xml()->HandleError(  GTextXml( "%s line %d contains error(s)  !!!!!!!!", 
		                                 __func__, __LINE__  ).str(),   GLocation(error->file, error->line,  "" ), DISABLE_EXCEPTION    );
	GXmlValidatorImpl::SetError(true);
}



void
GXmlValidatorImpl::SetError(const bool err)
{
	fHasError2 = err;
}

bool
GXmlValidatorImpl::HasError()
{
	return fHasError2;
}


bool 
GXmlValidatorImpl::DoExistFile( const string f  )
{
	FILE *fp = fopen(  f.c_str(), "r" );

	if( fp == nullptr)
	{
		g_common_xml()->HandleError( GTextXml(  "Cannot find XML-file %s", f.c_str() ).str(), GLOCATION, THROW_EXCEPTION );
		return false;
	}
	else
	{
		fclose(fp);
		return true;
	}
}


bool
GXmlValidatorImpl::IsValid( string xml ,  string xsd )
{
	int has_schema_errors = 0;

	try
	{
		GLocation location = GLocation(__FILE__, __LINE__, __func__);

		XML_ASSERT(  DoExistFile( xml ), GTextXml("could not open file %s", xml.c_str() ).str() , GLOCATION  ) ;
		XML_ASSERT(  DoExistFile( xsd ), GTextXml("could not open file %s", xsd.c_str() ).str(), GLOCATION  ) ;

		::xmlSetGenericErrorFunc(&location, DoError);
		SETPOS(); xmlSchemaParserCtxtPtr schemaTextParser = ::xmlSchemaNewParserCtxt(xsd.c_str());
		
		if( schemaTextParser == nullptr )
		{
			g_common_xml()->HandleError( "Could not create xmlSchemaParserCtxtPtr"   , GLOCATION, THROW_EXCEPTION );	
		}

		xmlSchemaSetParserErrors(schemaTextParser, DoError, DoWarning, &location);
		xmlSchemaSetParserStructuredErrors( schemaTextParser, schemaParseErrorHandler, &has_schema_errors);
		SETPOS(); xmlSchemaPtr schema = xmlSchemaParse(schemaTextParser);

		if( HasError() == true )
		{
			SetError(false);
			g_common_xml()->HandleError( GTextXml(   "XML file %s contains errors", xsd.c_str()  ).str() , GLOCATION, THROW_EXCEPTION );
		}

		XML_ASSERT(schema != nullptr, "Could not parse xmlSchemaPtr", GLOCATION ) ;

		xmlSetGenericErrorFunc(&location, DoError );

		// schemaParseErrorHandler

		SETPOS(); xmlSchemaValidCtxtPtr ctxt = xmlSchemaNewValidCtxt(schema);
		xmlSchemaSetValidStructuredErrors(ctxt, schemaParseErrorHandler, &has_schema_errors);
		
		XML_ASSERT ( has_schema_errors == false, "XML ore XSD contains errors", GLOCATION );
		XML_ASSERT (ctxt != nullptr, "Could not Create", GLOCATION );
		
		xmlSchemaSetValidErrors(ctxt, DoError, DoWarning, &location);
		if( HasError() == true )
		{
			SetError(false);
			g_common_xml()->HandleError( GTextXml( "XML file %s contains errors", xml.c_str()  ).str() , GLOCATION, THROW_EXCEPTION  );
		}

		SETPOS(); xmlDocPtr doc = xmlReadFile(xml.c_str(), nullptr, 0);
		XML_ASSERT(doc != nullptr,  GTextXml( "Could not parse %s", xml.c_str() ).str(), GLOCATION );
		SETPOS(); int ret = xmlSchemaValidateDoc(ctxt, doc);
		xmlSchemaFreeValidCtxt(ctxt);
		
		xmlFreeDoc(doc);
		
		XML_ASSERT( ret >= 0,  GTextXml( "%s validation generated an internal error", xml.c_str() ).str(), GLOCATION  );

		return(ret == 0);
	}
	
	#ifdef HAS_LOGGING
	catch (GException & e)
	{
	//	g_common_xml()->HandleError(  GTextXml( "%s", e.what() ).str() , GLOCATION, DISABLE_EXCEPTION  );
		throw(e);	
		return false;
	}
	#endif
	catch( std::exception &e)
	{
		//g_common_xml()->HandleError(  GTextXml( "%s", e.what() ).str() , GLOCATION, DISABLE_EXCEPTION  );
		throw(e);
		return false;
	}
	catch(std::string &e)
	{
		CERR << e << endl;
	}
	catch (...)
	{
		g_common_xml()->HandleError( "Unknown exception caught !!", GLOCATION, DISABLE_EXCEPTION  );
		return false;
	}

	return true;
}


void GXmlValidatorImpl::DoError(void *ctx, const char *msg, ...)
{
//    XML_FATAL("Calling DO ERROR");
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

	g_common_xml()->HandleError( buff, location , DISABLE_EXCEPTION  );
}

void GXmlValidatorImpl::DoWarning(void * ctx, const char * msg, ...)
{
 //   XML_FATAL("Calling DO WARNING");
	
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
	g_common_xml()->HandleError( buff,  location, DISABLE_EXCEPTION  );
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
