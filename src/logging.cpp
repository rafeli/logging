#include "logging.hpp"

std::ofstream *Logging::ofs = NULL;
std::stringstream *Logging::buffer = 0;
std::streambuf *oldCerrBuf;
std::string Logging::indent;
std::string Logging::indentedFunction;

Logging myLogging;


// stream operators
std::ostream& operator <<(std::ostream& os, std::vector<unsigned int> v) {
  os << v[0];
  for (unsigned int i=1; i<v.size(); i++) os << ":" << v[i] ;
  os << std::endl;
  return os;
}

Logging::Logging() {
}

Logging::~Logging() {
}

Logging& Logging::prepare() {
  return Logging::prepare("./test.log");
}
 
Logging& Logging::prepare(const std::string& logFileName) {

  // dont know how to set a std::ofstream* to std::cout
  // but logging to a file is probably better anyway ...
  Logging::ofs = new std::ofstream(logFileName);
  Logging::buffer = new std::stringstream();

  // redirect error to logfile
  oldCerrBuf = std::clog.rdbuf((Logging::buffer)->rdbuf());

  // set indentation to none
  Logging::indent = "";
  
  // set default logLevel to DEBUG
  myLogging.logLevel = DEBUG;
  return myLogging;
}

void Logging::finalize() {

  // reset cerr
  std::clog.rdbuf(oldCerrBuf);

  // close logfile
  if (ofs->is_open()) {
    ofs -> close();
  }
}

std::string Logging::getBuffer() {
  return (*Logging::buffer).str();
}

Logging& Logging::setLevel(int level_) {
  myLogging.logLevel = level_;
  return myLogging;
}

Logging& Logging::setClassLevel(std::string className, int level) {
  myLogging.classLevel[className] = level;
  return myLogging;
}

Logging& Logging::setMethodLevel(std::string methodName, int level) {
  // methodName e.g. "MyClass::doSomething"   i.e. with class, without parameter
  myLogging.methodLevel[methodName] = level;
  return myLogging;
}

void Logging::log(int status, std::string methodSignature) {

  // -1- copy the message itself, which has been written into buffer
  //     to the string s 
  std::string s = (*Logging::buffer).str()
             ,methodName, className;

  // -2- determine the logLevel of this type of messages, which is equal to the
  //     global log level unless set otherwise for this class or method
  int logLevel = myLogging.logLevel;
  methodName = methodSignature; // e.g. "int myClass::getSomeInt()"
  methodName = methodName.substr(0,methodName.find("(")); // remove argument
  methodName = methodName.substr(methodName.rfind(" ")+1); // remove return type and e.g. virtual
  if (myLogging.methodLevel.count(methodName) == 0) {
    className = methodName.substr(0,methodName.find("::"));
    if (myLogging.classLevel.count(className) == 1) {
      logLevel = myLogging.classLevel[className];
    }
  } else {
    logLevel = myLogging.methodLevel[methodName];
  }
  if (status <= logLevel) 


  //  -4- output status, method and message, e.g.: 
  // void MyModule::myMethod(): entering  ...
  // skip if status of message unimportant
  if (indent.size() > 100) indent = "";
  if (status <= logLevel) {
    if (s.find("ENTERING") != std::string::npos) indent += "  ";
    switch  (status) {
    case DEBUGD: 
      (*ofs) << " DEBUGD: " << indent;
      break;
    case DEBUG: 
      (*ofs) << "  DEBUG: " << indent ;
      break;
    case INFO: 
      (*ofs) << "INFO: " << indent;
      break;
    case WARNING: 
      (*ofs) << "WARNING: " << indent;
      break;
    case THROWING: 
      (*ofs) << "  ERROR: " << indent;
      break;
    case ERROR: 
      (*ofs) << "  ERROR: " << indent;
      break;
    default:
      std::cout << "LOGGING ERROR: unknown status\n";
      break;
    }
    (*ofs) <<  methodName << ": " << (*Logging::buffer).str() << std::endl;
    if (s.find("EXITING") != std::string::npos && indent.size()>0) {
      indent.erase(0,2);
    }
  }

  // clear buffer (has been written in Macro)
  (*Logging::buffer).clear();
  (*Logging::buffer).str("");

}

