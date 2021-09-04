#include "logging.h"

Logging::Logging(string filename)
{
    fs.open(filename, fstream::in | fstream::out | fstream::app);
}

Logging::~Logging()
{
    fs.close();
}

Logging& Logging::writelog(const string& logmsg)
{
    locale::global(locale("ru_RU.utf8"));
    time_t t = time(nullptr);
    char mbstr[100];
    if (strftime(mbstr, sizeof(mbstr), "%Y-%m-%d_%H:%M:%S", localtime(&t))) {
	fs << mbstr << " " << logmsg << endl;
	fs << flush;
    }
    return *this;
}

