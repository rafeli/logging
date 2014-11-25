#ifndef _LOGGING_HPP
#define _LOGGING_HPP

#define DEBUGD  30
#define DEBUG   20
#define INFO    10
#define WARNING 5
#define ERROR   1
#define THROWING 2


 #define MYLOG(n,s)                         \
  (*Logging::buffer) << s;                 \
  Logging::log(n,__PRETTY_FUNCTION__ )


// #define MYLOG(n,s)

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


class Logging  {


private:
  static const int logLevel =  DEBUG;
  static std::ofstream *ofs;

public:

  // maybe suboptimal: Logging is a MACRO and needs public access
  // to this buffer. Could write a public getBuffer, but does that help?
  static std::stringstream* buffer;

  //Constructor and Destructor (werden noch nicht gebraucht)
  Logging();
  ~Logging();

  // static methods 
  static void prepare();
  static void finalize();

  static void log(int status, std::string method);

  static void setLevel(int newLevel);

  static void setModuleLevel(int level, std::string module);


};

#endif // LOGGING_HPP
