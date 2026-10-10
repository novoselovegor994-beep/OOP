#include <iostream>
#include <string>

using namespace std;


class Bill {
		// задаем переменные 
private: 
	string surname;
	long long phonenum;
	double tarifpermin;
	int discountpercent;
	int starth;
	int startm;
	int endh;
	int endm;
	double totalprice;
public: 
				// конструктор
	Bill(string s, long long p, double tm, int d, int sh,
		int sm, int eh, int em) {
		surname = s;
		phonenum = p;
		tarifpermin = tm;
		discountpercent = d;
		starth = sh;
		startm = sm;
		endh = eh;
		endm = em;
		totalprice = 0;
	}
	// метод вычисления продолжительности разговора в минутах
	int durationminute() const {
		int start = starth * 60 + startm;
		int end = endh * 60 + endm;
		return end - start;
	}
	// сумма скидки
	double discountsum() const {
		double full = durationminute() * tarifpermin;
		return full * discountpercent / 100.0;
	}
	// сумма к оплате 
	double calctotalprice() {
		double full = durationminute() * tarifpermin;
		totalprice = full - discountsum();
		return totalprice;
	}
	// сравнение по тарифу
	bool raznicatariff(const Bill& other) {
		return tarifpermin < other.tarifpermin;
	}
	// вывод для проверки
	void print() const {
		cout << surname << " | " << phonenum
			<< " | тариф " << tarifpermin
			<< " | скидка " << discountpercent
			<< " | длительность " << durationminute() << " мин."
			<< " | к оплате: " << totalprice << endl;
	}
};
int main() {
	setlocale(LC_ALL, "russian");
	Bill b1("Новоселов", 9968909031, 5.0, 10, 10, 30, 11, 15);
	b1.calctotalprice();
	b1.print();
	return 0;
}