#ifndef _LOGGING_HPP
#define _LOGGING_HPP

#define DEBUGD  30
#define DEBUG   20
#define INFO    10
#define WARNING 5
#define THROWING 2
#define ERROR   1

#define THROW(s)                             \
  (*Logging::buffer) << s;                   \
  Logging::log(ERROR,__PRETTY_FUNCTION__ );  \
  throw std::string(s)


#define MYLOG(n,s)                          \
  (*Logging::buffer) << s;                  \
  Logging::log(n,__PRETTY_FUNCTION__ )


#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <exception>

namespace momo {

  class e : public std::exception {
    public:
    std::string msg;
    e(std::string s) {msg = s;}
    e(const char* s) {msg = s;}
    virtual const char* what() const throw() {
      return msg.c_str();
    }
  };

}

// some stream operator for standard objects:
std::ostream& operator << (std::ostream & os, std::vector<unsigned int> v);

class Logging  {


private:

//  static const int logLevel = DEBUG;
  static std::ofstream *ofs;
  static std::string indent, indentedFunction;

  // this is the first parameter that I changed to be a field of the object
  // myLogging that is instantiated in logging.cpp
  // TODO: check if all other static variables can be handled similarly,
  //       because I do not know what static does exactly (e.g. I could *not*
  //       declare logLevel the same way as 'indent' above. )
  int logLevel;

  std::map<std::string,int> classLevel, methodLevel;


public:

  // maybe suboptimal: Logging is a MACRO and needs public access
  // to this buffer. Could write a public getBuffer, but does that help?
  static std::stringstream* buffer;

  //Constructor and Destructor (werden noch nicht gebraucht)
  Logging();
  ~Logging();

  // set logLevel global, class or metho
  static Logging& setLevel(int newLevel);
  static Logging& setClassLevel(std::string, int);
  static Logging& setMethodLevel(std::string, int);

  // static methods 
  static Logging& prepare();
  static Logging& prepare(const std::string&);
  static void checkInit();
  static void finalize();

  static void log(int status, std::string method);

  static std::string getBuffer();

  friend std::ostream& operator <<(std::ostream& os, std::vector<unsigned int> v);

};

#endif // LOGGING_HPP
