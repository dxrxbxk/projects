#include "command_factory.hpp"


CommandFactory::CommandFactory(void)
: cmap(init()) {}


CommandFactory::~CommandFactory(void) {}

CommandFactory::map_t CommandFactory::init(void) {
	map_t cmap;

	cmap["CAP"]     = &Cap::create;
	cmap["JOIN"]    = &Join::create;
	cmap["NICK"]    = &Nick::create;
	cmap["USER"]    = &User::create;
	cmap["MODE"]    = &Mode::create;
	cmap["PING"]    = &Ping::create;
	cmap["PRIVMSG"] = &Privmsg::create;
	cmap["PASS"]    = &Pass::create;
	cmap["QUIT"]    = &Quit::create;
	cmap["TOPIC"]   = &Topic::create;
	cmap["KICK"]    = &Kick::create;
	cmap["INVITE"]  = &Invite::create;
	cmap["PART"]    = &Part::create;
	// add more commands here...

	return cmap;
}


CommandFactory& CommandFactory::shared(void) {
	static CommandFactory instance;
	return instance;
}


Command* CommandFactory::create(Connexion& conn, Message& msg) {
	CommandFactory& factory = shared();

	map_t::const_iterator it = factory.cmap.find(msg.command());
	if (it == factory.cmap.end())
		return NULL;
	return it->second(conn, msg);
}
