#include <iostream>
#include <string>
#include <map>


int	main() {
	std::string	nickname = "Diego";
	std::map<std::string*, int>	people;

	people[&nickname] = 1;
	std::cout << "nickname: " << nickname << "age: " << people[&nickname] << std::endl;

	nickname = "Diego2";
	std::cout << "nickname: " << nickname << "age: " << people[&nickname] << std::endl;

	return 0;
}
