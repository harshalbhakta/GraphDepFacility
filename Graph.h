#ifndef GRAPH_H
#define GRAPH_H
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Graph.h (ver 1.0)- 	Templatized class to be used for implementing Graph Data structure.					  // 																					   
//		 																									  //
//	Language		:   Microsoft Visual C++, 2010															  //
//	Platform		:   Toshiba Satellite (R25-S3503), Windows 7 Professional								  //
//	Application		:	CSE687 - Project #3 - Dependency Graph Facility, Spring 2011						  //
//	Author			:   Harshal Bhakta, Syracuse University.												  //
//	E-mail			:   harshal.c.bhakta@gmail.com															  //
//	Cell			:   714-876-4273																		  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
  Module Operations: 
  ==================

  This module is designed to be used as a graph data structure. The graph class will make use of templatized 
  vertex objects and store it in the adjacency list to maintain edge connections. The Vertex objects added to 
  the graph will hold unique id's. The adjacency list is maintained as a map<int,VertexNode> adjacency_list;

  The map will hold unique Vertex id as key and the entire Vertex object as the value. Inserting new vertex with 
  the same id as existing vertex, overwrites the value of the vertex in the graph.

  Default Copy Constructor works fine. ( Graph Id remains same ) ( All Vertex Id and Edge Id remain same )
  Default assignment operator works fine. ( Graph Id remains same ) ( All Vertex Id and Edge Id remain same )

  DepthFirstSearch Algorithm: http://www.cs.cmu.edu/afs/cs/academic/class/15451-s06/www/lectures/DFS-strong-components.pdf
  Topological Sort Algorithm: http://en.wikipedia.org/wiki/Topological_sorting

  Custom Functors: 
  --------------------
  DepthFirstSearch & CreateCondensedGraph are two algorithms supported by the Graph Object. Both the functions
  accept a functor as input which can be used to perform differnt actions on the Graph Vertex's. DepthFirstSearch
  algorithm provides a sample functor which enunciates the Vertex and edge as they are traversed. The Functor 
  can be used as an example to develop more functor operations to be carried out on the nodes as they are 
  encountered during Depth First Search. 
  
  Similarly, Condensed Graph function takes a functor input which 
  accepts _condensed_graph reference ,_original_graph reference and topoligical_sorted_components reference.
  The Condensed Graph functor references can be used for analysis of the graph and implementing custom algorithms.

  Global Algorithms: 
  --------------------
  Graph package provides 4 Global Algorithms to search and return a collection of Vertex and Edges.

  1) vector<EdgeItem> FetchEdges(const Graph&,EdgeComparator,EdgeTypeAlgo)
	 - Function to fetch a vector of edges by directly comparing EdgeType.
	 - Example Functor : EdgeComparator
  2) vector<Vertex> FetchVertex(const Graph&,Comparator,VertexTypeAlgo)
	 - Function to fetch a vector of Vertex by directly comparing VertexType.
	 - Example Functor : VertexComparator
  3) vector<EdgeItem> FetchEdgesCustomSearch(const Graph&,EdgeComparator,Value)
	 - Function to fetch a vector of Vertex by using custom comparison.
	 - Example Functor : EdgeComparatorCustom
  4) vector<Vertex> FetchVertexCustomSearch(const Graph&,Comparator,Value)
	 - Function to fetch a vector of Vertex by using custom comparison.
	 - Example Functor : VertexComparatorCustom

  Public Interface:
  =================

    Graph();											 // Create Graph Object.	
	void addVertex(const Vertex&);                       // Add a Vertex to the Graph.
	void DepthFirstSearch(Operation&, enunciate_mode);   // Depth fist Search on graph. 
	-													 // Accepts a functor to enunciate Vertex - Edge. 
	-													 // Referenc Functor : VertexFunctor
	void CreateCondensedGraph(Operation&);				 // Function to create condensed graph.
	-													 // Accepts a functor to enunciate Vertex - Edge. 
	-													 // Referenc Functor : CondensedOperation
	Vertex GetVertex(int);								 // Function to Get Vertex by Id.
	const map<int,VertexNode>& GetAdjacencyList() const; // Function to get const ref. of Adjacency list. 
	void ResetGraph();									 // Function to reset the graph.
	const int GetId() const;							 // Get Id of the current graph.

  Build Process:
  ==============
  
  Required files
    
	- Vertex.h, Vertex.cpp, Graph.h, Graph.cpp
  
  Build commands
    
	- cl /EHsc /DTEST_GRAPH Graph.cpp Vertex.cpp

  Maintenance History:
  ====================
  ver 1.0 : 31 Mar 11
  - first release
