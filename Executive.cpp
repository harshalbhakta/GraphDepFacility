////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Executive.cpp (ver 1.0)  -  Executive Module that Starts the Testing & Prints Summay output.	     		  // 																					   
//		 																									  //
//	Language		:   Visual C++, 2010																	  //
//	Platform		:   Toshiba Satellite (R25-S3503), Windows 7 Professional								  //
//	Application		:	CSE687 - Project #1 - CodeMetricsAnalyzer, Spring 2011								  //
//	Author			:   Harshal Bhakta, Syracuse University.												  //
//	E-mail			:   harshal.c.bhakta@gmail.com															  //
//	Cell			:   714-876-4273																		  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Executive.h"

/////////////////////////////////////////////////////////////
// Function to generate Graph from XML Files.
void Executive::GenerateGraphFromXMLFiles(const std::vector<std::string>& _files)
{
	Graph<std::string,std::string> xml_graph;

	try
	{
		GraphAlgorithm::GenerateGraphFromXML(_files,xml_graph);

		std::cout<<"\n Generated Graph " << "\n "<< std::string(55,'=');

		Display dp;
	
		dp.PrintGraph(xml_graph);
	}
	catch (std::exception& ex)
	{
		std::cout<<"\n Error Generating Graph from XML" << ex.what() ;
	}

	VertexFunctor<std::string,std::string> vf;

	std::cout<<"\n DepthFirstSearch on the Graph generated from XML \n "<< std::string(55,'=');
	std::cout<<"\n Note: Here DepthFirstSearch enunciates each Vertex and Edge.\n So if a Vertex is already traversed, the edge reaching \n it again is enunciated but repeating vertex is not." <<"\n "<< std::string(55,'-');

	try 
	{
		xml_graph.DepthFirstSearch(vf,xml_graph.VERTEX_EDGE);
	
		CondensedOperation<std::string,std::string> cdOp;
	
		xml_graph.CreateCondensedGraph(cdOp);	

		SearchOnXMLGeneratedGraph(xml_graph);
	}
	catch (std::exception& ex)
	{
		std::cout<<"\n Error Performing operation on Graph" << " " << ex.what();
	}
}

/////////////////////////////////////////////////////////////
// Function to test requirement 4 for Project 3.
void Executive::TestRequirement4()
{
	std::cout << "\n\n Testing Requirement 4 : " << " \n "
				  << std::string(55,'=') << std::endl;
	
	std::cout << "\n Testing Vertex Copy And Assignment : " << " \n " << std::string(55,'=') << std::endl;
	TestVertexCopyAndAssignment();

	std::cout << "\n Testing Graph Copy And Assignment : " << " \n " << std::string(55,'=') << std::endl;
	TestGraphCopyAndAssignment();

	std::cout << "\n Testing DepthFirstSearch : " << " \n " << std::string(55,'=') << std::endl;
	TestDepthFirstSearch();
}


/////////////////////////////////////////////////////////////
// Function to test requirement 5 for Project 3.
void Executive::TestRequirement5()
{
	std::cout << "\n\n Testing Requirement 5 : " << " \n "
				  << std::string(55,'=') << std::endl;

	std::cout << "\n Testing Condensed Graph + Strong Components + Topological Sort : " << " \n " << std::string(55,'=') << std::endl;	
	TestCondensedGraph();
}

/////////////////////////////////////////////////////////////
// Function to test requirement 7 for Project 3.
void Executive::TestRequirement7()
{

	std::cout << "\n\n Testing Requirement 7 : " << " \n "
				  << std::string(55,'=') << std::endl;

	std::cout << "\n Testing Global Algorithm for Vertex Search : " << " \n " << std::string(55,'=') << std::endl;	
	TestVertexSearch();

	std::cout << "\n Testing Global Algorithm for Edge Search : " << " \n " << std::string(55,'=') << std::endl;	
	TestEdgeSearch();
}

