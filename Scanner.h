#ifndef SCANNER_H
#define SCANNER_H
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Scanner.h - Scan XML Metadata Package Files.															  //
//  ver 2.0																									  //																					  //
//  Language:      Microsoft Visual C++ 2010																  //
//	Application:   CSE687 - Project #3 - Dependency Graph Facility, Spring 2011								  //
//  Platform:      Toshiba Satellite R25-S3503,Win7 Pro.													  //
//  Application:   CSE687 Pr2, Sp11																			  //
//  Author:        Harshal Bhakta, Syracuse University														  //
//                 (714) 876-4273, harshal.c.bhakta@gmail.com												  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
  Module Operations: 
  ==================
  
  The XMLMetadata Generated using the MetadataCreator will hold the info.
  about each package dependency. The dependency structure of the metadata
  xml files is such that if we recursively start traversal of metadata from
  base pacakge, we can fetch the entire project dependency.

  We supply the base package name as input for Scanning.

  Module starts by reading the initial XML File for base package. Dependencies
  for the current module are listed and the dependency packages from the XML 
  are used to pick up their respective XML and recursively perform the same 
  action as performed on the base package.

  Public Interface:
  =================
  
  ScanPackageRecurse(PackageName);			// Function call to recursivly traverse metadata starting at the base package.
  GetFiles();								// Function to get the list of all the files traversed.
  std::vector<Package> GetScannedPackages();// Function to fetch all scanned Packages.
  Package ScanXMLPackageFile(std::string);	// Function to fetch Package for single XML File.

  Build Process:
  ==============
  Required files
    
	- Scanner.h, Scanner.cpp
	- WinTools.h, WinTools.cpp, FileInfo.h, FileInfo.cpp, StringConversions.h,StringConversions.cpp
	- XmlDocument.h,XmlDocument.cpp,XmlElementParts.h,XmlElementParts.cpp,XmlNodes.h, XmlNodes.cpp
	- XmlDocumentFactories.h, XmlDocuementFactories.cpp, MTree.h, MTree.cpp,MNode.h,MNode.cpp
	- itokcollection.h, IXmlDocument.h, Tokenizer.h, Tokenizer.cpp

  Build commands 

    - cl /EHsc /DTEST_SCANNER Scanner.cpp Package.cpp Display.cpp ^
WinTools.cpp FileInfo.cpp XmlDocument.cpp XmlElementParts.cpp ^
XmlNodes.cpp XmlDocumentFactories.cpp MTree.cpp MNode.cpp Tokenizer.cpp

  Maintenance History:
  ====================
  ver 2.0 : 04 Apr 11
  - Addedd Package ScanXMLPackageFile(std::string) to scan single file.
  ver 1.0 : 26 Mar 11
  - first release
*/

#include <iostream>
#include <string>
#include <set>
#include <cctype>
#include "XmlDocument.h"
#include "xmlElementParts.h"
#include "WinTools.h"
#include "Package.h"

////////////////////////////////////////////////////////////////////
// Repository Location for Scanning Files.
// Program exe will look for a folder named MetadataRepository
// within the current folder and find a xml in that folder
#define REPOSITORY_LOCATION "MetadataRepository\\"

////////////////////////////////////////////////////////////////////
// Scanner class responsible for scanning and displaying dependency
class Scanner {

public : 

	Package ScanXMLPackageFile(std::string);	
	
	void ScanPackageRecurse(std::string);

	std::vector<Package> GetScannedPackages();

	std::vector<std::string> GetFiles();

private : 

	// Private Helper Function.
	std::string ExtractPackageName(std::string);
	void ExtractPackageInfo(std::string,std::string);
	void AddFileToList(std::string);
	std::string GetHeaderFile(std::string);
	std::string GetSourceFile(std::string);
	std::string GetTitle(std::string);
	std::vector<std::string> GetPackages(std::string);
	bool isFileExist(std::string);
	bool isFolderExist();
	std::string FormatToLower(std::string);

	// Private Data.
	std::vector<std::string> files;
	std::set<std::string> CompletedPackages;
	std::vector<Package> ScannedPackages;

};

#endif