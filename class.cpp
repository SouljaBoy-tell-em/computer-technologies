#include <iostream>
#include <vector>


using namespace std;


class Student {

	public:

		Student () {

			cout << name << " born.\n";
		}

		~Student () {

			cout << name << " died.\n";
		}

		void bot (string namesubject) {

			cout << name << " is boting a " << namesubject << endl;
			avScore++;
		}

		void set_name () {

			cin >> name;
		}

		string get_name () {

			return name;
		}

		void set_age () {

			cin >> age;
		}

		int get_age () {

			return age;
		}

		void set_avScore () {

			cin >> avScore;
		}

		double get_avScore () {

			return avScore;
		}

	private:
		string    name;
		int        age;
		double avScore;
};


int main (void) {

	int N = 0;
	cout << "Input amount of students: ";
	cin >> N;

	vector <Student> students (N);

	int i = 0;
	for (i = 0; i < N; i++) {

		students[i].set_name    ();
		students[i].set_age     ();
		students[i].set_avScore ();
	}

	cout << "INFO:\n\n";

	for (i = 0; i < N; i++) {

		cout << "Name: "    << students[i].get_name    () << endl;
		cout << "Age: "     << students[i].get_age     () << endl;
		cout << "avScore: " << students[i].get_avScore () << endl;
		cout << endl;
	}

	return 0;
}