*/

#include "Vertex.h"
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <set>

///////////////////////////////////////////////////////////////
// Templatized class to support Graph Datastructure.
template <typename VertexType,typename EdgeType>
class Graph {

public :
	
	typename typedef Vertex<VertexType,EdgeType> VertexNode;
	typedef Graph<VertexType,EdgeType> graph;
	enum enunciate_mode { VERTEX_ONLY, EDGE_ONLY , VERTEX_EDGE };

	Graph();
	~Graph();
	void addVertex(const Vertex<VertexType,EdgeType>&);
	template <typename Operation> 
	void DepthFirstSearch(Operation&, enunciate_mode);
	template <typename Operation>
	void CreateCondensedGraph(Operation&);
	Vertex<VertexType,EdgeType> GetVertex(int);
	const std::map<int,VertexNode>& GetAdjacencyList() const;
	void ResetGraph();
	const int GetId() const;

private :

	// Forward Declaration.
	struct StrongData;
	struct CondensedData;
	
	// Helper Function.
	void FindStrongComponentsRecurse(const int&,StrongData&,CondensedData&);
	void ResetStrongData(StrongData&);
	void ResetCondensedData(CondensedData&);
	void IncrementStrongData(const int&,StrongData&);
	void ExtractSingleComponent(const int&,StrongData&,CondensedData&);
	void FindStrongComponents(CondensedData&);
	void LinkStrongComponents(CondensedData&);
	void GenerateGraph(CondensedData&);
	void TopologicalSort(CondensedData&);
	void VisitTopologicalComponent(int,CondensedData&);
	template <typename Operation>
	void RecurseDepthFirstSearch( const Vertex<VertexType,EdgeType>&, Operation& , enunciate_mode, std::vector<int>& );
	bool IsVisited(int,const std::vector<int>&);
	bool IsInStack(int,StrongData&);
	bool IsIncomingComponent(int,CondensedData&);
	
	// Member Data.
	std::map<int,VertexNode> adjacency_list;
	Graph<std::pair<int,std::vector<int>>,int>* condensed_graph;
	std::vector<int> sorted_components;
	int id;
	static int graph_count; 

	// Member Data for Strong Components.
	struct StrongData {
		int strong_index ; // Index used for calculation of strong component.
		int strong_component ; // Count maintatined for strong_component.
		std::vector<int> strong_stack; // Stack to store current component content.
		std::map<int,int> strong_num; // Num value for each Vertex.
		std::map<int,int> strong_low_link; // Low link value for each Vertex.
	};

	// Member Data for Condesed Graph & Topoligical Sort.
	struct CondensedData {
		std::map<int,int> condensed_map; // Map <Vertex_id, Strong_Component>	
		std::map<int,Vertex<std::pair<int,std::vector<int>>,int>> components; // Store components with refrence to its content Vertex. 
		std::map<int,int> incoming_components; // Components having incoming edge.
		std::vector<int> visited_components; // Store visited components.
	};
};

///////////////////////////////////////////////////////////////
// Functor to be used for DFS to enunciate Vertex and/or Edge.
template <typename VertexType,typename EdgeType>
class VertexFunctor {
public:
  VertexFunctor(){}
  void operator()(const Vertex<VertexType,EdgeType>& _v) 
	{ 
		std::cout << "\n [ " << _v.GetVertex() << " ]"; 
	}
  void operator()(const Vertex<VertexType,EdgeType>& _from,EdgeType _et,const Vertex<VertexType,EdgeType>& _to) 
    { 
		std::cout << "\n [ " << _from.GetVertex() << " ]" << "---" << _et << "--->" << "[ "<< _to.GetVertex() << " ]" ; 
    }
private:  
};

///////////////////////////////////////////////////////////////
// Functor to be used for creating condensed graph.
template <typename VertexType,typename EdgeType>
class CondensedOperation {
public:
  CondensedOperation(){}

