// -*- mode: c++ -*-
#ifndef GSTRING2NUMBER_H
#define GSTRING2NUMBER_H


#include <string>
using std::string;


class  GString2Number
{
	public:	
		GString2Number();
		virtual ~GString2Number();

		double ToNumber( const string num );

};

#endif
