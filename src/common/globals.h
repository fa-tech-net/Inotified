//
// Created by adrien on 13/02/19.
//


#ifndef __INOTIFIED_GLOBALS__
#define __INOTIFIED_GLOBALS__
#include "Logger.h"

#ifndef __DEFAULT_LOGNAME__
# define __DEFAULT_LOGNAME__ "log"
#endif

class global
{
    /**
     * Globals
     */
public :
    Logging::Logger * log = 0 ;
    explicit global(const std::string & logname)
    {
        this->log = new Logging::Logger(logname+".log", logname+".err");
        this->log->toggleDisplay(); // Toggle display
    }
    virtual  ~global(){
        if (this->log != 0)
            delete(this->log);
    }


};

extern global glob;

#endif // __INOTIFIED_GLOBALS__
