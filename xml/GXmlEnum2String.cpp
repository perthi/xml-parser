// -*- mode: c++ -*-
#include "GXmlEnum2String.h"

#include <sstream>
#include <string>
using std::string;


GXmlEnum2String::GXmlEnum2String()
{

}

GXmlEnum2String::~GXmlEnum2String()
{

}



string
GXmlEnum2String ::Enum2String(  const eXML_NODETYPE type )
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
