/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:04:15 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 04:00:52 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODE_HPP
# define MODE_HPP

#include "command.hpp"
#include <cstdlib>

class Channel;

class Mode : public Command {

	public:

		Mode(Connexion&, Message&);
		~Mode(void);

		ret_type execute(void);

		static Command* create(Connexion&, Message&);

	private:

		bool		valid_mode(char c);

		ret_type	handle_user(void);
		ret_type	handle_channel(std::string&, std::string&);

		void		add_mode(const char* mode, Channel&);
		void		remove_mode(const char* mode, Channel&);

		void		split_keys(std::string const& keys);

		vec_str		_keys;

};

#endif
