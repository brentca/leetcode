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
}

// TODO: reference additional headers your program requires here
