////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// XMLGraphCreator.cpp (ver 1.0)- Class to be used for Constructing a Graph from XML Files.        		      // 																					   
//		 																									  //
//	Language		:   Microsoft Visual C++, 2010															  //
//	Platform		:   Toshiba Satellite (R25-S3503), Windows 7 Professional								  //
//	Application		:	CSE687 - Project #3 - Dependency Graph Facility, Spring 2011						  //
//	Author			:   Harshal Bhakta, Syracuse University.												  //
//	E-mail			:   harshal.c.bhakta@gmail.com															  //
//	Cell			:   714-876-4273																		  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "XMLGraphCreator.h"

///////////////////////////////////////////////////////////////
// Public function to build the graph.
void XMLGraphCreator::BuildGraph(const std::vector<std::string>& _files,Graph<std::string,std::string>& _graph)
{
	for each ( std::string file in _files )
	{
		Scanner sc;
	
		try 
		{

			Package pk = sc.ScanXMLPackageFile(file);
		
			if ( pk.getPackageName() != "" )
			{
				nodes[pk.getPackageName()] = pk;
			}
		}
		catch ( std::exception& ex)
		{
			std::cout<<"\n Error scanning file :" << file << " " << ex.what();
		}
		catch (...)
		{
			std::cout<<"\n Error scanning file :" << file;
		}
	}

	BuildVertex();

	BuildEdges();

	GenerateGraph(_graph);
}

///////////////////////////////////////////////////////////////
// Function to generate vertex for all detected packages.
void XMLGraphCreator::BuildVertex()
{
	std::map<std::string,Package>::iterator it = nodes.begin();

	while ( it != nodes.end() )
	{
		try 
		{
			Package pk = it->second;
			
			Vertex<std::string,std::string> vt;
			vt.SetValue(pk.getPackageName());

			nodes_vertex[it->first] = vt;
		}
		catch ( std::exception& ex )
		{
			std::cout<<"\n Error Creating Vertex" << ex.what();
		}

		++it;
	}
}

///////////////////////////////////////////////////////////////
// Function to connect pacakge vertex with approriate edges.
void XMLGraphCreator::BuildEdges()
{
	std::map<std::string,Vertex<std::string,std::string>>::iterator it = nodes_vertex.begin();

	while ( it != nodes_vertex.end() )
	{
		try 
		{

			Package source_pk = nodes[it->first];

			std::vector<std::string> dep = source_pk.getDependencyList();

			for ( int i = 0 ; i < (int)dep.size() ; i++ )
			{
				Package dest_pk = nodes[dep[i]];

				std::string path = getPackagePath(dest_pk);
			
				if ( IsVertexExist(dep[i]) )
				{
					nodes_vertex[it->first].AddEdge(nodes_vertex[dep[i]],path);	
				}
			}

		}
		catch ( std::exception& ex )
		{
			std::cout<<"\n Error Creating Vertex" << ex.what();
		}

		++it;
	}
}

///////////////////////////////////////////////////////////////
// Function to fetch the package path to be used for edge.
std::string XMLGraphCreator::getPackagePath(Package& pk)
{
	std::string path = "NIL";
	
	if ( pk.getHeader() != "NA" )
	{
		path = pk.getHeader();

		path = path.substr(0,path.find_last_of("\\"));	
	}
	else if ( pk.getSource() != "NA" )
	{
		path = pk.getSource();

		path = path.substr(0,path.find_last_of("\\"));	
	}

	return path;
}

///////////////////////////////////////////////////////////////
// Function to generate graph. Add Vertex and Edges to the graph.
void XMLGraphCreator::GenerateGraph(Graph<std::string,std::string>& _graph)
{
	_graph.ResetGraph();

	std::map<std::string,Vertex<std::string,std::string>>::iterator it = nodes_vertex.begin();

	while ( it != nodes_vertex.end() )
	{
		_graph.addVertex(it->second);

		++it;
	}
}

///////////////////////////////////////////////////////////////
// Function to check if a vertex exsists or not for a package.
bool XMLGraphCreator::IsVertexExist(std::string _package)
{
	bool exists = false;

	std::map<std::string,Vertex<std::string,std::string>>::iterator it = nodes_vertex.begin();

	while ( it != nodes_vertex.end() )
	{
		if ( it->first == _package )
		   { 
			   exists = true; 
			   break; 
		   }

		++it;
	}

	return exists;
}

//
//----< test stub >--------------------------------------------

#ifdef XMLGRAPHCREATOR

int main( int argc, char* argv[])
{
	XMLGraphCreator xml;

	std::cout<<"\n\n Creating Graph for parser.xml,tokenizer.xml & semiexpression.xml : ";

	std::cout << "\n "<< std::string(55,'=');

	std::vector<std::string> files;
	files.push_back("..\\MetadataRepository\\parser.xml");
	files.push_back("..\\MetadataRepository\\tokenizer.xml");
	files.push_back("..\\MetadataRepository\\semiexpression.xml");

	Graph<std::string,std::string> g;

	xml.BuildGraph(files,g);

	VertexFunctor<std::string,std::string> vf;

	g.DepthFirstSearch(vf,g.VERTEX_EDGE);

	CondensedOperation<std::string,std::string> co;

	g.CreateCondensedGraph(co);

	std::cout<<"\n\n";

}

#endif