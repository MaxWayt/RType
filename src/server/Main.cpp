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
    if (!sConfig->LoadConfig())
    {
        std::cerr << "Fail to load config `" << DEFAULT_CONFIG_FILE << "`" << std::endl;
        return 1;
    }
    sConfig->DumpConfig();

    Server server;
    server.Start();
    server.Wait();
    return 0;
}
