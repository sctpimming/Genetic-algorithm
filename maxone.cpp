#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using lli = unsigned long long int;

#define rep(i,k,n) for(int i=(k);i!=int(n);++i)
#define sz(x) x.size()
#define all(x) x.begin(),x.end()
#define dbg(x) cout << "debug :" << x << "\n"
#define dbg2(x,y) cout << "debug :" << x << ":" << y << "\n"
#define input() (*istream_iterator<int>(cin))
#define strin() (*istream_iterator<string>(cin))
#define output(x) cout << x

const int mxitr = 1000, popsz = 10, bit_num = 10;
const double p_cross = 0.5;
using arr = array<int, bit_num>;
std::vector<arr> population, parent, children;

int cost_function(int idx){
	int cost = 0;
	for(int gene : population[idx]) cost += gene;
	//cout << "solution " << idx << " fitness value : " << cost << "\n";
	return cost;
}

void init_sol(){
	arr sol;
	rep(i, 0, bit_num) sol[i] = (rand()%10 < 5) ? 0 : 1;
	population.push_back(sol);
	cout << "initialize solution : " ;
	for(int gene : sol) cout << gene;
	cout << "\n";
}

void selection(){
	dbg("selection state\n");
	int current_pop = sz(population);
	rep(i, 0, current_pop){
		int cost = cost_function(i), rand_val = (rand()%bit_num)+1;
		if(rand_val < cost) parent.push_back(population[i]);
	}
}

void reproduction(){
	dbg("reproduction state\n");
	int parent_size = sz(parent);
	rep(itr, 0, 10){
		arr child;
		int pa1 = rand()%parent_size, pa2 = rand()%parent_size;
		while(pa1 == pa2) {
			dbg("random");
	 		pa1 = rand()%parent_size;
	   	pa2 = rand()%parent_size;
	   	dbg2(pa1, pa2);
		}
		rep(i, 0, bit_num){
			int rand_val = double((rand()%100)/100);
			if(rand_val < p_cross) child[i] = population[pa1][i];
			else child[i] = population[pa2][i];
		}
		children.push_back(child);
	}
}

void mutation(){
	dbg("mutation state\n");
	int children_size = sz(children);

	rep(itr, 0, 5){
		int child_idx = rand()%children_size;
		int bit_idx = rand()%bit_num;
		children[child_idx][bit_idx] = (children[child_idx][bit_idx]) ? 0 : 1;
	}
	for(arr child: children) population.push_back(child);
}

int solve(){
	int gen = 1, mx = -1, current_pop;
	//initialize random solution + find best.
	rep(i, 0, popsz) init_sol();
	rep(i, 0, popsz) mx = max(mx, cost_function(i));
	while(gen <= mxitr) {
		cout << "this is generation : " << gen << "\n";
		selection();
		reproduction();
		mutation();
		current_pop = sz(population);
		rep(i, 0, current_pop){
			int cost = cost_function(i);
			//cout << "solution : " << i << " ";
			//for(int gene : population[i]) cout << gene;
			//cout << "\n" << "fitness is : " << cost << "\n";
			mx = max(mx, cost);
			if(cost == bit_num) return cost;
		}
		parent.clear();
		children.clear();
		gen++;
	}
	return mx;
}

int main(){
	srand(time(NULL));
	cout << "best sol is: " << solve();
	return 0;
}