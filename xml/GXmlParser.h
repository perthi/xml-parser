// -*- mode: c++ -*-

/***************************************************
* @copyright Kongsberg Ferrotech                   *
* @author Per Thomas Hille <pth@embc.no>           *
*                                                  *
* SW developed by Embedded Consulting AS           *
* for Semcon Norge AS                              *
****************************************************/

#pragma once

#include  <xml/GXmlNode.h>
#include  <xml/GXmlStreamReader.h>
#include  <xml/GXmlAttribute.h>
#include  <xml/GString2Number.h>

#include "GXmlParser.h"
#include "GXmlMacros.h"
#include  <xml/GCommon.h>
#include <stdio.h>
#include <string.h>

#include <string>
using std::string;
#include <memory>

#include <map>
using std::map;

#include <vector>
using std::vector;

class GXmlEntity;

#ifdef HAS_LOGGING
#include <logging/LLogApi.h>
#include <exception/GException.h>
using namespace LOGMASTER;
#endif


class GXmlParser
{
public:
    API GXmlParser();
    API virtual ~GXmlParser();
	virtual  vector< std::shared_ptr<GXmlEntity> > API ParseXML(const string  /*xml*/, const string  /*xsd*/ )  = 0;
	inline string  Enum2String( eXML_NODETYPE );

    template<typename T>
	inline T String2Enum(const string hash, std::map<string, T>*);

protected:
	template<typename T = string>
    inline T  GetTagValue( std::shared_ptr<GXmlStreamReader> xmlReader,  const string tagname, const bool read_node  = true);

	template<typename T>
	inline T  GetTagValue( std::shared_ptr<GXmlStreamReader> xmlReader,  const string tagname, GLocation l ,const bool read_node  = true );

	template<typename T >
	inline T     GetTagValueOrNothing( std::shared_ptr<GXmlStreamReader> xmlReader, const string tagname, GLocation l, bool *has_value ,const bool read_node = true );

	void   AssertTagOpenGroup(std::shared_ptr<GXmlStreamReader> xmlReader, const string, GLocation l, const bool read_node = true );
	void   AssertTagCloseGroup(std::shared_ptr<GXmlStreamReader> xmlReader, const string, GLocation l,  const bool read_node = true  );
	void   AssertTag(std::shared_ptr<GXmlStreamReader> xmlReader, const string, GLocation l, eXML_NODETYPE node_type, const bool read_node = true  );
	void   PrinttAttributes( const GXmlNode * const node , GLocation l );
	bool   HasAttributes(  const GXmlNode * const node ) const;

  	template < typename T>    string Hash2String( const map< string, T>   *m, const int ncols = 8, const string sep = "");
};



inline string
GXmlParser::Enum2String(  const eXML_NODETYPE type )
{
	switch (type )
	{
	  case eXML_NODETYPE::EOpenTagNode:
				return "EOpenTagNode";
			  break; 
      case eXML_NODETYPE::ECloseTagNode:
			return "ECloseTagNode";
			  break; 
      case eXML_NODETYPE::ESingleTagNode:
			return "ESingleTagNode";
			  break; 
      case eXML_NODETYPE::ETextNode:
			return "ETextNode";
			  break; 
      case eXML_NODETYPE::ECommentNode:
			return "ECommentNode";
			  break; 
      case eXML_NODETYPE::EProcInstrNode:
			return "EProcInstrNode";
			  break; 
      case eXML_NODETYPE::EDocTypeNode:
			return "EDocTypeNode";
			  break; 
      case eXML_NODETYPE::ECDataNode:
			return "ECDataNode";
			break;
		case eXML_NODETYPE::UNKNOWN :
			return "UNKNOWN";
			break;	
	default:
		std::stringstream buffer;
		buffer << 	"Type not" << (int)type << "reckognized";
		return  buffer.str();	
		break;
	}

}


template<typename T>
inline T
GXmlParser::GetTagValue( std::shared_ptr<GXmlStreamReader> xmlReader, const string tagname,const bool read_node  )
{
	GXmlNode	*node = nullptr;
	if( read_node == true)
	{
		node	= xmlReader->ReadNode();
	}
	else
	{
		node	= xmlReader->GetCurrentNode();	
	}

	

	XML_ASSERT( node != nullptr,  "  xmlReader->ReadNode() returned a ZERO POINTER !!!", GLOCATION );

	if( node->GetType()  == eXML_NODETYPE::ESingleTagNode)
	{
		g_common()->HandleError( GText( "%s is a single tag node (with no value) !!", tagname.c_str() ).str(), GLOCATION, DISABLE_EXCEPTION );
		vector<GXmlAttribute> tmp =  node->GetAttributes();

		// for (size_t i = 0; i < tmp.size(); i++)
		// {
		// 	FORCE_DEBUG("Attribute name= %s, value = %s",tmp.at(i).GetName(), tmp.at(i).GetValue() );
		// }
		 return "";
	}

	XML_ASSERT( node->GetType() == eXML_NODETYPE::EOpenTagNode, 
	GText("Unexpcted node type %d (name = %s, type = %s, value = %s)", 
	                 node->GetType(), 
					 node->GetName().c_str(),   
					 Enum2String(node->GetType()).c_str(),  
					 node->GetValue().c_str() ).str() , GLOCATION ) ;
	
	string name = node->GetName();
	XML_ASSERT(node->GetName() == tagname, 
	GText( "expected %s, got %s (type = %s)", tagname.c_str(), node->GetName().c_str(),  Enum2String( node->GetType()).c_str()  ).str(), GLOCATION );
	
	
	node =  xmlReader->ReadNode();

	if (node->GetType() == eXML_NODETYPE::ECloseTagNode)
	{
		return "";
	}

	string value = node->GetValue();
	node = xmlReader->ReadNode();
	return value;
}