/////////////////////////////////////////////////////////////
// Function to test requirement 7 for Project 3.
void Executive::TestVertexSearch()
{
	Graph<std::string,std::string> g;

	Vertex<std::string,std::string> v1, v2, v3, v4, v5;
	v1.SetValue("Parser");
	v2.SetValue("Parser");
	v3.SetValue("Parser");
	v4.SetValue("Package");
	v5.SetValue("PackageHandler");
	v1.AddEdge(v4,"DependsOn");
	v1.AddEdge(v5,"DependsOn");

	v4.AddEdge(v5,"DependsOn");

	g.addVertex(v1);
	g.addVertex(v2);
	g.addVertex(v3);
	g.addVertex(v4);
	g.addVertex(v5);	

	Display dp;

	dp.PrintGraphVerbose(g);

	std::cout << "\n Search using Vertex Value = Parser : ";

	GraphAlgorithm::VertexComparatorCustom<std::string,std::string,std::string> _comp; 

	std::vector<Vertex<std::string,std::string>> _vertex = GraphAlgorithm::FetchVertexCustomSearch(g,_comp,"Parser");
	std::cout<<"\n\n Entries Found : "<< _vertex.size() << "\n";
	std::cout << std::string(55,'-') << "\n";
	
	for ( int i = 0 ; i < (int) _vertex.size() ; i++ )
	{
		std::cout<<" Vertex Id = "<< _vertex[i].GetId() << "\n" ;	
	}
}

/////////////////////////////////////////////////////////////
// Function to test requirement 7 for Project 3.
void Executive::TestEdgeSearch()
{
	Graph<std::string,std::string> g;

	Vertex<std::string,std::string> v1, v2, v3, v4, v5;
	v1.SetValue("Parser");
	v2.SetValue("Parser");
	v3.SetValue("Parser");
	v4.SetValue("Package");
	v5.SetValue("PackageHandler");

	v1.AddEdge(v4,"Edge1");
	v1.AddEdge(v5,"Edge1");

	v4.AddEdge(v5,"DependsOn");

	g.addVertex(v1);
	g.addVertex(v2);
	g.addVertex(v3);
	g.addVertex(v4);
	g.addVertex(v5);	

	Display dp;

	dp.PrintGraphVerbose(g);

	std::cout << "\n Search using Edge Value = Edge1 : ";

	GraphAlgorithm::EdgeComparatorCustom<std::string,std::string,std::string> _comp; 

	std::vector<GraphAlgorithm::EdgeItem<std::string,std::string>> edge_items = GraphAlgorithm::FetchEdgesCustomSearch(g,_comp,"Edge1");
	std::cout<<"\n\n Entries Found : "<< edge_items.size() << "\n";
	std::cout << std::string(55,'-') << "\n";
	
	for ( int i = 0 ; i < (int) edge_items.size() ; i++ )
	{
		std::cout<<" From Vertex = " << edge_items[i].from_vertex.GetId() << " Edge = "<< edge_items[i].edge << " To Vertex = " << edge_items[i].to_vertex.GetId() << "\n" ;	
	}
	std::cout<<"\n";
}

/////////////////////////////////////////////////////////////
// Function to test Vertex Copy and Assignment Operation.
void Executive::TestVertexCopyAndAssignment()
{
	Display dp;

	std::cout << "\n Vertex 1: Created with value 10. Edge to Vertex 2,3" << " \n";
	std::cout << " Vertex 2: Created with value 20. Edge to Vertex 3" << " \n";
	std::cout << " Vertex 3: Created with value 30. Edge to Vertex 1" << " \n";

	Vertex<int,int> v1 , v2 , v3 , v5;
	v1.SetValue(10);
	v2.SetValue(10);
	v3.SetValue(10);

	v1.AddEdge(v2,1); 
	v1.AddEdge(v3,2);
	v2.AddEdge(v3,1); 
	v3.AddEdge(v1,1);

	dp.PrintVertex(v1);
	dp.PrintVertex(v2);
	dp.PrintVertex(v3);

	std::cout << "\n\n Copying v1 to v4 using Copy Constructor & v2 to v5 using assignment : " << " \n " << std::string(55,'-') << std::endl;

	Vertex<int,int> v4 = v1;
	v5 = v2;

	dp.PrintVertex(v1);
	dp.PrintVertex(v4);
	dp.PrintVertex(v2);
	dp.PrintVertex(v5);

	std::cout << "\n\n Modifying v1, v2 & v5 to demonstrate copies are independent : " << " \n " << std::string(55,'-') << std::endl;

	v1.AddEdge(v2,100);
	v2.AddEdge(v1,5);
	v5.AddEdge(v3,10);

	dp.PrintVertex(v1);
	dp.PrintVertex(v4);
	dp.PrintVertex(v2);
	dp.PrintVertex(v5);

}

