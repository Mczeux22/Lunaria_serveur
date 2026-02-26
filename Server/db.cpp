/**
 * @ Author: Lopapon
 * @ Create Time: 2026-02-25 23:13:52
 * @ Modified by: Your name
 * @ Modified time: 2026-02-26 20:17:48
 * @ Description:
 */

#include "db.hpp"

// Instance globale
Database*	g_db = nullptr;

Database::Database(const std::string& connection_string)
{
	conn_ = PQconnectdb(connection_string.c_str());

	if (PQstatus(conn_) != CONNECTION_OK)
	{
		std::cerr << "[DB] Erreur de connexion : "
			<< PQerrorMessage(conn_) << std::endl;
		PQfinish(conn_);
		conn_ = nullptr;
	}
	else
	{
		std::cout << "[DB] Connecté à PostgreSQL." << std::endl;
	}
}

Database::~Database()
{
	if (conn_)
		PQfinish(conn_);
}

bool	Database::is_connected() const
{
	return conn_ != nullptr && PQstatus(conn_) == CONNECTION_OK;
}

std::string	Database::hash_password(const std::string& password)
{
	return password;
}

LoginResult	Database::login(const std::string& username,
				const std::string& password,
				uint32_t& out_account_id)
{
	if (!is_connected())
		return LoginResult::DB_ERROR;

	const char*	params[2] = {
		username.c_str(),
		password.c_str()
	};

	PGresult*	res = PQexecParams(conn_,
		"SELECT id FROM accounts "
		"WHERE username = $1 "
		"AND password_hash = crypt($2, password_hash)",
		2,		// Nombre de paramètres
		nullptr,	// Types (nullptr = auto)
		params,
		nullptr,	// Tailles (nullptr = strings)
		nullptr,	// Formats (nullptr = texte)
		0		// Résultat en texte
	);

	if (PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		std::cerr << "[DB] Erreur login : "
			<< PQerrorMessage(conn_) << std::endl;
		PQclear(res);
		return LoginResult::DB_ERROR;
	}

	if (PQntuples(res) == 0)
	{
		PQclear(res);
		return LoginResult::WRONG_PASSWORD;
	}

	out_account_id = std::stoul(PQgetvalue(res, 0, 0));
	PQclear(res);
	return LoginResult::OK;
}

bool	Database::create_account(const std::string& username,
				const std::string& password)
{
	if (!is_connected())
		return false;

	const char*	params[2] = {
		username.c_str(),
		password.c_str()
	};
	PGresult*	res = PQexecParams(conn_,
		"INSERT INTO accounts (username, password_hash) "
		"VALUES ($1, crypt($2, gen_salt('bf')))",
		2,
		nullptr,
		params,
		nullptr,
		nullptr,
		0
	);

	bool	ok = PQresultStatus(res) == PGRES_COMMAND_OK;
	if (!ok)
		std::cerr << "[DB] Erreur create_account : "
			<< PQerrorMessage(conn_) << std::endl;

	PQclear(res);
	return ok;
}