#include <iostream>
#include "echocli.h"

using namespace std;

int main(int argc, char* argv[])
{
    EchoClientCLI cli;
    cli.run(argv,argc);
    return 0;
}
