#include <iostream>

#include "include/threadpool.h"
#include "include/stdafx.h"
#include "include/handler.h"


using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;


std::unique_ptr<handler> g_httpHandler;

void on_initialize(const string_t& address,const int& capacity)
{
    uri_builder uri(address);
    auto addr = uri.to_uri().to_string();
    g_httpHandler = std::unique_ptr<handler>(new handler(addr,capacity));
    g_httpHandler->open().wait();
    
    ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;

    return;
}

void on_shutdown()
{
    g_httpHandler->close().wait();
    return;
}

#ifdef _WIN32
int wmain(int argc, wchar_t* argv[])  //stream and max capacity in arguments
#else
int main(int argc, char* argv[])
#endif
{
    
    int threads = 0;
    int capacity = 2;               //for testing otherwise error iterator map/set
    if (argc == 3) 
    {
#ifdef _WIN32
        threads = _wtoi(argv[1]);
        capacity = _wtoi(argv[2]);
#else
        threads = atoi(argv[1]);
        capacity = atoi(argv[2]);
#endif
    }
    else {
        cout << "Please restart service with parameters: threads count, max cache capacity" << '\n';
       return 0; //commented for testing
    }
    
    crossplat::threadpool::initialize_with_threads(threads);

    utility::string_t address = U("http://127.0.0.1:8080");
    
    
    on_initialize(address,capacity);
    std::cout << "Press ENTER to exit." << std::endl;

    std::string line;
    std::getline(std::cin, line);

    on_shutdown();
    return 0;
}
