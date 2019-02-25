/*
 * MIT License
 * 
 * Copyright (c) 2018 Adrien FAVRE <favre_a@pm.me>
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
 
# include "Logger.h"

using namespace Logging;

const std::vector<std::pair<unsigned char , std::pair<std::string, std::string> > > Logger::default_levels = 
  {
    {L_DBG, {"DEBUG", 		"DEBUG"}},
    {L_NOT, {"NOTICE", 		"NOTICE"}},
    {L_INF, {"INFORMATION", "INFO"}},
    {L_WAR, {"WARNING", 	"WARN"}},
    {L_ERR, {"ERROR", 		"ERROR"}},
    {L_FAT, {"FATAL", 		"FATAL"}},
  };


std::string Logger::getDate()
{
	std::ostringstream oss;
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    oss << std::put_time(&tm, "%Y/%m/%d %H:%M:%S");
	auto str = oss.str();
	return str;
}

Logger::Logger() : min_error_level(3)
{
    __stdLog.copyfmt(std::cout);
    __stdLog.clear(std::cout.rdstate());                          
    __stdLog.basic_ios<char>::rdbuf(std::cout.rdbuf());           
    __errLog.copyfmt(std::cerr);
    __errLog.clear(std::cout.rdstate());                          
    __errLog.basic_ios<char>::rdbuf(std::cout.rdbuf());           
}

Logger::Logger(const std::string &logfile, const std::string &errorlog) : min_error_level(3)
{
	__display = false;
	__stdLog.open(logfile, std::ofstream::out | std::ofstream::app);
	if (!__stdLog.is_open())
		Logger::slogError("WARN", "Cannot open logfile : '"+logfile+"'");
	__errLog.open(errorlog, std::ofstream::out | std::ofstream::app);
	if (!__errLog.is_open())
		Logger::slogError("WARN", "Cannot open logfile : '"+errorlog+"'");
}

Logger::~Logger()
{
	__display = true;
	if (__stdLog.is_open())
		__stdLog.close();
	if (__errLog.is_open())
		__errLog.close();
}
void Logger::toggleDisplay()
{
	
	this->__display = !this->__display;
}
 
void Logger::slog(const std::string & level, const std::string & message)  
{
	std::cout << Logger::getDate() << " - [" << level << "] - " << message << std::endl;
}

void Logger::slogError(const std::string & level, const std::string & message)  
{
	std::cerr << Logger::getDate() << " - [" << level << "] - " << message << std::endl;
}


void Logger::log(unsigned char level, const std::string & message)
{
	if (level < this->__min_level)
		return;
	std::string level_str;
	bool isError = false;
	if (level < default_levels.size())
	{
		level_str = std::get<1>(std::get<1>(default_levels[level]));
		if (level >= this->min_error_level)
			isError = true;
	}
	else
		level_str = "INFO";
	
	isError ?  this->logError(level_str, message) : this->log(level_str, message);
}

void Logger::logError(const std::string & level, const std::string & message)
{
	std::ostream & stream = this->__errLog;
	stream << Logger::getDate() << " - [" << level << "] - " << message << std::endl;
	if (__display)
		std::cerr << Logger::getDate() << " - [" << level << "] - " << message << std::endl;
}

void Logger::logError(unsigned char level, const std::string & message)
{
	if (level < this->__min_level)
		return;
	std::string level_str;
	bool isError = false;
	if (level < default_levels.size())
	{
		level_str = std::get<1>(std::get<1>(default_levels[level]));
		if (level >= this->min_error_level)
			isError = true;
	}
	else
		level_str = "ERROR";

	this->logError(level_str, message);
}


void Logger::log(const std::string & level, const std::string & message)
{
	std::ostream & stream = this->__stdLog;
	if (__display)
		std::cout << Logger::getDate() << " - [" << level << "] - " << message << std::endl;
	
	if (!__display && !this->__stdLog.is_open())
	{
		throw std::runtime_error("Cannot write file, display is disabled");
	}
	stream << Logger::getDate() << " - [" << level << "] - " << message << std::endl;
}

void Logger::setMinimalLogLevel(unsigned char logLevel)
{
	this->__min_level = logLevel;
}

void Logger::enableDebug()
{
	this->__prev_level = this->__min_level;
	this->__min_level = L_DBG; // == 0
	this->__debug_enabled = true;

}

void Logger::disableDebug()
{
	if (this->__debug_enabled)
		this->__min_level = this->__prev_level;
	this->__debug_enabled = false;
}


/*
 * int test()
 * {
 * Logger * l = new Logger("./losadasdg/out", "./losadg/err");
 * //l->toggleDisplay();
 * l->log("test", "test");
 * l->log(1, "test");
 * l->log(L_ERR, "test error");
 * Logger::slog("TEST", "test");
 * return (0);
 * }
 */