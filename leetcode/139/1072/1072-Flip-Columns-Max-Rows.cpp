#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <string>
using namespace std;


int numOfFlips(const vector<vector<int>>& matrix){
	map<vector<int>, int> lookup;
	int largestRows = 0;
	for(const vector<int>& row : matrix){

		vector<int> flippedRow(row.size(), 1);
		for(size_t i = 0; i < row.size(); ++i){
			flippedRow[i] = flippedRow[i]^row[i];
		}
		
		//update lookup table, if the key was not specified yet, create one
		//else, update its count

		if(lookup.find(row) != lookup.end()){
			int currCount = ++lookup[row];
			if(currCount > largestRows) largestRows = currCount;
		}
		else if(lookup.find(flippedRow) != lookup.end()){
			int currCount = ++lookup[flippedRow];
			if(currCount > largestRows) largestRows = currCount;
		}
		else{
			int currCount = lookup[row] = 1;//store by obj specified by left operand
			if(currCount > largestRows) largestRows = currCount;
		}
	}
	// unsigned res = 0;
	// for(const pair<vector<int>, int>& p : lookup){
	// 	if(p.second == largestRows){
	// 		for(int val : p.first){
	// 			if(val) ++ res;
	// 		}
	// 		return max(res, (unsigned)(matrix[0].size() - res));
	// 	}
	// }
	return largestRows;
}
int main(){
	map<vector<int>, int> arrs;
	//vector<vector<int>> matrix;
	//int n; string s; char c;
	/*
	while(!cin.eof()){
		getline(cin, s);
		stack<int> operators;
		for(char c :  s){
			//vector<int> vec = new vector<int>();
			// isdigit(c) && operators.top() == '[' ? matrix.back().push_back(c - '0') : matrix.push_back(new vector<int>());
			//vector is allocated on the heap
			// if(isdigit(c) ){
			// 	if(operators.top() == '['){
			// 		matrix.back().push_back(c - '0');
			// 	}
			//  	else{
			// 		matrix.push_back(vector<int>());
			// 		operators.pop();
			// 		operators.pop();
			// 	 }
			// }
			isdigit(c) && operators.top() == ']' ? matrix.back().push_back(c - '0') : matrix.push_back(vector<int>());
			if(c == '[' || c  == ']') operators.push(c);
		}
		for(const vector<int>& r : matrix){
			for(int c : r){
				cout << c <<' ';
			}
			cout << endl;
		}
		cout << numOfFlips(matrix) << endl;
	}
	*/
	int n,m,num;
	while(!cin.eof()){
		cin >> n >> m;
		vector<vector<int>> matrix;
		while(n-- > 0){
			int c = m;
			matrix.push_back(vector<int>());
			while(c-- > 0){
				cin >> num;
				matrix.back().push_back(num);
			}
		}
		cout << endl;
		for(const vector<int>& r : matrix){
			for(int c : r){
				cout << c <<' ';
			}
			cout << endl;
		}
		cout << endl;
		cout << numOfFlips(matrix) << endl;
	}
}
/*python
def maxEqualRowsAfterFlips(self, A):
        return max(collections.Counter(tuple(x ^ r[0] for x in r) for r in A).values())

cache = collections.defaultdict(int)
*/
