/*
 * RType
 *
 */

#include "Server.h"
#include "ConfigMgr.h"

#include <iostream>

int main(int ac, char** av)
{
	const char* file = (ac > 1 ? av[1] : DEFAULT_CONFIG_FILE);
    sConfig->SetConfigFile(file);
    if (!sConfig->LoadConfig())
    {
        std::cerr << "Fail to load config `" << file << "`" << std::endl;
        return 1;
    }
    sConfig->DumpConfig();

    Server server;
    server.Start();
    server.Wait();
    return 0;
}
