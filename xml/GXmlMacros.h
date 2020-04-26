

#include  "GCommonXML.h"
#include  "GTextXml.h"

#ifdef HAS_LOGGING
#include  <utilities/GLocation.h>
#else
#include  "GLocationXml.h"
#endif

#define XML(s,l, m) \
if( s >= 0 ) \
{ \
   g_common_xml()->HandleError( m, l, THROW_EXCEPTION ); \
}



#define XML_ASSERT(expr, m, l)  \
if(! (expr) ) \
{ \
   g_common_xml()->HandleError( m, l, THROW_EXCEPTION ); \
}


