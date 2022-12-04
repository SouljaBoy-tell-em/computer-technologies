#include <iostream>
#include <vector>


using namespace std;


class Student {

	public:

		Student () {

			cout << "I born.\n";
		}

		~Student () {

			cout << name << " died.\n";
		}

		void bot (string nameSubject) {

			namesubject = nameSubject;

			if (avScore <= 9)
				avScore++;
		}

		void set_name () {

			cout << "Input name of student:\n";
			cin >> name;
		}

		string get_name () {

			return name;
		}

		int set_age () {

			cout << "Input age of student:\n";
			cin >> age;

			return age;
		}

		int get_age (int newAge) {

			if (age <= 50)
				age = newAge;
			
			return age;
		}

		void set_avScore () {

			cout << "Input average score of student:\n";
			cin >> avScore;
		}

		double get_avScore () {

			return avScore;
		}

		string printNameSubject () {

			return namesubject;
		}

	private:
		string    name;
		int        age;
		double avScore;
		string namesubject;
};


int main (void) {

	int N = 0;
	cout << "Input amount of students: ";
	cin >> N;

	vector <Student> students     (N);
	vector <int>	 saveLastAge  (N);

	int i = 0;
	for (i = 0; i < N; i++) {

		int saveAge = 0;
		students[i].set_name ();
		saveAge = students[i].set_age ();
		students[i].set_avScore ();
		saveLastAge[i] = saveAge;
	}

	for (i = 0; i < N; i++)	{

		char answer = '\0';
		cout << "Does " << students[i].get_name () << "want to pobotat' ?(y/n)\n";
		cin >> answer;

		if (answer == 'y') {

			string answerSubject = "";
			cout << "What does " << students[i].get_name () << "want to pobotat'?\n";
			cout << "Input title of subject:\n";
			cin >> answerSubject;
			students[i].bot (answerSubject);
		}

		else
			students[i].bot ("nothing");
	}

	for (i = 0; i < N; i++) {

		char answer = '\0';
		cout << "Do you want change age of " << students[i].get_name () << "? (y/n)\n";
		cin >> answer;

		if (answer == 'y') {

			int newAge = 0;
			cout << "Input NEW age of " << students[i].get_name () << ":\n";
			cin >> newAge;
			students[i].get_age (newAge);
			saveLastAge[i] = students[i].get_age (newAge);
		}
	}

	cout << "\n\nINFO:\n\n";

	for (i = 0; i < N; i++) {

		cout << "Name: "    << students[i].get_name    () << endl;
		cout << "Age: "     << students[i].get_age     (saveLastAge[i]) << endl;
		cout << "avScore: " << students[i].get_avScore () << endl;
		cout << students[i].get_name () << " is boting a " << students[i].printNameSubject () << endl;
		cout << endl;
	}

	return 0;
}
