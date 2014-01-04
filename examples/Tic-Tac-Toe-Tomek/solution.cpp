#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

#include "../../include/Concepts.h"
#include "../../include/MulticaseSolver.h"
#include "../../include/MulticaseSolverPolicies.h"


/************* SOLUTION *****************/
class TicTacToeTomekSolver{
public:
	static const int N = 4;
// Problem definition
	class Input{
	public:
		Input():_board(N,std::vector<char>(N)){}
		std::vector<std::vector<char> > _board;
	};
	class Output{
	public:
		Output():_xWins(false),_oWins(false),_ended(true){}
		bool _xWins;
		bool _oWins;
		bool _ended;
	};
	class Param{};
public:
// Fetch input
	template <class Stream>
	static void fetchInput(Stream& stream, Input& input){
		char e;
		for(int j = 0; j < N; ++j){
			for(int i = 0; i < N; ++i)
				stream >> input._board[j][i];
			stream.get(e);
		}
		stream.get(e);
	}
// Solution
	static void solve(const Input& input, Output& output, const Param& param = Param()){
		//check
		for(int j = 0; j < N; ++j){
			for(int i = 0; i < N; ++i){
				char c = input._board[j][i];
				if(!(c == '.' || c == 'X' || c == 'O' || c == 'T'))
					throw std::logic_error("invalid input");
				if(c == '.')
					output._ended = false;
			}
		}
		
		for(int i = 0; i < N; ++i){
			if(!output._xWins) output._xWins = checkColumn(input,i,'X','T');
			if(!output._oWins) output._oWins = checkColumn(input,i,'O','T');
			if(!output._xWins) output._xWins = checkRow(input,i,'X','T');
			if(!output._oWins) output._oWins = checkRow(input,i,'O','T');
		}
		if(!output._xWins) output._xWins = checkDiag1(input,'X','T');
		if(!output._oWins) output._oWins = checkDiag1(input,'O','T');
		if(!output._xWins) output._xWins = checkDiag2(input,'X','T');
		if(!output._oWins) output._oWins = checkDiag2(input,'O','T');
	
	}
	
	static bool checkColumn(const Input& input, int i, char player, char jolly){
		for(int j = 0; j < N; ++j){
			if(input._board[j][i] != player && input._board[j][i] != jolly)
				return false;
		}
		return true;
	} 
	static bool checkRow(const Input& input, int j, char player, char jolly){
		for(int i = 0; i < N; ++i){
			if(input._board[j][i] != player && input._board[j][i] != jolly)
				return false;
		}
		return true;
	}
	static bool checkDiag1(const Input& input, char player, char jolly){
		for(int i = 0; i < N; ++i){
			if(input._board[i][i] != player && input._board[i][i] != jolly)
				return false;
		}
		return true;
	} 	
	static bool checkDiag2(const Input& input, char player, char jolly){
		for(int i = 0; i < N; ++i){
			if(input._board[i][N-i-1] != player && input._board[i][N-i-1] != jolly)
				return false;
		}
		return true;
	} 	
	
	
// Write output
	template <class Stream>
	static void writeOutput(Stream& stream, Output& output){ 
		if(output._xWins){
			stream << "X won";
			return;
		}
		if(output._oWins){
			stream << "O won";
			return;
		}
		if(output._ended){
			stream << "Draw";
		}else{
			stream << "Game has not completed";
		}
	}
};

/************* Main *****************/
int main(int argc, char *argv[]){
	try{
		if(argc!=3){
			std::cout << "Wrong number of parameter";
			return 1;
		}
		typedef	CoCoHe::MulticaseSolver<TicTacToeTomekSolver,CoCoHe::GoogleCodeJam2013SolverPolicy> MulticaseSolver;
		
		std::ifstream inputStream(argv[1]);
		std::ofstream outputStream(argv[2]);
		
		MulticaseSolver::solve(inputStream,outputStream,std::cout);
		
	}catch(...){
		return 2;
	}
	return 0;
}