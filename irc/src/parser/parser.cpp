/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 01:09:59 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 22:09:33 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"
#include "utils.hpp"


const char* state_debug[] = {
	"DEFAULT",
	"PREFIX",
	"COMMAND",
	"PARAMS",
	"MIDDLE",
	"TRAILING",
	"DCC",
	"COMMAND_END",
	"ERROR",
	"END"
};

const char* chartype_debug[] = {
	"COLON",
	"LF",
	"CR",
	"SP",
	"OTHER",
	"CTL",
	"SOH",
	"NUL",
};

const char* action_debug[] = {
	"SKIP",
	"INCREMENT",
	"RESET",
	"RESET_AND_INCR",
	"ADD_PREFIX",
	"ADD_COMMAND",
	"ADD_MIDDLE",
	"ADD_TRAILING",
	"ADD_DCC_PARAM",
	"P_ERROR"
};

void 	Parser::debug(void) {
	PRINT("current char: " + std::string(1, *msg) + " chartype: " + chartype_debug[c_table[static_cast<uint8_t>(*msg)]] + " state: " + state_debug[tr.state] + " action: " + action_debug[tr.action]);
}

void	Parser::increment(void) { ++i; }

void	Parser::reset(void) { i = 0; }

void	Parser::addPrefix(void) {
	std::string	prefix(msg - i, i);
	i = 0;
	request.addPrefix(prefix);
}

void	Parser::addCommand(void) {
	std::string	command(msg - i, i);
	i = 0;
	request.addCommand(command);
}

void	Parser::addMiddle(void) {
	std::string	middle(msg - i, i);
	i = 0;
	request.addMiddle(middle);
}

void	Parser::addTrailing(void) {
	std::string	trailing(msg - i, i);
	i = 0;
	request.addTrailing(trailing);
}

void	Parser::addDccParam(void) {
	std::string	param(msg - i, i);
	i = 0;
	request.addDccParam(param);
}

void	Parser::skip(void) {
}

void	Parser::pError(void) {
	throw std::runtime_error(" :Parsing error");
}

void debug_raw(const char* msg) {

	std::cout << "\n\n\n\x1b[32mRAW: \x1b[0m";
	while (*msg) {
		if (*msg < 32) {
			if (*msg == '\r')
				std::cout << " CR ";
			else if (*msg == '\n')
				std::cout << " LF ";
			else
				std::cout << std::hex << static_cast<uint8_t>(*msg);
		}
		else {
			std::cout << *msg;
		}
		++msg;
	}
	std::cout << std::endl<< std::endl;
}


void	Parser::run(void) {

	// Logger::log("parsing request: " + std::string(msg));

	while (tr.state != ERROR && tr.state != END) {
	//	 debug();
		e_chartype type = c_table[static_cast<uint8_t>(*msg)];
		tr = t_table[tr.state][type];
		(this->*a_table[tr.action])();
		++msg;
	}
}

Parser::action_p	Parser::a_table[Parser::A_SIZE] = {
	&Parser::skip,
	&Parser::increment,
	&Parser::reset,
	&Parser::addPrefix,
	&Parser::addCommand,
	&Parser::addMiddle,
	&Parser::addTrailing,
	&Parser::addDccParam,
	&Parser::pError,
};

