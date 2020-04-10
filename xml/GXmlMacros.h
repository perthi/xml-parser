

#include  "GCommon.h"
#include  "GText.h"
#include  "GLocation.h"

#define XML(s,l, m) \
if( s >= 0 ) \
{ \
   g_common()->HandleError( m, l, THROW_EXCEPTION ); \
}



#define XML_ASSERT_EXCEPTION(expr, m, l)  \
if(! (expr) ) \
{ \
   g_common()->HandleError( m, l, THROW_EXCEPTION ); \
}


