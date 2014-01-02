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
	
	

}

#endif