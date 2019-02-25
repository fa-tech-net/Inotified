/*
 * MIT License
 * 
 * Copyright (c) 2018 Adrien FAVRE <tarto@tarto.fr>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
 
#ifndef __LOGGER_H__
#define __LOGGER_H__
 
#include <string>
#include <iostream>
#include <istream>
#include <fstream>
#include <vector>
#include <utility>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <stdexcept>

#define L_DBG 0
#define L_NOT 1
#define L_INF 2
#define L_WAR 3
#define L_ERR 4
#define L_FAT 5

namespace Logging
{

  class Logger
  {
  public:
    void toggleDisplay();
    static  void slog(const std::string & level, const std::string & message) ;
    static  void slogError(const std::string & level, const std::string & message) ;
    static  std::string getDate() ;
    void log(const std::string & level, const std::string & message);
    void log(unsigned char level, const std::string & message) ;
    void logError(const std::string & level, const std::string & message);
    void logError(unsigned char level, const std::string & message);
    Logger(const std::string &logfile, const std::string &errorlog);
    Logger();
    virtual ~Logger();
    void setFormat(const std::string &); // TODO : implement
    void setDateFormat(const std::string &); // TODO : implement
    static const std::vector<std::pair<unsigned char , std::pair<std::string, std::string> > > default_levels;
    void setMinimalLogLevel(unsigned char logLevel);
    void enableDebug();
    void disableDebug();
  private:
    std::string __dateFormat;
    std::string __OutputFormat;
    std::ofstream  __stdLog ;
    std::ofstream  __errLog ;
    unsigned char __min_level;
    bool __debug_enabled;
    unsigned char __prev_level;
    bool __display;
    unsigned char min_error_level;
		
  };

  // Level <LongName, ShortName>
 
}


#endif /* __LOGGER_H__ */
