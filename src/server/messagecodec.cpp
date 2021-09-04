#include "messagecodec.h"
#include <cstring>

Messagecodec::Messagecodec(map<string, Channel*>* channels)
{
    channels_ = channels;
}

string Messagecodec::decode(string msg)
{
    string request;
    int tt = msg.find(", ");
    if (tt < 0)
        return "fail, invalid message: " + msg;
    string scom = msg.substr(0, tt);
    map<string, int>::const_iterator itc = commands_.find(scom);
    int command = -1;
    if (itc == commands_.end())
        return "fail, command \"" + scom + "\" is not valid";
    else {
        command = itc->second;
//        request = "finded command: " + scom;
    }
    string strtmp = msg.substr(tt + 2);
    tt = strtmp.find(", ");
    if (tt < 0)
        return "fail, channel not specified";
    string sch = strtmp.substr(0, tt);
    map<string, Channel*>::const_iterator it = channels_->find(sch);
    Channel* channel = nullptr;
    if (it == channels_->end())
        return "fail, command \"" + scom + "\" , channel \""
            + sch + "\" is not valid";
    else {
//        std::string strCh = it->first;
        channel = it->second;
        // request = request + ", finded channel: \""
        //     + strCh + "\" state: " + to_string(curChannel_->getState());
    }
    Range range;
    if (command == 1) {
        strtmp = strtmp.substr(tt + 2);
        tt = strtmp.find(", ");
        if (tt < 0)
            return "fail, range not specified";
        string sr = strtmp.substr(0, tt);
        map<string, Range>::const_iterator itr = range_.find(sr);
        if (itr == range_.end())
            return "fail, range \"" + sr + "\" is not valid";
        else {
            range = itr->second;
            // request = request + " finded range: " + sr;
        }
    }
    return encode(channel, command, range);
}

string Messagecodec::encode(Channel* channel, int command, Range range)
{
    if (!channel)
        return "fail";
    switch (command) {
        case -1:
            return "fail";
            break;
        case 0:
            return channel->getState();
            break;
        case 1:
            return channel->setRange(range);
            break;
        case 2:
            return channel->startMeasure();
            break;
        case 3:
            return channel->stopMeasure();
            break;
        case 4:
            return channel->getResult();
            break;
        default:
            return "fail";
            break;
    }
    return "fail";
}
