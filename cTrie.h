//Most Recent Changes.. 
//Removed the exist() check from insertWord.. Works fine.. Need To look for faster ways to check existence
//After Deleting All.. Root->children doesn't has all indices set to NULL
// .... Maybe verdict is never equating to zero in deleteWord

#ifndef CONDENSED_TRIE_H
#define CONDENSED_TRIE_H
#include<iostream>
#include<vector>
#include<string>
#include<stack>
using namespace std;

class Node{
	vector<Node *> children;
	bool isTerminal;
	string str;

	public:
	Node() {
		children.resize(26,NULL);
		isTerminal = false;
	}

	int getChildren() const{
		int count = 0;
		for(int i=0;i<children.size();i++){
			if(children[i]!=NULL){
				count++;
			}
		}
		return count;
	}

	friend class CondensedTrie;
};

class CondensedTrie{
	Node *root;

	static int breakPoint(string word, string temp){
		int index = 0;
		int limit = word.size() < temp.size() ? word.size() : temp.size();

		for(int i=0; i<limit ;i++){
			if(word[i]!=temp[i]){
				break;
			}
			index++;
		}
		return index;
	}

	void updateBranch(Node *oldParent,string remaining){
		Node *newParent = new Node;
		newParent->children = oldParent->children;
		newParent->isTerminal = oldParent->isTerminal;
		oldParent->children.clear();
		oldParent->children.resize(26,NULL);
		oldParent->children[remaining[0]-'a'] = newParent;
//		cout << remaining;
		newParent->str = remaining;
//		cout << "Setting isTerminal " << newParent->isTerminal << " For " << newParent->str << " Because Of " << oldParent->str << endl;
//		cout << "Updated Branch From " << oldParent->str << " TO " << newParent->str << endl;
	}
	
	void insertWordHelper(string word,int index,Node *current){
		if(word == "" || word[index]=='\0'){
			return;
		}

//		cout << "Inserting " << word << endl;

		for(int i=index; word[i];){
			if(current->children[word[i]-'a'] == NULL){
//		cout << "Set " << word << "  on " << current->str << " whose terminal is " << current->isTerminal << endl;
				current->children[word[i]-'a'] = new Node;
				current = current->children[word[i]-'a'];
				current->str = word;
				current->isTerminal = true;
				break;
			}
			
			current = current->children[word[i]-'a'];
			
			while(current->getChildren()!=0){
				if(current->children[word[0]-'a']){
					int index = breakPoint(word,current->str);
					if(index==current->str.size()){
						Node *temp = current->children[word[0]-'a'];
						word = word.substr(index,word.size()+1);
						current = temp;
					}
					else{
						break;
					}
				}
				else
					break;
			}

			int diff_index = breakPoint(word,current->str);
			string remaining = current->str.substr(diff_index,current->str.size()+1);
//			cout << word << "   " << diff_index << endl;
			
			current->str = current->str.replace(diff_index, current->str.size() - diff_index, "");
//			cout << "STR = " << current->str << endl;
//			cout << "Remaining = " << remaining << endl;

			word = word.substr(diff_index,word.size()+1);
//			cout << "Truncated = " << word << endl;

			if(remaining!=""){
				if(current->getChildren()!=0){
					updateBranch(current,remaining);
					current->isTerminal = false;
					if(word=="" && current->children[remaining[0]-'a']->isTerminal){
		//equivalent to if(word=="" && prevStateOfCurrent)
						current->isTerminal = true;
					}
				}
				else{
					if(word!="")
						current->isTerminal = false;
					else
						current->isTerminal = true;
					insertWordHelper(remaining,0,current);
				}
			}
			else{
				if(word=="")
					current->isTerminal = true;
			}

			if(word==""){
				break;
			}

		}
		return;
	}

	void printAllWordsHelper(vector<const string> &wordsList , const Node *node) const{
		if(!node){
			cout << endl;
			return;
		}

		wordsList.push_back(node->str);

		if(node->isTerminal){
			for(int k=0;k<wordsList.size();k++){
				cout << wordsList[k];
			}
			cout << endl;
		}

		for(int i=0;i<26;i++){
			if(node->children[i]){
		//		cout << node->str << " " << i << endl;
		//		cout << (node->isTerminal ? "True\n" : "False\n");
				printAllWordsHelper(wordsList,node->children[i]);
			}
		}
		wordsList.pop_back();
	}

