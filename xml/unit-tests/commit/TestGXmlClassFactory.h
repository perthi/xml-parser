// -*- mode: c++ -*-

#ifndef TESTGXMLCLASSFACTORY_H
#define TESTGXMLCLASSFACTORY_H


/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#ifdef _WIN32
#include <gtest/gtest.h>
#else
#include <gtest-linux/gtest.h>
#endif



class TestGXmlClassFactory : public testing::Test
{
public:
	virtual void SetUp() override;
	TestGXmlClassFactory();
	~TestGXmlClassFactory();
};

#endif // !TESTGXMLCLASSFACTORY_H