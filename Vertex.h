#ifndef VERTEX_H
#define VERTEX_H
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
/*
  Module Operations: 
  ==================

  The Vertex class will be responsible for holding the information related to the vertex. The data stored for
  each vertex object will be used by the Graph Class to construct a collection of Vertex objects. The data
  stored for vertex class is designed to support the Graph Class. Graph class will be holding the adjacency 
  list of vertex. Each vertex should hold the reference to its child vertex. The Vertex will hold this 
  reference as a id number of the child in the adjacency list.

  For Example : Consider graph adjacency list.
	
		   Id :  [ Vertex Obj | Value				| List(ReferenceIndex,Edge) ]
		-----------------------------------------------------------------------------
			0 :  [ vertex 1	  | ["Root"]			| ( 1,<1,"Edge1">) (2,<2,"Edge2">)  ]
			1 :  [ vertex 2   | ["LeftChild"]		| ( 3,<3,"Edge3">)				]
			2 :  [ vertex 3   | ["RighChild"]		| ( 3,<4,"Edge4">)				]
			3 :  [ vertex 4   | ["SecondLevel"]		| (          )			    ]

  Data Structure used in the Vertex class: 

   VertexType - Holds the value of the Vertex.
    Reference - Reference Id to destination vertex. 
 		 Edge - Holds the edges - ( List(ReferenceIndex,Edge) )
 
  Default Copy Constructor works fine. ( Vertex Id and Edge Id remain same )
  Default assignment operator works fine. ( Vertex Id and Edge Id remain same )

  Public Interface:
  =================

    Vertex();										// Create vertex object.
	void SetValue(const VertexType&);				// Set value of vertex.
	void AddEdge(const Vertex&,const EdgeType&);	// Add edge to current vertex.
	void ClearEdges();								// Clear all edges.
	void ResetId();									// Assign new Id. (Useful after copy)
	const VertexType& GetVertex() const;			// Get vertex value.
	const vector<pair<int,edge>>& GetEdges() const; // Get vector of edges.
	const int& GetId() const;						// Get Id of the vertex.
  
  Build Process:
  ==============
  
  Required files
    
	- Vertex.h,Vertex.cpp
  
  Build commands

	- cl /EHsc /DTEST_VERTEX Vertex.cpp

  Maintenance History:
  ====================
  ver 1.0 : 31 Mar 11
    - first release
*/

#include <vector>

///////////////////////////////////////////////////////////////
// class to represent a vertex to be used in the Graph Class.
template <typename VertexType,typename EdgeType>
class Vertex {

public:

	typename typedef std::pair<int,EdgeType> edge;
	Vertex();
	void SetValue(const VertexType&);
	void AddEdge(const Vertex<VertexType,EdgeType>&,const EdgeType&);
	void ClearEdges();
	void ResetId();
	const VertexType& GetVertex() const;
	const std::vector<std::pair<int,edge>>& GetEdges() const;
	const int& GetId() const;

private:

	int id;
	VertexType vertex_value;
	std::vector<std::pair<int,edge>> edges;
	static int vertex_count; 
	static int edge_count;
};

///////////////////////////////////////////////////////////////
// Initialize the static count to keep track of Vertex ID.
template <typename VertexType, typename EdgeType>
int Vertex<VertexType,EdgeType>::vertex_count = 0;

///////////////////////////////////////////////////////////////
// Initialize the static count to keep track of Edge ID.
template <typename VertexType, typename EdgeType>
int Vertex<VertexType,EdgeType>::edge_count = 0;

///////////////////////////////////////////////////////////////
// Constructor - Increment static count to assign new ID.
template <typename VertexType, typename EdgeType>
Vertex<VertexType,EdgeType>::Vertex() : id(++vertex_count) { }

///////////////////////////////////////////////////////////////
// Set the value of the Vertex.
template <typename VertexType, typename EdgeType>
void Vertex<VertexType,EdgeType>::SetValue(const VertexType& _vertex_value) 
{ 
	vertex_value = _vertex_value;
}

///////////////////////////////////////////////////////////////
// Function to add a new edge. 
// Argument taken as Destination Vertex & Edge(Id+EdgeValue).
template <typename VertexType,typename EdgeType>
void Vertex<VertexType,EdgeType>::AddEdge(const Vertex<VertexType,EdgeType>& _vertex,const EdgeType& _edge)
{
	if ( _vertex.id == id )
	{	// Ignore self edge.  
		return; 
	}

	std::vector<std::pair<int,std::pair<int,EdgeType>>> ::iterator iter = edges.begin();

	for ( ; iter != edges.end() ; iter++)
	{
		if ( iter->first == _vertex.GetId() )
		{   // Update if edge already exist.
			iter->second.second = _edge;
			
			return; 
		} 
	}

	++edge_count;

	// Add new edge to the vertex.
	edges.push_back(std::make_pair(_vertex.GetId(),std::make_pair(edge_count,_edge)));
}

///////////////////////////////////////////////////////////////
// Get the value of the Vertex.
template <typename VertexType, typename EdgeType>
const VertexType& Vertex<VertexType,EdgeType>::GetVertex() const
{ 
	return vertex_value ;
}

///////////////////////////////////////////////////////////////
// Get the edges pair vector for the Vertex.
template <typename VertexType, typename EdgeType>
const std::vector<std::pair<int, typename Vertex<VertexType,EdgeType>::edge>>& Vertex<VertexType,EdgeType>::GetEdges() const
{ 
	return edges ;
}

///////////////////////////////////////////////////////////////
// Get the id of the Vertex.
template <typename VertexType, typename EdgeType>
const int& Vertex<VertexType,EdgeType>::GetId() const
{ 
	return id ;
}

///////////////////////////////////////////////////////////////
// Increment Id and assign New Id.
// Should be used after copying vertex outside graph.
template <typename VertexType, typename EdgeType>
void Vertex<VertexType,EdgeType>::ResetId() 
{ 
	id = ++vertex_count;
}

///////////////////////////////////////////////////////////////
// Clear all the edges associated to current vertex.
template <typename VertexType, typename EdgeType>
void Vertex<VertexType,EdgeType>::ClearEdges()
{ 
	edges.clear();
}

#endif
