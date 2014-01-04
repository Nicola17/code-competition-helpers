#include <iostream>
#include <fstream>
#include <stdexcept>

#include "../include/MulticaseSolver.h"
#include "../include/MulticaseSolverPolicies.h"


/************* SOLUTION *****************/
class MySolver{
public:
	class Input{};
	class Output{};
	class Param{};
public:
	template <class Stream>
	static void fetchInput(Stream& stream, Input& input){}
	static void solve(const Input& input, Output& output, const Param& param = Param()){}
	template <class Stream>
	static void writeOutput(Stream& stream, Output& output){ stream << "- - - -";}
};
/************* Main *****************/
int main(int argc, char *argv[]){
	try{
		if(argc!=3){
			std::cout << "Wrong number of parameter";
			return 1;
		}
		typedef	CoCoHe::MulticaseSolver<MySolver,CoCoHe::GoogleCodeJam2013SolverPolicy> MulticaseSolver;
		
		std::ifstream inputStream(argv[1]);
		std::ofstream outputStream(argv[2]);
		
		MulticaseSolver::solve(inputStream,outputStream,std::cout);
		
	}catch(...){
		return 2;
	}
	return 0;
}