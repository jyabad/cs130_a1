#include <string>
#include <iostream>
#include "blockchain.cpp"
#include "sha256.h"
using namespace std;

int main(){
    Blockchain bc;
    int operation = 0;
    while (operation != 4){
        cout << "Welcome to the transaction-chain application...." << endl;
        cout << "1) Add a transaction to the chain." << endl;
        cout << "2) Find Balance of a person." << endl;
        cout << "3) Print the chain." << endl;
        cout << "4) Exit." << endl;
        cout << "Which operation do you want to make? (1,2,3,4):" << endl;
        cin >> operation;
        if(operation != 1 && operation != 2 && operation != 3 && operation != 4){
            cout << "wrong operation!";
        }else if(operation == 1){
            int amount = 0;
            string sender = "";
            string receiver = "";
            cout << "Integer amount of money:" << endl;
            cin >> amount;
            cout << endl << "Sender name" << endl;
            cin >> sender;
            cout << endl << "Receiver name" << endl;
            cin >> receiver;
            cout << endl;
            bc.add(amount, sender, receiver);
        }else if(operation == 2){
            string person = "";
            cout << "Person Name" << endl;
            cin >> person;
            bc.getBalance(person);
        }else if(operation == 3){
            bc.print();
        }else {
        }
    }
}