  // Function to print the Repository Location.
   void PrintCondensedGraph(const Graph<std::pair<int,std::vector<int>>,int>& _graph);

  void operator()(const Graph<std::pair<int,std::vector<int>>,int>& _condensed_graph,const Graph<VertexType,EdgeType>& _graph,const std::vector<int>& _sorted_components) 
	{ 
		PrintCondensedGraph(_condensed_graph);
		// CondensedOperation Accepts Reference to _condensed_graph - _original Graph - _sorted_components.
		// Custom operation can be performed using these references.
    }
private:  
};

//////////////////////////////////////////////////////////////
// Function to print the condensed Graph.
template <typename VertexType,typename EdgeType>
void CondensedOperation<VertexType,EdgeType>::PrintCondensedGraph(const Graph<std::pair<int,std::vector<int>>,int>& _graph)
{
	std::cout<<"\n Condensed Graph Id: "<<_graph.GetId();

	std::cout << "\n "<< std::string(55,'=');

	const std::map<int,Vertex<std::pair<int,std::vector<int>>,int>>& graph_adjacency = _graph.GetAdjacencyList();

	std::map<int,Vertex<std::pair<int,std::vector<int>>,int>>::const_iterator it = graph_adjacency.begin();

	while ( it != graph_adjacency.end() )
	{
		Vertex<std::pair<int,std::vector<int>>,int> _vertex = it->second;

		std::cout<<"\n\n Vertex - [ "<<_vertex.GetVertex().first <<" ] ";

		std::cout << "\n "<< std::string(55,'-');

		std::vector<std::pair<int, std::pair<int,int>>> edges = _vertex.GetEdges();

		for ( int i = 0 ; i < (int)edges.size() ; i++ )
		{
			std::map<int,Vertex<std::pair<int,std::vector<int>>,int>>::const_iterator it = graph_adjacency.find(edges[i].first);

			if ( it != graph_adjacency.end() )
			{
				std::cout<<"\n [ "<<_vertex.GetVertex().first<<" ] " << "---" << edges[i].second.second << "--->"<<" [ " << it->second.GetVertex().first << " ]" ;
			}
		}

		++it;	
	}

	std::cout<<"\n";
}

///////////////////////////////////////////////////////////////
// Initialize the static count to keep track of Graph ID.
template <typename VertexType, typename EdgeType>
int Graph<VertexType,EdgeType>::graph_count = 0;

///////////////////////////////////////////////////////////////
// Function to return Graph Id.
template <typename VertexType, typename EdgeType>
const int Graph<VertexType,EdgeType>::GetId() const
{
	return id;
}

///////////////////////////////////////////////////////////////
// Default constructor to increment the count for new graph id.
template <typename VertexType, typename EdgeType>
Graph<VertexType,EdgeType>::Graph() : id(++graph_count),condensed_graph(0) { }

///////////////////////////////////////////////////////////////
// Destructor.
template <typename VertexType, typename EdgeType>
Graph<VertexType,EdgeType>::~Graph() 
{ 
	delete condensed_graph;
}

///////////////////////////////////////////////////////////////
// Fucntion to return the reference to Adjacency List.
template <typename VertexType, typename EdgeType>
const std::map<int,Vertex<VertexType,EdgeType>>& Graph<VertexType,EdgeType>::GetAdjacencyList() const
{
	return adjacency_list;
}

///////////////////////////////////////////////////////////////
// Function to add Vertex to the current graph object.
template <typename VertexType,typename EdgeType>
void Graph<VertexType,EdgeType>::addVertex(const VertexNode& _vertex)
{
	adjacency_list[_vertex.GetId()] = _vertex;
}

///////////////////////////////////////////////////////////////
// Function to perform Depth First Search on current Graph.
template <typename VertexType,typename EdgeType> template <typename Operation>
void Graph<VertexType,EdgeType>::DepthFirstSearch(Operation& _vf, enunciate_mode mode)
{
	std::vector<int> visited_vertex;

	std::map<int,VertexNode>::iterator it;

	it = adjacency_list.begin();

	while ( it != adjacency_list.end() )
	{
		if ( ! IsVisited((*it).first,visited_vertex) )
		{
			visited_vertex.push_back((*it).first);
			
			RecurseDepthFirstSearch((*it).second,_vf,mode,visited_vertex);
		}
	
		++it;
	}
}