/////////////////////////////////////////////////////////////
// Function to test Graph Copy and Assignment Operation.
void Executive::TestGraphCopyAndAssignment()
{
	Display dp;
	Graph<std::string,std::string> g;

	std::cout << "\n Graph 1 Created using v1,v2,v3" << " \n";

	Vertex<std::string,std::string> v1, v2, v3, v4 , v5;
	v1.SetValue("Node1");
	v2.SetValue("Node2");
	v3.SetValue("Node3");
	v1.AddEdge(v2,"Edge1"); 
	v1.AddEdge(v3,"Edge2");
	v2.AddEdge(v3,"Edge3"); 
	v3.AddEdge(v1,"Edge4");
	v4.SetValue("NewNode4");
	v5.SetValue("NewNode5");

	g.addVertex(v1);
	g.addVertex(v2);
	g.addVertex(v3);

	dp.PrintGraph(g);

	std::cout << "\n\n Copying graph g to g1 using Copy Constructor & g to g2 using assignment : " << " \n "
				  << std::string(55,'-') << std::endl;
	Graph<std::string,std::string> g1 = g;
	Graph<std::string,std::string> g2;
	g2 = g;
	
	dp.PrintGraph(g);
	dp.PrintGraph(g1);
	dp.PrintGraph(g2);
	
	std::cout << "\n\n Modifying g, g1 & g2 to demonstrate copies are independent : " << " \n "
				  << std::string(55,'-') << std::endl;
	v1.SetValue("ModifiedNode1");
	g.addVertex(v1);
	g1.addVertex(v4);
	g2.addVertex(v5);

	dp.PrintGraph(g);
	dp.PrintGraph(g1);
	dp.PrintGraph(g2);
}

/////////////////////////////////////////////////////////////
// Function to test DepthFirstSearch.
void Executive::TestDepthFirstSearch()
{
	Graph<std::string,std::string> g;

	std::cout<<"\n Sample Graph taken for testing as below : \n";
	std::cout<<"\n   [ Node1 ] <------- [ Node3 ]   ";
	std::cout<<"\n       |\t\t^   ";
	std::cout<<"\n       |\t\t|   ";
	std::cout<<"\n       V\t\t|";
	std::cout<<"\n   [ Node2 ] -----------+";
	std::cout<<"\n       |	";
	std::cout<<"\n       |	";
	std::cout<<"\n       V	";
	std::cout<<"\n   [ Node4 ] \n\n";

	Vertex<std::string,std::string> v1, v2, v3, v4;
	v1.SetValue("Node1");
	v2.SetValue("Node2");
	v3.SetValue("Node3");
	v4.SetValue("Node4");

	v3.AddEdge(v1,"Edge1");
	v1.AddEdge(v2,"Edge2");
	v2.AddEdge(v3,"Edge3");
	v2.AddEdge(v4,"Edge4");

	g.addVertex(v1);
	g.addVertex(v2);
	g.addVertex(v3);
	g.addVertex(v4);

	VertexFunctor<std::string,std::string> vf;

	std::cout<<"\n Depth First Search : Vertex Only \n";
	g.DepthFirstSearch(vf,g.VERTEX_ONLY);

	std::cout<<"\n Depth First Search : Edge Only \n";
	g.DepthFirstSearch(vf,g.EDGE_ONLY);

	std::cout<<"\n Depth First Search : Vertex-Edge \n";
	g.DepthFirstSearch(vf,g.VERTEX_EDGE);

	std::cout<<"\n";
}

/////////////////////////////////////////////////////////////
// Function to test condensed Graph + Strong Components + Topoligical Sort.
void Executive::TestCondensedGraph()
{
	Graph<std::string,std::string> g;

	Vertex<std::string,std::string> v1, v2, v3, v4;
	v1.SetValue("Node1");
	v2.SetValue("Node2");
	v3.SetValue("Node3");
	v4.SetValue("Node4");

	v3.AddEdge(v1,"Edge1");
	v1.AddEdge(v2,"Edge2");
	v2.AddEdge(v3,"Edge3");
	v2.AddEdge(v4,"Edge4");

	g.addVertex(v1);
	g.addVertex(v2);
	g.addVertex(v3);
	g.addVertex(v4);

	CondensedOperation<std::string,std::string> co;

	g.CreateCondensedGraph(co);
}

//-----------------TEST STUB---------------------//

#ifdef TEST_EXECUTIVE

int main(int argc,char* argv[])
{



}

#endif 
