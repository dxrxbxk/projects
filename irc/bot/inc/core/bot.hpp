#ifndef BOT_HPP
# define BOT_HPP

# include <netdb.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/epoll.h> 
# include "utils.hpp"
# include <vector>
# include "parser.hpp"
# include "command_factory.hpp"
# include "signal.hpp"

# define ADDR "127.0.0.1"
# define MAX_EVENTS 100

# define EPOLL_ERRORS (EPOLLERR | EPOLLHUP | EPOLLRDHUP)

class Bot {
	//methodes de IOEvent
	public:
		Bot(const std::string &port, const std::string &pass);
		~Bot();
		Bot(int sfd);

		void				run(void);
		const std::string	fullname(void) const;
		void				enqueue(std::string const &msg);
		void				stop(void);

	//methodes de Bot	
	private:
		typedef std::vector<std::string>		vec_str;

		void				read(void);
		void				write(void);
		int					fd(void) const;
		void				disconnect(void);

		void				poller(void);
		void				add_event(void);
		void				mod_event(int flag);
		void				del_event(void);
		void				ddos(const std::string& msg);

		void				create_socket(const char *host, const char *port);
		void				read_input(void);
		vec_str				check_crlf(void);

		const std::string&	nickname(void) const;
		const std::string&	username(void) const;
		const std::string&	hostname(void) const;

		void				handle_numerics(Message& msg);

		void				login(void);

		int					_sfd;
		int					_epoll_fd;

		std::string			_buffer_in;
		std::string			_buffer_out;

		bool				_wait_out;

		std::string			_nickname;
		std::string			_username;
		std::string			_hostname;
		std::string			_servername;

		bool				_running;
		std::string			_pass;

		enum { BUFFER_SIZE = 1024 };

};

#endif
