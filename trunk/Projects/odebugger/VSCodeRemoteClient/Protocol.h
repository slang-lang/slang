
#ifndef ObjectiveScript_odebugger_RemoteClient_Protocol_h
#define ObjectiveScript_odebugger_RemoteClient_Protocol_h


// Library includes
#include <string>
#include <Json/Value.h>

// Project includes
#include <Common/AClient.h>
#include <Core/Types.h>

// Forward declarations

// Namespace declarations


namespace VSCodeDebug {


class ProtocolMessage
{
public:
	ProtocolMessage(std::string type_)
	: seq(-1),
	  type(type_)
	{ }

	ProtocolMessage(std::string type_, int seq_)
	: seq(seq_),
	  type(type_)
	{ }

	virtual ~ProtocolMessage()
	{ }

public:
	int seq;
	std::string type;
};


class Event : public ProtocolMessage
{
public:
	Event(const std::string type_)
	: ProtocolMessage("event"),
	  eventtype(type_)
	{ }

public:
	std::string eventtype;
};


class Request : public ProtocolMessage
{
public:
	Request(int id, const std::string& cmd, const StringList& args)
	: ProtocolMessage("request", id),
	  arguments(args),
	  command(cmd)
	{ }

public:
	StringList arguments;
	std::string command;
};


class Response : public ProtocolMessage
{
public:
	Response(const Request& req)
	: ProtocolMessage("response"),
	  request(req),
	  success(false)
	{ }

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
