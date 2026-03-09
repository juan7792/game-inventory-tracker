#include <iostream>
#include "queries.h"
#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
#include <string>

using namespace std;

/*----- SUPERCLASS SqlQuery -----*/
//Constructor
SqlQuery::SqlQuery()
{
	
}
//Destructor
SqlQuery::~SqlQuery()
{
	
}
//Create DB method - input pointer to variable that stores directory
void SqlQuery::createDB(const char* s)
{
	sqlite3* DB;
	int exit = 0; //declare and initialize instance exit = 0 and will change if there is an error in SQL

	exit = sqlite3_open(s, &DB); //open/create DB using address of directory and pointer DB address

	sqlite3_close(DB); //close DB

}
//Create tables method - input pointer to variable that stores directory and string with query to create table
void SqlQuery::createTables(const char* s, string query)
{
	sqlite3* DB;

	try
	{
		int exit = 0; //declare and initialize instance exit = 0 and will change if there is an error in SQL
		exit = sqlite3_open(s, &DB); //open DB

		char* messageError;
		exit = sqlite3_exec(DB, query.c_str(), NULL, 0, &messageError);
		//if error in query, exit != 0
		if (exit != SQLITE_OK)
		{
			cerr << "Error Create Table" << endl;
			sqlite3_free(messageError);
		}
		sqlite3_close(DB);
	}
	catch (const exception & e)
	{
		cerr << e.what();
	}
}
//Insert data method - input pointer to variable that stores directory and string with query to create table
void SqlQuery::insertData(const char* s, string query)
{
	sqlite3* DB;
	char* messageError;

	int exit = sqlite3_open(s, &DB);

	exit = sqlite3_exec(DB, query.c_str(), NULL, 0, &messageError);

	if (exit != SQLITE_OK)
	{
		cerr << "Error Insert Data: check query" << endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Record created successfully!" << endl;
}
//Select data method - input pointer to variable that stores directory and string with query to create table
void SqlQuery::selectData(const char* s, string query)
{
	sqlite3* DB;

	int exit = sqlite3_open(s, &DB);

	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
}
//Callback function for select methods
int SqlQuery::callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++)
	{
		//column name and value
		cout << azColName[i] << ": " << argv[i] << endl;
	}
	
	cout << endl;

	return 0;
}
//Delete data method
void SqlQuery::deleteData(const char* s, string query)
{
	sqlite3* DB;

	int exit = sqlite3_open(s, &DB);

	sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
}
//Get user ID (static variable)
string SqlQuery::getID()
{
	return userID;
}
//Initialize static variables
string SqlQuery::userID;
char SqlQuery::userInput1;