	static bool existHelper(const Node *node, string word, vector<const string> &V){
		if(!node)
			return false;
		V.push_back(node->str);
		if(node->isTerminal){
			string temp;
			for(int i=0;i<V.size();i++){
				temp += V[i];
			}
			if(temp == word){
				cout << "Exists\n";
				return true;
			}
		}

		for(int i=0;i<26;i++){
			if(node->children[i]!=0){
				if(existHelper(node->children[i],word,V)){
					return true;
				}
				else{
					continue;
				}
			}
		}
		V.pop_back();
		return false;
	}

	static bool deleteWordHelper(Node *parent, string word,int index){
		if(!parent)
			return false;
//		cout << "word = " << word << " " << index << endl;
		string temp = word.substr(index,word.size()+1);
//		cout << "temp = " << temp << endl;
		int point = breakPoint(temp,parent->str);
//		cout << "parent->str = " << parent->str  << "  point = " << point << endl;
		if(point < parent->str.size()){
			return false;
		}
		index += point;
//		cout << "Index = " << index << endl;
		if(index == word.size()){
			if(!parent->isTerminal)
				return false;
			parent->isTerminal = false;
			if(parent->getChildren()==0){
				delete parent;
				return true;
			}
			return false;
		}
		bool verdict = deleteWordHelper(parent->children[temp[point]-'a'],word,index);
		if(verdict){
//			cout << parent->str << "__";
//			cout << word << " " << index << endl;
			parent->children[word[index]-'a'] = NULL;
			if(parent->isTerminal == false && parent->getChildren()==0){
				delete parent;
				return true;
			}
		}
		return false;
	}

	static void fillWordsInVectorForParent(const Node *node,vector<const string> &wordList,vector<const string> &finalList){
		if(!node)
			return;
		wordList.push_back(node->str);
		if(node->isTerminal){
			string temp;
			for(int i=0;i<wordList.size();i++){
				temp += wordList[i];
			}
			finalList.push_back(temp);
		}

		for(int i=0;i<26;i++){
			if(node->children[i]){
				fillWordsInVectorForParent(node->children[i],wordList,finalList);
			}
		}
		wordList.pop_back();
	}

	public:
	static int noOfWords;
	CondensedTrie() {
		root = new Node;
	}

	void insertWord(string word){
		if(word == ""){// || exist(word)){
			return;
		}
		insertWordHelper(word,0,root);
//		cout << "\n\n";
//		vector<const string> wordsList;
//		printAllWordsHelper(wordsList,root);
		noOfWords++;
	}

	void printAllWords() const{
		vector<const string> wordsList;
		printAllWordsHelper(wordsList,root);
	}

	bool exist(string word) const{
		vector<const string> V;
		return existHelper(root,word,V);
	}

	void deleteWord(const string &word){
		if(word=="" || isEmpty() ){//|| !exist(word)){
//			cout << "*";
			return;
		}
		bool verdict = deleteWordHelper(root->children[word[0]-'a'],word,0);
		noOfWords--;
//		cout << (verdict ? "True" : "False") << endl;
		if(verdict){
//			cout << "================================================\n";
			root->children[word[0]-'a'] = NULL;
		}
	}

	bool isEmpty() const{
//		cout << "**Children Of Root** = " << root->getChildren() << endl;
		return root->getChildren()==0;
	}

	void getAllWordsWithPrefix(const string &pre) const{
		vector<const string> wordList,finalList;
		
		if(!root->children[pre[0]-'a']){
			return;
		}
		const Node *current = root;
		for(int i=0;pre[i];){
			current = current->children[pre[i]-'a'];
			wordList.push_back(current->str);
			string temp = pre.substr(i,pre.size());
			int index = breakPoint(temp,current->str);
			if(index < temp.size() && index < current->str.size()){
				cout << "Sorry, No Words Found For The Prefix " << pre << endl;
				return;
			}
			i+=index;
		}
		wordList.pop_back();
		fillWordsInVectorForParent(current,wordList,finalList);

		cout << "Words With Prefix " << pre << ": \n";
		for(int i=0;i<finalList.size();i++){
			cout << finalList[i] << endl;
		}
	}
};

int CondensedTrie::noOfWords = 0;

#endif