///////////////////////////////////////////////////////////////
// Recursive function to support DepthFirstSearch.
template <typename VertexType,typename EdgeType> template <typename Operation>
void Graph<VertexType,EdgeType>::RecurseDepthFirstSearch(const Vertex<VertexType,EdgeType>& _start_vertex, Operation& _vf, enunciate_mode mode,std::vector<int>& visited_vertex)
{
		std::vector<std::pair<int,std::pair<int,EdgeType>>> edges = _start_vertex.GetEdges();

		if ( mode == VERTEX_EDGE || mode == VERTEX_ONLY )
		{ // Enunciate Vertex
		  _vf(_start_vertex);
		} 

		for ( int j = 0 ; j < (int)edges.size() ; j++ )
		{
			if ( mode == VERTEX_EDGE || mode == EDGE_ONLY )
			{   // Enunciate Edge
			  _vf(_start_vertex,edges[j].second.second,adjacency_list[edges[j].first]);  
			} 
			if ( ! IsVisited(edges[j].first,visited_vertex) )
			{	// If already not visisted, call recursive function.

				visited_vertex.push_back(edges[j].first);
				
				RecurseDepthFirstSearch(adjacency_list[edges[j].first],_vf,mode,visited_vertex);		
			}
		}
}

///////////////////////////////////////////////////////////////
// Function to generate Condensed Graph.
// Accept functor to return references to graph & sorted components.
template <typename VertexType,typename EdgeType> template <typename Operation>
void Graph<VertexType,EdgeType>::CreateCondensedGraph(Operation& _operation)
{
	condensed_graph = new Graph<std::pair<int,std::vector<int>>,int>();

	CondensedData condensed_data;

	ResetCondensedData(condensed_data);
	
	FindStrongComponents(condensed_data);

	LinkStrongComponents(condensed_data);

	GenerateGraph(condensed_data);

	TopologicalSort(condensed_data);

	const Graph<std::pair<int,std::vector<int>>,int>& ref_condensed_graph = *condensed_graph;

	const Graph<VertexType,EdgeType>& ref_graph = *this;

	const std::vector<int>& ref_sorted_components = sorted_components;

	_operation(ref_condensed_graph,ref_graph,ref_sorted_components);
}

///////////////////////////////////////////////////////////////
// Function to create edges between detected strong components.
template <typename VertexType,typename EdgeType>
void Graph<VertexType,EdgeType>::LinkStrongComponents(CondensedData& condensed_data)
{
	std::map<int,VertexNode>::iterator it;

	it = adjacency_list.begin();

	while ( it != adjacency_list.end() )
	{
		const std::vector<std::pair<int,std::pair<int,EdgeType>>> edges = it->second.GetEdges();

		for ( int i = 0 ; i < (int) edges.size() ; i++ )
		{
			int source_node = it->first ;
			
			int dest_node = edges[i].first ;			

			// Source node & Dest node belong to different components. Generate link.
			if ( condensed_data.condensed_map[source_node] != condensed_data.condensed_map[dest_node] )
			{
				condensed_data.incoming_components[condensed_data.condensed_map[dest_node]] = condensed_data.condensed_map[dest_node];

				condensed_data.components[condensed_data.condensed_map[source_node]].AddEdge(condensed_data.components[condensed_data.condensed_map[dest_node]],0);
			}
		}

		++it;
  	 }
}

///////////////////////////////////////////////////////////////
// Function to reset the strong data before analysis.
template <typename VertexType,typename EdgeType>
void Graph<VertexType,EdgeType>::ResetStrongData(StrongData& strong_data)
{
	strong_data.strong_stack.clear();
	strong_data.strong_num.clear();
	strong_data.strong_low_link.clear();
	strong_data.strong_index = 0 ;
	strong_data.strong_component = 0;
	
	std::map<int,VertexNode>::iterator it;

	it = adjacency_list.begin();

	while ( it != adjacency_list.end() )
	{
		strong_data.strong_num[(*it).first] = 0;
	
		++it;
	}
}

