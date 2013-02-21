#ifndef EXECUTIVE_H
#define EXECUTIVE_H
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Executive.h (ver 1.0)  -  Executive Module that Starts the Testing & Prints Summay output.	     		  // 																					   
//		 																									  //
//	Language		:   Visual C++, 2010																	  //
//	Platform		:   Toshiba Satellite (R25-S3503), Windows 7 Professional								  //
//	Application		:	CSE687 - Project #1 - CodeMetricsAnalyzer, Spring 2011								  //
//	Author			:   Harshal Bhakta, Syracuse University.												  //
//	E-mail			:   harshal.c.bhakta@gmail.com															  //
//	Cell			:   714-876-4273																		  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
  Module Operations: 
  ==================

  This module acts as the executive controller. It fetches the list of the files from 
  the CmdLineAgrs. It further used uses the facility developed for Project 3 to test and 
  display results. The Executive generates the graph from XML Metadata files and test various 
  algorithms on the files.

  Public Interface:
  =================
  
  	void GenerateGraphFromXMLFiles(const std::vector<std::string>&); // Test Project 3 by building graph from xml.
	void TestRequirement4();										 // Test Requirement 4
	void TestRequirement5();										 // Test Requirement 5
	void TestRequirement7();										 // Test Requirement 7

  Build Process:
  ==============
  Required files
    - Executive.h, Executive.cpp, Scanner.h, Scanner.cpp
	- Graph.h, Graph.cpp, GraphAlgorithm.h, GraphAlgorithm.cpp
	- XMLGraphCreator.h ,XMLGraphCreator.cpp
	- WinTools.h, WinTools.cpp, FileInfo.h, FileInfo.cpp, StringConversions.h,StringConversions.cpp
	- XmlDocument.h,XmlDocument.cpp,XmlElementParts.h,XmlElementParts.cpp,XmlNodes.h, XmlNodes.cpp
	- XmlDocumentFactories.h, XmlDocuementFactories.cpp, MTree.h, MTree.cpp,MNode.h,MNode.cpp
	- itokcollection.h, IXmlDocument.h, Tokenizer.h, Tokenizer.cpp
  
  Build commands
    - devenv GraphDepFacility.sln /rebuild debug

  Maintenance History:
  ====================
  ver 1.0 : 11 Apr 11
  - first release
*/

#include <string>
#include <iostream>
#include <vector>
#include "GraphAlgorithm.h"
#include "Display.h"
#include "Graph.h"

////////////////////////////////////////////////////////////////////
// Executive Controller class to test Graph Dep Facility.
class Executive{

public :

	void GenerateGraphFromXMLFiles(const std::vector<std::string>&);

	void TestRequirement4();

	void TestRequirement5();

	void TestRequirement7();

private : 

	void TestVertexCopyAndAssignment();

	void TestGraphCopyAndAssignment();

	void TestDepthFirstSearch();

	void TestCondensedGraph();

	void TestVertexSearch();

	void TestEdgeSearch();

	template <typename VertexType,typename EdgeType>
	void SearchOnXMLGeneratedGraph(const Graph<VertexType,EdgeType>&);

};

///////////////////////////////////////////////////////////////
// Templatized function to search Vertex & Edge.
template <typename VertexType,typename EdgeType>
void Executive::SearchOnXMLGeneratedGraph(const Graph<VertexType,EdgeType>& xml_graph)
{
	Display dp;

	std::cout<<"\n Testing Search By Vertex. Search Value = Parser " 
		 << "\n "<< std::string(55,'=');

	GraphAlgorithm::VertexComparator<std::string,std::string> _comp;
	std::string search_name = "parser";

	std::vector<Vertex<std::string,std::string>> _vertex = GraphAlgorithm::FetchVertex(xml_graph,_comp,search_name);
	
	std::cout<<"\n\n Vertex Found : "<< _vertex.size() << "\n "
		<< std::string(55,'-') << "\n";

	for ( int i = 0 ; i < (int) _vertex.size() ; i++ )
	{	
		dp.PrintVertex(_vertex[i]);
	}

	std::cout<<"\n\n Testing Search By Edge. Search Value = 'C:\\Harshal\\OOD' " 
		<< "\n "<< std::string(55,'=');

	GraphAlgorithm::EdgeComparator<std::string,std::string> _compEdge;

	search_name = "C:\\Harshal\\OOD";

	std::vector<GraphAlgorithm::EdgeItem<std::string,std::string>> edge_items = GraphAlgorithm::FetchEdges(xml_graph,_compEdge,search_name);

	std::cout<<"\n\n Edges Found : "<< edge_items.size() 
		<< "\n" << std::string(55,'-') << "\n";
	
	for ( int i = 0 ; i < (int) edge_items.size() ; i++ )
	{
		std::cout<<" From Vertex = " << edge_items[i].from_vertex.GetVertex() << " Edge = "<< edge_items[i].edge << " To Vertex = " << edge_items[i].to_vertex.GetVertex() << "\n" ;	
	}
}




#endif