Parser::transition		Parser::t_table[Parser::S_SIZE][Parser::CT_SIZE] = {
	/* DEFAULT */
	{
		{ PREFIX, INCREMENT }, /* COLON */
		{ ERROR, P_ERROR }, /* LF */
		{ COMMAND_END, INCREMENT }, /* CR */
		{ ERROR, P_ERROR }, /* SP */
		{ COMMAND, INCREMENT }, /* OTHER */
		{ ERROR, P_ERROR }, /* CTL */
		{ ERROR, P_ERROR }, /* SOH */
		{ ERROR, P_ERROR }, /* NUL */

	},
	/* PREFIX */
	{
		{ ERROR, P_ERROR }, /* COLON */
		{ ERROR, P_ERROR }, /* LF */
		{ ERROR,  P_ERROR }, /* CR */
		{ COMMAND, ADD_PREFIX }, /* SP */
		{ PREFIX, INCREMENT}, /* OTHER */
		{ ERROR, P_ERROR }, /* CTL */
		{ ERROR, P_ERROR }, /* SOH */
		{ ERROR, P_ERROR }, /* NUL */

	},
	/* COMMAND */
	{
		{ ERROR, P_ERROR }, /* COLON */
		{ ERROR, P_ERROR }, /* LF */
		{ COMMAND_END, ADD_COMMAND }, /* CR */
		{ PARAMS, ADD_COMMAND }, /* SP */
		{ COMMAND, INCREMENT }, /* OTHER */
		{ ERROR, P_ERROR }, /* CTL */
		{ ERROR, P_ERROR }, /* SOH */
		{ ERROR, P_ERROR }, /* NUL */

	},
	/* PARAMS */
	{
		{ TRAILING, INCREMENT }, /* COLON */
		{ ERROR, P_ERROR }, /* LF */
		{ ERROR, P_ERROR }, /* CR */
		{ ERROR, P_ERROR }, /* SP */
		{ MIDDLE, INCREMENT }, /* OTHER */
		{ ERROR, P_ERROR }, /* CTL */
		{ ERROR, P_ERROR }, /* SOH */
		{ ERROR, P_ERROR }, /* NUL */

	},
	/* MIDDLE */
	{
		{ MIDDLE, INCREMENT }, /* COLON */
		{ ERROR, P_ERROR }, /* LF */
		{ COMMAND_END, ADD_MIDDLE }, /* CR */
		{ PARAMS, ADD_MIDDLE }, /* SP */
		{ MIDDLE, INCREMENT }, /* OTHER */
		{ ERROR, P_ERROR }, /* CTL */
		{ ERROR, P_ERROR }, /* SOH */
		{ ERROR, P_ERROR }, /* NUL */

	},
	/* TRAILING */
	{
		{ TRAILING, INCREMENT }, /* COLON */
		{ ERROR, P_ERROR }, /* LF */
		{ COMMAND_END, ADD_TRAILING }, /* CR */
		{ TRAILING, INCREMENT }, /* SP */
		{ TRAILING, INCREMENT }, /* OTHER */
		{ ERROR, P_ERROR }, /* CTL */
		{ DCC, RESET }, /* SOH */
		{ ERROR, P_ERROR }, /* NUL */

	},
	/* DCC */
	{
		{ DCC, INCREMENT }, /* COLON */
		{ ERROR, P_ERROR }, /* LF */
		{ ERROR, P_ERROR}, /* CR */
		{ DCC, ADD_DCC_PARAM }, /* SP */
		{ DCC, INCREMENT }, /* OTHER */
		{ ERROR, P_ERROR }, /* CTL */
		{ TRAILING, ADD_DCC_PARAM }, /* SOH */
		{ ERROR, P_ERROR }, /* NUL */
	},
	/* COMMAND_END */
	{
		{ ERROR, P_ERROR }, /* COLON */
		{ END, SKIP }, /* LF */
		{ ERROR, P_ERROR }, /* CR */
		{ ERROR, P_ERROR }, /* SP */
		{ ERROR, P_ERROR }, /* OTHER */
		{ ERROR, P_ERROR }, /* CTL */
		{ ERROR, P_ERROR }, /* SOH */
		{ ERROR, P_ERROR }, /* NUL */
	},
};

Message		Parser::parse(const std::string& ref) {
	Message	request;
	Parser(ref, request).run();
	return request;
}

Parser::Parser(const std::string& ref, Message& req)
: msg(ref.c_str()), i(0), request(req) {
	tr.state = DEFAULT;
	tr.action = SKIP;
}

const Parser::e_chartype	Parser::c_table[256] = {
	//0-31
    NUL, SOH, CTL, CTL, CTL, CTL, CTL, CTL,
    CTL, CTL, LF, CTL, CTL, CR, CTL, CTL,
    CTL, CTL, CTL, CTL, CTL, CTL, CTL, CTL,
    CTL, CTL, CTL, CTL, CTL, CTL, CTL, CTL,
	//32-63
    SP, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
    OTHER, OTHER, COLON, OTHER, OTHER, OTHER, OTHER, OTHER,
	//64-95
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
	//96-127
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, CTL,
	//128-159
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
	//160-191
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
	//192-223
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
	// 224-255
	OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
	OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
	OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,
	OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER
};
