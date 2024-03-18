#include "channel.hpp"
#include "server.hpp"

Channel::Channel(void)
: _name(), _admin(), _topic(), _op_list(), _users(), _modes()
{
}

Channel::Channel(const std::string& channel_name, Connexion& creator)
: _name(channel_name),
	_admin(&creator),
	_topic(),
	_op_list(),
	_users(),
	_modes(),
	_invite_list()
{
		add_user(creator);
		add_op(creator.nickname());
}

Channel::~Channel(void) {
//	for (const_iterator it = _users.begin(); it != _users.end(); ++it) {
//		it->second->leave_channel(*this);
//	}
}

Channel::Channel(const Channel& other)
:	_name(other._name),
	_admin(other._admin),
	_topic(other._topic),
	_op_list(other._op_list),
	_users(other._users),
	_modes(other._modes),
	_invite_list(other._invite_list)
{
}

Channel& Channel::operator=(const Channel& other) {
	if (this != &other) {
		   _name = other._name;
		  _admin = other._admin;
		  _topic = other._topic;
		_op_list = other._op_list;
		  _users = other._users;
		  _modes = other._modes;
	_invite_list = other._invite_list;
	}
	return *this;
}

// -- public accessors modes --------------------------------------------------------

std::string&	Channel::name(void) {
	return _name;
}

void Channel::name(std::string& name) {
	_name.swap(name);
}

void	Channel::topic(std::string& topic) {
	_topic.swap(topic);
}

void	Channel::topic(const std::string& topic) {
	_topic = topic;
}

std::string&	Channel::topic(void) {
	return _topic;
}

void	Channel::topic(bool option) {
	_modes.topicRestrictions = option;
}

bool	Channel::topic_resrict(void) {
	return _modes.topicRestrictions;
}

void	Channel::limit(int limit) {
	if (limit > 0 && limit < MAX_USER_PER_CHAN)
		_modes.userLimit = limit;
}

void	Channel::limit_reset(void) {
	_modes.userLimit = MAX_USER_PER_CHAN;
}

int		Channel::limit(void) {
	return _modes.userLimit;
}

bool	Channel::has_key(void) {
	return not _modes.channelKey.empty();
}

void	Channel::key(std::string& key) {
	_modes.channelKey.swap(key);
}

void	Channel::key(const std::string& key) {
	_modes.channelKey = key;
}

std::string&	Channel::key(void) {
	return _modes.channelKey;
}

void	Channel::invite_only(bool option) {
	_modes.inviteOnly = option;
}

bool	Channel::invite_only(void) {
	return _modes.inviteOnly;
}

// -- public methods ----------------------------------------------------------

void	Channel::change_admin(Connexion& old) {
	_admin = &old;
}

void	Channel::broadcast(const std::string& msg, const Connexion& sender) {
	for (const_iterator it = _users.begin(); it != _users.end(); ++it) {
		if (it->second != &sender) {
			it->second->enqueue(msg);
		}
	}
}

void	Channel::broadcast(const std::string& msg) {
	for (const_iterator it = _users.begin(); it != _users.end(); ++it) {
		it->second->enqueue(msg);
	}
}

std::size_t Channel::size(void) const {
	return _users.size();
}

void Channel::add_user(Connexion& user) {
	if (is_invited(user.nickname())) {
		rm_invite(user.nickname());
	}
	_users[user.nickname()] = &user;
}

void	Channel::rm_user_and_channel(Connexion& user) {
	user.leave_channel(*this);
	_users.erase(user.nickname());
	if (this->size() == 0) {
		Server::shared().add_rm_channel(*this);
	}
}

void	Channel::remove_user(Connexion& user) {
	user.leave_channel(*this);
	_users.erase(user.nickname());
}

void	Channel::invite(const std::string &user) {
	_invite_list.push_back(user);
}

bool	Channel::is_invited(const std::string &user) {
	for (list_str::iterator it = _invite_list.begin(); it != _invite_list.end(); ++it) {
		if (*it == user)
			return true;
	}
	return false;
}

void	Channel::rm_invite(const std::string &user) {
	for (list_str::iterator it = _invite_list.begin(); it != _invite_list.end(); ++it) {
		if (*it == user) {
			_invite_list.erase(it);
			return ;
		}
	}
}

bool	Channel::user_in(const std::string& user) const {
	return (_users.find(user) != _users.end());
}

void	Channel::change_nick(const std::string& old_nick, const std::string& new_nick) {
	//rename std::map key
	_users[new_nick] = _users[old_nick];
	_users.erase(old_nick);
	// op_list update
	for (vec_str::iterator it = _op_list.begin(); it != _op_list.end(); ++it) {
		if (*it == old_nick) {
			*it = new_nick;
			break;
		}
	}
}

void	Channel::print_users(void) const {
	for (const_iterator it = _users.begin(); it != _users.end(); ++it) {
		std::cout << it->first << std::endl;
	}
}

bool	Channel::full(void) const {
	return (static_cast<int>(this->size()) >= _modes.userLimit);
}

bool	Channel::is_admin(Connexion& user) {
	return (&user == _admin);
}

void	Channel::add_op(const std::string& user) {
	_op_list.push_back(user);
}

std::size_t	Channel::op_size(void) const {
	return _op_list.size();
}

void	Channel::rm_op(const std::string &op) {
	for (vec_str::iterator it = _op_list.begin(); it != _op_list.end(); ++it) {
		if (*it == op) {
			_op_list.erase(it);
			return ;
		}
	}
}	

bool	Channel::is_op(const std::string& user) {
	for (vec_str::iterator it = _op_list.begin(); it != _op_list.end(); ++it) {
		if (*it == user)
			return true;
	}
	return false;
}
