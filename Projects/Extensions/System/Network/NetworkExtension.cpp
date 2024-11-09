
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
#include "Shutdown.h"
#include "Socket.h"
#include "Write.h"

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace System {
namespace Network {


SystemNetworkExtension::SystemNetworkExtension()
: AExtension( "Network", "0.0.2" )
{
}

void SystemNetworkExtension::initialize( ExtensionNamespace* scope )
{
	// domain constants
	scope->define( "AF_UNIX", new Runtime::Int32Type( AF_UNIX ) );
	scope->define( "AF_INET", new Runtime::Int32Type( AF_INET ) );
	scope->define( "AF_IPX", new Runtime::Int32Type( AF_IPX ) );
	//scope->define( "AF_NETLINK", new Runtime::Int32Type( AF_NETLINK ) );
	//scope->define( "AF_X25", new Runtime::Int32Type( AF_X25 ) );
	//scope->define( "AF_AX25", new Runtime::Int32Type( AF_AX25 ) );
	//scope->define( "AF_ATMPVC", new Runtime::Int32Type( AF_ATMPVC ) );
	scope->define( "AF_APPLETALK", new Runtime::Int32Type( AF_APPLETALK ) );
	//scope->define( "AF_PACKET", new Runtime::Int32Type( AF_PACKET ) );
	//scope->define( "AF_ALG", new Runtime::Int32Type( AF_ALG ) );

#ifdef _WIN32
	// Win32 only
#else
	// Unix/Linux only
	scope->define( "AF_LOCAL", new Runtime::Int32Type( AF_LOCAL ) );
	scope->define( "AF_INET6", new Runtime::Int32Type( AF_INET6 ) );

	scope->define( "EAFNOSUPPORT", new Runtime::Int32Type( EAFNOSUPPORT ) );
	scope->define( "ENOBUFS", new Runtime::Int32Type( ENOBUFS ) );
	scope->define( "EPROTONOSUPPORT", new Runtime::Int32Type( EPROTONOSUPPORT ) );
#endif

	// type constants
	scope->define( "SOCK_STREAM", new Runtime::Int32Type( SOCK_STREAM ) );
	scope->define( "SOCK_DGRAM", new Runtime::Int32Type( SOCK_DGRAM ) );
	scope->define( "SOCK_SEQPACKET", new Runtime::Int32Type( SOCK_SEQPACKET ) );
	scope->define( "SOCK_RAW", new Runtime::Int32Type( SOCK_RAW ) );
	scope->define( "SOCK_RDM", new Runtime::Int32Type( SOCK_RDM ) );
	//scope->define( "SOCK_PACKET", new Runtime::Int32Type( SOCK_PACKET ) );
	//scope->define( "SOCK_NONBLOCK", new Runtime::Int32Type( SOCK_NONBLOCK ) );
	//scope->define( "SOCK_CLOEXEC", new Runtime::Int32Type( SOCK_CLOEXEC ) );

	scope->define( "INADDR_ANY", new Runtime::StringObject( std::string( "0.0.0.0" ) ) );


	/*
	 * howto arguments for shutdown(2), specified by Posix.1g.
	 */
#ifdef _WIN32
	 // Win32 only
#else
	scope->define( "SHUT_RD", new Runtime::Int32Type( SHUT_RD ) );		// shut down the reading side
	scope->define( "SHUT_WR", new Runtime::Int32Type( SHUT_WR ) );		// shut down the writing side
	scope->define( "SHUT_RDWR", new Runtime::Int32Type( SHUT_RDWR ) );	// shut down both sides
#endif
}

void SystemNetworkExtension::provideMethods( ExtensionMethods& methods )
{
	methods.push_back( new Accept() );
	methods.push_back( new Bind() );
	methods.push_back( new Close() );
	methods.push_back( new Connect() );
	methods.push_back( new Listen() );
	methods.push_back( new ReadBool() );
	methods.push_back( new ReadDouble() );
	methods.push_back( new ReadFloat() );
	methods.push_back( new ReadInt() );
	methods.push_back( new ReadString() );
	methods.push_back( new Shutdown() );
	methods.push_back( new Socket() );
	methods.push_back( new WriteBool() );
	methods.push_back( new WriteDouble() );
	methods.push_back( new WriteFloat() );
	methods.push_back( new WriteInt() );
	methods.push_back( new WriteString() );
}


}
}
}
}
