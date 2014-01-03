#ifndef CONCEPTS_H
#define CONCEPTS_H

namespace CoCoHe{

	//! A concept that describes a class that implements the solution to a given problem
	/*!
		\author Nicola Pezzotti
	*/
	class SolverConcept{
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
	
	class MulticaseSolverPolicyConcept{
		template <class Stream>
		static int getNofTestCase(Stream& stream){return 0;}
		template <class Stream>
		static void writeDecoratedOutput(Stream& stream, const std::string& str, int testCase){}
	};

}

#endif