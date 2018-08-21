
// Header
#include "NetworkExtension.h"

// Library includes

// Project includes
#include "Accept.h"
#include "Bind.h"
#include "Close.h"
#include "Connect.h"
#include "Listen.h"
#include "Read.h"
#include "Socket.h"
#include "Write.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {
namespace Network {


SystemNetworkExtension::SystemNetworkExtension()
: AExtension("Network")
{
}

SystemNetworkExtension::~SystemNetworkExtension()
{
}

void SystemNetworkExtension::initialize(IScope* scope)
{
	// domain constants
	scope->define("AF_UNIX", new Runtime::IntegerObject(AF_UNIX));
	scope->define("AF_INET", new Runtime::IntegerObject(AF_INET));
	scope->define("AF_IPX", new Runtime::IntegerObject(AF_IPX));
	//scope->define("AF_NETLINK", new Runtime::IntegerObject(AF_NETLINK));
	//scope->define("AF_X25", new Runtime::IntegerObject(AF_X25));
	//scope->define("AF_AX25", new Runtime::IntegerObject(AF_AX25));
	//scope->define("AF_ATMPVC", new Runtime::IntegerObject(AF_ATMPVC));
	scope->define("AF_APPLETALK", new Runtime::IntegerObject(AF_APPLETALK));
	//scope->define("AF_PACKET", new Runtime::IntegerObject(AF_PACKET));
	//scope->define("AF_ALG", new Runtime::IntegerObject(AF_ALG));

#ifdef _WIN32
	// Win32 only
#else
	// Unix/Linux only
	scope->define("AF_LOCAL", new Runtime::IntegerObject(AF_LOCAL));
	scope->define("AF_INET6", new Runtime::IntegerObject(AF_INET6));

	scope->define("EAFNOSUPPORT", new Runtime::IntegerObject(EAFNOSUPPORT));
	scope->define("ENOBUFS", new Runtime::IntegerObject(ENOBUFS));
	scope->define("EPROTONOSUPPORT", new Runtime::IntegerObject(EPROTONOSUPPORT));
#endif

	// type constants
	scope->define("SOCK_STREAM", new Runtime::IntegerObject(SOCK_STREAM));
	scope->define("SOCK_DGRAM", new Runtime::IntegerObject(SOCK_DGRAM));
	scope->define("SOCK_SEQPACKET", new Runtime::IntegerObject(SOCK_SEQPACKET));
	scope->define("SOCK_RAW", new Runtime::IntegerObject(SOCK_RAW));
	scope->define("SOCK_RDM", new Runtime::IntegerObject(SOCK_RDM));
	//scope->define("SOCK_PACKET", new Runtime::IntegerObject(SOCK_PACKET));
	//scope->define("SOCK_NONBLOCK", new Runtime::IntegerObject(SOCK_NONBLOCK));
	//scope->define("SOCK_CLOEXEC", new Runtime::IntegerObject(SOCK_CLOEXEC));

	scope->define("INADDR_ANY", new Runtime::StringObject(std::string("0.0.0.0")));


	// finalize initialization
	AExtension::initialize(scope);
}

void SystemNetworkExtension::provideMethods(ExtensionMethods &methods)
{
	methods.push_back(new Accept());
	methods.push_back(new Bind());
	methods.push_back(new Close());
	methods.push_back(new Connect());
	methods.push_back(new Listen());
	methods.push_back(new ReadBool());
	methods.push_back(new ReadDouble());
	methods.push_back(new ReadFloat());
	methods.push_back(new ReadInt());
	methods.push_back(new ReadString());
	methods.push_back(new Socket());
	methods.push_back(new WriteBool());
	methods.push_back(new WriteDouble());
	methods.push_back(new WriteFloat());
	methods.push_back(new WriteInt());
	methods.push_back(new WriteString());
}


}
}
}
}
