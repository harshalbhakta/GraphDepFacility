////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Display.cpp (ver 1.0)  -  Module to handle formatted output for Graph and Vertex class.					  // 																					   
//		 																									  //
//	Language		:   Visual C++, 2010																	  //
//	Platform		:   Toshiba Satellite (R25-S3503), Windows 7 Professional								  //
//	Application		:	CSE687 - Project #3 - Dependency Graph Facility, Spring 2011						  //
//	Author			:   Harshal Bhakta, Syracuse University.												  //
//	E-mail			:   harshal.c.bhakta@gmail.com															  //
//	Cell			:   714-876-4273																		  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Display.h"

//-------------------------<TEST STUB>-------------------------//

#ifdef TEST_DISPLAY

void main ( int argc, char* argb[] )
{
	Vertex<int,int> vInt_1;
	vInt_1.SetValue(1);

	Vertex<int,int> vInt_2;
	vInt_2.SetValue(2);

	Vertex<int,int> vInt_3;
	vInt_3.SetValue(3);

	vInt_1.AddEdge(vInt_1,0);
	vInt_1.AddEdge(vInt_2,1);
	vInt_1.AddEdge(vInt_3,2);

	vInt_2.AddEdge(vInt_3,3);

	vInt_3.AddEdge(vInt_1,4);

	Vertex<std::string,std::string> vString_1;
	vString_1.SetValue("Vertex String 1");

	Vertex<std::string,std::string> vString_2;
	vString_2.SetValue("Vertex String 2");

	Vertex<std::string,std::string> vString_3;
	vString_3.SetValue("Vertex String 3");

	vString_1.AddEdge(vString_1,"edge 1");
	vString_1.AddEdge(vString_3,"edge 2");
	
	vString_2.AddEdge(vString_1,"edge 3");
	vString_2.AddEdge(vString_3,"edge 4");

	vString_3.AddEdge(vString_1,"edge 5");
	vString_3.AddEdge(vString_1,"edge 6");

	Display dp;

	std::cout<<"\n\n Testing Vertex Print : ";

	std::cout << "\n "<< std::string(55,'=');

	dp.PrintVertex(vInt_1);
	dp.PrintVertex(vInt_2);
	dp.PrintVertex(vInt_3);

	dp.PrintVertex(vString_1);
	dp.PrintVertex(vString_2);
	dp.PrintVertex(vString_3);

	Graph<int,int> g;
	g.addVertex(vInt_1);
	g.addVertex(vInt_2);
	g.addVertex(vInt_3);

	std::cout<<"\n\n Testing Graph Print Normal Mode : ";

	std::cout << "\n "<< std::string(55,'=');

	dp.PrintGraph(g);

	std::cout<<"\n\n Testing Graph Print Verbose Mode : ";

	std::cout << "\n "<< std::string(55,'=');

	dp.PrintGraphVerbose(g);

}

#endif