///////////////////////////////////////////////////////////////
// Function to reset the condensed data before analysis.
template <typename VertexType,typename EdgeType>
void Graph<VertexType,EdgeType>::ResetCondensedData(CondensedData& condensed_data)
{	
	condensed_data.condensed_map.clear();
	condensed_data.components.clear();
	condensed_data.incoming_components.clear();
	condensed_data.visited_components.clear();

	sorted_components.clear();
}

///////////////////////////////////////////////////////////////
// Function to detect strong components.
template <typename VertexType,typename EdgeType>
void Graph<VertexType,EdgeType>::FindStrongComponents(CondensedData& condensed_data)
{
	std::cout<<"\n\n Detecting Strong Components ";

	std::cout << "\n "<< std::string(55,'=') << "\n";

	StrongData strong_data;

	ResetStrongData(strong_data);

	std::map<int,VertexNode>::iterator it;

	it = adjacency_list.begin();

	while ( it != adjacency_list.end() )
	{
		if ( strong_data.strong_num[(*it).first] == 0 )
		{
			FindStrongComponentsRecurse((*it).first,strong_data,condensed_data);
		}
	
		++it;
	}
	std::cout<<"\n";
}

///////////////////////////////////////////////////////////////
// Function to increment strong data for new node.
template <typename VertexType,typename EdgeType>
void Graph<VertexType,EdgeType>::IncrementStrongData(const int& _vertex_index,StrongData& strong_data)
{
		++strong_data.strong_index;

		strong_data.strong_num[_vertex_index] = strong_data.strong_index;
		
		strong_data.strong_low_link[_vertex_index] = strong_data.strong_index;

		strong_data.strong_stack.push_back(_vertex_index);
}

///////////////////////////////////////////////////////////////
// Recursicve Function to find strong components.
template <typename VertexType,typename EdgeType>
void Graph<VertexType,EdgeType>::FindStrongComponentsRecurse(const int& _vertex_index,StrongData& strong_data,CondensedData& condensed_data)
{
		IncrementStrongData(_vertex_index,strong_data);

		std::vector<std::pair<int,std::pair<int,EdgeType>>> edges = adjacency_list[_vertex_index].GetEdges();

		for ( int j = 0 ; j < (int)edges.size() ; j++ )
		{
			if ( strong_data.strong_num[edges[j].first] == 0 )
			{   // Check if already visisted. If not, call recursive function.

				FindStrongComponentsRecurse(edges[j].first,strong_data,condensed_data);		

				strong_data.strong_low_link[_vertex_index] = std::min(strong_data.strong_low_link[_vertex_index],strong_data.strong_low_link[edges[j].first]);				
			}
			else if ( (strong_data.strong_num[edges[j].first] < strong_data.strong_num[_vertex_index]) && IsInStack(edges[j].first,strong_data) )
			{
				strong_data.strong_low_link[_vertex_index] = std::min(strong_data.strong_low_link[_vertex_index],strong_data.strong_num[edges[j].first]);
			}
		}

		ExtractSingleComponent(_vertex_index,strong_data,condensed_data);
}


///////////////////////////////////////////////////////////////
// Function to extract a single component.
template <typename VertexType,typename EdgeType>
void Graph<VertexType,EdgeType>::ExtractSingleComponent(const int& _vertex_index,StrongData& strong_data,CondensedData& condensed_data)
{
		if ( strong_data.strong_low_link[_vertex_index] == strong_data.strong_num[_vertex_index] )
		{
			++strong_data.strong_component;
	
			std::cout<<"\n Strong Component #" << strong_data.strong_component <<" : ";
			
			// Add to components map 
			Vertex<std::pair<int,std::vector<int>>,int> newVertex;

			std::pair<int,std::vector<int>> newPair = condensed_data.components[strong_data.strong_component].GetVertex();

			newPair.first = strong_data.strong_component;

			// End Add to componentes map

			while ( (int)strong_data.strong_stack.size() > 0 && strong_data.strong_num[strong_data.strong_stack[(int)strong_data.strong_stack.size() - 1]] >= strong_data.strong_num[_vertex_index] )
			{
				int top_element = strong_data.strong_stack[(int)strong_data.strong_stack.size() - 1];

				newPair.second.push_back(top_element);

				condensed_data.condensed_map[top_element] = strong_data.strong_component;

				std::cout<<adjacency_list[top_element].GetVertex()<<", ";			

				strong_data.strong_stack.erase(strong_data.strong_stack.end() - 1);
			}
			
			condensed_data.components[strong_data.strong_component].SetValue(newPair);

			std::cout<<"\n";
		}	
}

