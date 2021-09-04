#ifndef LOGGING_H
#define LOGGING_H

#include <fstream>

using namespace std;

class Logging
{
public:
    Logging(string filename);
    ~Logging();
    Logging& writelog(const string& logmsg);
    friend Logging& operator<<(Logging& l, const string& logmsg) {
        return l.writelog(logmsg);
    }

private:
    fstream fs;

};

#endif // LOGGING_H
