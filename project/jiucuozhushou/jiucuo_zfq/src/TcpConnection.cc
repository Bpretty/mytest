 ///
 /// @file    TcpConnection.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-07 17:12:51
 ///
 

#include "../include/TcpConnection.h"
#include "../include/InetAddress.h"
#include "../include/EventLoop.h"

#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>

#include <sstream>

namespace wd
{

struct train_t
{
    int len;
    char buff[1024];
};



TcpConnection::TcpConnection(int fd, EventLoop * loop)
: _sock(fd)
, _socketIo(fd)
, _localAddr(getLocalAddr(fd))
, _peerAddr(getPeerAddr(fd))
, _isShutdwonWrite(false)
, _loop(loop)
{
}

TcpConnection::~TcpConnection()
{
	if(!_isShutdwonWrite) {
		shutdown();
	}
}

string TcpConnection::receive()
{
	char buff[65536] = {0};
	_socketIo.readline(buff, sizeof(buff));
	return string(buff);
}
	
void TcpConnection::send(const string & msg)
{
    train_t train;
    train.len = msg.size();
    memcpy(train.buff,msg.c_str(),train.len);
	_socketIo.writen((char*)&train,4+train.len);
}

void TcpConnection::sendInLoop(const string & msg)
{
	_loop->runInLoop(std::bind(&TcpConnection::send, this, msg));
}

void TcpConnection::shutdown()
{
	if(!_isShutdwonWrite) {
		_isShutdwonWrite = true;
		_sock.shutdownWrite();
	}
}

string TcpConnection::toString() const
{
	std::ostringstream oss;
	oss << _localAddr.ip() << ":" << _localAddr.port() << " --> "
		<< _peerAddr.ip() << ":" << _peerAddr.port();
	return oss.str();
}


InetAddress TcpConnection::getLocalAddr(int fd)
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(struct sockaddr);
	if(getsockname(_sock.fd(), (struct sockaddr*)&addr, &len) == -1) {
		perror("getsockname");
	}
	return InetAddress(addr);
}

InetAddress TcpConnection::getPeerAddr(int fd)
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(struct sockaddr);
	if(getpeername(_sock.fd(), (struct sockaddr*)&addr, &len) == -1) {
		perror("getpeername");
	}
	return InetAddress(addr);
}

void TcpConnection::setConnectionCallback(const TcpConnectionCallback & cb)
{
	_onConnection = std::move(cb);
}

void TcpConnection::setMessageCallback(const TcpConnectionCallback & cb)
{
	_onMessage = std::move(cb);
}

void TcpConnection::setCloseCallback(const TcpConnectionCallback & cb)
{
	_onClose = std::move(cb);
}

void TcpConnection::handleConnectionCallback()
{
	if(_onConnection) {
		_onConnection(shared_from_this());
	}
}

void TcpConnection::handleMessageCallback()
{
	if(_onMessage) {
		_onMessage(shared_from_this());
	}
}

void TcpConnection::handleCloseCallback()
{
	if(_onClose) {
		_onClose(shared_from_this());
	}
}

}//end of namespace wd
