////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Graph.cpp (ver 1.0)- 	Templatized class to be used for implementing Graph Data structure.				  // 																					   
//		 																									  //
//	Language		:   Microsoft Visual C++, 2010															  //
//	Platform		:   Toshiba Satellite (R25-S3503), Windows 7 Professional								  //
//	Application		:	CSE687 - Project #3 - Dependency Graph Facility, Spring 2011						  //
//	Author			:   Harshal Bhakta, Syracuse University.												  //
//	E-mail			:   harshal.c.bhakta@gmail.com															  //
//	Cell			:   714-876-4273																		  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Graph.h"

//--------------<<< TEST STUB >>>----------------//

#ifdef TEST_GRAPH

//////////////////////////////////////////////////////////////
// Function to print the Repository Location.
template <typename VertexTypeAlgo,typename EdgeTypeAlgo>
void PrintGraph(const Graph<VertexTypeAlgo,EdgeTypeAlgo>& _graph)
{
	std::cout<<"\n";

	std::cout<<" Graph Id: "<<_graph.GetId();

	std::cout << "\n "<< std::string(55,'=');

	const std::map<int,Vertex<VertexTypeAlgo,EdgeTypeAlgo>>& graph_adjacency = _graph.GetAdjacencyList();

	std::map<int,Vertex<VertexTypeAlgo,EdgeTypeAlgo>>::const_iterator it = graph_adjacency.begin();

	while ( it != graph_adjacency.end() )
	{
	
		Vertex<VertexTypeAlgo,EdgeTypeAlgo> _vertex = it->second;

		std::cout<<"\n\n Vertex - [ "<<_vertex.GetVertex()<<" ] ";

		std::cout << "\n "<< std::string(55,'-');

		std::vector<std::pair<int, std::pair<int,EdgeTypeAlgo>>> edges = _vertex.GetEdges();

		for ( int i = 0 ; i < (int)edges.size() ; i++ )
		{
			std::map<int,Vertex<VertexTypeAlgo,EdgeTypeAlgo>>::const_iterator it = graph_adjacency.find(edges[i].first);

			if ( it != graph_adjacency.end() )
			{
				std::cout<<"\n [ "<<_vertex.GetVertex()<<" ] " << "---" << edges[i].second.second << "--->"<<" [ " << it->second.GetVertex() << " ]" ;
			}
		}

		++it;	
	}

	std::cout<<"\n";
}

class CustomElement {

private : 
	int num;
	std::string name;
};

