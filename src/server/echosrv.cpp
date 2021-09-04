#include "application.h"

int main(int argc, char *argv[])
{
    Application app(argv[0]);
    int ii = app.init();
    if (ii > 0)
        return ii;
    return app.run();
}
