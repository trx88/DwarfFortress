#include "OutputWindowLogger.h"
#include <sstream>

#ifdef _MSC_VER
#include "Windows.h"
#endif

#if !defined(NDEBUG) && defined(_MSC_VER)
#define LOG(args)            \
{                             \
   std::wostringstream os_;    \
   os_ << "\n\n";                   \
   os_ << args;                   \
   os_ << "\n\n";                   \
   OutputDebugString( os_.str().c_str() );  \
}
#else
#define LOG(args)
#endif

void OutputWindowLogger::LogToOutput(const char* s)
{
	LOG(s)
}
