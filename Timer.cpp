#include "MTime.h"


Time::Time(){}

Time::Time(size_t current_time) : day(current_time) {}

Time& Time::operator++() {
  ++day;
  return *this;
}

Time Time::operator+(const Time add) { return Time(add.day + day); }
Time Time::operator-(const Time subs) { return Time(day - subs.day); }

Time& Time::operator=(const Time new_time) {
  day = new_time.day;
  return *this;
}

Time& Time::operator+=(const Time add_new) {
  *this = *this + add_new;
  return *this;
}

Time& Time::operator-=(const Time subs_new) {
  *this = *this - subs_new;
  return *this;
}

Time::~Time(){}

bool Time::operator==(const Time eq) { return day == eq.day; }

bool Time::operator!=(const Time neq) { return !(day == neq.day); }

bool Time::operator<(const Time less) { return day < less.day; }

bool Time::operator>(const Time more) { return day > more.day; }

Timer::Timer() : cur_time(0) {}

void Timer::addDay() { ++cur_time; }

Time Timer::getTime() { return cur_time; }

Timer global_timer = Timer();