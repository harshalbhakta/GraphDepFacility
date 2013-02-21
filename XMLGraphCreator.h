#ifndef XMLGRAPHCREATOR_H
#define XMLGRAPHCREATOR_H
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// XMLGraphCreator.h (ver 1.0)- Class to be used for Constructing a Graph from XML Files.        		      // 																					   
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

  XMLGraphCreator class will be responsible for building a graph using the XML Metadatafiles. The module will
  use the Scanner to scan the meta data files and extract Package information for each package. Each pacakge
  detected will have a vertex associated to it in the Graph. The package vertex will be linked to each other
  using "Path" edges based on dependency. Once the Vertex and Edges have been created the Graph received is 
  resetted and filled.

  Public Interface:
  =================   

  Function provided by the class to build a Graph from a list of XML Metadata Files.
  A Graph reference is taken as input and the Graph is then filled with new data.

  void BuildGraph(const std::vector<std::string>&,Graph<std::string,std::string>&); // Generate Graph for XML Files.

  Build Process:
  ==============
  
  Required files
    
	- XMLGraphCreator.h , XMLGraphCreator.cpp
    - WinTools.h, WinTools.cpp, FileInfo.h, FileInfo.cpp, StringConversions.h,StringConversions.cpp
	- XmlDocument.h,XmlDocument.cpp,XmlElementParts.h,XmlElementParts.cpp,XmlNodes.h, XmlNodes.cpp
	- XmlDocumentFactories.h, XmlDocuementFactories.cpp, MTree.h, MTree.cpp,MNode.h,MNode.cpp
	- itokcollection.h, IXmlDocument.h, Tokenizer.h, Tokenizer.cpp

  Build commands
    
	- cl /EHsc /DXMLGRAPHCREATOR XMLGraphCreator.cpp Scanner.cpp Package.cpp Display.cpp ^
WinTools.cpp FileInfo.cpp XmlDocument.cpp XmlElementParts.cpp ^
XmlNodes.cpp XmlDocumentFactories.cpp MTree.cpp MNode.cpp Tokenizer.cpp

  Maintenance History:
  ====================
  ver 1.0 : 31 Mar 11
  - first release
*/

#include "Graph.h"
#include "Package.h"
#include "Scanner.h"
#include <string>

///////////////////////////////////////////////////////////////
// Class to generate Graph for XML Metadata Files.
class XMLGraphCreator {

public:

	void BuildGraph(const std::vector<std::string>&,Graph<std::string,std::string>&);

private:

	// Helper Functions
	void ScanPackages(std::vector<std::string>);
	void BuildVertex();
	void BuildEdges();
	void GenerateGraph(Graph<std::string,std::string>&);
	std::string getPackagePath(Package&);
	bool IsVertexExist(std::string);

	// Memeber Data
	std::map<std::string,Vertex<std::string,std::string>> nodes_vertex;
	std::map<std::string,Package> nodes;
};

#endif