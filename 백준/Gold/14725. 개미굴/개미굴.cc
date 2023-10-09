#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int N, K;
char feed[16];

class Trie{
	int floor = 0;
	string feed = "";
	vector<Trie*> child = vector<Trie*>();

	public: 

	Trie(){}

	Trie(int floor, string feed){
		this->floor = floor;
		this->feed = feed;
	}
	
	Trie* append(string toAppend, int appendFloor){
		bool exists = false;
		
		for (auto c : child){
			if (c->feed.compare(toAppend) == 0){
				return c;
			}
		}
		Trie* newTrie = new Trie(appendFloor, toAppend);
		this->child.push_back(newTrie);
		return newTrie;
	}
	
	static bool compare(Trie* a, Trie* b){
		return a->feed.compare(b->feed) < 0;
	}

	void retrieve(){
		sort(child.begin(), child.end(), compare);	
		if (floor) {
			for (int i = 0; i < floor - 1; i++) printf("--");
			printf("%s\n", feed.c_str());
		}
		for (int i = 0; i < child.size(); i++) {
			child[i]->retrieve();
		}
	}
};

Trie entrance;
Trie*  parent;

int main(){
	scanf("%d", &N);

	for (int i = 0; i < N; i++){
		scanf("%d", &K);
		parent = &entrance;

		for (int j = 0; j < K; j++){
			scanf("%s", feed);
			parent = parent->append(feed, j + 1);
		}
	}
	
	entrance.retrieve();
}