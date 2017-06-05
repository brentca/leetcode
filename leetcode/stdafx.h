// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;
namespace OOD{
	/*respondent, manager, and director begin*/
	class CallHandler;
	class Call;

	class Employee{
	public:
		bool free;
		int rank;
		CallHandler* callhandle;
		Employee(int rank, CallHandler* handle) : free(true), rank(rank), callhandle(handle){}

		void ReceiveCall(Call* incall);

		void HandledCall(Call* incall);

		void NotHandledCall(Call* incall);
	};

	class Fresher : public Employee{
	public:
		Fresher(CallHandler* handle) : Employee(0, handle){}
	};

	class Leader : public Employee{
	public:
		Leader(CallHandler* handle) : Employee(1, handle){}
	};

	class Manager : public Employee{
	public:
		Manager(CallHandler* handle) : Employee(2, handle){}
	};

	class Call{
	public:
		int rank;
		int time;
	};

	class CallHandler {
	public:
		const int LEVEL = 3;
		const int FRESHERS = 5;
		std::vector<vector<Employee*>> emplevels;
		queue<Call*> callque;

		CallHandler(){
			emplevels.resize(LEVEL);
		}

		Employee* getCallHandler(Call* incall);

		void getNextCall(Employee* emp) {}
		void dispatchCall(Call* incall);
	};
	/*respondent, manager, and director end*/

	
	/*deck card begin*/
	enum Suit {
		CLUB = 0,
		SPRADE,
		DIAMOND,
		HEART
	};

	class Card {
	public:
		Card(int value, Suit suit) : facevalue(value), suit(suit) {}

		virtual int getValue() { return facevalue; }
		Suit getSuit() { return suit; }
		bool isAvailable() { return available; }
		void setAvailable(bool bAvail) { available = bAvail;}

	private:
		bool available;

	protected :
		int facevalue;
		Suit suit;
	};

	class Deck {
	public:
		Deck() { dealidx = 0; }
		void shuffle() {
			int len = cards.size();
			for (int i = 0; i < len; ++i) {
				int j = rand() % (len - i) + i;
				swap(cards[j], cards[i]);
			}
		}

		int remainCards() { return cards.size() - dealidx; }
		void setDeckCards(vector<Card>& deckcards) {
			cards.clear();
			for (auto it : deckcards)
				cards.push_back(it);
		}

		Card dealCard(){
			++dealidx;
			Card ret = cards.back();
			cards.pop_back();
			return ret;
		}
	private:
		vector<Card> cards;
		int dealidx;
	};

	class Hand{
	public:
		int getsScore() {
			int ret = 0;
			for (auto it : cards)
				ret += it.getValue();
			return ret;
		}

		void addCard(Card& card) {
			cards.push_back(card);
		}

	private:
		vector<Card> cards;
	};

	class BlackJackCard : public Card {
	public:
		BlackJackCard(int value, Suit suit) : Card(value, suit){}
		bool isAce() { return  facevalue == 1; }
		int getValue() {
			if (isAce())
				return 1;
			else if (facevalue > 10)
				return 10;
			else
				return facevalue;
		}

		int minValue() {
			if (isAce())
				return 1;

			return getValue();
		}

		int maxValue() {
			if (isAce())
				return 11;

			return getValue();
		}

		bool isFaceCard() {
			return facevalue > 10 && facevalue < 14;
		}
	};

	class BlackJackhand {
	public:
		int getScore() {
			vector<int> scores = possibleScores();

			int maxUnder = INT_MIN;
			int minOver = INT_MAX;
			for (auto it : scores) {
				if (it > 21 && it < minOver)
					minOver = it;
				else if (it <= 21 && it > maxUnder)
					maxUnder = it;
			}

			return maxUnder == INT_MIN ? minOver : maxUnder;
		}

		bool isButed() { return getScore() > 21; }
		bool is21() { return getScore() == 21; }

	private:
		vector<int> possibleScores() { vector<int>ret; return ret; }
	};
	/*deck card end*/

	/*jukebox begin*/
	class User {
	public:
		User(){}
		User(string name, long id) : uname(name), uid(id){}
		User(const User& other) { uname = other.uname; uid = other.uid; }
		User& operator= (const User& other) { uname = other.uname; uid = other.uid; }

		void setName(string strName) { uname = strName; }
		void setId(long id) { uid = id; }

		string getName() { return uname; }
		long getId() { return uid; }

	private:
		string uname;
		long uid;
	};

	class CD {
	public:
		CD(){}
		/* data for id, artist, songs, etc */
	};

	class Song {
	public:
		Song(){}
		/* data for id, CD (could be null), title, length, etc */
	};

	class Playlist {
	public:
		Playlist() {}
		void addSong(Song song) { songs.push(song); }
		Song getSong() { return songs.front(); }
		void remvSong() { songs.pop(); }

	private:
		queue<Song> songs;
	};

	class CDPlayer {
	public:
		CDPlayer(){}
		CDPlayer(CD& cd, Playlist& list) : cd(cd), playlist(list) {}

		void playSong() {}

