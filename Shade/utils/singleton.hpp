#pragma once

template <typename T>
class Singleton {
private:
	Singleton(const Singleton& s) = delete;
	Singleton& operator=(const Singleton& s) = delete;

protected:
	Singleton() = default;
	virtual ~Singleton() = default;

public:
	static T& Get() {
		static T instance;
		return instance;
	}
};