#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <stdexcept>
#include <iterator>


#include "../../include/MulticaseSolver.h"
#include "../../include/MulticaseSolverPolicies.h"

/************* SOLUTION *****************/
class LawnmowerSolver{
public:
// Problem definition
	class Input{
	public:
		Input(){}
		void reset(int r, int c){_lawn = std::vector<std::vector<int> >(r,std::vector<int>(c));}
		std::vector<std::vector<int> > _lawn;
	};
	class Output{
	public:
		Output():_validConf(false){}
		bool _validConf;
	};
	class Param{};
public:
// Fetch input
	template <class Stream>
	static void fetchInput(Stream& stream, Input& input){
		int rows(0),cols(0);
		stream >> rows;
		stream >> cols;
		input.reset(rows,cols);
		for(int j = 0; j < rows; ++j)
			for(int i = 0; i < cols; ++i)
				stream >> input._lawn[j][i];
	}
public:
// Solution
	static void solve(const Input& input, Output& output, const Param& param = Param()){
		std::set<int> heightSet;
		generateHeightSet(input,heightSet);
		
		output._validConf = false;
		Input wrkInput = input;
		for (std::set<int>::iterator it = heightSet.begin(); it != heightSet.end(); ++it){
			//int nextW = *(std::next(it)); //C++11
			std::set<int>::iterator itn = it;
			++itn;
			int nextW = *itn;
			if(!processHeight(wrkInput,*it,nextW))
				return;
		}
		output._validConf = true;
	}
	
private:
	static void generateHeightSet(const Input& input, std::set<int>& heightSet){
		int rows = input._lawn.size();
		int cols = input._lawn[0].size();
		
		for(int j = 0; j < rows; ++j)
			for(int i = 0; i < cols; ++i)
				heightSet.insert(input._lawn[j][i]);
	}
	
	static bool processHeight(Input& input, int height, int nextHeight){
		int rows = input._lawn.size();
		int cols = input._lawn[0].size();
		
		std::vector<std::vector<bool> > visitedOnCol(rows,std::vector<bool>(cols,false));
		for(int j = 0; j < rows; ++j)
			for(int i = 0; i < cols; ++i){
				if(input._lawn[j][i]!=height)
					continue;
				bool validRow = true;
				bool validCol = true;
				if(!visitedOnCol[j][i])
					for(int j_n = 0; j_n < rows; ++j_n){
						if(input._lawn[j_n][i]!=height){
							validCol = false;
							break;
						}
					}
				
				for(int i_n = 0; i_n < cols; ++i_n){
					if(input._lawn[j][i_n]!=height){
						validRow = false;
						break;
					}
				}
				if(!validRow&&!validCol)
					return false;
					
				if(validRow){
					break;
				}
				if(validCol){
					for(int j_n = 0; j_n < rows; ++j_n)
						visitedOnCol[j_n][i] = true;
				}
				
			}
			
		for(int j = 0; j < rows; ++j)
			for(int i = 0; i < cols; ++i)
				if(input._lawn[j][i]==height)
					input._lawn[j][i]=nextHeight;
		return true;
	}

public:
// Write output
	template <class Stream>
	static void writeOutput(Stream& stream, Output& output){ 
		if(output._validConf)
			stream << "YES";
		else
			stream << "NO";
	}
};

/************* Main *****************/
int main(int argc, char *argv[]){
	try{
		if(argc!=3){
			std::cout << "Wrong number of parameter";
			return 1;
		}
		typedef	CoCoHe::MulticaseSolver<LawnmowerSolver,CoCoHe::GoogleCodeJam2013SolverPolicy> MulticaseSolver;
		
		std::ifstream inputStream(argv[1]);
		std::ofstream outputStream(argv[2]);
		
		MulticaseSolver::solve(inputStream,outputStream,std::cout);
		
	}catch(...){
		return 2;
	}
	return 0;
}