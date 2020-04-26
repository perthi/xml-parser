// -*- mode: c++ -*-

#include <xml/GXmlValidator.h>

#include <iostream>
using std::cout;
using std::endl;

#include <memory>
#include <functional>
#include <xml/GDefinitions.h>
#include <xml/GXmlValidator.h>

#include <xml/GXmlMacros.h>
#include <xml/LEnums.h>
#include <xml/GColor.h>
#include <xml/GLocationXml.h>
#include <xml/GCommonXML.h>

bool help(  const string exename );
/// int LogeLevel2Color(   const eLOGLEVEL level  );


/// void PrintMessage( const string msg, const GLocationXml l, const eLOGLEVEL level, bool fileinfo = true );
void ScanArguments( int argc, const char ** argv, string &xml, string &xsd );


int main(int argc, const char **  argv )
{
    string xml =  "";
    string xsd =  "";

    ScanArguments( argc, argv, xml, xsd );

    bool has_error = false;
    auto  validator = std::make_shared<GXmlValidator>();

    try
    {
        if( validator->IsValid(xml, xsd) ==  true )
        {
          ///  PrintMessage( GTextXml( "SUCCSESS !!, %s is well formed and validated against %s", xml.c_str(), xsd.c_str() ).str(), GLOCATION_SRC, eLOGLEVEL::LOG_INFO    );
            g_common_xml()->HandleError(GTextXml("SUCCSESS !!, %s is well formed and validated against %s", xml.c_str(), xsd.c_str()).str(), GLOCATION_SRC, DISABLE_EXCEPTION );
        }
        else
        {
            // HandleError(const string message, const GLocationXml  l_xml, const bool   disable_exception)
            g_common_xml( )->HandleError( GTextXml(  "Failed to validate %s against %s", xml.c_str(), xsd.c_str()).str(), 
                GLOCATION_SRC, DISABLE_EXCEPTION   );
            help( string( argv[0] )  );
            has_error = true;
            return -1;
        }
    }
    catch(const std::exception&  /*e*/)
    {
        //PrintMessage(  string( e.what()), GLOCATION_SRC, eLOGLEVEL::LOG_FATAL   );
        help( string( argv[0] )  );
        has_error = true;
    }
    catch( const string e)
    {
        ///PrintMessage(  e,  GLOCATION_SRC, eLOGLEVEL::LOG_FATAL   );
        has_error = true;
    }
    catch(...)
    {
        ///PrintMessage(   GTextXml( "Unknown exception caught parsing files: xml = %s\txsd = %s", xml.c_str(), xsd.c_str() ).str()  ,     GLOCATION_SRC, eLOGLEVEL::LOG_ERROR   );
        help( string( argv[0] )  );
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

    return 0;
}


void 
ScanArguments( int argc, const char ** argv, string &xml, string &xsd )
{
    COUT << "ARGC = " << argc << endl;
    if( argc < 2 || argc > 3 )
    {
        help( argv[0] );
    }
    else
    if( argc  == 2 &&   ( string(argv[1]) == "-h"  || string(argv[1]) == "--help"   ) )
    {
        help( argv[0] );
    } 
    else
    {
        COUT "TP0" << endl;
        xml = string(argv[1]);
        xsd = string( argv[2]);
    }
}



//void 
//PrintMessage( const string msg, const GLocationXml l, const eLOGLEVEL level, bool fileinfo  )
//{
//    int color_code = LogeLevel2Color(level);
//    #ifdef _WIN32
//            static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//            if (fgEnableColor == true)
//            {
//                SetConsoleTextAttribute(hConsole,  color_code );
//            }
//            cout << string(msg->fMsg);
//#else           
//            string msg_out = "";
//
//            if( fileinfo == true )
//            {
//                msg_out = l.str() + ":" + msg; 
//            }
//            else
//            {
//                msg_out = msg;
//            }
//            cout << "\033" << "[1;"  << color_code << "m"  <<  msg_out << "\033" << "[0m" << endl;
//#endif  
//#ifdef _WIN32            
//            SetConsoleTextAttribute(hConsole, CONSOLE_DEFAULT);
//#endif     
//
//}


//int
//LogeLevel2Color (  const  eLOGLEVEL level  )
//{
//    switch (  level )
//    {
//    case  eLOGLEVEL::LOG_FORCE_DEBUG:
//        return A_ORANGE;      
//        break;
//    case  eLOGLEVEL::LOG_DEBUG:
//        return  A_CYAN ;      
//        break;    
//  case  eLOGLEVEL::LOG_INFO:
//        return  A_GREEN ;      
//        break;  
//    case  eLOGLEVEL::LOG_WARNING:
//        return  A_YELLOW ;      
//        break;   
//    case  eLOGLEVEL::LOG_ERROR:
//        return  A_RED ;      
//        break;  
//
//  case  eLOGLEVEL::LOG_FATAL:
//        return  A_PURPLE ;      
//        break;  
//  case  eLOGLEVEL::LOG_OFF:
//  case  eLOGLEVEL::LOG_ALL:
//        return A_GRAY;
//        break;
//    default:
//        break;
//    }
//
//    return 0;
//}



bool
help( const string ex )
{
    cout << endl;
    g_common_xml()->HandleError(GTextXml("Usage: %s  [xml-file]  [xsd-file]", ex.c_str()).str(), GLOCATION_SRC, DISABLE_EXCEPTION );
 ///   PrintMessage(  GText( "Usage: %s  [xml-file]  [xsd-file]", ex.c_str() ).str()  ,  GLOCATION, eLOGLEVEL::LOG_INFO, false );
    cout << endl;
    return true;
}