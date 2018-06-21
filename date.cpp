#include "stdafx.h"
#include "date.h"
#include <iostream>
#include <cstdlib>
using namespace std;

namespace {
	//存储平年中的某个月1日之前有多少天，为便于getMaxDay函数实现，该数组多出一项
	const int DAY_BEFORE_MONTH[] = { 0, 30, 59, 90, 120, 151, 181, 212, 243, 
		273, 304, 334, 365 };
}

Date::Date(int y, int m, int d)
	:year(y), month(m), day(d) {
	if (day <= 0 || day > getMaxDay()) {
		cout << "Invalid date: ";
		show();
		cout << endl;
		exit(1);
	}

	int years = year - 1;
	totalDays = years * 365 + years / 4 + years / 400 - years / 100
		+ DAY_BEFORE_MONTH[month - 1] + day;
	if (isLeapYear() && month > 2) {   //year这一年为闰年
		totalDays++;
	}
}

int Date::getMaxDay() const {
	if (isLeapYear() && month == 2)
		return 29;
	else
		return DAY_BEFORE_MONTH[month] - DAY_BEFORE_MONTH[month - 1];
}

void Date::show() const {
	cout << getYear() << "-" << getMonth() << "-" << getDay();
}

