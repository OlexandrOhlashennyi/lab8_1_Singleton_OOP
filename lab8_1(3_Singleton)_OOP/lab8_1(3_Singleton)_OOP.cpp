#include <iostream>

using namespace std;

class DigitalCounter {
private:
	static DigitalCounter* object;
	static int count;

	int* counter;
	int* min_value;
	int* max_value;
	int n;
	void counterIncrease(int*);
	
	DigitalCounter() {
		n = 3;
		counter = new int[n];
		min_value = new int[n];
		max_value = new int[n];
		for (int i = 0; i < n; i++) {
			counter[i] = min_value[i] = 0;
			max_value[i] = 9;
		}
	}

public:
	static DigitalCounter& getInstance() {
		if (count == 0) {
			object = new DigitalCounter();
			count++;
		}
		return *object;
	}

	int getN() { return n; }
	int getCounter(int* arr) {
		for (int i = 0; i < n; i++) arr[i] = counter[i];
	}
	void getMinimum(int* arr) {
		for (int i = 0; i < n; i++) arr[i] = min_value[i];
	}
	void getMaximum(int* arr) {
		for (int i = 0; i < n; i++) arr[i] = max_value[i];
	}

	void setMinimum(int* arr) {
		for (int i = 0; i < n; i++) min_value[i] = arr[i];
	}
	void setMaximum(int* arr) {
		for (int i = 0; i < n; i++) arr[i] = min_value[i];
	}
	void setCounter(int* arr) {
		for (int i = 0; i < n; i++) counter[i] = arr[i];
	}
	void Increase();

	friend ostream& operator<<(ostream& output, const DigitalCounter& DC) {
		for (int i = 0; i < DC.n - 1; i++) {
			output << DC.counter[i] << " : ";
		}
		output << DC.counter[DC.n - 1] << endl;
		return output;
	}
	friend istream& operator>>(istream& input, DigitalCounter& DC) {
		cout << "n: ";
		cin >> DC.n;
		DC.counter = new int[DC.n];
		DC.min_value = new int[DC.n];
		DC.max_value = new int[DC.n];

		cout << "max: ";
		for (int i = 0; i < DC.n; i++) {
			input >> DC.max_value[i];
		}
		cout << "min: ";
		for (int i = 0; i < DC.n; i++) {
			int temp;
			input >> temp;
			if (temp >= DC.max_value[i])
				DC.min_value[i] = DC.max_value[i] - 1;
			else
				DC.min_value[i] = temp;
		}
		cout << "counter: ";
		for (int i = 0; i < DC.n; i++) {
			int temp;
			input >> temp;
			if (temp > DC.max_value[i])
				DC.counter[i] = DC.max_value[i];
			else if (temp < DC.min_value[i])
				DC.counter[i] = DC.min_value[i];
			else
				DC.counter[i] = temp;
		}
		return input;
	}

	DigitalCounter operator++() {
		this->Increase();
		return *this;
	}
	DigitalCounter operator++(int) {
		this->Increase();
		return *this;
	}
};

int DigitalCounter::count = 0;
DigitalCounter* DigitalCounter::object = 0;

int main() {
	DigitalCounter& dc = DigitalCounter::getInstance();
	cin >> dc;

	cout << endl  << "counter: " << dc << endl;

	dc++;

	cout << endl << "after ++: " << dc << endl;

	return 0;
}

void DigitalCounter::Increase() {
	counterIncrease(counter + n - 1);
}

void DigitalCounter::counterIncrease(int* counter) {
	(*counter)++;
	if (*counter > max_value[counter - this->counter]) {
		*counter = min_value[counter - this->counter];
		counterIncrease(--counter);
	}
}


/*
3
23 59 59
0 0 0
1 1 2
*/