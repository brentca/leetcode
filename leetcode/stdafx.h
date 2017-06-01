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
		void shuffle() {}
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
}

// TODO: reference additional headers your program requires here
