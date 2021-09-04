#include "channel.h"
#include <sstream>
#include <iomanip>

Channel::Channel()
{}

string Channel::getState()
{
    int ii = rand()%4;
    if (ii < 1)
        return "fail";
    state_ = State(rand()%4 - 1);
    string answer = "ok, ";
    switch (state_) {
        case State::error:
            answer += "error_state";
            break;
        case State::idle:
            answer += "idle_state";
            break;
        case State::measure:
            answer += "measure_state";
            break;
        case State::busy:
            answer += "busy_state";
            break;
        default:
            break;
    }
    return answer;
}

string Channel::setRange(Range range)
{
    int ii = rand()%4;
    if (ii < 1)
        return "fail";
    range_ = range;
    string answer = "ok, ";
    switch (range_) {
        case Range::range0:
            answer += "range0";
            break;
        case Range::range1:
            answer += "range1";
            break;
        case Range::range2:
            answer += "range2";
            break;
        case Range::range3:
            answer += "range3";
            break;
        default:
            break;
    }
    return answer;
}

string Channel::getResult()
{
    int ii = rand()%4;
    if (ii < 1)
        return "fail";
    int min;
    int max;
    int divider;
    int precision;
    switch (range_) {
        case Range::range0:
            min = 0;
            max = 999;
            divider = 1000000;
            precision = 6;
            break;
        case Range::range1:
            min = 0;
            max = 999;
            divider = 1000;
            precision = 3;
            break;
        case Range::range2:
            min = 0;
            max = 99999;
            divider = 100;
            precision = 3;
            break;
        case Range::range3:
            min = 100000;
            max = 99999999;
            divider = 100;
            precision = 3;
            break;
        default:
            break;
    }
    string ss;
    for (int i = 0; i < 8; i++)
        ss = ss + random(min, max, divider, precision) + ", ";
    return "ok, " +  ss;
}

string Channel::startMeasure()
{
    int ii = rand()%4;
    if (ii < 1)
        return "fail";
    return "ok";
}

string Channel::stopMeasure()
{
    int ii = rand()%4;
    if (ii < 1)
        return "fail";
    return "ok";
}

string Channel::random(int min, int max, int divider, int precision)
{
    ostringstream streamObj;
    streamObj << fixed;
    streamObj << setprecision(precision);
    float ff = min + rand() % (max - min);
    ff = ff / divider;
    streamObj << ff;
    string ss = streamObj.str();
    ss = ss.replace(ss.find(","), 1, ".");
    return ss;
}
