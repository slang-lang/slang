
#ifndef Slang_slang_dbg_RemoteClient_Protocol_h
#define Slang_slang_dbg_RemoteClient_Protocol_h


// Library includes
#include <string>
#include <utility>
#include <json/value.h>

// Project includes
#include <Common/AClient.h>
#include <Core/Common/Types.h>

// Forward declarations

// Namespace declarations
using namespace Slang;


namespace VSCodeDebug {


class ProtocolMessage
{
public:
	ProtocolMessage(std::string type_)
	: seq(-1),
	  type(std::move(type_))
	{ }

	ProtocolMessage(std::string type_, int seq_)
	: seq(seq_),
	  type(std::move(type_))
	{ }

	virtual ~ProtocolMessage() = default;

public:
	virtual Json::Value serialize() const = 0;

public:
	int seq;
	std::string type;
};


class Event : public ProtocolMessage
{
public:
	explicit Event(std::string eventtype_)
	: ProtocolMessage("event"),
	  eventtype(std::move(eventtype_))
	{ }

public:
	Json::Value serialize() const {
		Json::Value result;

		result[ "seq" ] = seq;
		result[ "type" ] = type;

		result[ "eventtype" ] = eventtype;

		return result;
	}

public:
	std::string eventtype;
};


class Request : public ProtocolMessage
{
public:
	Request(int id, std::string  cmd, StringList  args)
	: ProtocolMessage("request", id),
	  arguments(std::move(args)),
	  command(std::move(cmd))
	{ }

public:
	Json::Value serialize() const {
		Json::Value result;

		result[ "seq" ] = seq;
		result[ "type" ] = type;

		result[ "command" ] = command;

		if ( !arguments.empty() ) {
			Json::Value args;
			for ( const auto& argument : arguments ) {
				args.append( Json::Value( argument ) );
			}
			result[ "arguments" ] = args;
		}

		return result;
	}

public:
	StringList arguments;
	std::string command;
};


class Response : public ProtocolMessage
{
public:
	explicit Response(const Request& req)
	: ProtocolMessage("response", req.seq),
	  request(req),
	  success(false)
	{ }

public:
	Json::Value serialize() const {
		Json::Value result;

		result[ "seq" ] = seq;
		result[ "type" ] = type;

		result[ "success" ] = success;

		return result;
	}

public:
	Request request;
	bool success;
};


class MessageConverter
{
public:
	ProtocolMessage* convert(const std::string& message) const;

private:
	Event* convertToEvent(const Json::Value& message) const;
	Request* convertToRequest(const Json::Value& message) const;
	Response* convertToResponse(const Json::Value& message) const;
};


}


#endif
