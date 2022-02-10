#include <iostream> // vstup, vystup, chybovy vystup
#include <fstream>
#include <string> //retezce c++
#include <string.h>
#include <getopt.h> //getopt_long
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstdlib> //strtol
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <vector>
#include <sstream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
#define BSIZE 1024

std::string command;

//--------------Prevzato z manualni stranky base64-------------------
//std::string base64_encode(unsigned char const*, unsigned int len);

static const unsigned char base64_table[65] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/**
* base64_encode - Base64 encode
* @src: Data to be encoded
* @len: Length of the data to be encoded
* @out_len: Pointer to output length variable, or %NULL if not used
* Returns: Allocated buffer of out_len bytes of encoded data,
* or empty string on failure
*/
std::string base64_encode(const unsigned char *src, size_t len)
{
    unsigned char *out, *pos;
    const unsigned char *end, *in;

    size_t olen;

    olen = 4 * ((len + 2) / 3); /* 3-byte blocks to 4-byte */

    if (olen < len)
        return std::string(); /* integer overflow */

    std::string outStr;
    outStr.resize(olen);
    out = (unsigned char *)&outStr[0];

    end = src + len;
    in = src;
    pos = out;
    while (end - in >= 3)
    {
        *pos++ = base64_table[in[0] >> 2];
        *pos++ = base64_table[((in[0] & 0x03) << 4) | (in[1] >> 4)];
        *pos++ = base64_table[((in[1] & 0x0f) << 2) | (in[2] >> 6)];
        *pos++ = base64_table[in[2] & 0x3f];
        in += 3;
    }

    if (end - in)
    {
        *pos++ = base64_table[in[0] >> 2];
        if (end - in == 1)
        {
            *pos++ = base64_table[(in[0] & 0x03) << 4];
            *pos++ = '=';
        }
        else
        {
            *pos++ = base64_table[((in[0] & 0x03) << 4) |
                                  (in[1] >> 4)];
            *pos++ = base64_table[(in[1] & 0x0f) << 2];
        }
        *pos++ = '=';
    }

    return outStr;
}

