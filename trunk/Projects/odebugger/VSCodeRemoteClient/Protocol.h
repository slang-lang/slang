
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
	virtual Json::Value serialize() const = 0;

public:
	int seq;
	std::string type;
};


class Event : public ProtocolMessage
{
public:
	Event(const std::string eventtype_)
	: ProtocolMessage("event"),
	  eventtype(eventtype_)
	{ }

public:
	Json::Value serialize() const {
		Json::Value result;

		result.addMember("seq", seq);
		result.addMember("type", type);

		result.addMember("eventtype", eventtype);

		return result;
	}

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
	Json::Value serialize() const {
		Json::Value result;

		result.addMember("seq", seq);
		result.addMember("type", type);

		result.addMember("command", command);

		if ( !arguments.empty() ) {
			Json::Value args;
			for ( StringList::const_iterator it = arguments.begin(); it != arguments.end(); ++it ) {
				args.addElement(Json::Value(*it));
			}
			result.addMember("arguments", args);
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
	Response(const Request& req)
	: ProtocolMessage("response", req.seq),
	  request(req),
	  success(false)
	{ }

public:
	Json::Value serialize() const {
		Json::Value result;

		result.addMember("seq", seq);
		result.addMember("type", type);

		result.addMember("success", success);

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
