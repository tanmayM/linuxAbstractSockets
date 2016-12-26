# linuxAbstractSockets
Unix domain sockets without actual filesystem path for socket. Useful when limited permissions

When we create unix domain socket, we need to give actual filesystem path (e.g. /opt/mySocket) when we create socket.
This is OK as long as we have permissions. If we don't then it creates problem. Abstract sockets come handy in this
situation. The socket exists in abstract namespace and not as actual filesystem file. 

All that is needed is a tweak in the way we name the socket.

This is also useful for java to C communication using java LocalSocket (Java local sockets don't use actual path but 'names'.
Hence you need to use abstract sockets on the C side for communication)
