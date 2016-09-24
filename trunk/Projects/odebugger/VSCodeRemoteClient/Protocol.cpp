
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
		if ( !msg.isMember("type") ) {
			return 0;
		}

		if ( msg["type"].asString() == "event" ) {
			result = convertToEvent(msg);
		}
		else if ( msg["type"].asString() == "response" ) {
			result = convertToResponse(msg);
		}
		else if ( msg["type"].asString() == "request" ) {
			result = convertToRequest(msg);
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
	StringList arguments;
	std::string command = message["command"].asString();
	int seq = -1;

	if ( message.isMember("seq") ) {
		seq = message["seq"].asInt();
	}

	if ( message.isMember("arguments") ) {
		Json::Value array = message["arguments"];

		for ( Json::Value::Members::const_iterator it = array.members().begin(); it != array.members().end(); ++it ) {
			arguments.push_back(it->asString());
		}
	}

	return new Request(seq, command, arguments);
}

Response* MessageConverter::convertToResponse(const Json::Value& message) const
{
	Request* request = convertToRequest(message["request"]);

	Response* response = new Response(*request);
	response->success = message["success"].asBool();

	return response;
}


}