/*
 * RType
 *
 */

#include "Server.h"
#include "ConfigMgr.h"

#include <iostream>

int main(int ac, char** av)
{
    sConfig->SetConfigFile(DEFAULT_CONFIG_FILE);
    sConfig->LoadConfig();
    sConfig->DumpConfig();

    Server server();
    return 0;
}
