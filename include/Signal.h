#pragma once
#include <map>
#include <functional>
using namespace std;

template<typename... Args>
class Signal
{
private:
	map<int, const function<void(Args...)>> mSlots;
	int mCurrentId;

public:
	Signal();

	template<typename T>
	int connect(T* member, void(T::*func)(Args...));
	template<typename T>
	int connect(T* member, void(T::*func)(Args...) const);
	int connect(const function<void(Args...)>& slot);

	void disconnect(int id);
	void disconnectAll();

	void emit(Args...) const;
};

#include "Signal.inl"