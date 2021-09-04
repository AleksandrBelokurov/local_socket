#ifndef MESSAGECODEC_H
#define MESSAGECODEC_H

#include <iostream>
#include <list>
#include <map>
#include "channel.h"

using namespace std;

class Messagecodec
{
public:
    Messagecodec(map<string, Channel*>* channels);

    string decode(string msg);
    string encode(Channel* channel, int command, Range range);

private:
    map<string, Channel*>* channels_;
    map<string, int> commands_{
        {"get_status",      0},
        {"set_range",       1},
        {"start_measure",   2},
        {"stop_measure",    3},
        {"get_result",      4},
    };
    map<string, Range> range_{
        {"range0", Range::range0},
        {"range1", Range::range1},
        {"range2", Range::range2},
        {"range3", Range::range3},
    };

};

#endif // MESSAGECODEC_H
