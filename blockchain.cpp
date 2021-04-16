#include <string>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <sstream>
using namespace std;

#include <openssl/sha.h>
string sha256(const string str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

class Transaction{
    public:
        int getAmount(){return amount;}
        string getSender(){return sender;}
        string getReceiver(){return receiver;}
        string getNonce(){return nonce;}
        string getHash(){return hash;}
        Transaction * getPrev(){return prev;}
        Transaction(int amount1, string sender1, string receiver1){
            amount = amount1;
            sender = sender1;
            receiver = receiver1;
        }
        void setHash(int amount1, string sender1, string receiver1, string nonce1);
        void setHash(int h);
        void setNonce(int amount1, string sender1, string receiver1);
        void setPrev(Transaction * prev1){prev = prev1;}
        string printBlock();
    private:
        Transaction * prev;
        int amount;
        string sender;
        string receiver;
        string nonce;
        string hash;
};

class Blockchain{
    public:
        Blockchain(){
            head = NULL;
        }
        void add(int amount, string sender, string receiver);
        int getBalance(string person);
        void printOldTransactions();
    private:
        Transaction * head;
};

void Transaction::setHash(int h){
    hash = "";
}

void Transaction::setHash(int amount1, string sender1, string receiver1, string nonce1){
    hash = sha256(to_string(amount1) + sender1 + receiver1 + nonce1);
}

void Transaction::setNonce(int amount1, string sender1, string receiver1){
    nonce = 'a';
    string hash1 = sha256(to_string(amount1) + sender1 + receiver1 + nonce);
    while(hash1.at(hash1.length()-1) != '0'){
        nonce = char(rand() % 26 + 97);
        hash1 = sha256(to_string(amount1) + sender1 + receiver1 + nonce);
    }
}

string Transaction::printBlock(){
    string print = "";
    print += "Amount: " + to_string(getAmount()) + '\n';
    print += "Sender: " + getSender() + '\n';
    print += "Receiver: " + getReceiver() + '\n';
    print += "Nonce: " + getNonce() + '\n';
    print += "Hash: " + getHash() + '\n';
    return print;
}

void Blockchain::add(int amount, string sender, string receiver){
    Transaction * new1 = new Transaction(amount, sender, receiver);
    if(head == NULL){
        head = new1;
        head->setPrev(NULL);
        head->setHash(0);
    }else{
        Transaction * temp = head;
        head = new1;
        head->setPrev(temp);
        head->setHash(head->getPrev()->getAmount(), head->getPrev()->getSender(), head->getPrev()->getReceiver(), head->getPrev()->getNonce());
    }
    head->setNonce(amount, sender, receiver);
    

}

int Blockchain::getBalance(string person){
    int balance = 50;
    Transaction * temp = head;
    while (temp != NULL){
        if(temp->getSender() == person){
            balance -= temp->getAmount();
        }
        if(temp->getReceiver() == person){
            balance += temp->getAmount();
        }
        temp = temp->getPrev();
    }
    return balance;
}


void Blockchain::printOldTransactions(){
    string print = "";
    Transaction * temp = head;
    while (temp != NULL){
        print = temp->printBlock() + print;
        temp = temp->getPrev();
    }
    cout << print;
}
