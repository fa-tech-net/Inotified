//
// Created by adrien on 12/02/19.
//

#include "InotifyWrapper.h"
#include "../../common/Logger.h"


InotifyWrapper::InotifyWrapper()
{
    log->log(L_DBG, "<InotifyWrapper.cpp>::InotifyWrapper::InotifyWrapper() :");
    this->__iNotify_fd = inotify_init1(IN_NONBLOCK);
    if (this->__iNotify_fd == -1)
    {
        log->logError(L_DBG, "Call function 'this->__iNotify_fd = inotify_init1(IN_NONBLOCK);', failure : Returns -1 ");
        log->logError(L_FAT, "Failed to initialize inotify");
        throw std::runtime_error("inotify_init1(IN_NONBLOCK) returns -1 ");
    }
    log->log(L_NOT, "Initialized inotify API");
}

inline bool InotifyWrapper::__checkFlag(unsigned int mask) const
{
    for (auto i = inotify_valid_flags.begin(); i != inotify_valid_flags.end(); i++)
        if ((mask & *i) == *i)
            return (true);
    return (false);
}

InotifyWrapper::~InotifyWrapper()
{

}

std::string InotifyWrapper::generateID(const std::string & path, unsigned int flag)
{
    unsigned char buf[SHA_DIGEST_LENGTH];
    std::string value = path + std::to_string(flag);
    SHA1(reinterpret_cast<const unsigned  char *>(value.c_str()), value.length(), buf);
    return (std::string(reinterpret_cast<const char *>(buf)));
}

iEvent* InotifyWrapper::newIevent(int wd = NULL)
{
    log->log(L_DBG, "<InotifyWrapper.cpp>::InotifyWrapper::InotifyWrapper() :");
    auto * tmp = new iEvent();
    tmp->events = new std::vector<inotify_event>();
    tmp->watch_descriptor = wd;
    tmp->timestamp = std::time(0);
    log->log(L_NOT, "New Ievent created");
    return(tmp);
}


int         InotifyWrapper::monitorFile(const std::string & path, unsigned int event) {
    log->log(L_DBG, "<InotifyWrapper.cpp>::InotifyWrapper::monitorFile(const std::string &, unsigned int)");
    char hex[10];
    snprintf(hex, 10, "0x%X", event);
    hex[10] = 0;
    /* Checking flag */
    if (!this->__checkFlag(event)) {
        log->logError(L_ERR, "Invalid flag provided !");
        log->logError(L_ERR, "Event value : " + std::string(hex));
        throw std::runtime_error("Invalid flag provided, value = " + std::string(hex));
    }
    /* Add watch with provided flag */
    int watch_descriptor = inotify_add_watch(this->__iNotify_fd, path.c_str(), event);
    log->log(L_DBG, "Call function inotify_add_watch(this->__iNotify_fd, path.c_str(), event);");
    log->log(L_DBG, "With values : ");
    log->log(L_DBG, "\tthis->__iNotify_fd => '" + std::to_string(this->__iNotify_fd) + "'");
    log->log(L_DBG, "\tpath.c_str() => '" + path + "'");
    log->log(L_DBG, "\tevent => '" + std::string(hex) + "'");
    if (watch_descriptor == -1) {
        log->logError(L_ERR, "Cannot monitor file : '" + path + "' error when calling inotify_add_watch ");
        throw std::runtime_error("Cannot monitor file : '" + path + "', error when calling inotify_add_watch");
    }
    log->log(L_NOT, "New watch descriptor created : " + path);
    auto *ev = newIevent(watch_descriptor);
//    auto
//    const std::vector<std::pair<std::string, std::vector<iEvent *>>>;
//    this->_iStack.push_back(this->generateID(path, flag));
}

void        InotifyWrapper::removeMonitoring(const std::string &) {}
const std::vector<std::pair<std::string, std::vector< iEvent *>>>  & InotifyWrapper::getAllEvents() const {}
const std::vector<iEvent *> & InotifyWrapper::getEvents(int fd) const {}
