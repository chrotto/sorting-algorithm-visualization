#pragma once
#include "Signal.h"

template<typename... Args>
Signal<Args...>::Signal() : mCurrentId(0)
{
	// Nothing to do
}

template<typename... Args>
template<typename T>
int Signal<Args...>::connect(T* member, void(T::*func)(Args...))
{
	return connect([=](Args... args) {(member->*func)(args...); });
}

template<typename... Args>
template<typename T>
int Signal<Args...>::connect(T* member, void(T::*func)(Args...) const)
{
	return connect([=](Args... args) {(member->*func)(args...); });
}

template<typename... Args>
int Signal<Args...>::connect(const function<void(Args...)>& slot)
{
	mSlots.insert(make_pair(++mCurrentId, slot));
	return mCurrentId;
}

template<typename... Args>
void Signal<Args...>::disconnect(int id)
{
	mSlots.erase(id);
}

template<typename... Args>
void Signal<Args...>::disconnectAll()
{
	mSlots.clear();
}

template<typename... Args>
void Signal<Args...>::emit(Args... args) const
{
	for (auto it : mSlots)
		it.second(args...);
}