// -*- mode: c++ -*-



#include <xml/GXmlValidator.h>



#include <iostream>
using std::cout;
using std::endl;



#include <memory>
#include <functional>

#include <xml/GDefinitions.h>
#include <xml/GXmlValidator.h>



bool help( );



int main(int argc, const char **  argv )
{
    /*
    string xml;
    string xsd;

    vector<string> tokens = g_tokenizer()->Tokenize(argc, argv);

    auto  xml_arg =  new  GCommandLineArgument < string >("-xml", "-xml [XML filename]", "The XML filename to use", &xml, fgkMANDATORY, 0 );
    auto  xsd_arg =  new  GCommandLineArgument < string >("-xsd", "-xsd [XSD filename]", "The XSD filename to use", &xsd, fgkMANDATORY, 0 );
    g->AddArgument(xml_arg);
    g->AddArgument(xsd_arg);


    if( g_string()->Contains(tokens, "-help") )
    {
        help();
        return 0;
    }


    bool has_error = false;

    auto  validator = std::make_shared<GXmlValidator>();

    try
    {
        if( validator->IsValid(xml, xsd) ==  true )
        {
            XML_INFO("SUCCSESS !!, %s is well formed and validated against %s", xml.c_str(), xsd.c_str() );
        }
        else
        {
            help();
            XML_FATAL("Failed to validate %s against %s", xml.c_str(), xsd.c_str() );
            has_error = true;
            return -1;
        }
    }
    catch(const std::exception& e)
    {
        help();
        XML_FATAL("%s", e.what() );
        has_error = true;
    }
    catch( const string e)
    {
        help();
        XML_FATAL("%s", e.c_str() ) ;
        has_error = true;
    }
    catch(...)
    {
        help();
        XML_FATAL( "Unknown exception caught parsing files: xml = %s\txsd = %s", xml.c_str(), xsd.c_str()  );
        has_error = true;
    }

    if( has_error == true )
    {

        return -1;
    }
    else
    {
        return -1;
    }

    // POP();

    */

    return 0;

}



bool
help(  )
{
    cout << "NOT YEST IMPLEMENTED" << endl;
    return true;
}