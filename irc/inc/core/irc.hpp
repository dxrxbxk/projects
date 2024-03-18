/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 03:32:53 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/01 02:11:22 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

# include <iostream>
# include <cstdio>
# include <string>
# include <cstring>
# include <cstdlib>
# include <cerrno>
# include <sstream>
# include <csignal>
# include <map>
# include <vector>

# include <arpa/inet.h>
# include <poll.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netinet/tcp.h>
# include <unistd.h>
# include <sys/types.h>
# include <netdb.h>
# include <sys/wait.h>

# include "utils.hpp"
# include "signal.hpp"
# include "sharedfd.hpp"
# include "server.hpp"
# include "crypt.hpp"

class Irc {
	public:
		Irc(void);
		~Irc(void);

		static int	start(const std::string&, const std::string&);

	private:

		static void init(struct addrinfo*);
		static int	create(const std::string&, const std::string&);
		static int	create_socket(const std::string&);
		static void getSocketInfo(const int);
		static void	check_pipe(void);
		static void	check_crypt(ServerInfo&, const std::string&);

};

#endif