int main(int argc, char *argv[])
{

    using namespace std;
    int option_index = 0;
    string message;
    char buffer[100000];
    int c;
    char *pEnd;
    char server_addr[] = "127.0.0.1";
    char port_num[] = "32323";
    string code_pwd;
    bool addr = false;
    bool port = false;

    bool help = false;
    int argccopy = argc;
    while (argccopy--)
    {
        if (strcmp(argv[argccopy], "--address") == 0)
        {
            addr = true;
            strcpy(server_addr, argv[argccopy + 1]);
        }
        else if (strcmp(argv[argccopy], "--port") == 0)
        {
            port = true;
            strcpy(port_num, argv[argccopy + 1]);
        }
        else if (strcmp(argv[argccopy], "--help") == 0)
        {
            help = true;
        }
    }
    while ((c = getopt(argc, argv, "ha:p:")) != -1)
    {
        switch (c)
        {
        case 'a':
            addr = true;
            if (strcmp(server_addr, "") == 0)
                strcpy(server_addr, optarg);
            break;
        case 'p':
            port = true;
            if (strcmp(port_num, "") == 0)
                strcat(port_num, optarg);
            break;
        case 'h':
            help = true;
            break;
        default:
            cerr << "Wrong arguments" << endl;
            return 0;
        }
    }
    if (help)
    {
        cout << "usage: client [ <option> ... ] <command> [<args>] ..." << endl;
        cout << endl;
        cout << "<option> is one of" << endl;
        cout << endl;
        cout << "   -a <addr>, --address <addr>" << endl;
        cout << "      Server hostname or address to connect to" << endl;
        cout << "   -p <port>, --port <port>" << endl;
        cout << "      Server port to connect to" << endl;
        cout << "   --help, -h" << endl;
        cout << "      Show this help" << endl;
        cout << "   --" << endl;
        cout << "      Do not treat any remaining argument as a switch (at this level)" << endl;
        cout << " " << endl;
        cout << " Multiple single-letter switches can be combined after" << endl;
        cout << " one -. For example, -h- is the same as -h --." << endl;
        cout << " Supported commands:" << endl;
        cout << "   register <username> <password>" << endl;
        cout << "   login <username> <password>" << endl;
        cout << "   list" << endl;
        cout << "   send <recipient> <subject> <body>" << endl;
        cout << "   fetch <id>" << endl;
        cout << "   logout" << endl;
    }

    int port_number;
    port_number = strtol(port_num, &pEnd, 10);
    if (*pEnd)
    {
        cout << "Port number is a string" << endl;
    }
    if (port == false) {
        port_number = 32323;
    }
    char *pas;
    string login;
    char *mes;
    for (int i = 1; i < argc; i++)
    {
        char *arg = argv[i];
        if (strcmp(arg, "register") == 0)
        {
            if (argc != i + 3)
            {
                cout << "i = " << i << endl;
                cout << "argc = " << argc << endl;
                cerr << "Invalid arguments\n";
                exit(1);
            }
            pas = argv[i + 1];
            login = argv[i + 2];
            code_pwd = base64_encode((const unsigned char *)(login.c_str()), login.length());
            code_pwd = "\"" + code_pwd + "\"";
            string bracket = "(";
            message = bracket + "register" + " \"" + pas + "\" " + code_pwd + ")";

            break;
        }
        else if (strcmp(arg, "login") == 0)
        {
            if (argc != i + 3)
            {
                cout << "i = " << i << endl;
                cout << "argc = " << argc << endl;
                cerr << "Invalid arguments\n";
                exit(1);
            }
            pas = argv[i + 1];
            login = argv[i + 2];
            code_pwd = base64_encode((const unsigned char *)login.c_str(), login.length());
            code_pwd = "\"" + code_pwd + "\"";
            command = "login";
            string bracket = "(";
            message = bracket + "login" + " \"" + pas + "\" " + code_pwd + ")";
            break;
        }
        else if (strcmp(arg, "send") == 0)
        {
            if (argc != i + 4)
            {
                cout << "i = " << i << endl;
                cout << "argc = " << argc << endl;
                cerr << "Invalid arguments\n";
                exit(1);
            }
            string line;
            ifstream file("login-create");
            if (file.is_open())
            {
                getline(file, line);
            }
            file.close();
            if (line == "")
            {
                cout << "Not logged in" << endl;
                exit(1);
            }
            pas = argv[i + 1];
            login = argv[i + 2];
            mes = argv[i + 3];
            string bracket = "(";
            message = bracket + "send" + " " + line + +" \"" + pas + "\" \"" + login + "\" \"" + mes + "\"" + ")";
            break;
        }
        else if (strcmp(arg, "list") == 0)
        {
            if (argc != i + 1)
            {
                cout << "i = " << i << endl;
                cout << "argc = " << argc << endl;
                cerr << "Invalid arguments\n";
                exit(1);
            }
            string line;
            ifstream file("login-create");
            if (file.fail())
            {
                cout << "Not logged in" << endl;
                exit(1);
            }
            if (file.is_open())
            {
                getline(file, line);
            }
            file.close();
            string bracket = "(";
            message = bracket + "list" + " " + line + ")";
            break;
        }
        else if (strcmp(arg, "logout") == 0)
        {
            if (argc != i + 1)
            {
                cout << "i = " << i << endl;
                cout << "argc = " << argc << endl;
                cerr << "Invalid arguments\n";
                exit(1);
            }
            string line;
            ifstream file("login-create");
            if (file.fail())
            {
                cout << "Not logged in" << endl;
                exit(1);
            }
            if (file.is_open())
            {
                getline(file, line);
            }
            file.close();
            string bracket = "(";
            message = bracket + "logout " + line + ")";
            remove("login-create");
            break;
        }
        else if (strcmp(arg, "fetch") == 0)
        {
            if (argc != i + 2)
            {
                cout << "i = " << i << endl;
                cout << "argc = " << argc << endl;
                cerr << "Invalid arguments\n";
                exit(1);
            }

            string line;
            ifstream file("login-create");
            if (file.is_open())
            {
                getline(file, line);
            }
            file.close();

            if (line == "")
            {
                cout << "Not logged in" << endl;
                exit(1);
            }
            pas = argv[i + 1];
            string bracket = "(";
            message = bracket + "fetch " + line + " " + pas + ")";
            break;
        }
    }

    int sock, log;
    struct sockaddr_in addrs;

    if (inet_pton(AF_INET, server_addr, &(addrs.sin_addr)) > 0)
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock <= 0)
        {
            cerr << "Failed socket\n";
            exit(1);
        }

        bzero(&addrs, sizeof(addrs));
        addrs.sin_family = AF_INET;
        addrs.sin_addr.s_addr = inet_addr(server_addr);
        addrs.sin_port = htons(port_number);

        if (connect(sock, (struct sockaddr *)&addrs, sizeof(addrs)) != 0)
        {
            cerr << "Connecting failed" << endl;
            exit(1);
        }

        int dst = send(sock, message.c_str(), message.length(), 0);

        int src = recv(sock, buffer, BSIZE, 0);
        string resp = buffer;
        cout << "SUCCESS: " << resp << endl;
        if (!command.compare("login"))
        {
            resp.erase(0, resp.find("\"") + 1);
            resp.erase(0, resp.find("\"") + 1);
            resp.erase(0, resp.find("\"") + 1);
            ofstream o("login-create");
            o << "\"" + resp.substr(0, resp.find("\"") + 1);
        }
    }
}