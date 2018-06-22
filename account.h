#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

#include "date.h"
#include "accumulator.h"
#include <string>
using std::string;

class Account {                  //�˻���
private:
	string id;                   //�˺�
	double balance;              //���

	static double total;         //�����˻����ܽ��

protected:
	//����������õĹ��캯��
	Account(const Date &date, const string &id);
	//��¼һ���ˣ�dateΪ���ڣ�amountΪ��descΪ˵��
	void record(const Date &date, double amount, const string &desc);
	//���������Ϣ
	void error(const string &msg) const;

public:
	const string &getId() const { return id; }
	double getBalance() const { return balance; }

	//�����ֽ�dateΪ���ڣ�amountΪ��descΪ����˵��
	virtual void deposit(const Date &date, double amount, const string &desc) = 0;
	//ȡ���ֽ�dateΪ���ڣ�amountΪ��descΪ����˵��
	virtual void withdraw(const Date &date, double amount, const string &desc) = 0;
	//���㣨������Ϣ����ѵȣ���ÿ�½���һ�Σ�dateΪ��������
	virtual void settle(const Date &date) = 0;
	//��ʾ�˻���Ϣ
	virtual void show() const;

	static double getTotal() { return total; }
};


class SavingsAccount: public Account {    //�����˻���
private:
	Accumulator acc;                //����������Ϣ���ۼ���
	double rate;                    //����������
public:
	SavingsAccount(const Date &date, const string &id, double rate);
	double getRate() const { return rate; }
	//�����ֽ�
	void deposit(const Date &date, double amount, const string &desc); 
	//ȡ���ֽ�
	void withdraw(const Date &date, double amount, const string &desc); 
	void settle(const Date &date);  //������Ϣ��ÿ��1��1�յ���һ�θú���
};

class CreditAccount : public Account {     //�����˻���
private:
	Accumulator acc;              //����������Ϣ���ۼ���
	double credit;                //���ö��
	double rate;                  //Ƿ���������
	double fee;                   //���ÿ����

	//���Ƿ���
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
	//��ÿ������ö��
	double getAvailableCredit() const {
		if (getBalance() < 0) {
			return credit + getBalance();
		}
		else
			return credit;
	}
	//�����ֽ�
	void deposit(const Date &date, double amount, const string &desc);
	//ȡ���ֽ�
	void withdraw(const Date &date, double amount, const string &desc);
	//������Ϣ����ѣ�ÿ��1�յ���һ�θú���
	void settle(const Date &date);
	void show() const;
};

#endif  //_ACCOUNT_H_
