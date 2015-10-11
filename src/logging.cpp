#include "logging.hpp"

std::ofstream *Logging::ofs = 0;
std::stringstream *Logging::buffer = 0;
std::streambuf *oldCerrBuf;
std::string Logging::indent;
std::string Logging::indentedFunction;
std::string logAny ="qqq";


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

void Logging::prepare() {
  Logging::prepare("./test.log");
}
 

void Logging::prepare(const std::string& logFileName) {
  // dont know how to set a std::ofstream* to std::cout
  // but logging to a file is probably better anyway ...
  Logging::ofs = new std::ofstream(logFileName);
  Logging::buffer = new std::stringstream();

  // redirect error to logfile
  oldCerrBuf = std::clog.rdbuf((Logging::buffer)->rdbuf());

  // set indentation to none
  Logging::indent = "";
  
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

void Logging::log(int status, std::string method) {


  std::string s = (*Logging::buffer).str();

  // output the status, method and message, e.g.: 
  // void MyModule::myMethod(): entering  ...
  // skip if status of message unimportant
  if (indent.size() > 100) indent = "";
  if (status <= logLevel || method.find(logAny)!=std::string::npos) {
    switch  (status) {
    case DEBUGD: 
      (*ofs) << " DEBUGD: " << indent;
      break;
    case DEBUG: 
      if (s.find("EXITING") != std::string::npos && indent.size()>0) {
        indent.erase(0,2);
      }
      (*ofs) << "  DEBUG: " << indent ;
      if (s.find("ENTERING") != std::string::npos) indent += "  ";
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
    (*ofs) <<  method << ": " << (*Logging::buffer).str() << std::endl;
  }

  // clear buffer (has been written in Macro)
  (*Logging::buffer).clear();
  (*Logging::buffer).str("");

}

