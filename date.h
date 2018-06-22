#ifndef _DATE_H_
#define _DATE_H_

class Date {
private:
	int year;
	int month;
	int day;
	int totalDays;  //该日期是从公元元年1月1日开始的第几天

public:
	Date(int y, int m, int d); //y,m,d表示年月日
	int getYear() const { return year; }
	int getMonth() const { return month; }
	int getDay() const { return day; }
	int getMaxDay() const;
	bool isLeapYear() const {   //判断是否为闰年
		return ( (year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
	}
	void show() const;  //输出当前日期
	int operator-(const Date &date) const{    //计算两个日期之间差多少天
		return totalDays - date.totalDays;
	}
};

#endif  //_DATE_H_
