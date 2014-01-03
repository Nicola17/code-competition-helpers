#ifndef MULTICASESOLVER_H
#define MULTICASESOLVER_H

#include <sstream>

namespace CoCoHe{

	template <class Solver, class Policy>
	class MulticaseSolver{
	public:
		typedef Solver solver_type;
		typedef typename Solver::Input 	solver_input_type;
		typedef typename Solver::Output	solver_output_type;
		typedef typename Solver::Param 	solver_param_type;
		
	public:
		template <class InStream, class OutStream, class LogStream>
		static void solve(InStream& in, OutStream& out, LogStream& log = 0, const solver_param_type& param = solver_param_type()){
			//Get # of test case
			const int nTestCase(Policy::getNofTestCase(in));
			{
				log << "# of test case: " << nTestCase << "\n";
			}
			
			for(int tc = 0; tc < nTestCase; ++tc){
				{
					log << "Solving test case " << (tc+1) << "... ";
				}
				
				solver_input_type 	input;
				solver_output_type 	output;
				std::stringstream 	sstream;
				
				Solver::fetchInput(in,input);
				Solver::solve(input,output,param);
				Solver::writeOutput(sstream,output);
				
				Policy::writeDecoratedOutput(out,sstream.str(),tc+1);
				{
					log << "done\n";
				}
			}
			
		}
	};


}

#endif