
#ifndef ECHOCLI_H_INCLUDED
#define ECHOCLI_H_INCLUDED

#include "cli.h"
#include "tcpsocket.h"
#include "echotcpclient.h"

class EchoClientCLI : public CmdLineInterface {
private:
    EchoTcpClient client;
public:
    EchoClientCLI();
    ~EchoClientCLI();
    void initCmd();
private:
   //add code here

   void doGet(string cmd_argv[], int cmd_argc);
   void doHead(string cmd_argv[], int cmd_argc);
   void doOpen(string cmd_argv[], int cmd_argc);
   void doEcho(string cmd_argv[], int cmd_argc);
   void doClose(string cmd_argv[], int cmd_argc);
   void doHelp(string cmd_argv[], int cmd_argc);
};


#endif // ECHOCLI_H_INCLUDED
