#include <iostream>
#include <stdio.h>
#include <string.h>
#include <map>
#include <string>
#include <vector>


using namespace std;


void addBus (map<string, vector<string> > &mp);
void busesForStop (map<string, vector<string> > &mp);
void stopForBus (map<string, vector<string> > &mp);
void outputAllBuses (map<string, vector<string> > &mp);

int main()
{
    int N;
    cin >> N;

    map <string, vector<string> > mp;

    int i = 0;
    for (i = 0; i < N; i++) {

        string command;
        cin >> command;
        
        if (command == "NEW_BUS")   
            addBus (mp);

        else if (command == "ALL_BUSES")
            outputAllBuses (mp);

        else if (command == "BUSES_FOR_STOP")
            busesForStop (mp);

        else if (command == "STOPS_FOR_BUS")
            stopForBus (mp);
    }

    return 0;
}

void addBus (map<string, vector<string> > &mp) {

    string name;
    cin >> name;

    int amountBusStation = 0;
    cin >> amountBusStation;

    int i = 0;
    for (i = 0; i < amountBusStation; i++) {

        string nameBusStation;
        cin >> nameBusStation;

        mp[name].push_back(nameBusStation);
    }         
}


void outputAllBuses (map<string, vector<string> > &mp)
{
    if (! mp.size())
        cout << "Buses didn't add.\n";

    else {

        for (auto i : mp) { // перебор map 

            cout << "Bus #" << i.first << ": ";

            for (auto j : i.second) // перебор значений
                cout << j << " ";

            cout << endl;
        }
    }
}

void busesForStop (map<string, vector<string> > &mp)
{
    string nameBusStation;
    cin >> nameBusStation;

    bool isBusStation = 0;

    for (auto i : mp)
        for (auto j : i.second)
            if (j == nameBusStation)
                isBusStation = true;

    if (isBusStation) {

        for (auto i : mp) {

            for (auto j : i.second) {

                if (nameBusStation == j) {
                    cout << i.first << " ";
                    break;
                }
            }
        }
        cout << endl;
    }
    
    else
        cout << "So stop not found\n"; 
}

void stopForBus (map <string, vector<string> > &mp)
{

    bool exist = false, isBusStation = false;

    string bus;
    cin >> bus;

    for (auto i : mp)
        if (i.first == bus)
            isBusStation = true;
    
    if (isBusStation) {
        for (auto i : mp[bus]) {
            cout << "Stop " << i << ": ";
 
            for (auto j : mp) {

                for (auto k : j.second)
                    if (i == k && j.first != bus) {
                        cout << j.first << " ";
                        exist = true;
                        break;
                    }
            }

            if (!exist)
                cout << "Only this bus\n";
            
            else
                cout << endl;
        }
    }

    else
        cout << "Buses not found\n";
}