///////////////////////////////////////////////////////////////
// Function to generate the graph for strong components.
template <typename VertexType,typename EdgeType>
void Graph<VertexType,EdgeType>::GenerateGraph(CondensedData& condensed_data)
{
	std::map<int,Vertex<std::pair<int,std::vector<int>>,int>>::iterator it;

	it = condensed_data.components.begin();

	while ( it != condensed_data.components.end() )
	{
		condensed_graph->addVertex(it->second);
	
		++it;
	}
}

///////////////////////////////////////////////////////////////
// Function to topologically sort strong components.
template <typename VertexType,typename EdgeType>
void Graph<VertexType,EdgeType>::TopologicalSort(CondensedData& condensed_data)
{
	std::cout<<"\n Topological Sorting of Strong Components ";

	std::cout << "\n "<< std::string(55,'=') << "\n";

	const std::map<int,Vertex<std::pair<int,std::vector<int>>,int>>& ref_condensed_adjacency = condensed_graph->GetAdjacencyList();

	std::map<int,Vertex<std::pair<int,std::vector<int>>,int>>::const_iterator& it = ref_condensed_adjacency.begin();

	while ( it != ref_condensed_adjacency.end() )
	{
		if ( ! ( IsIncomingComponent(it->second.GetVertex().first,condensed_data) ) )
		{
			VisitTopologicalComponent(it->second.GetVertex().first,condensed_data);
		}
		++it;
	}

	std::cout<<"\n";
}

///////////////////////////////////////////////////////////////
// Function to fetch the vertex based on Id.
template <typename VertexType,typename EdgeType>
Vertex<VertexType,EdgeType> Graph<VertexType,EdgeType>::GetVertex(int _id)
{
	return adjacency_list[_id];	
}

///////////////////////////////////////////////////////////////
// Function to Visit components in topological order.
template <typename VertexType,typename EdgeType>
void Graph<VertexType,EdgeType>::VisitTopologicalComponent(int _node,CondensedData& condensed_data)
{
	const std::map<int,Vertex<std::pair<int,std::vector<int>>,int>>& ref_condensed_adjacency = condensed_graph->GetAdjacencyList();
	
	if ( std::find(condensed_data.visited_components.begin(),condensed_data.visited_components.end(),_node) == condensed_data.visited_components.end() )
	{
		condensed_data.visited_components.push_back(_node);

		std::vector<std::pair<int,std::pair<int,int>>> component_edges = condensed_data.components[_node].GetEdges();
	
		for ( int i = 0 ; i < (int)component_edges.size() ; i++ )
		{
			int node = condensed_graph->GetVertex(component_edges[i].first).GetVertex().first;

			VisitTopologicalComponent(node,condensed_data);
		}

		sorted_components.push_back(_node);
		
		std::cout<<" Component #: "<<_node <<"\n";
	}
}

///////////////////////////////////////////////////////////////
// Function to check if a node is already visited.
template <typename VertexType,typename EdgeType>
bool Graph<VertexType,EdgeType>::IsVisited(int _index,const std::vector<int>& visited_vertex)
{
	bool exists = false;

	for ( int i = 0 ; i < (int)visited_vertex.size() ; i++ )
	{
		if ( visited_vertex[i] == _index )
		   { exists = true; break; }
	}

	return exists;
}

///////////////////////////////////////////////////////////////
// Function to check if node is already in stack of strong component.
template <typename VertexType,typename EdgeType>
bool Graph<VertexType,EdgeType>::IsInStack(int _index,StrongData& strong_data)
{
	bool exists = false;

	for ( int i = 0 ; i < (int)strong_data.strong_stack.size() ; i++ )
	{
		if ( strong_data.strong_stack[i] == _index )
		   { 
			   exists = true; 
			   break; 
		   }
	}

	return exists;
}

