#ifndef GRAPHALGORITHM_H
#define GRAPHALGORITHM_H
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GraphAlgorithm.h (ver 1.0)- 	Holds Global Algorithm to Generate the Graph from a list of metadata files.   // 																					   
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

  Graph Algorithm module is responsible for providing a global algortihm to be used for generating graph
  from metadata files. GraphAlgorithg will be using the facility of XMLGraphCreator class to 
  generate and return reference of the graph for metadata files.

  Public Interface:
  =================

  Global algorithm to Generate Graph from a list of Metadata Files.

  The algorithm accepts a list of filenames and a Reference to a Graph.

  The algorithm fills the referenced graph with the information extracted from metadata files.

  void GenerateGraphFromXML(const std::vector<std::string>&,Graph<std::string,std::string>&);

  Build Process:
  ==============
  
  Required files
    
	- GraphAlgorithm.h, GraphAlgorithm.cpp
  
  Build commands
    
	- cl /EHsc /DTEST_GRAPHALGORITHM GraphAlgorithm.cpp

  Maintenance History:
  ====================
  ver 1.0 : 31 Mar 11
  - first release
*/

#include <vector>
#include "Graph.h"
#include "XMLGraphCreator.h"
#include <list>

///////////////////////////////////////////////////////////////
// Graph Algorithm namespace.
namespace GraphAlgorithm 
{
	///////////////////////////////////////////////////////////////
	// Global function to generate graph from a list of meta data files.
	void GenerateGraphFromXML(const std::vector<std::string>&,Graph<std::string,std::string>&);
}

#endif