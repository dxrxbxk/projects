/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 22:59:12 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 00:53:47 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "types.hpp"
#include "utils.hpp"
#define BUFFER_SIZE 1024

static const char* message_irc = 
"This server has been sponsored by 935\r\n"
" \r\n"
"-------------------------------------------------------------------\r\n"
"[%] Server Staff =-\r\n"
" \r\n"
".::. Administrator....:\r\n"
"                        Terry Davis\r\n"
"\r\n"
".::. Operators........:\r\n"
"                        diroyer\r\n"
"                        tutur\r\n"
"                        momadani\r\n"
" \r\n"
"-------------------------------------------------------------------\r\n"
"[%] Server Policies =-\r\n"
" \r\n"
"a. No spamming or advertising allowed, if found you will be banned from this server/network.\r\n"
"b. No malicious bots, including flood and nick/channel chasers.\r\n"
"c. No channel filler bots/clients.\r\n"
"   # A channel filler is a client or bot which is connected just to fill a channel and make it look bigger.\r\n"
"d. Operator impersonation will not be tolerated and cause you to be banned from this server/network.\r\n"
" \r\n"
"\"REMEMBER IRC IS A PRIVILEGE, NOT A RIGHT\"\r\n"
"-------------------------------------------------------------------\r\n"
" \r\n"
"Thank you for using BackRooms.42.net, we hope you enjoy the stay with us.";


Server::Server(void)
:	_initialized(false),
	_info(),
	_socket(),
	_poller(),
	_channels(),
	_conns(),
	_nicks(),
	_rm_list(),
	_motd(message_irc)
{
}

Server::Server(const Server&) {}

Server::~Server(void) {}

Server& Server::operator=(const Server&) { return *this; }

// -- public static methods ----------------------------------------------------

Server& Server::shared(void) {
	static Server instance;
	return instance;
}

void Server::init(ServerInfo& info, const Shared_fd& socket) {
	if (_initialized == true)
		throw std::runtime_error("server already initialized");

	_info = info;
	_socket = socket;

	//Logger::set_server(*this);

	_poller.add_event(*this);

//_poller.add_event(Logger::shared());

#if defined PIPE
	_poller.add_event(Signal::shared());
#endif

	_initialized = true;

}

// print channel and users in it with _channels and _nicks
void Server::print_channels(void) const {
	channel_iterator it = _channels.begin();
	while (it != _channels.end()) {
		std::cout << "channel: " << it->first << std::endl;
		it->second.print_users();
		++it;
	}
}

void Server::run(void) {
	while (_initialized == true)
	{
		_poller.run();
		rm_channels();
		remove_rm_list();
	}
}

void Server::stop(void) {
	_initialized = false;
}

void	Server::accept(void) {
	int cfd;

	//Logger::info("new socket connexion");
	PRINT("new connection");

	cfd = ::accept(_socket, NULL, NULL);

	if (cfd == -1) {
		ERROR(handleSysError("accept"));
		return;
	}

	Connexion& conn = _conns[cfd] = Connexion(cfd);
	_poller.add_event(conn);

	if (not has_password())
		conn.tracker(PASS);
}


l_str	Server::check_crlf(void) {
	std::string::size_type	pos;
	l_str					l_msg;

	while ((pos = _buffer_in.find("\r\n")) != std::string::npos) {
		l_msg.push_back(_buffer_in.substr(0, pos + 2));
		_buffer_in.erase(0, pos + 2);
	}
	return l_msg;
}

void Server::read(void) {
	accept();
}

void	Server::write(void) {
}

int Server::fd(void) const {
	return _socket;
}

void Server::disconnect(void) {
	PRINT("server disconnected");
}

void	Server::broadcast(const std::string& msg) {
	for (nick_iterator it = _nicks.begin(); it != _nicks.end(); ++it) {
			it->second->enqueue(msg);
	}
}

void	Server::broadcast(const std::string& msg, const Connexion& sender) {
	for (nick_iterator it = _nicks.begin(); it != _nicks.end(); ++it) {
		if (it->second != &sender)
			it->second->enqueue(msg);
	}
}

Channel&	Server::channel(const std::string& channel_name) {
	return _channels[channel_name];
}

Channel&	Server::get_channel(const std::string& channel_name) {
	return _channels[channel_name];
}

Channel& Server::create_channel(const std::string& name, Connexion& creator) {
	return _channels[name] = Channel(name, creator);
}

bool	Server::channel_exist(const std::string& name) const {
	return _channels.count(name);
}

void	Server::remove_channel(const std::string& name) {
	_channels.erase(name);
}

void	Server::ch_nick(Connexion& conn, std::string& new_nick) {	
	_nicks[new_nick] = &conn;
	// change name (key) in every channel user in
	for (channel_iterator_m it = _channels.begin(); it != _channels.end(); ++it) {
		if (it->second.user_in(conn.nickname())) {
			it->second.change_nick(conn.nickname(), new_nick);
		}
	}
	_nicks.erase(conn.nickname());
	conn.nickname(new_nick);
}

bool	Server::nick_exist(const std::string& nick) {
	return _nicks.count(nick);
}

Connexion& Server::get_conn(const std::string& nick) {
	return *_nicks[nick];
}

void Server::accept_newcomer(Connexion& conn) {
	_nicks[conn.nickname()] = &conn;
}

void	Server::remove_newcomer(const Connexion& conn) {
	_nicks.erase(conn.nickname());
}

vec_str		Server::motd(void) {
	std::string::size_type	pos;
	vec_str					l_msg;
	std::string				motd = _motd;

	while ((pos = motd.find("\r\n")) != std::string::npos) {
		l_msg.push_back(motd.substr(0, pos + 2));
		motd.erase(0, pos + 2);
	}
	return l_msg;
}

// -- public accessors --------------------------------------------------------

std::size_t Server::get_nb_conns(void) const {
	return _conns.size();
}

const std::string& Server::address(void) const {
	return _info.addr;
}

const std::string& Server::port(void) const {
	return _info.port;
}

const std::string& Server::password(void) const {
	return _info.password;
}

const std::string& Server::name(void) const {
	return _info.name;
}

bool Server::has_password(void) const {
	return not _info.password.empty();
}

Poll&	Server::poller(void) {
	return _poller;
}

void Server::add_rm_list(Connexion& conn) {
	_rm_list.push(&conn);
}

void Server::remove_rm_list(void) {
	while (!_rm_list.empty())
	{
		Connexion& conn = *_rm_list.top();
		_poller.del_event(conn);
		_nicks.erase(conn.nickname());
		_conns.erase(conn.fd());
		_rm_list.pop();
	}
}

void Server::add_rm_channel(Channel& channel) {
	_rm_channels.push(&channel);
}

void Server::rm_channels(void) {
	while (!_rm_channels.empty())
	{
		Channel& channel = *_rm_channels.top();
		_channels.erase(channel.name());
		_rm_channels.pop();
	}
}