///////////////////////////////////////////////////////////////
// Function to check if a component has incoming edges or not.
template <typename VertexType,typename EdgeType>
bool Graph<VertexType,EdgeType>::IsIncomingComponent(int _component,CondensedData& condensed_data)
{
	bool is_incoming = false;

	std::map<int,int>::iterator it = condensed_data.incoming_components.begin();

	while ( it != condensed_data.incoming_components.end() )
	{
		if ( it->first == _component )
		   { 
			   is_incoming = true; 
			   break; 
		   }

		++it;
	}

	return is_incoming;
}

///////////////////////////////////////////////////////////////
// Function to reset the graph.
template <typename VertexType,typename EdgeType>
void Graph<VertexType,EdgeType>::ResetGraph()
{
	adjacency_list.clear();

	condensed_graph = 0 ;

	sorted_components.clear();
}

///////////////////////////////////////////////////////////////
// GraphAlgorithm to hold global algorithms for search.
namespace GraphAlgorithm 
{

///////////////////////////////////////////////////////////////
// Custom Structure to return results.
template<class VertexTypeAlgo,class EdgeTypeAlgo>
struct EdgeItem {

	Vertex<VertexTypeAlgo,EdgeTypeAlgo> from_vertex;

	EdgeTypeAlgo edge;

	Vertex<VertexTypeAlgo,EdgeTypeAlgo> to_vertex;

};

/////////////////////////CUSTOM VERSION/////////////////////////////

///////////////////////////////////////////////////////////////
// Functor to perform custom search for Vertex.
template <typename VertexTypeAlgo,typename EdgeTypeAlgo,typename Value>
class VertexComparatorCustom {
public:
  VertexComparatorCustom(){}

	  bool operator()(const Vertex<VertexTypeAlgo,EdgeTypeAlgo>& _vertex,Value _value) 
		{ 
			if ( _vertex.GetVertex() == _value )
				return true;
  
			return false;
		}

private:  
};

///////////////////////////////////////////////////////////////
// Functor to perform custom search for Edge.
template <typename VertexTypeAlgo,typename EdgeTypeAlgo,typename Value>
class EdgeComparatorCustom {
public:
  EdgeComparatorCustom(){}

	bool operator()(const std::pair<int,std::pair<int,EdgeTypeAlgo>>& _edge,Value _value) 
	{ 
		if ( _edge.second.second == _value )
			return true;
  
		return false;
	}

private:  
};

///////////////////////////////////////////////////////////////
// Global function to fetch list of vertex. ( Custom Search )
template<typename VertexTypeAlgo,typename EdgeTypeAlgo ,typename Comparator,typename Value>
std::vector<Vertex<VertexTypeAlgo,EdgeTypeAlgo>> FetchVertexCustomSearch(const Graph<VertexTypeAlgo,EdgeTypeAlgo>& _graph,Comparator _comparator,Value _value)
{
	std::vector<Vertex<VertexTypeAlgo,EdgeTypeAlgo>> _vertex_match_list;

	const std::map<int,Vertex<VertexTypeAlgo,EdgeTypeAlgo>>& ref_adjacency_list = _graph.GetAdjacencyList();

	std::map<int,Vertex<VertexTypeAlgo,EdgeTypeAlgo>>::const_iterator it = ref_adjacency_list.begin();

	while ( it != ref_adjacency_list.end() )
	{
		if ( _comparator(it->second,_value) )
		{
			_vertex_match_list.push_back(it->second);
		}
	
		++it;
	}

	return _vertex_match_list;
}

///////////////////////////////////////////////////////////////
// Global function to fetch list of edges. ( Custom Search )
template<typename VertexTypeAlgo,typename EdgeTypeAlgo ,typename EdgeComparator,typename Value>
std::vector<EdgeItem<VertexTypeAlgo,EdgeTypeAlgo>> FetchEdgesCustomSearch(const Graph<VertexTypeAlgo,EdgeTypeAlgo>& _graph,EdgeComparator _comparator,Value _value)
{
	std::vector<EdgeItem<VertexTypeAlgo,EdgeTypeAlgo>> EdgeList;

	std::map<int,Vertex<VertexTypeAlgo,EdgeTypeAlgo>> ref_adjacency_list = _graph.GetAdjacencyList();

	std::map<int,Vertex<VertexTypeAlgo,EdgeTypeAlgo>>::const_iterator it = ref_adjacency_list.begin();

	while ( it != ref_adjacency_list.end() )
	{
		std::vector<std::pair<int,std::pair<int,EdgeTypeAlgo>>> _edges = it->second.GetEdges() ;
		
		for ( int i = 0 ; i < (int)_edges.size() ; i++ )
		{
			if ( _comparator(_edges[i],_value) )
			{
				EdgeItem<VertexTypeAlgo,EdgeTypeAlgo> ei;
					
				ei.from_vertex = it->second;
				ei.edge = _edges[i].second.second;
				ei.to_vertex =  ref_adjacency_list[_edges[i].first];

				EdgeList.push_back(ei);
			}
		}
	
		++it;
	}

	return EdgeList;
}

/////////////////////////NORMAL VERSION/////////////////////////////

///////////////////////////////////////////////////////////////
// Functor to perform search for Vertex based on VertexType.
template <typename VertexTypeAlgo,typename EdgeTypeAlgo>
class VertexComparator {
public:
  VertexComparator(){}

