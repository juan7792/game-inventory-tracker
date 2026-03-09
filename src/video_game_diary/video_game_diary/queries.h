#ifndef QUERIES_H_INCLUDED
#define QUERIES_H_INCLUDED

using namespace std;
//Superclass with SQL queries
class SqlQuery
{
	public:
		SqlQuery();  //Constructor
		~SqlQuery(); //Destructor
		void createDB(const char*);
		void createTables(const char*, string);
		void insertData(const char*, string);
		void selectData(const char*, string);
		/* argc: holds the number of results, argv: holds each value in array, azColName: holds each column returned in array */
		static int callback(void* NotUsed, int argc, char** argv, char** azColName);
		static string userID; //ID that will be selected in first menu and will then be used in second menu
		static string getID();
		static char userInput1; //User input in first menu
		void deleteData(const char*, string); //Delete data from tables
};
//Subclass to create necessary tables
class SqlCreateTables : public SqlQuery
{
	public:
		SqlCreateTables(); //Constructor
		~SqlCreateTables(); //Destructor
		/*----- TABLES USING METHOD OF SUPERCLASS -----*/
		//Tables for entities
		void createUsersTable(const char*);
		void createVideoGamesTable(const char*);
		//Tables for actions (relational)
		void createOwnedGamesTable(const char*);
		void createPlayedGamesTable(const char*);
		void createWantToPlayGamesTable(const char*);
};
//Subclass to insert data into tables
class SqlInsertData : public SqlQuery
{
	public:
		SqlInsertData(); //Constructor
		~SqlInsertData(); //Destructor
		/*----- TABLES USING METHOD OF SUPERCLASS -----*/
		//Tables for entities
		void insertDataUsersTable(const char*);
		void insertDataVideoGamesTable(const char*, string);
		//Tables for actions (relational)
		void insertDataOwnedGamesTable(const char*, string, string);
		void insertDataPlayedGamesTable(const char*, string, string);
		void insertDataWantToPlayGamesTable(const char*, string, string);
};
//Subclass to retrieve data from tables
class SqlSelectData : public SqlQuery
{
public:
	SqlSelectData(); //Constructor
	~SqlSelectData(); //Destructor
	/*----- TABLES USING METHOD OF SUPERCLASS -----*/
	//Tables for entities
	void selectDataUsersTable(const char*); //users
	void selectDataVideoGamesTable(const char*, string, bool);
	void selectDataVideoGamesTable(const char*, string); //video games
	//Tables for actions (relational)
	void selectDataOwnedGamesTable(const char*, string);
	void selectDataPlayedGamesTable(const char*, string);
	void selectDataWantToPlayGamesTable(const char*, string);
	static int counterSelectData; //used to break first loop
};
//Subclass to delete data from tables
class SqlDeleteData : public SqlQuery
{
	public:
		SqlDeleteData();
		~SqlDeleteData();
		void deleteDataWantToPlayGamesTable(const char*, string, string);
};
#endif // QUERIES_H_INCLUDED