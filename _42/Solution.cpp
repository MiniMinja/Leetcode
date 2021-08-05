#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution{
	private:
		void max2(vector<int>& height, int start, int end, int& a, int& b){
			int highest1 = 0;
			int highest2 = 0;
			for(int i = start;i<=end;i++){
				if(height[i] > highest1){
					highest1 = height[i];
					a = i;
				}	
			}
			for(int i = start;i<=end;i++){
				if(height[i] > highest2 && height[i] <= highest1 && i!=a){
					highest2 = height[i];
					b = i;
				}
			}
		}

		int area(vector<int>& height, int start, int end){
			int h = min(height[start], height[end]);
			int dirt = 0;
		       	for(int i = start+1;i<end;i++){
				dirt += height[i];
			}
			return h * (end - start-1) - dirt;
		}

		int recurseT(vector<int>& height, int start, int end){
			cout << "start: " << start << " end: " << end << endl;
			if(end - start <= 1) return 0;
			int index1 = start;
			int index2 = end;

			max2(height, start, end, index1, index2);
			//make index1 always left of index2
			if(index2 < index1){
				int temp = index1;
				index1 = index2;
				index2 = temp;
			}
			
			//iterate throught index1-index2 and calculate the area
			int a = area(height, index1, index2);
			int al = recurseT(height, start, index1);
			int ar = recurseT(height, index2 , end);
			cout << "Area: " << a + al + ar << endl;
			return a + al + ar;
		}
	public:
		int trap(vector<int>& height){
			return recurseT(height, 0, height.size()-1);
		}
};

void printVector(const vector<int>& v){
	for(int i:v){
		cout << i << " ";
	}
	cout << endl;
}

void removeWhitespace(string& line){
	int size = line.length();
	for(int i = 0;i<size;i++){
		if(line[i] == ' '){
			line.erase(i, 1);
			i--;
			size--;
		}
	}
}

int main(){
	ifstream test_cases;
	test_cases.open("Solution.in");

	ifstream exp_ans;
	exp_ans.open("Solution.out");
	string ans;

	Solution sol;
	string line;
	int count = 0;
	while( getline(test_cases, line) && getline(exp_ans, ans) ){
		vector<int> c;
		removeWhitespace(line);
		line.erase(0, 1); //get rid of "["
		line.erase(line.length()-1, 1);//get rid of "]"

		stringstream inputs(line);
		string s;
		while (getline(inputs,s,',')){
			c.push_back(stoi(s));
		}

		cout << "Testing case " << count << ": " << endl;
		int exp = stoi(ans);
		int act = sol.trap(c);

		if(exp != act){
			cout << "\tExpected: " << exp << " but got: " << act << endl;
		}
		else{
			cout << "\tCorrect!" << endl;
		}
		count++;
	}
}
