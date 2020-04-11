

#include  <xml/GCommon.h>
#include  <xml/GText.h>

#ifdef HAS_LOGGING
#include  <utilities/GLocation.h>
#else
#include  <xml/GLocation.h>
#endif

#define XML(s,l, m) \
if( s >= 0 ) \
{ \
   g_common()->HandleError( m, l, THROW_EXCEPTION ); \
}



#define XML_ASSERT(expr, m, l)  \
if(! (expr) ) \
{ \
   g_common()->HandleError( m, l, THROW_EXCEPTION ); \
}


