#ifndef DISPLAY_H
#define DISPLAY_H
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Display.h (ver 1.0)  -  Module to handle formatted output for Graph and Vertex class.					  // 																					   
//		 																									  //
//	Language		:   Visual C++, 2010																	  //
//	Platform		:   Toshiba Satellite (R25-S3503), Windows 7 Professional								  //
//	Application		:	CSE687 - Project #3 - Dependency Graph Facility, Spring 2011						  //
//	Author			:   Harshal Bhakta, Syracuse University.												  //
//	E-mail			:   harshal.c.bhakta@gmail.com															  //
//	Cell			:   714-876-4273																		  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
  Module Operations: 
  ==================

  This module will be responsible for handling the output of Graph and Vertex class. The module will provide public
  interfaces to print detailed information about the Graph and the Vertex elements.

  Templatized Function to print VertexType and EdgeType that support "<<" operator.

  Public Interface:
  =================

  template <typename VertexType,typename EdgeType>
  void PrintVertex(const Vertex&);	    // Function that prints a Vertex passed as reference. 
  void PrintGraphVerbose(const Graph&); // Function that prints a Graph in verbose mode. ( Id )
  void PrintGraph(const Graph&);        // Function that prints a Graph in normal mode.

  Build Process:
  ==============
  
  Required files

    - Display.h, Display.cpp , Graph.h ,Graph.cpp
	- Vertex.h, Vertex.cpp
  
  Build commands ( Can be used directly copying from here )

    - cl /EHsc /DTEST_DISPLAY Display.cpp Graph.cpp Vertex.cpp
	 
  Maintenance History:
  ====================
  ver 1.0 : 30 Mar 11
*/
#include <iostream>
#include "Graph.h"

////////////////////////////////////////////////////////////////////
// Display class responsible for formatted graph output.
class Display{

public  :

	template <typename VertexType,typename EdgeType>
	void PrintVertex(const Vertex<VertexType,EdgeType>&);

	template <typename VertexType,typename EdgeType>
	void PrintGraphVerbose(const Graph<VertexType,EdgeType>&);
	
	template <typename VertexType,typename EdgeType>
	void PrintGraph(const Graph<VertexType,EdgeType>&);

private :

};

//////////////////////////////////////////////////////////////
// Function to print the a Vertex.
template <typename VertexType,typename EdgeType>
void Display::PrintVertex(const Vertex<VertexType,EdgeType>& _vertex)
{
	std::cout<<"\n";

	std::cout<<" Vertex Id: "<<_vertex.GetId()<<" - "<<"Vertex Value: "<<_vertex.GetVertex();

	std::cout << "\n "<< std::string(55,'-');

	std::vector<std::pair<int, std::pair<int,EdgeType>>> edges = _vertex.GetEdges();

	for ( int i = 0 ; i < (int)edges.size() ; i++ )
	{
		std::cout<<"\n Edge-> RefId ( "<<edges[i].first <<" ) |"<<" Id ( "<<edges[i].second.first <<" ) |"<< " Value ( " <<edges[i].second.second << " )";
	}

	std::cout << "\n "<< std::string(55,'-');
}

//////////////////////////////////////////////////////////////
// Function to print Graph in Verbose mode with "id"
template <typename VertexType,typename EdgeType>
void Display::PrintGraphVerbose(const Graph<VertexType,EdgeType>& _graph)
{

	std::cout<<"\n";

	std::cout<<" Graph Id: "<<_graph.GetId();

	std::cout << "\n "<< std::string(55,'-');

	const std::map<int,Vertex<VertexType,EdgeType>>& graph_adjacency = _graph.GetAdjacencyList();

	std::map<int,Vertex<VertexType,EdgeType>>::const_iterator it = graph_adjacency.begin();

	while ( it != graph_adjacency.end() )
	{
	
		Vertex<VertexType,EdgeType> _vertex = it->second;

		std::cout<<"\n\n Vertex Id: "<<_vertex.GetId()<<" - "<<"Vertex Value: "<<_vertex.GetVertex();

		std::cout << "\n "<< std::string(55,'-');

		std::vector<std::pair<int, std::pair<int,EdgeType>>> edges = _vertex.GetEdges();

		for ( int i = 0 ; i < (int)edges.size() ; i++ )
		{
			std::cout<<"\n Edge-> RefId ( "<<edges[i].first <<" ) |"<<" Id ( "<<edges[i].second.first <<" ) |"<< " Value ( " <<edges[i].second.second << " )";
		}

		++it;	
	}

	std::cout<<"\n";
}

//////////////////////////////////////////////////////////////
// Function to print Graph in normal mode.
template <typename VertexType,typename EdgeType>
void Display::PrintGraph(const Graph<VertexType,EdgeType>& _graph)
{
	std::cout<<"\n";

	std::cout<<" Graph Id: "<<_graph.GetId();

	std::cout << "\n "<< std::string(55,'=');

	const std::map<int,Vertex<VertexType,EdgeType>>& graph_adjacency = _graph.GetAdjacencyList();

	std::map<int,Vertex<VertexType,EdgeType>>::const_iterator it = graph_adjacency.begin();

	while ( it != graph_adjacency.end() )
	{
	
		Vertex<VertexType,EdgeType> _vertex = it->second;

		std::cout<<"\n\n Vertex - [ "<<_vertex.GetVertex()<<" ] ";

		std::cout << "\n "<< std::string(55,'-');

		std::vector<std::pair<int, std::pair<int,EdgeType>>> edges = _vertex.GetEdges();

		for ( int i = 0 ; i < (int)edges.size() ; i++ )
		{
			std::map<int,Vertex<VertexType,EdgeType>>::const_iterator it = graph_adjacency.find(edges[i].first);

			if ( it != graph_adjacency.end() )
			{
				std::cout<<"\n [ "<<_vertex.GetVertex()<<" ] " << "---" << edges[i].second.second << "--->"<<" [ " << it->second.GetVertex() << " ]" ;
			}
		}

		++it;	
	}

	std::cout<<"\n";
}

#endif