template < >
inline int
GXmlParser::GetTagValue( std::shared_ptr<GXmlStreamReader> xmlReader, const string tagname, const bool read_node   )
{
    string tmp =  GetTagValue( xmlReader, tagname, read_node);
	return (int)GString2Number().ToNumber(tmp);
  ///  return g_numbers()->ToInteger(tmp);
}


template < >
inline float
GXmlParser::GetTagValue( std::shared_ptr<GXmlStreamReader> xmlReader, const string tagname, const bool read_node  )
{
    string tmp =  GetTagValue( xmlReader, tagname, read_node);
	
	return (float)GString2Number().ToNumber(tmp);
	
	///return g_numbers()->ToFloat<float>(tmp);
}


template < >
inline bool
GXmlParser::GetTagValue( std::shared_ptr<GXmlStreamReader> xmlReader, const string tagname, const bool read_node  )
{
    string tmp =  GetTagValue( xmlReader, tagname, read_node);

    if(tmp == "true")
	{
		return true;
	}
	else if(tmp == "false")
	{
		return false;
	}
	else
	{
		g_common()->HandleError(  GText(  "unexpected value for boolean %s, expected either \"true\" or \"false\"",  tmp.c_str() ).str(), GLOCATION, THROW_EXCEPTION  );
	}

	return false;
}


template<typename T>
inline T
GXmlParser::GetTagValue( std::shared_ptr<GXmlStreamReader> xmlReader,  const string tagname, GLocation l, const bool read_node )
{
///	LLogging::Instance()->Log(  eMSGLEVEL::LOG_INFO, eMSGSYSTEM::SYS_XML, l,  "tag = %s", tagname.c_str() );
	return 	GetTagValue<T>( xmlReader,  tagname , read_node );
}




template<typename T>
inline T
GXmlParser::String2Enum(const string hash, std::map<string, T>* m)
{
	auto it = m->find(hash);

	XML_ASSERT(it != m->end(), 
	GText( "could not find enum for hash tag %s, \n legal values are: %s", hash.c_str(), Hash2String(m).c_str()).str() ,
	GLOCATION ) ;
	
	return (T)it->second;
}


template<typename T>
inline T
GXmlParser::GetTagValueOrNothing( std::shared_ptr<GXmlStreamReader> xmlReader, const string tagname, GLocation l, bool *has_value,  const bool read_node )
{
	string tmp = GetTagValue<string>( xmlReader, tagname, l, read_node  );
	if(tmp == "")
	{
///		XML_INFO("value for %s is empty", tagname.c_str()  );
		*has_value = false;
		return (T)-1;
	}
	else
	{
	///	T ret = g_numbers()->ToNumber<T>(tmp);
	    T ret = (T)GString2Number().ToNumber(tmp);
		*has_value = true;
		return ret;
		//return -1;
	}
}

/*** Takes as input a hasmap and extracts the hash codes into a vector.
 *   For instance if the input is map<string, int> (i.e the hash code is a string)
 *   then the function returns a string with all the hash entries in the map. The string
 *   is formatted according to the prameters "ncols" and "sep"
 *   @tparam T1 the type of the hash entries (not used)
 *   @param[in] m The hash map to process
 *   @param[in]  ncols The number of colums printed to the output. 
 *   @param[in] sep   The separator used between each antry in a column. Default is "tab"
 *   @return a vector of hash codes/entries */
template <typename T>
string 
GXmlParser::Hash2String(const map<string, T> *m, const int ncols, const string sep)
{
    std::stringstream buffer;

    int i = 0;

    for (auto iter = m->begin(); iter != m->end(); ++iter)
    {
        if (i % ncols == 0 && i != 0)
        {
            buffer << endl;
        
        }
        string tmp = iter->first;
        if (sep == "")
        {
            buffer << iter->first << (strlen(tmp.c_str()) < 8 ? "\t\t" : "\t");
        }
        else
        {
            buffer << iter->first << sep;
        }
        i++;
    }

    return buffer.str();
}

