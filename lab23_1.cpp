#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
#include <algorithm>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names,vector <int> &scores, vector <char> &grades){
    ifstream source;
    source.open(filename);
    
    string line;
    char n[100];
    char format[] = "%[^:]: %d %d %d";
    int s1, s2, s3;
    while(getline(source,line)){
        const char *temp = line.c_str();
        
        sscanf(temp, format, n, &s1, &s2, &s3);
        names.push_back(string(n));
        scores.push_back(int (s1+s2+s3) );
        grades.push_back( score2grade (int (s1+s2+s3)) );
        
    }
}

void getCommand(string &command, string &key){
    cout << "Please input your command:\n";
    cin >> command;
    command = toUpperStr(command);
    //cout << "Command : " << command <<endl ; 
   if(command == "NAME" or command ==  "GRADE"){
     //  cout << "True "  ; 
        cin.ignore();
        getline(cin,key);
      //  cout << "key :  " << key << endl; 
    }
}

void searchName(vector<string> &names, vector<int> &scores, vector<char> &grades, string key)
{
    vector<string> names_toupper;
    for(unsigned int i = 0 ; i < names.size() ; i++)
    {
        names_toupper.push_back(toUpperStr(names[i]));
    }
    
    unsigned int index = distance(names_toupper.begin() , find(names_toupper.begin() , names_toupper.end() , key));
    
    if(index == names_toupper.size())
    {
        cout << "---------------------------------\n" ; 
        cout << "Cannot found.\n";
        cout << "---------------------------------\n" ;
    }
    else
    {
        cout << "---------------------------------\n" ;
        cout << names[index] << "'s score = " << scores[index] << endl;
        cout << names[index] << "'s grade = " << grades[index] << endl;
        cout << "---------------------------------\n" ;
    }
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key)
{
    int count = 0 ;
    
    cout << "---------------------------------\n" ;
    
    for(unsigned int i = 0 ; i < names.size() ; i++)
    {
        if(grades[i] == key[0])
        {
            count++;
            cout << names[i] << " (" << scores[i] << ")" << endl;
        }
    }
    
    if(count == 0)
    {
        cout << "Cannot found.\n";
    }
    
    cout << "---------------------------------\n" ;

}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}