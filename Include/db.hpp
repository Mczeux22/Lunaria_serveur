/**
 * @ Author: Lopapon
 * @ Create Time: 2026-02-25 23:12:30
 * @ Modified by: Lopapon
 * @ Modified time: 2026-02-25 23:42:37
 * @ Description:
 */

#ifndef DB_HPP
#define DB_HPP

#include <iostream>
#include <string>
#include <cstdint>
#include <libpq-fe.h>

enum class LoginResult
{
	OK,
	WRONG_PASSWORD,
	ACCOUNT_NOT_FOUND,
	DB_ERROR
};

class	Database
{
public:
	Database(const std::string& connection_string);
	~Database();

	bool		is_connected() const;

	LoginResult	login(const std::string& username,
				const std::string& password,
				uint32_t& out_account_id);

	bool		create_account(const std::string& username,
					const std::string& password);

private:
	std::string	hash_password(const std::string& password);

	PGconn*	conn_;
};

extern Database* g_db;

#endif