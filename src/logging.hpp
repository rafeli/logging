#ifndef _LOGGING_HPP
#define _LOGGING_HPP

#define DEBUGD  30
#define DEBUG   20
#define INFO    10
#define WARNING 5
#define THROWING 2
#define ERROR   1

#define THROW(s)                           \
  throw std::string(s)


#define MYLOG(n,s)                         \
  (*Logging::buffer) << s;                 \
  Logging::log(n,__PRETTY_FUNCTION__ )


#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

// some stream operator for standard objects:
std::ostream& operator << (std::ostream & os, std::vector<unsigned int> v);

class Logging  {


private:
  static const int logLevel = DEBUG;
  static std::ofstream *ofs;
  static std::string indent, indentedFunction;

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

  static std::string getBuffer();

  static void setLevel(int newLevel);

  static void setModuleLevel(int level, std::string module);


};

#endif // LOGGING_HPP
