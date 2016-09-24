
// Header
#include "Protocol.h"

// Library includes
#include <Json/Json.h>

// Project includes

// Namespace declarations


namespace VSCodeDebug {


ProtocolMessage* MessageConverter::convert(const std::string& message) const
{
	ProtocolMessage* result = 0;

	Json::Reader r;
	Json::Value msg;

	if ( r.parse(message, msg) ) {
		if ( msg.isMember("event") ) {
			result = convertToEvent(msg["event"]);
		}
		else if ( msg.isMember("response") ) {
			result = convertToResponse(msg["response"]);
		}
		else if ( msg.isMember("request") ) {
			result = convertToRequest(msg["request"]);
		}
	}

	return result;
}

Event* MessageConverter::convertToEvent(const Json::Value& message) const
{
	return new Event(message.asString());
}

Request* MessageConverter::convertToRequest(const Json::Value& message) const
{
	StringList args;
	std::string command = message["command"].asString();
	int id = -1;

	if ( message.isMember("id") ) {
		id = message["id"].asInt();
	}

	if ( message.isMember("args") ) {
		Json::Value array = message["args"];

		for ( Json::Value::Members::const_iterator it = array.members().begin(); it != array.members().end(); ++it ) {
			args.push_back(it->asString());
		}
	}

	return new Request(id, command, args);
}

Response* MessageConverter::convertToResponse(const Json::Value& message) const
{
	Request* request = convertToRequest(message["request"]);

	Response* response = new Response(*request);
	response->success = message["success"].asBool();

	return response;
}


}