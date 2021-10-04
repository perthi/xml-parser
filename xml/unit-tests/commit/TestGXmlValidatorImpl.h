// -*- mode: c++ -*-

#ifndef TESTGXMLVALIDATORIMPL_H
#define TESTGXMLVALIDATORIMPL_H

/****************************************************
* Copyright: Embedded Consulting AS and others.
* For more information please contact pth@embc.no
******************************************************/

#ifdef _WIN32
#include <gtest/gtest.h>
#else
#include <gtest-embc/gtest.h>
#endif

#include <string>

using std::string;


class TestGXmlValidatorImpl : public testing::Test
{
    protected:
        static void SetUpTestCase();

        static string fDataDir;

};

#endif // !TESTGXMLVALIDATORIMPL_H
