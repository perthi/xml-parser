// -*- mode: c++ -*-

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/



#ifdef _WIN32
#include <gtest/gtest.h>
#else
#include <gtest-linux/gtest.h>
#endif


int  main(int argc, char** argv) 
{ 
	::testing::InitGoogleTest(&argc, argv); 
	return  RUN_ALL_TESTS(); 
}

