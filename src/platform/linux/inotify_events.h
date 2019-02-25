//
// Created by adrien on 12/02/19.
//

#ifndef INOTIFIED_INOTIFY_EVENTS_H
#define INOTIFIED_INOTIFY_EVENTS_H

#include <sys/inotify.h>
#include <vector>


std::vector<std::pair<int, const char * > > inotify_description = {
        {IN_ACCESS,"File was accessed (e.g., read(2), execve(2)).\n"},
        {IN_ATTRIB, "Metadata changed—for example, permissions (e.g.,\n"
                "chmod(2)), timestamps (e.g., utimensat(2)), extended\n"
                "\tattributes (setxattr(2)), link count (since Linux 2.6.25;\n"
                "e.g., for the target of link(2) and for unlink(2)), and\n"
                "user/group ID (e.g., chown(2)).\n" },
        {IN_CLOSE_WRITE, "File opened for writing was closed.\n"},
        {IN_CLOSE_NOWRITE, "File or directory not opened for writing was closed.\n"},
        {IN_CREATE, "File/directory created in watched directory (e.g., open(2)\n"
                    "O_CREAT, mkdir(2), link(2), symlink(2), bind(2) on a UNIX\n"
                    "domain socket).\n"},
        {IN_DELETE, "File/directory deleted from watched directory.\n"},
        {IN_DELETE_SELF, "Watched file/directory was itself deleted.  (This event\n"
                        "also occurs if an object is moved to another filesystem,\n"
                        "since mv(1) in effect copies the file to the other\n"
                        "filesystem and then deletes it from the original filesystem.)\n"
                        "In addition, an IN_IGNORED event will subsequently\n"
                        "be generated for the watch descriptor.\n"},
        {IN_MODIFY, "File was modified (e.g., write(2), truncate(2)).\n"},
        {IN_MOVE_SELF, "Watched file/directory was itself moved."},
        {IN_MOVED_FROM, "Generated for the directory containing the old filename\n"
                        "when a file is renamed."},
        {IN_MOVED_TO, "Generated for the directory containing the new filename\n"
                        "when a file is renamed."},
        {IN_OPEN, "File or directory was opened."},
        {IN_ALL_EVENTS, "is defined as a bit mask of all of the above\n"
                       "events.  This macro can be used as the mask argument when calling\n"
                       "inotify_add_watch(2).\n"},
        {IN_MOVE, "Equates to IN_MOVED_FROM | IN_MOVED_TO."},
        {IN_CLOSE, "Equates to IN_CLOSE_WRITE | IN_CLOSE_NOWRITE."},
        {IN_EXCL_UNLINK, "By default, when watching events on the children of a\n"
                        "directory, events are generated for children even after\n"
                        "they have been unlinked from the directory.  This can\n"
                        "result in large numbers of uninteresting events for some\n"
                        "applications (e.g., if watching /tmp, in which many appli‐\n"
                        "cations create temporary files whose names are immediately\n"
                        "unlinked).  Specifying IN_EXCL_UNLINK changes the default\n"
                        "behavior, so that events are not generated for children\n"
                        "after they have been unlinked from the watched directory.\n"},
        {IN_MASK_ADD, "If a watch instance already exists for the filesystem\n"
                      "object corresponding to pathname, add (OR) the events in\n"
                      "mask to the watch mask (instead of replacing the mask).\n"},
        {IN_ONESHOT, "Monitor the filesystem object corresponding to pathname\n"
                     "for one event, then remove from watch list.\n"},
        {IN_ONLYDIR, "Watch pathname only if it is a directory.  Using this flag\n"
                     "provides an application with a race-free way of ensuring\n"
                     "that the monitored object is a directory.\n"
                     "The following bits may be set in the mask field returned by read(2):\n"},
        {IN_IGNORED, "Watch was removed explicitly (inotify_rm_watch(2)) or\n"
                     "automatically (file was deleted, or filesystem was\n"
                     "unmounted).  See also BUGS.\n"},
        {IN_ISDIR, "Subject of this event is a directory."},
        {IN_Q_OVERFLOW, "Event queue overflowed (wd is -1 for this event)."},
        {IN_UNMOUNT, "Filesystem containing watched object was unmounted.  In\n"
                     "addition, an IN_IGNORED event will subsequently be gener‐\n"
                     "ated for the watch descriptor.\n"}
};





#endif //INOTIFIED_INOTIFY_EVENTS_H