/*----- SUBCLASS SqlCreateTables -----*/
//Constructor
SqlCreateTables::SqlCreateTables() : SqlQuery() //call constructor of superclass, Maigualida
{

}
//Destructor
SqlCreateTables::~SqlCreateTables()
{

}
//Create "users" table
void SqlCreateTables::createUsersTable(const char* s)
{
	string sql = "CREATE TABLE IF NOT EXISTS users("
		"id INTEGER PRIMARY KEY, "
		"username TEXT NOT NULL); ";

	createTables(s, sql);

}
//Create "video_games" table
void SqlCreateTables::createVideoGamesTable(const char* s)
{
	string sql = "CREATE TABLE IF NOT EXISTS video_games("
		"id INTEGER PRIMARY KEY, "
		"user_id INTEGER, "
		"video_game_name TEXT NOT NULL, "
		"release_date TEXT NOT NULL, "
		"console TEXT NOT NULL, "
		"FOREIGN KEY(user_id) REFERENCES users(id)); ";

	createTables(s, sql);

}
//Create "owned_games" table
void SqlCreateTables::createOwnedGamesTable(const char* s)
{
	string sql = "CREATE TABLE IF NOT EXISTS owned_games("
		"user_id INTEGER, "
		"video_game_id INTEGER, "
		"video_game_name TEXT, "  //JOIN
		"observations TEXT NOT NULL); ";

	createTables(s, sql);

}
//Create "played_games" table
void SqlCreateTables::createPlayedGamesTable(const char* s)
{
	string sql = "CREATE TABLE IF NOT EXISTS played_games("
		"user_id INTEGER, "
		"video_game_id INTEGER, "
		"video_game_name TEXT, "  //JOIN
		"end_date TEXT NOT NULL, "
		"rating INTEGER, "
		"observations TEXT NOT NULL); ";

	createTables(s, sql);

}
//Create "want_to_play_games" table
void SqlCreateTables::createWantToPlayGamesTable(const char* s)
{
	string sql = "CREATE TABLE IF NOT EXISTS want_to_play_games("
		"user_id INTEGER, "
		"video_game_id INTEGER, "
		"video_game_name TEXT, "  //JOIN
		"rating_interest INTEGER, "
		"observations TEXT NOT NULL); ";

	createTables(s, sql);

}
/*----- SUBCLASS SqlInsertData -----*/
//Constructor
SqlInsertData::SqlInsertData() : SqlQuery() //call constructor of superclass, Maigualida
{

}
//Destructor
SqlInsertData::~SqlInsertData()
{

}
//Insert data into "users" table
void SqlInsertData::insertDataUsersTable(const char* s)
{
	string sql = "INSERT INTO users(username) VALUES('%s');";
	
	//variable to be added into query
	string username; cout << "Enter your username: "; getline(cin, username);

	char sqlStr[1024]; //change into something according to the real memory needed for the query

	sprintf_s(sqlStr, sql.c_str(), username.c_str());

	insertData(s, sqlStr);
}
//Insert data into "video_games" table
void SqlInsertData::insertDataVideoGamesTable(const char* s, string user_id)
{
	string sql = "INSERT INTO video_games(user_id, video_game_name, release_date, console) VALUES('%s', '%s', '%s', '%s');";

	//variable to be added into query
	string video_game_name; cout << "Enter the name of the video game you want to add to your pool: "; getline(cin, video_game_name);
	string release_date; cout << "Enter the release date of the video game (dd-mm-yyyy): "; getline(cin, release_date);
	string console; cout << "Enter the console where the video game is available: "; getline(cin, console);

	char sqlStr[1024]; //change into something according to the real memory needed for the query

	sprintf_s(sqlStr, sql.c_str(), user_id.c_str(), video_game_name.c_str(), release_date.c_str(), console.c_str());

	insertData(s, sqlStr);
}
//Insert data into "owned_games" table
void SqlInsertData::insertDataOwnedGamesTable(const char* s, string user_id, string video_game_id)
{
	string sql = "INSERT INTO owned_games(user_id, video_game_id, video_game_name, observations) VALUES('%s', '%s', '%s', '%s');";

	//variable to be added into query
	string video_game_name; cout << "Enter the video game name from the list: "; getline(cin, video_game_name);
	string observations; cout << "Enter observations: "; getline(cin, observations);

	char sqlStr[1024]; //change into something according to the real memory needed for the query

	sprintf_s(sqlStr, sql.c_str(), user_id.c_str(), video_game_id.c_str(), video_game_name.c_str(), observations.c_str());

	insertData(s, sqlStr);
}
//Insert data into "played_games" table
void SqlInsertData::insertDataPlayedGamesTable(const char* s, string user_id, string video_game_id)
{
	string sql = "INSERT INTO played_games(user_id, video_game_id, video_game_name, end_date, rating, observations) VALUES('%s', '%s', '%s', '%s', '%s', '%s');";

	//variable to be added into query
	string video_game_name; cout << "Enter the video game name from the list: "; getline(cin, video_game_name);
	string end_date; cout << "When did you finish the game (dd-mm-yyyy)? "; getline(cin, end_date);
	string rating; cout << "What is your rating (1-10)? "; getline(cin, rating);
	string observations; cout << "Enter observations: "; getline(cin, observations);

	char sqlStr[1024]; //change into something according to the real memory needed for the query

	sprintf_s(sqlStr, sql.c_str(), user_id.c_str(), video_game_id.c_str(), video_game_name.c_str(), end_date.c_str(), rating.c_str(), observations.c_str());

	insertData(s, sqlStr);
}
//Insert data into "want_to_play_games" table
void SqlInsertData::insertDataWantToPlayGamesTable(const char* s, string user_id, string video_game_id)
{
	string sql = "INSERT INTO want_to_play_games(user_id, video_game_id, video_game_name, rating_interest, observations) VALUES('%s', '%s', '%s', '%s', '%s');";

	//variable to be added into query
	string video_game_name; cout << "Enter the video game name from the list: "; getline(cin, video_game_name);
	string rating_interest; cout << "Rate your interest (1-10): "; getline(cin, rating_interest);
	string observations; cout << "Enter observations: "; getline(cin, observations);

	char sqlStr[1024]; //change into something according to the real memory needed for the query

	sprintf_s(sqlStr, sql.c_str(), user_id.c_str(), video_game_id.c_str(), video_game_name.c_str(), rating_interest.c_str(), observations.c_str());

	insertData(s, sqlStr);
}
/*----- SUBCLASS SqlSelectData -----*/
//Counter to break loop
int SqlSelectData::counterSelectData = 0;
//Constructor
SqlSelectData::SqlSelectData() : SqlQuery() //call constructor of superclass, Maigualida
{
	counterSelectData++;
}
//Destructor
SqlSelectData::~SqlSelectData()
{

}
//Select data from "users" table
void SqlSelectData::selectDataUsersTable(const char* s)
{
	string sql = "SELECT * FROM users;";

	selectData(s, sql);
}
//Select data from "video_games" table
void SqlSelectData::selectDataVideoGamesTable(const char* s, string user_id)
{
	string sql = "SELECT id, video_game_name, release_date, console FROM video_games WHERE user_id='%s';";

	char sqlStr[1024];

	sprintf_s(sqlStr, sql.c_str(), user_id.c_str());

	selectData(s, sqlStr);
}
//Select all data from "video_games" table
void SqlSelectData::selectDataVideoGamesTable(const char* s, string user_id, bool k)
{
	string sql = "SELECT * FROM video_games WHERE user_id='%s';"; 
	
	char sqlStr[1024];

	sprintf_s(sqlStr, sql.c_str(), user_id.c_str());

	selectData(s, sqlStr);
}
//Select data from "owned_games" table
void SqlSelectData::selectDataOwnedGamesTable(const char* s, string user_id)
{
	string sql = "SELECT video_game_name, observations FROM owned_games WHERE user_id='%s';";

	char sqlStr[1024];

	sprintf_s(sqlStr, sql.c_str(), user_id.c_str());

	selectData(s, sqlStr);
}
//Select data from "played_games" table
void SqlSelectData::selectDataPlayedGamesTable(const char* s, string user_id)
{
	string sql = "SELECT video_game_name, end_date, rating, observations FROM played_games WHERE user_id='%s';";

	char sqlStr[1024];

	sprintf_s(sqlStr, sql.c_str(), user_id.c_str());

	selectData(s, sqlStr);
}
//Select data from "want_to_play_games" table
void SqlSelectData::selectDataWantToPlayGamesTable(const char* s, string user_id)
{
	string sql = "SELECT video_game_name, rating_interest, observations FROM want_to_play_games WHERE user_id='%s';";

	char sqlStr[1024];

	sprintf_s(sqlStr, sql.c_str(), user_id.c_str());

	selectData(s, sqlStr);
}
/*----- SUBCLASS SqlDeleteData -----*/
//Constructor
SqlDeleteData::SqlDeleteData() : SqlQuery() //call constructor of superclass, Maigualida
{
	
}
//Destructor
SqlDeleteData::~SqlDeleteData()
{

}
//Delete data from "want_to_play_games" table
void SqlDeleteData::deleteDataWantToPlayGamesTable(const char* s, string user_id, string video_game_id)
{
	string sql = "DELETE FROM want_to_play_games WHERE user_id = %s AND video_game_id = %s;";

	char sqlStr[1024]; //change into something according to the real memory needed for the query

	sprintf_s(sqlStr, sql.c_str(), user_id.c_str(), video_game_id.c_str());

	deleteData(s, sqlStr);
}