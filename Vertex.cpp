////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Vertex.h (ver 1.0)  - Templatized Class to hold vertex information = NodeValue +  Edge					  // 																					   
//		 																									  //
//	Language		:   Microsoft Visual C++, 2010															  //
//	Platform		:   Toshiba Satellite (R25-S3503), Windows 7 Professional								  //
//	Application		:	CSE687 - Project #3 - Dependency Graph Facility, Spring 2011						  //
//	Author			:   Harshal Bhakta, Syracuse University.												  //
//	E-mail			:   harshal.c.bhakta@gmail.com															  //
//	Cell			:   714-876-4273																		  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Vertex.h"

//--------------<<< TEST STUB >>>----------------//

#ifdef TEST_VERTEX

#include <iostream>
#include <string>

///////////////////////////////////////////////////////////////
// Test-Stub function to print vertex.
template <typename VertexType, typename EdgeType>
void printVertex(const Vertex<VertexType,EdgeType>& _vertex)
{
	std::cout<<"\n";

	std::cout<<" Vertex Id: "<<_vertex.GetId()<<" - "<<"Vertex Value: "<<_vertex.GetVertex();

	std::cout << "\n "<< std::string(55,'-');

	std::vector<std::pair<int, std::pair<int,EdgeType>>> edges = _vertex.GetEdges();

	for ( int i = 0 ; i < (int)edges.size() ; i++ )
	{
		std::cout<<"\n Edge-> RefId ( "<<edges[i].first <<" ) |"<<" Id ( "<<edges[i].second.first <<" ) |"<< " Value ( " <<edges[i].second.second << " )";
	}

	std::cout<<"\n";
}

///////////////////////////////////////////////////////////////
// Test-Stub function to test Vertex class. 
int main (int argc, char* argv[])
{
	std::cout<<"\n\n Creating Vertex<int,int> and assigning value to '1'";

	std::cout << "\n "<< std::string(55,'=');

	Vertex<int,int> v1;
	v1.SetValue(1);

	printVertex(v1);

	std::cout<<"\n\n Copy Construct Vertex : v1->v2 (Id Remains Same) \n Change Value of v2 to '2' ";

	std::cout << "\n "<< std::string(55,'=');

	Vertex<int,int> v2 = v1;
	v2.SetValue(2);

	printVertex(v1);

	printVertex(v2);

	std::cout<<"\n\n Adding Edge v1->v3 : Does not affect v1's copy v2.";

	std::cout << "\n "<< std::string(55,'=');

	Vertex<int,int> v3;
	v3.SetValue(10);

	v1.AddEdge(v3,5);

	printVertex(v1);

	printVertex(v2);

	std::cout<<"\n\n Adding Edge v2->v4 : Does not affect v1.";

	std::cout << "\n "<< std::string(55,'=');

	Vertex<int,int> v4 ;
	v4.SetValue(20);
	
	v2.AddEdge(v4,20);
	
	printVertex(v1);

	printVertex(v2);

	std::cout<<"\n\n Adding Edge again from v2->v4 overwrites edge value. ( 20->40 )";

	std::cout << "\n "<< std::string(55,'=');

	printVertex(v2);

	v2.AddEdge(v4,40);

	printVertex(v2);

	std::cout<<"\n\n Assigning new Id to v4. Reset Id.";

	std::cout << "\n "<< std::string(55,'=');

	printVertex(v4);

	v4.ResetId();

	printVertex(v4);

	std::cout<<"\n\n Clearing edges for v1.";

	std::cout << "\n "<< std::string(55,'=');

	printVertex(v1);

	v1.ClearEdges();

	printVertex(v1);

	std::cout<<"\n\n Get Vertex Value using GetVertex() for v1.";

	std::cout << "\n "<< std::string(55,'=');

	printVertex(v1);

	std::cout<< " Vertex Value = " << v1.GetVertex();

	std::cout<<"\n\n Get Vertex Value using GetVertex() for v1.";

	std::cout << "\n "<< std::string(55,'=');

	printVertex(v1);

	std::cout<< " Id = " << v1.GetId();

	std::cout<<"\n\n Test GetEdges() for v2.";

	std::cout << "\n "<< std::string(55,'=');

	v2.AddEdge(v3,5);
	v2.AddEdge(v4,5);

	std::vector<std::pair<int,std::pair<int,int>>> ed = v2.GetEdges();

	printVertex(v2);

	for ( int i = 0 ; i < (int)ed.size() ; i++ )
	{
		 std::cout<<"\n Edge-> RefId ( "<<ed[i].first <<" ) |"<<" Id ( "<<ed[i].second.first <<" ) |"<< " Value ( " <<ed[i].second.second << " )";
	}

	std::cout<<"\n \n";
}

#endif