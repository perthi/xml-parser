// -*- mode: c++ -*-
#pragma once



enum class eXML_NODETYPE
    {
     EOpenTagNode = 1, 
     ECloseTagNode = 2, 
     ESingleTagNode = 3, 
     ETextNode = 4, 
     ECommentNode = 5, 
     EProcInstrNode = 6, 
     EDocTypeNode = 7 , 
     ECDataNode =8,
     UNKNOWN = 99
    };
