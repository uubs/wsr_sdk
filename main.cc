#include "server/server.h"

int main() {
    //Server s("StartTaskQueue", "FiniTaskQueue", 1024 * 8);
    Server s(1024 * 8);
    s.Start();
}