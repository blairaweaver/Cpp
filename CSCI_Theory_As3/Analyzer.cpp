#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;

void Analyzer(string s){
	for(int i = 0; i < s.length(); i++){
		//for r1 to r6 to r32
		if(s[i] == 'i' && s[i+1] == 'f'  && !(isalpha(s[i+2])) && !(isdigit(s[i+2])) ){
			cout << s[i] << "\t| " << s[i] << endl;
			cout << s[i+1] << "\t| " << s[i+1] << endl;
			cout << s[i] << s[i+1] << "\t| Keyword" <<  endl;
			i++;
			continue;
		}
		//for r1->r14->r32 <, >, <=, and >=
		if(s[i] == '>' || s[i] == '<'){
				cout << s[i] << "\t| " << s[i] << endl;
			if(s[i+1] == '='){
				cout << s[i+1] << "\t|" << s[i+1] << endl;
				cout << s[i] << s[i+1] << "\t| Comparison" <<  endl;
				i++;
				continue;
			}
			else{
				cout << s[i] << "\t| Comparison" <<  endl;
			}
		}
		//for r1->r14->r32 = and ==
		if(s[i] == '='){
			if(s[i+1] == '='){
				cout << s[i] << "\t| " << s[i] << endl;
				cout << s[i+1] << "\t| " << s[i+1] << endl;
				cout << s[i] << s[i+1] << "\t| Comparison" <<  endl;
				i++;
				continue;
			}
			else{
				cout << s[i] << "\t| " << s[i] << endl;
				cout << s[i] << "\t| Assignment" << endl;
			}
		}
		//for r1 to r11
		if(isalpha(s[i])){
			int count = 1;
			string temp = "";
			temp+=s[i];
			cout << s[i] << "\t| " << s[i] << endl;
			while(isdigit(s[i+count]) || isalpha(s[i+count])){
				temp += s[i+count];
				cout << s[i+count] << "\t| " << s[i+count] << endl;
				count++;
			}
			cout << temp << "\t| Variable" << endl;
			i+=count-1;
			continue;
		}
		//for r1 to r12
		if(isdigit(s[i])){
			int count = 1;
			string temp = "";
			temp+=s[i];
			cout << s[i] << "\t| " << s[i] << endl;
			while(isdigit(s[i+count])){
				temp += s[i+count];
				cout << s[i+count] << "\t| " << s[i+count] << endl;
				count++;
			}
			cout << temp << "\t| Integer Constant" << endl;
			i+=count-1;
			continue;
		}		
				
		//for r1->r32 Arithmetic, ;, (, and )
		if(s[i]== '+' || s[i] == '*' || s[i] == '/' || s[i] == '%'){
			cout << s[i] << "\t| " << s[i] << endl;
			cout << s[i] << "\t| Arithmetic Symbol" << endl;
		}
		if(s[i] == ';')
			cout << s[i] << "\t| ;" << endl;
		if(s[i] == '(')
			cout << s[i] << "\t|(" << endl;
		if(s[i] == ')')
			cout << s[i] << "\t| )" << endl;
		//for r1 to r4 to r32
		if(s[i] == '|' && s[i+1] == '|'){
			cout << s[i] << "\t| " << s[i] << endl;
			cout << s[i+1] << "\t| " << s[i+1] << endl;
			cout << s[i] << s[i+1] << "\t| Logical" <<  endl;
			i++;
			continue;
		}
		//for r1 to r5 to r32
		if(s[i] == '&' && s[i+1] == '&'){
			cout << s[i] << "\t| " << s[i] << endl;
			cout << s[i+1] << "\t| " << s[i+1] << endl;
			cout << s[i] << s[i+1] << "\t| Logical" <<  endl;
			i++;
			continue;
		}
		//for r1 to r7 to r32
		if(s[i] == '!' && s[i+1] == '='){
			cout << s[i] << "\t| " << s[i] << endl;
			cout << s[i+1] << "\t| " << s[i+1] << endl;
			cout << s[i] << s[i+1] << "\t| Logical" <<  endl;
			i++;
			continue;
		}
		if(s[i] == '-'){
			if(s[i+1] == '-'){
				cout << s[i] << "\t| " << s[i] << endl;
				cout << s[i+1] << "\t| " << s[i+1] << endl;
				cout << s[i] << s[i+1] << "\t| --" <<  endl;
				i++;
				continue;
			}
			else{
				cout << s[i] << "\t| " << s[i] << endl;
				cout << s[i] << "\t| Arithmetic Symbol" << endl;
			}
		}
	}
}

int main(int argc, char* argv[]) {
	//variables
	string input;
	vector <string> result;
	string temp = "";
	//get input string. would prefer to change this to take command line input
	cout << "Type input string: ";
	getline (cin, input);
	
	
	
	//break string into substrings by white space
	for (auto x : input){
		if (x== ' '){
			result.push_back(temp);
			temp = "";
		}
		else{
			temp += x;
		}
	}
	result.push_back(temp);

	//Table header
	cout << "---------------" << endl;
	cout << "Symbol\t| Type\t" << endl;
	cout << "---------------" << endl;

	//Send substrings to Analyzer
	for (auto x : result){
		Analyzer(x);
	}
}
