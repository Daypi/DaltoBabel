#include			<fstream>
#include			<iostream>
#include			"AccountManager.h"

AccountManager::AccountManager()
{
}

AccountManager::~AccountManager()
{
}

void				AccountManager::save()
{
	std::fstream	fs("Accounts.sav", std::ios::in | std::ios::out | std::ios::binary);

	if (!fs)
		std::cerr << "Could not open Accounts.sav" << std::endl;
	fs.write(reinterpret_cast<const char *>(this), sizeof(AccountManager));
}

void				AccountManager::load()
{
	std::fstream	fs("Accounts.sav", std::ios::in | std::ios::out | std::ios::binary);

	if (!fs)
		std::cerr << "Could not open Accounts.sav" << std::endl;
	fs.read(reinterpret_cast<char *>(this), sizeof(AccountManager));
}
