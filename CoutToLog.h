#include <fstream>
#include <iomanip>
#include <sstream>
#include <iostream>
#include "windows.h"

class CoutToLog : public std::streambuf
{
public:

  CoutToLog(const char * iFilePath, std::basic_ios< char >& iReplacedStream = std::cout, unsigned iMode = std::ios::out | std::ios::trunc) :
    mFilePath(iFilePath, iMode),
    mReplacedStream(iReplacedStream),
    mDestinationStream(),
    wNewLine(true)
  {
    // Replace target streambuf with file streambuf
    iReplacedStream.rdbuf(mFilePath.rdbuf());

    // Override the streambuf
    mDestinationStream = mReplacedStream.rdbuf(this);
  }

  ~CoutToLog()
  {
    // Reset original streambuf
    mReplacedStream.rdbuf(mDestinationStream);
  }

protected:

  int_type overflow(int_type iChar = traits_type::eof())
  {
    if (traits_type::eq_int_type(iChar, traits_type::eof()))
    {
      return mDestinationStream->pubsync() == -1 ? iChar : traits_type::not_eof(iChar);
    }

    if (wNewLine)
    {
      // Get timestamp
      SYSTEMTIME wSystemTime;
      GetSystemTime(&wSystemTime);
      std::ostringstream wTimeStamp;
      wTimeStamp << wSystemTime.wYear << "-"
        << std::setw(2) << std::setfill('0') << wSystemTime.wMonth << "-"
        << std::setw(2) << std::setfill('0') << wSystemTime.wDay << " "
        << std::setw(2) << std::setfill('0') << wSystemTime.wHour << ":"
        << std::setw(2) << std::setfill('0') << wSystemTime.wMinute << ":"
        << std::setw(2) << std::setfill('0') << wSystemTime.wSecond << "."
        << std::setw(3) << std::setfill('0') << wSystemTime.wMilliseconds;
      
      // Print timestamp
      std::ostream wTempStream(mDestinationStream);
      if (!(wTempStream << wTimeStamp.str() << "  "))
      {
        return traits_type::eof();
      }
    }
    wNewLine = traits_type::to_char_type(iChar) == '\n';
    return mDestinationStream->sputc(iChar);
  }

  // Flush ofstream at endl
  int sync()
  {
    return mDestinationStream->pubsync();
  }

private:

  // Non-copyable
  CoutToLog(const CoutToLog&);
  CoutToLog& operator=(const CoutToLog&);

  // Members
  std::basic_ios< char >& mReplacedStream;
  std::streambuf* mDestinationStream;
  std::ofstream mFilePath;
  bool wNewLine;
};

