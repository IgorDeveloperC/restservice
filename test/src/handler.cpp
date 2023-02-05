#include "../include/handler.h"


handler::handler()
{
	//ctor
}
handler::handler(utility::string_t url, const int capacity) :m_listener(url), _cache(capacity)
{
	m_listener.support(methods::GET, std::bind(&handler::handle_get, this, std::placeholders::_1));
	m_listener.support(methods::POST, std::bind(&handler::handle_post, this, std::placeholders::_1));
}
handler::~handler()
{
	//dtor
}

//
// Get Request 
//
void handler::handle_get(http_request message)
{
	mutex.lock_shared();
	auto uri_parameters = uri::split_query(message.request_uri().query());

	pplx::task<void>t;
	if (!uri_parameters.contains(U("key"))) {
		message.reply(status_codes::BadRequest);
		mutex.unlock_shared();
		return;
	}
	try {
		int key = stoi(uri_parameters[U("key")]);
		
		int result = _cache.Find(key);
		message.reply(status_codes::OK, result);
	}
	catch (...) {
		message.reply(status_codes::BadRequest);
	}
	mutex.unlock_shared();
	return;

};

//
// A POST request
//
void handler::handle_post(http_request message)
{
	mutex.lock();
	json::value input_json = message.extract_json().get();

	try {
		int _key = input_json.at(U("key")).as_integer();
		int _value = input_json.at(U("value")).as_integer();
		_cache.Add(_key, _value);
		message.reply(status_codes::OK, "Added key and value to cache");
	}
	catch (...) {
		message.reply(status_codes::BadRequest);
	}
	mutex.unlock();
	return;
};


