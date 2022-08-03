#ifndef ECHOTCPCLIENT_H_INCLUDED
#define ECHOTCPCLIENT_H_INCLUDED

#include "tcpclient.h"

class EchoTcpClient: public TcpClient
{
private:

public:
    bool getHTTP(const string& url, int item);
    string getHTML(const string& url, int item);
    bool headHTTP(const string& url);
    bool echo(const string& msg);
};


#endif // ECHOTCPCLIENT_H_INCLUDED

