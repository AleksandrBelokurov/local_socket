#ifndef CHANNEL_H
#define CHANNEL_H

#include <iostream>

using namespace std;

enum class State {
    error = -1,
    idle,
    measure,
    busy,
};

enum class Range {
    range0, //[0.0000001 ... 0.001)
    range1, //[0.001 ... 1)
    range2, //[1 ... 1000)
    range3, //[1000 ... 1000000)
};

class Channel
{
public:
    Channel();

    string getState();
    string setRange(Range range);
    string startMeasure();
    string stopMeasure();
    string getResult();

private:
    Range range_ = Range::range0;
    State state_ = State::idle;
    string random(int min, int max, int divider, int precision);

};

#endif //CHANNEL_H
