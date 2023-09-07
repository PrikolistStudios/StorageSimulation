#pragma once
#include <random>

class Time {
 private:
  size_t day;

 public:
  Time();
  Time(size_t current_time);

  Time& operator++();
  Time operator+(const Time add);
  Time operator-(const Time subs);

  Time& operator=(const Time new_time);
  Time& operator+=(const Time add_new);
  Time& operator-=(const Time sub_news);

  bool operator==(const Time eq);
  bool operator!=(const Time neq);
  bool operator<(const Time less);
  bool operator>(const Time more);

 // operator size_t() const { return day; }
  size_t get_day() { return day; }

  ~Time();
};

class Timer {
 private:
  Time cur_time;

 public:
  Timer();

  void addDay();
  Time getTime();

};

extern Timer global_timer;