	  bool operator()(const Vertex<VertexTypeAlgo,EdgeTypeAlgo>& _vertex,VertexTypeAlgo _value) 
		{ 
			if ( _vertex.GetVertex() == _value )
				return true;
  
			return false;
		}

private:  
};

///////////////////////////////////////////////////////////////
// Functor to perform search for Vertex based on EdgeType.
template <typename VertexTypeAlgo,typename EdgeTypeAlgo>
class EdgeComparator {
public:
  EdgeComparator(){}

	bool operator()(const std::pair<int,std::pair<int,EdgeTypeAlgo>>& _edge,EdgeTypeAlgo _value) 
	{ 
		if ( _edge.second.second == _value )
			return true;
  
		return false;
	}

private:  
};

///////////////////////////////////////////////////////////////
// Global Function to search Vertex based on VertexType.
template<typename VertexTypeAlgo,typename EdgeTypeAlgo ,typename Comparator>
std::vector<Vertex<VertexTypeAlgo,EdgeTypeAlgo>> FetchVertex(const Graph<VertexTypeAlgo,EdgeTypeAlgo>& _graph,Comparator _comparator,VertexTypeAlgo _value)
{
	std::vector<Vertex<VertexTypeAlgo,EdgeTypeAlgo>> _vertex_match_list;

	const std::map<int,Vertex<VertexTypeAlgo,EdgeTypeAlgo>>& ref_adjacency_list = _graph.GetAdjacencyList();

	std::map<int,Vertex<VertexTypeAlgo,EdgeTypeAlgo>>::const_iterator it = ref_adjacency_list.begin();

	while ( it != ref_adjacency_list.end() )
	{
		if ( _comparator(it->second,_value) )
		{
			_vertex_match_list.push_back(it->second);
		}
	
		++it;
	}

	return _vertex_match_list;
}

///////////////////////////////////////////////////////////////
// Global Function to search Edges based on EdgeType.
template<typename VertexTypeAlgo,typename EdgeTypeAlgo ,typename EdgeComparator>
typename std::vector<EdgeItem<VertexTypeAlgo,EdgeTypeAlgo>> FetchEdges(const Graph<VertexTypeAlgo,EdgeTypeAlgo>& _graph,EdgeComparator _comparator,EdgeTypeAlgo _value)
{
	std::vector<EdgeItem<VertexTypeAlgo,EdgeTypeAlgo>> EdgeList;

	std::map<int,Vertex<VertexTypeAlgo,EdgeTypeAlgo>> ref_adjacency_list = _graph.GetAdjacencyList();

	std::map<int,Vertex<VertexTypeAlgo,EdgeTypeAlgo>>::const_iterator it = ref_adjacency_list.begin();

	while ( it != ref_adjacency_list.end() )
	{
		std::vector<std::pair<int,std::pair<int,EdgeTypeAlgo>>> _edges = it->second.GetEdges() ;
		
		for ( int i = 0 ; i < (int)_edges.size() ; i++ )
		{
			if ( _comparator(_edges[i],_value) )
			{
				EdgeItem<VertexTypeAlgo,EdgeTypeAlgo> ei;
					
				ei.from_vertex = it->second;
				ei.edge = _edges[i].second.second;
				ei.to_vertex =  ref_adjacency_list[_edges[i].first];

				EdgeList.push_back(ei);
			}
		}
	
		++it;
	}

	return EdgeList;
}

}

#endif