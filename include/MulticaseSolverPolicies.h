#ifndef MULTICASESOLVERPOLICIES_H
#define MULTICASESOLVERPOLICIES_H

#include <string>

namespace CoCoHe{

	class GoogleCodeJam2013SolverPolicy{
	public:
		template <class Stream>
		static int getNofTestCase(Stream& stream){
			int res(0);
			stream >> res;
			return res;
		}
		
		template <class Stream>
		static void writeDecoratedOutput(Stream& stream, const std::string& str, int testCase){
			stream << "Case #" << testCase << ": " << str << std::endl;
		}
	};

}

#endif