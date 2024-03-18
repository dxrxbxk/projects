/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 01:31:10 by diroyer           #+#    #+#             */
/*   Updated: 2023/08/27 14:49:54 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <netdb.h>
# include <cerrno>
# include <cstring>
# include <sstream>

# include <sys/types.h>
# include <sys/socket.h>
# include <unistd.h>
# include <fcntl.h>

# include "sharedfd.hpp"

#define GREEN "\x1b[32m"
#define RESET_C "\x1b[0m"
#define RED "\x1b[31m"
#define PRINT(str) std::cout << str << std::endl
#define ERROR(str) std::cerr <<  RED << str << RESET_C << std::endl


void				closeFd(int fd);

//void				readSignalPipe(void);

std::string			handleGaiError(int errcode);
std::string			handleSysError(const std::string& syscall);

std::string			custom_inet_ntoa(struct in_addr addr);
std::string			intToString(int num);


void setnonblocking(const int);




namespace utils {

	template <typename T>
	static std::string to_string(const T& t) {
		std::stringstream stream;
		stream << t;
		return stream.str();
	}

	template <typename T>
	static std::string to_hex(const T& t) {
		std::stringstream stream;
		stream << std::hex << t;
		return stream.str();
	}

	template <typename T>
	static T to_integer(const std::string& str) {
		std::stringstream ss(str);
		T integer;
		if (not (ss >> integer) || not ss.eof())
			throw std::runtime_error("overflow or underflow");
		return integer;
	}

}

#endif