int main (int argc, char* argv[])
{	
	std::cout<<" Testing Graph Class";

	std::cout << "\n "<< std::string(55,'=');

	std::cout<<"\n Creating Vertexes for the Graph ";

	Graph<std::string,std::string> graph_test_file;
	
	Vertex<std::string,std::string> vt1;
	vt1.SetValue("main");
	
	Vertex<std::string,std::string> vt2;
	vt2.SetValue("CPPXPath");
	
	Vertex<std::string,std::string> vt3;
	vt3.SetValue("CPPXmlNode");

	Vertex<std::string,std::string> vt4;
	vt4.SetValue("CPPXmlTextNode");

	Vertex<std::string,std::string> vt5;
	vt5.SetValue("VectorOfString");

	Vertex<std::string,std::string> vt6;
	vt6.SetValue("TestString");

	Vertex<std::string,std::string> vt7;
	vt7.SetValue("circular");
	
	vt1.AddEdge(vt2,"Path");

	vt2.AddEdge(vt3,"Path");
	vt2.AddEdge(vt4,"Path");
	vt2.AddEdge(vt5,"Path");
	
	vt3.AddEdge(vt6,"Path");
	vt3.AddEdge(vt2,"Path");

	vt4.AddEdge(vt3,"Path");
	
	vt5.AddEdge(vt7,"Path");

	vt7.AddEdge(vt5,"Path");

	graph_test_file.addVertex(vt1);
	graph_test_file.addVertex(vt2);
	graph_test_file.addVertex(vt3);
	graph_test_file.addVertex(vt4);
	graph_test_file.addVertex(vt5);
	graph_test_file.addVertex(vt6);
	graph_test_file.addVertex(vt7);

	std::cout<<" Printing the created Graph";

	std::cout << "\n "<< std::string(55,'=');

	PrintGraph(graph_test_file);

	std::cout<<"\n Copying Graph: Copied Graph Displayed Below ";

	std::cout << "\n "<< std::string(55,'=');

	Graph<std::string,std::string> graphCopy = graph_test_file;

	PrintGraph(graphCopy);

	VertexFunctor<std::string,std::string> vft;

	std::cout<<"\n Performing Depth First Search on Graph ";

	std::cout << "\n "<< std::string(55,'=');

	graph_test_file.DepthFirstSearch(vft,graph_test_file.VERTEX_EDGE);
	
	CondensedOperation<std::string,std::string> cot;

	std::cout<<"\n\n Creating condensed graph ";

	std::cout << "\n "<< std::string(55,'=');

	graph_test_file.CreateCondensedGraph(cot);

	std::cout<<"\n \n";
	
	Graph<std::string,std::string> g;

	Vertex<std::string,std::string> v1;
	v1.SetValue("Parser");

	Vertex<std::string,std::string> v2;
	v2.SetValue("Parser");

	Vertex<std::string,std::string> v3;
	v3.SetValue("Semi");

	Vertex<std::string,std::string> v4;
	v4.SetValue("Package");

	Vertex<std::string,std::string> v5;
	v5.SetValue("PackageHandler");

	v1.AddEdge(v2,"DependsOn");
	v1.AddEdge(v3,"DependsOn");

	v4.AddEdge(v5,"K");

	g.addVertex(v1);
	g.addVertex(v2);
	g.addVertex(v3);
	g.addVertex(v4);
	g.addVertex(v5);	

	std::cout<<"\n\n Testing Custom Algorithm to Search Vertex 'Parser' ";

	std::cout << "\n "<< std::string(55,'=');

	PrintGraph(g);

	GraphAlgorithm::VertexComparatorCustom<std::string,std::string,std::string> _comp; 

	std::vector<Vertex<std::string,std::string>> _vertex = GraphAlgorithm::FetchVertexCustomSearch(g,_comp,"Parser");

	std::cout<<"\n Entries Found : "<< _vertex.size() << "\n";
	
	std::cout << std::string(55,'-') << "\n";
	
	for ( int i = 0 ; i < (int) _vertex.size() ; i++ )
	{
		std::cout<<" Vertex Id = "<< _vertex[i].GetId() << "\n" ;	
	}

	std::vector<Vertex<std::string,std::string>> _vertex_normal = GraphAlgorithm::FetchVertex(g,_comp,v1.GetVertex());

	std::cout<<"\n\n Testing Normal Algorithm to Search Vertex 'Parser' ";

	std::cout << "\n "<< std::string(55,'=');

	PrintGraph(g);

	std::cout<<"\n Entries Found : "<< _vertex_normal.size() << "\n";
	
	std::cout << std::string(55,'-') << "\n";
	
	for ( int i = 0 ; i < (int) _vertex_normal.size() ; i++ )
	{
		std::cout<<" Vertex Id = "<< _vertex_normal[i].GetId() << "\n" ;	
	}

	std::vector<Vertex<std::string,std::string>> _vertex_copy = _vertex;

	_vertex_copy.push_back(v4);

	GraphAlgorithm::EdgeComparatorCustom<std::string,std::string,std::string> _comp_edge;

	std::vector<GraphAlgorithm::EdgeItem<std::string,std::string>> edge_items = GraphAlgorithm::FetchEdgesCustomSearch(g,_comp_edge,"K");

	std::cout<<"\n\n Testing Custom Algorithm to Search Edge 'K' ";

	std::cout << "\n "<< std::string(55,'=');

	PrintGraph(g);

	std::cout<<"\n Entries Found : "<< edge_items.size() << "\n";
	
	std::cout << std::string(55,'-') << "\n";
	
	for ( int i = 0 ; i < (int) edge_items.size() ; i++ )
	{
		std::cout<<" From Vertex = " << edge_items[i].from_vertex.GetId() << "Edge = "<< edge_items[i].edge << " To Vertex = " << edge_items[i].to_vertex.GetId() << "\n" ;	
	}

	std::vector<GraphAlgorithm::EdgeItem<std::string,std::string>> edge_items_normal = GraphAlgorithm::FetchEdgesCustomSearch(g,_comp_edge,"K");

	
	std::cout<<"\n\n Testing Normal Algorithm to Search Edge 'K' ";

	std::cout << "\n "<< std::string(55,'=');

	PrintGraph(g);

	std::cout<<"\n Entries Found : "<< edge_items.size() << "\n";
	
	std::cout << std::string(55,'-') << "\n";
	
	for ( int i = 0 ; i < (int) edge_items_normal.size() ; i++ )
	{
		std::cout<<" From Vertex = " << edge_items_normal[i].from_vertex.GetId() << "Edge = "<< edge_items_normal[i].edge << " To Vertex = " << edge_items_normal[i].to_vertex.GetId() << "\n" ;	
	}

	std::vector<Vertex<std::string,std::string>> _vertex_copy_2 ;
	
	_vertex_copy_2 = _vertex;

	_vertex_copy_2.push_back(v5);

	VertexFunctor<std::string,std::string> fv; 

	g.DepthFirstSearch(fv,g.VERTEX_EDGE);

	Graph<std::string,std::string> gCopy = g;

	Graph<std::string,std::string> gCopy_Assign;

	gCopy_Assign = g;

	Graph<int,int> gNew;

	Vertex<int,int> v1New;
	v1New.SetValue(1);

	Vertex<int,int> v2New;
	v2New.SetValue(2);

	Vertex<int,int> v3New;
	v3New.SetValue(3);

	Vertex<int,int> v4New;
	v4New.SetValue(4);

	Vertex<int,int> v5New;
	v5New.SetValue(5);

	Vertex<int,int> v6New;
	v6New.SetValue(6);

	Vertex<int,int> v7New;
	v7New.SetValue(7);

	Vertex<int,int> v8New;
	v8New.SetValue(8);

	v1New.AddEdge(v4New,0);
	v1New.AddEdge(v7New,0);

	v2New.AddEdge(v5New,0);
	v2New.AddEdge(v7New,0);

	v3New.AddEdge(v1New,0);

	v8New.AddEdge(v4New,0);

	v5New.AddEdge(v6New,0);
	v5New.AddEdge(v4New,0);
	v5New.AddEdge(v7New,0);
	
	v6New.AddEdge(v2New,0);

	v7New.AddEdge(v3New,0);

	gNew.addVertex(v1New);
	gNew.addVertex(v2New);
	gNew.addVertex(v3New);
	gNew.addVertex(v4New);
	gNew.addVertex(v5New);
	gNew.addVertex(v6New);
	gNew.addVertex(v7New);
	gNew.addVertex(v8New);

	std::cout<<"\n Strong Componentes \n ";

	VertexFunctor<int,int> vf;

	gNew.DepthFirstSearch(vf,gNew.VERTEX_EDGE);

	CondensedOperation<int,int> co;

	gNew.CreateCondensedGraph(co);

	/* 
	============================================================================
	Error when a custom object without operator overlading used as template.
	============================================================================
	Error C2676: binary '==' : 'CustomElement' does not define this operator or 
	a conversion to a type acceptable to the predefined operator.
	============================================================================

	Graph<CustomElement,int> cstGraph;

	CustomElement ce;

	VertexFunctor<CustomElement,int> fvCst;

	cstGraph.DepthFirstSearch(fvCst,cstGraph.EDGE_ONLY);

	*/
}

#endif