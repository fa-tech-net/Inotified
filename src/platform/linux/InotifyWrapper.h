//
// Created by adrien on 12/02/19.
//

#ifndef INOTIFIED_INOTIFYWRAPPER_H
#define INOTIFIED_INOTIFYWRAPPER_H

#include <sys/inotify.h>
#include <openssl/sha.h>
#include <inttypes.h>
#include <errno.h>
#include <stdexcept>
#include <vector>
#include <string>
#include <ctime>


#define IBUFFER_SIZE 4096 // @TODO : add this parameter in configuration file

/**
 *
 * struct inotify_event {
 *   int      wd;       // Watch descriptor
 *   uint32_t mask;     // Mask describing event
 *   uint32_t cookie;   // Unique cookie associating related
 *                                    events (for rename(2))
 *   uint32_t len;      // Size of name field
 *   char     name[];   // Optional null-terminated name
*/

#include "../../common/globals.h"

Logging::Logger * l = glob.log;

typedef struct iNotified_event
{
    std::time_t timestamp;
    std::vector<inotify_event> * events;
    int watch_descriptor;
} iEvent;




class InotifyWrapper {
    public :
        InotifyWrapper();
        virtual ~InotifyWrapper();
        int monitorFile(const std::string & path, unsigned int event);
        void removeMonitoring(const std::string &);
        const std::vector<std::pair<std::string, std::vector< iEvent *>>>  & getAllEvents() const;
        const std::vector<iEvent *> & getEvents(int hash) const;
        iEvent * newIevent(int);
        std::string generateID(const std::string &, unsigned int);

    private :
        std::vector<std::pair<std::string, std::vector<iEvent * >>> _iStack;
        int __iNotify_fd;
        bool __checkFlag(unsigned int) const;

};


std::vector<unsigned int> inotify_valid_flags = {IN_ACCESS,
                              IN_ATTRIB,
                              IN_CLOSE_WRITE,
                              IN_CLOSE_NOWRITE,
                              IN_CREATE,
                              IN_DELETE,
                              IN_DELETE_SELF,
                              IN_MODIFY,
                              IN_MOVE_SELF,
                              IN_MOVED_FROM,
                              IN_MOVED_TO,
                              IN_OPEN,
                              IN_ALL_EVENTS,
                              IN_MOVE,
                              IN_CLOSE,
                              IN_EXCL_UNLINK,
                              IN_MASK_ADD,
                              IN_ONESHOT,
                              IN_ONLYDIR,
                              IN_IGNORED,
                              IN_ISDIR,
                              IN_Q_OVERFLOW,
                              IN_UNMOUNT};

#endif //INOTIFIED_INOTIFYWRAPPER_H
