#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

#include "date.h"
#include "accumulator.h"
#include <string>
using std::string;

class Account {                  //账户类
private:
	string id;                   //账号
	double balance;              //余额

	static double total;         //所以账户的总金额

protected:
	//供派生类调用的构造函数
	Account(const Date &date, const string &id);
	//记录一笔账，date为日期，amount为金额，desc为说明
	void record(const Date &date, double amount, const string &desc);
	//报告错误信息
	void error(const string &msg) const;

public:
	const string &getId() const { return id; }
	double getBalance() const { return balance; }

	//存入现金，date为日期，amount为金额，desc为款项说明
	virtual void deposit(const Date &date, double amount, const string &desc) = 0;
	//取出现金，date为日期，amount为金额，desc为款项说明
	virtual void withdraw(const Date &date, double amount, const string &desc) = 0;
	//结算（计算利息、年费等），每月结算一次，date为结算日期
	virtual void settle(const Date &date) = 0;
	//显示账户信息
	virtual void show() const;

	static double getTotal() { return total; }
};


class SavingsAccount: public Account {    //储蓄账户类
private:
	Accumulator acc;                //辅助计算利息的累加器
	double rate;                    //存款的年利率
public:
	SavingsAccount(const Date &date, const string &id, double rate);
	double getRate() const { return rate; }
	//存入现金
	void deposit(const Date &date, double amount, const string &desc); 
	//取出现金
	void withdraw(const Date &date, double amount, const string &desc); 
	void settle(const Date &date);  //结算利息，每年1月1日调用一次该函数
};

class CreditAccount : public Account {     //信用账户类
private:
	Accumulator acc;              //辅助计算利息的累加器
	double credit;                //信用额度
	double rate;                  //欠款的日利率
	double fee;                   //信用卡年费

	//获得欠款额
	double getDebt() const {
		double balance = getBalance();
		return (balance < 0 ? balance : 0);
	}

public:
	CreditAccount(const Date &date, const string &id,
		double credit, double rate, double fee);
	double getCredit() const { return credit; }
	double getRate() const { return rate; }
	double getFee() const { return fee; }
	//获得可用信用额度
	double getAvailableCredit() const {
		if (getBalance() < 0) {
			return credit + getBalance();
		}
		else
			return credit;
	}
	//存入现金
	void deposit(const Date &date, double amount, const string &desc);
	//取出现金
	void withdraw(const Date &date, double amount, const string &desc);
	//结算利息和年费，每月1日调用一次该函数
	void settle(const Date &date);
	void show() const;
};

#endif  //_ACCOUNT_H_
