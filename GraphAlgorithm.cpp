////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GraphAlgorithm.cpp (ver 1.0)- Holds Global Function to Generate the Graph from a list of metadata files.   // 																					   
//		 																									  //
//	Language		:   Microsoft Visual C++, 2010															  //
//	Platform		:   Toshiba Satellite (R25-S3503), Windows 7 Professional								  //
//	Application		:	CSE687 - Project #3 - Dependency Graph Facility, Spring 2011						  //
//	Author			:   Harshal Bhakta, Syracuse University.												  //
//	E-mail			:   harshal.c.bhakta@gmail.com															  //
//	Cell			:   714-876-4273																		  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "GraphAlgorithm.h"

///////////////////////////////////////////////////////////////
// Global function to generate graph from a list of meta data files.
void GraphAlgorithm::GenerateGraphFromXML(const std::vector<std::string>& _files,Graph<std::string,std::string>& _graph)
{
	XMLGraphCreator graph_creator;

	graph_creator.BuildGraph(_files,_graph);
}

//--------------<<< TEST STUB >>>----------------//

#ifdef TEST_GRAPHALGORITHM

int main(int argc,char* argv[])
{
	std::vector<std::string> files;
	files.push_back("..\\MetadataRepository\\parser.xml");
	files.push_back("..\\MetadataRepository\\tokenizer.xml");
	files.push_back("..\\MetadataRepository\\semiexpression.xml");

	std::cout<<"\n\n Creating Graph for parser.xml,tokenizer.xml & semiexpression.xml : ";

	std::cout << "\n "<< std::string(55,'=');

	Graph<std::string,std::string> g;

	GraphAlgorithm::GenerateGraphFromXML(files,g);

	VertexFunctor<std::string,std::string> vf;

	g.DepthFirstSearch(vf,g.VERTEX_EDGE);

	std::cout<<"\n\n";

}

#endif