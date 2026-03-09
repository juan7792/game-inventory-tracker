// video_game_diary.cpp : This file contains the 'main' function. Program execution begins and ends there.
// QLO

#include <iostream>  //standard input/output stream objects
#include <stdio.h>
#include <sqlite3.h> //declaration of sqlite3 functions
#include "queries.h" //header file with declaration of classes and instances
#include <string.h>
#include <string>
#include <conio.h>
#include <cstdlib>

using namespace std;
//methods to avoid unnecessary use of space by class instances
void methodCreateDB(const char*);
void createAllTables(const char*);
void pressEnter();

int main()
{
	//directory address pointer
	const char* dir = "C:\\Users\\Juan\\Desktop\\video_game_diary\\video_games.db";
	
	//create DB and tables
	methodCreateDB(dir);
	createAllTables(dir);

	//menu 1
	char user_input_1; //input from first menu

	SqlQuery sql;

	do 
	{
		cout << "Users menu" << endl;
		cout << "Choose your option and press enter: " << endl;
		cout << "1) Add user" << endl;
		cout << "2) Select existing user" << endl;
		cout << "Press Esc to exit program" << endl;
		cout << endl;

		SqlQuery::userInput1 = _getch();

		switch(SqlQuery::userInput1)
		{
			case '1':
			{
				SqlInsertData sqlInsertData;
				sqlInsertData.insertDataUsersTable(dir);
				break;
			}
			case '2':
			{
				SqlSelectData sqlSelectData;
				sqlSelectData.selectDataUsersTable(dir);
				cout << "Enter user ID: ";
				getline(cin, sqlSelectData.userID);
				cout << endl;
				break;
			}
		}
		if (SqlSelectData::counterSelectData != 0 && SqlQuery::userID.empty() == 0) //access static instance of class
		{
			system("cls");
			break;
		}
		pressEnter();
		system("cls");
	}while(SqlQuery::userInput1 != 27);

	//menu 2
	char user_input_2;

	if (SqlQuery::userInput1 != 27)
	{
		do
		{
			cout << "Video games menu" << endl;
			cout << "Choose your option and press enter: " << endl;
			cout << "1) Add video game to pool" << endl;
			cout << "2) Add owned game" << endl;
			cout << "3) Add played game" << endl;
			cout << "4) Add video game to wanted list" << endl;
			cout << "5) View video games pool" << endl;
			cout << "6) View owned games" << endl;
			cout << "7) View played games" << endl;
			cout << "8) View games from wanted list" << endl;
			cout << "Press Esc to exit program" << endl;
			cout << endl;

			user_input_2 = _getch();

			switch (user_input_2)
			{
				case '1':
				{
					cout << "This is your current video game pool:" << endl;
					cout << endl;

					SqlSelectData sqlSelectData;
					sqlSelectData.selectDataVideoGamesTable(dir, SqlSelectData::userID);

					SqlInsertData sqlInsertData;
					sqlInsertData.insertDataVideoGamesTable(dir, SqlQuery::userID);
					break;
				}
				case '2':
				{
					SqlSelectData sqlSelectData;
					sqlSelectData.selectDataVideoGamesTable(dir, SqlQuery::userID);

					string video_game_id;
					cout << "Enter video game ID: ";
					getline(cin, video_game_id);

					SqlInsertData sqlInsertData;
					sqlInsertData.insertDataOwnedGamesTable(dir, SqlQuery::userID, video_game_id);
					break;
				}
				case '3':
				{
					SqlSelectData sqlSelectData;
					sqlSelectData.selectDataVideoGamesTable(dir, SqlQuery::userID);

					string video_game_id;
					cout << "Enter video game ID: ";
					getline(cin, video_game_id);

					SqlInsertData sqlInsertData;
					sqlInsertData.insertDataPlayedGamesTable(dir, SqlQuery::userID, video_game_id);

					//delete entry in wanted list if exists
					SqlDeleteData sqlDeleteData;
					sqlDeleteData.deleteDataWantToPlayGamesTable(dir, SqlQuery::userID, video_game_id);
					break;
				}
				case '4':
				{
					SqlSelectData sqlSelectData;
					sqlSelectData.selectDataVideoGamesTable(dir, SqlQuery::userID, true);

					string video_game_id;
					cout << "Enter video game ID: ";
					getline(cin, video_game_id);

					SqlInsertData sqlInsertData;
					sqlInsertData.insertDataWantToPlayGamesTable(dir, SqlQuery::userID, video_game_id);
					break;
				}
				case '5':
				{
					cout << "This is your video game pool:" << endl;
					cout << endl;

					SqlSelectData sqlSelectData;
					sqlSelectData.selectDataVideoGamesTable(dir, SqlQuery::userID);
					break;
				}
				case '6':
				{
					cout << "These are your owned video games:" << endl;
					cout << endl;

					SqlSelectData sqlSelectData;
					sqlSelectData.selectDataOwnedGamesTable(dir, SqlQuery::userID);
					break;
				}
				case '7':
				{
					cout << "These are your video games you have played:" << endl;
					cout << endl;

					SqlSelectData sqlSelectData;
					sqlSelectData.selectDataPlayedGamesTable(dir, SqlQuery::userID);
					break;
				}
				case '8':
				{
					cout << "Wanted list:" << endl;
					cout << endl;

					SqlSelectData sqlSelectData;
					sqlSelectData.selectDataWantToPlayGamesTable(dir, SqlQuery::userID);
					break;
				}
			}
			pressEnter();
			system("cls");
		} while (user_input_2 != 27);
	}

	return 0;
}

void methodCreateDB(const char* directory)
{
	SqlQuery sqldb;

	sqldb.createDB(directory);
}
void createAllTables(const char* directory)
{
	SqlCreateTables sqltables;

	sqltables.createUsersTable(directory);
	sqltables.createVideoGamesTable(directory);
	sqltables.createOwnedGamesTable(directory);
	sqltables.createPlayedGamesTable(directory);
	sqltables.createWantToPlayGamesTable(directory);
}
void pressEnter()
{
	cout << "Press Enter to continue" << endl;
	while (_getch() != 13); //loop undefinitely until Enter is pressed
}