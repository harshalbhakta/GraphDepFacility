////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// main.cpp (ver 1.0)  -  Source File to test CodeMetricsAnalyzer - Provider of function main()				  // 																					   
//		 																									  //
//	Language		:   Visual C++, 2010																	  //
//	Platform		:   Toshiba Satellite (R25-S3503), Windows 7 Professional								  //
//	Application		:	CSE687 - Project #3 - Dependency Graph Facility, Spring 2011						  //
//	Author			:   Harshal Bhakta, Syracuse University.												  //
//	E-mail			:   harshal.c.bhakta@gmail.com															  //
//	Cell			:   714-876-4273																		  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
* Module Operations:
* ==================
* - main() : Dependency Graph Facility Application start point.
* - Uses 'CmdLineArgs' to check and store command line arguments. 
* - Calls Executive to Test Requirements for Project 3.

* Build Process:
* ==============
* devenv GraphDepFacility.sln /rebuild debug
* 
* Maintenance History:
* ====================
* ver 1.0 : 11 Apr 2011
*
* - Initial Release
*/

#include "CmdLineArgs.h"
#include "Executive.h"


///////////////////////////////////////////////////////////////
// Print Project Header.
void PrintHeader()
{
		std::cout<<std::endl<<"--------------------------------------------------------";
		std::cout<<std::endl<<"	    Graph Dep Facility : GDF , v1.0	";
		std::cout<<std::endl<<"--------------------------------------------------------";
		std::cout<<std::endl<<"C++ Template Graph Facility		  Harshal Bhakta	";
		std::cout<<std::endl<<"--------------------------------------------------------";
}

///////////////////////////////////////////////////////////////
// Main function for Project 3.
int main(int argc,char* argv[])
{
	try 
	{
		CmdLineArgs cla;		

		if(cla.ValidateAndStoreArgs(argc,argv))
		{
			PrintHeader();

			std::cout<<"\n Fetching Files based on criteria ";
			std::cout << "\n "<< std::string(55,'=');

			std::vector<std::string> ptrFiles = cla.getFiles();

			std::cout<<"\n Building Graph from XML Files ";

			std::cout << "\n "<< std::string(55,'=');

			Executive ex;

			ex.GenerateGraphFromXMLFiles(ptrFiles);

			ex.TestRequirement4();

			ex.TestRequirement5();

			ex.TestRequirement7();
		}
		else
		{
			cla.printManual();
		}
	}
	catch ( std::exception ex)
	{ std::cout<<"Application ended in error : "<<ex.what(); }

}
