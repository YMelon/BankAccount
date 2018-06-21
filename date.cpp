#include "stdafx.h"
#include "date.h"
#include <iostream>
#include <cstdlib>
using namespace std;

namespace {
	//�洢ƽ���е�ĳ����1��֮ǰ�ж����죬Ϊ����getMaxDay����ʵ�֣���������һ��
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
	if (isLeapYear() && month > 2) {   //year��һ��Ϊ����
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

