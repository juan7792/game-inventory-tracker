# Game Inventory & Progress Tracker

A C++ console application for managing a personal video game library and tracking gameplay progress using a relational SQLite database.

The program allows users to create accounts, maintain a personal game library, track owned and played games, and keep a wishlist of games they want to play. All data is stored in a SQLite database and accessed through a simple console interface.

The system architecture is illustrated in:

docs/game-inventory-tracker-architecture.pdf

---

## Architecture

The application is written in C++ and uses the SQLite C API (`sqlite3.h`) for database interaction.

The design separates database operations from application logic through a set of classes responsible for executing SQL queries and managing user interactions.

Main components include:

- Console-based user interface
- Database access layer using SQLite
- Object-oriented design for query execution and menu logic

---

## Database Schema

The system uses five relational tables.

### users
Stores user accounts.

- id (primary key)
- username

### video_games
Stores the main video game library for each user.

- id (primary key)
- user_id (foreign key → users.id)
- game_name
- platform
- genre

### owned_games
Stores games owned by the user.

- user_id
- game_id

### played_games
Stores games that the user has completed or played.

- user_id
- game_id

### want_to_play_games
Stores games the user wants to play in the future.

If a game is added to the owned list, it is automatically removed from the wishlist to maintain data consistency.

---

## Features

- User account creation and selection
- Personal video game library management
- Tracking of owned games
- Tracking of completed/played games
- Wishlist for future games
- Console-based navigation through interactive menus

---

## Technologies

- C++
- SQLite
- Object-Oriented Programming