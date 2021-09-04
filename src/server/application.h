#ifndef APPLICATION_H
#define APPLICATION_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <algorithm>
#include <set>
#include <map>
#include <cstring>
#include <iostream>

#include "logging.h"
#include "messagecodec.h"
#include "channel.h"

using namespace std;

class Application
{
public:
    Application(char*& filename);

    int init();
    int run();

private:
    string sock_path_{"/tmp/relay_socket"};
    static const int buf_size_{1024};
    int listener_;
    struct sockaddr_un addr_;
    set<int> clients_;
    char buf[buf_size_];
    int bytes_read_;
    string logFileName_;
    Logging* log_;
    Messagecodec* msgcodec_;
    list<string> channelNames_{
        "channel0",
        "channel1",
        "channel2",
        "channel3",
    };
    map<string, Channel*> channels_;

};

#endif //APPLICATION_H
