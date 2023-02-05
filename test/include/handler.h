#ifndef HANDLER_H
#define HANDLER_H

#pragma once

#include <iostream>
#include "stdafx.h"
#include <shared_mutex>

#include "Cache_map.h"

using namespace std;
using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;


class handler
{
    public:
        handler();
        handler(utility::string_t url, const int capacity);
        virtual ~handler();

        pplx::task<void>open(){return m_listener.open();}
        pplx::task<void>close(){return m_listener.close();}

    protected:

    private:
        void handle_get(http_request message);
        void handle_post(http_request message);
        http_listener m_listener;
        shared_mutex mutex;
        Cache_map _cache;
};

#endif // HANDLER_H