		Playlist getPlaylist() { return playlist; }
		void setPlaylist(Playlist& other) { playlist = other; }

		CD getCD() { return cd; }
		void setCD(CD& other) { cd = other; }

	private:
		CD cd;
		Playlist playlist;
	};

	class SongSelector {
	public:
		SongSelector(){}
		Song getCurrentSong() { return song; }

	private:
		Song song;
	};

	class JukeBox {
	public:
		JukeBox(CDPlayer& cdPlayer, User& user,
			vector<CD>& cdCollection, SongSelector& ts) {}
		Song getCurrentSong() { return ts.getCurrentSong(); }
		void setUser(User& other) { user = other; }

	private:
		CDPlayer cdPlayer;
		User user;
		vector<CD> cdCollection;
		SongSelector ts;
	};
	/*jukebox end*/

	/*online book reader begin*/
	class Reader {
	public:
		Reader(int id, string detail, int type) : uerid(id), details(detail), type(type){}
		int uerid;
		string details;
		int type;
		
		void renewMembership() {}
		// set/get userid, type
	};

	class Book {
	public:
		Book() {}
		string details;
		int id;
		// set/get userid, type
	};

	class Display {
	public:
		void displayUser(Reader* user) { activeuser = user; refreshUsername(); }
		void displayBook(Book* book) { 
			activebook = book;
			currpage = 0;
			refreshTitle(); 
			refreshDetails();
			refreshPage();
		}

		void nextPage() { ++currpage; refreshPage(); }
		void previousPage() { --currpage; refreshPage(); }

	private:
		Book* activebook;
		Reader* activeuser;
		int currpage;

		void refreshUsername() { /* updates username display */ }
		void refreshTitle() { /* updates title display */ }
		void refreshDetails() { /* updates details display */ }
		void refreshPage() { /* updated page display */ }
	};

	class UserManage {
	public:
		Reader* addUser(int id, string details, int accountType) {
			if (users.count(id))
				return users[id];

			Reader* newuser = new Reader(id, details, accountType);
			users[id] = newuser;
			return newuser;
		}

		void removeUser(int id) {
			if (0 == users.count(id))
				return;

			Reader* tmp = users[id];
			users.erase(id);
			delete tmp;
		}

		Reader* getUser(int id) {
			Reader* ret = NULL;

			if (users.count(id))
				ret = users[id];
			return ret;
		}

	private:
		unordered_map<int, Reader*> users;
	};

	class Library {
	public:
		//add, remove book
	private:
		unordered_map<int, Book*> books;
	};

	class OnlineReaderSystem {
	public:
		OnlineReaderSystem() {}
		Library* getLibrary() { return library; }
		Display* getDisplay() { return display; }
		UserManage* getUserManage() { return userManager; }

		Book* getActiveBook() { return activeBook; }
		void setActiveBook(Book* book) {
			activeBook = book;
			display->displayBook(activeBook);
		}

		void setActiveUser(Reader* user) {
			activeUser = user;
			display->displayUser(activeUser);
		}
	private:
		Library* library;
		UserManage* userManager;
		Display* display;
		Book* activeBook;
		Reader* activeUser;
	};

	/*online book reader end*/


	/*file system begin*/
	class Directory;
	class Entry {
	public:
		virtual int getSize() { return 0; };

		string getFullPath();

	protected:
		Directory* parent;
		long created;
		long lastUpdated;
		long lastAccessed;
		string name;
	};

	class File: public Entry {
	public:
		int getSize() { return size; }
		string getContents() { return content; }
		void setContents(string c) { content = c; }

	private:
		int size;
		string content;
	};


	class Directory : public Entry {
	public:
		int getSize();

		string getPath() { return path; }
	protected:
		vector<Entry> getContents() { return contents; }
		string path;
		vector<Entry> contents;
	};
	/*file system end*/

	/*hash table begin*/
	template <class K, class V> class Cell {
	private:
		K key;
		V value;

	public:
		Cell(K k, V v) : key(k), value(v) {}
		K getKey() { return key; }
		V getValue() { return value; }

		bool equivalent(K k) { return key == k; }
		bool equivalent(Cell& other) { return equivalent(other.getKey()); }
	};

	template <class K, class V> class MyHashMap{
	public:
		MyHashMap() {
			items.resize(MAX_SIZE);
		}

		int hashCodeofKey(K key){
			return key.hashCode() % items.size();
		}

		void put(K key, V value) {
			bool found = false;

			int x = hashCodeofKey(key);

			for (auto it : items[x])
				if (it.equivalent(key)) {
					items[x].erase(it);
					break;
				}

			Cell cell = new Cell(key, value);
			items[x].insert(cell);
		}

		V get(K key) {
			V value;
			int x = hashCodeofKey(key);
			for (auto it : items[x])
				if (it.equivalent(key)) {
					value = it.getValue();
					break;
				}

			return value;
		}

	private:
		const int MAX_SIZE = 10;
		vector<list<Cell<K, V>*>> items;
	};
	/*hash table end*/



	/*online book reader begin*/
	/*jukebox end*/
}

// TODO: reference additional headers your program requires here
