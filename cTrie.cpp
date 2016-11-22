#include "cTrie.h"
#include <algorithm>
int main(){
	CondensedTrie T;
	
	for(int i=0;i<235886;i++){
		string word;
		cin >> word;
		transform(word.begin(),word.end(),word.begin(),::tolower);
		T.insertWord(word);
		if(i%10000==0){
			cout << "[  Words Inserted  =  " << CondensedTrie::noOfWords << "  ]\n";
		}
	}
/*	T.insertWord("romane");
	T.insertWord("romanus");
	T.insertWord("alphonso");
	T.insertWord("rubens");
	T.insertWord("rubicon");
	T.insertWord("romulus");
	T.insertWord("alphabeta");
	T.insertWord("rubicundus");
	T.insertWord("alfaromeo");
	T.insertWord("ruber");
	T.insertWord("alphabet");
	T.insertWord("alpha");
	T.printAllWords();
	cout << "\n";
	cout << "$$$$$$$$$$$$$$$$$$$$$\n";
	T.deleteWord("alphabet");
	T.deleteWord("alpha");
	T.deleteWord("alphabeta");
	T.deleteWord("ruber");
	T.deleteWord("alphonso");
	T.deleteWord("alfaromeo");
	T.deleteWord("rubicon");
	T.deleteWord("romane");
	T.deleteWord("romulus");
	T.deleteWord("romanus");
	T.deleteWord("rubicundus");
	cout << T.isEmpty() << endl;
	T.deleteWord("rubens");
	cout << T.isEmpty() << endl;
	T.insertWord("alpha");
	T.insertWord("romane");
	T.insertWord("rubicon");
	T.insertWord("rubens");
	T.insertWord("alphabeta");
	T.insertWord("rubicundus");
	T.insertWord("ruber");
	T.insertWord("rub");
	T.insertWord("al");
	T.insertWord("alfaromeo");
	T.insertWord("romanus");
	T.insertWord("alphonso");
	T.insertWord("romulus");
	T.insertWord("alphabet");*/
	T.printAllWords();
	cout << "=======================";
//	T.getAllWordsWithPrefix("al");
	cout << "\n";
	T.getAllWordsWithPrefix("bur");
	cout << "\n";
	T.getAllWordsWithPrefix("a");
	cout << "\n";
	T.getAllWordsWithPrefix("r");
	cout << "\n";
	T.getAllWordsWithPrefix("rub");
	cout << "\n";
//	T.getAllWordsWithPrefix("alp");
	cout << "\n";
	T.getAllWordsWithPrefix("roman");
	cout << "\n";
//	T.getAllWordsWithPrefix("alf");
	cout << "\n";
//	T.getAllWordsWithPrefix("alpa");
	cout << "\n";
/*	T.insertWord("alphabeta");
	T.insertWord("alphabet");
	T.insertWord("alpha");
	T.insertWord("alfaromeo");
	T.insertWord("al");
	T.deleteWord("al");*/
//	T.getAllWordsWithPrefix("alfaro");
	cout << "\n";
	T.getAllWordsWithPrefix("pra");cout<<endl;

	for(int i=0;i<235886;i++){
		string word;
		cin >> word;
		transform(word.begin(),word.end(),word.begin(),::tolower);
		T.deleteWord(word);
		if(i){
			cout << "[  Words Remaining  =  " << CondensedTrie::noOfWords << "  ]\n";
			cout << "Deleted " << word << endl;
	cout << T.isEmpty() << endl;
		}
	}
	cout << T.isEmpty() << endl;
//	T.getAllWordsWithPrefix("roman");
//	T.getAllWordsWithPrefix("a");
	cout << "\n";
return 0;
}
