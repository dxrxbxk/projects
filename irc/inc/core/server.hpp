/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 22:59:22 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 00:48:52 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "types.hpp"
# include "io_event.hpp"
# include "connexion.hpp"
# include "channel.hpp"
# include "epoll.hpp"
# include "signal.hpp"
# include "sharedfd.hpp"
# include <stack>
#include <string>

struct ServerInfo {
	std::string name;
	std::string addr;
	std::string port;
	std::string password;

	ServerInfo() : name(), addr(), port(), password() {};

	~ServerInfo() {};

	ServerInfo(const std::string& n, const std::string& ip, const std::string& p, const std::string& cp)
        : name(n), addr(ip), port(p), password(cp) {}

	void add_password(std::string &p)		{ password.swap(p); } 
	void add_password(const std::string &p) { password = p; }

};

class Server : public IOEvent {

	public:

		/* initialize server */
		void init(ServerInfo&, const Shared_fd&);

		/* run server */
		void run(void);

		/* stop server */
		void stop(void);


		// -- IOEvent methods ---------------------------------------------------

		void				read(void);
		void				write(void);
		int					fd(void) const;
		void				disconnect(void);


		// -- public methods ----------------------------------------------------

		Connexion&		get_conn(const std::string&);
		void	ch_nick(Connexion&, std::string&);
		bool	nick_exist(const std::string&);

		void	accept_newcomer(Connexion&);
		void	remove_newcomer(const Connexion&);

		void	broadcast(const std::string&, const Connexion&);
		void	broadcast(const std::string& msg);

		void	accept(void);

		// -- public accessors -------------------------------------------------

		const std::string&	name(void) const;
		const std::string&	port(void) const;
		const std::string&	address(void) const;
		const std::string&	password(void) const;
		std::size_t			get_nb_conns(void) const;
		Poll&				poller(void) ;

		bool 				has_password(void) const;

		Channel&			get_channel(const std::string&);
		Channel&			channel(const std::string&);
		bool				channel_exist(const std::string&) const;
		Channel&			create_channel(const std::string&, Connexion&);
		void				remove_channel(const std::string&);
		void				print_channels(void) const;

		void				add_rm_list(Connexion&);
		void				remove_rm_list(void);

		void				add_rm_channel(Channel&);
		void				rm_channels(void);

		void				motd(const std::string&);
		vec_str				motd(void);


		// -- public static methods --------------------------------------------

		static Server& shared(void);


	private:

		// -- private methods --------------------------------------------------
		void				read_input(void);
		l_str				check_crlf(void);

		typedef std::map<std::string, Channel>::const_iterator		channel_iterator;
		typedef std::map<std::string, Connexion*>::const_iterator	nick_iterator;
		typedef std::map<std::string, Channel>::iterator			channel_iterator_m;

		// -- private constructors ---------------------------------------------

		Server(void);
		~Server(void);
		Server(const Server&);
		Server& operator=(const Server&);

		// -- private types ----------------------------------------------------

		typedef std::map<int, Connexion>			conn_map;
		typedef std::map<std::string, Channel>		channel_map;
		typedef std::map<std::string, Connexion*>	nick_map;
		typedef std::stack<Connexion*>				rm_list;
		typedef std::stack<Channel*>				rm_channel;


		// -- private members --------------------------------------------------

		bool			_initialized;
		ServerInfo		_info;
		Shared_fd		_socket;
		Poll			_poller;
		channel_map 	_channels;
		conn_map		_conns;
		nick_map		_nicks;
		rm_list			_rm_list;
		rm_channel		_rm_channels;
		std::string		_motd;

		std::string		_buffer_in;
		std::string		_buffer_out;

};
#endif
