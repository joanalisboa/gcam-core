/*
* This software, which is provided in confidence, was prepared by employees of
* Pacific Northwest National Laboratory operated by Battelle Memorial Institute.
* Battelle has certain unperfected rights in the software which should not be
* copied or otherwise disseminated outside your organization without the express
* written authorization from Battelle. All rights to the software are reserved
* by Battelle. Battelle makes no warranty, express or implied, and assumes no
* liability or responsibility for the use of this software.
*/

/*! 
* \file land_allocator_printer.cpp
* \ingroup Objects
* \brief The LandAllocatorPrinter class source file.
*
* \author Jim Naslund
*/

#include "util/base/include/definitions.h"

#include <boost/lexical_cast.hpp>

#include "reporting/include/land_allocator_printer.h"
#include "util/base/include/util.h"
#include "containers/include/region.h"
#include "land_allocator/include/land_leaf.h"
#include "land_allocator/include/land_node.h"

using namespace std;

/*! 
* \brief Default Constructor
* \param aRegionToPrint region to print.
* \param aFile file to print to.
*/
LandAllocatorPrinter::LandAllocatorPrinter( const std::string& aRegionToPrint, std::ostream& aFile ):
mFile( aFile ),
mCorrectRegion(false),
mRegionToPrint(aRegionToPrint),
mNumNodes(0)
{
}

/*!
* \brief Begin visiting a region with the graph printer.
* \details Opens the graph and prints the header.
* \param aRegion Region to visit.
* \param aPeriod Period for which to visit.
*/
void LandAllocatorPrinter::startVisitRegion( const Region* aRegion, const int aPeriod ){
    // Check if this is the region to print.
    if(aRegion->getName() == mRegionToPrint ){
        mCorrectRegion = true;
        // Print the graph header.
        mFile << "digraph " << util::replaceSpaces( aRegion->getName() ) << " {" << endl;
    }
    else {
        // Don't print this region.
        mCorrectRegion = false;
    }
}

/*!
* \brief End visiting a region with the graph printer.
* \details Closes the graph.
* \param aRegion Region to visit.
* \param aPeriod Period for which to visit.
*/
void LandAllocatorPrinter::endVisitRegion( const Region* aRegion, const int aPeriod ){
    if( mCorrectRegion ){
        // Now close the graph.
        mFile << "}" << endl << endl;
    }
}

/*!
* \brief Begin visiting a landNode.
* \details Outputs the node, its parent-child relationship if application and
* \details pushes its name onto the parent stack.
* \param aLandNode landNode to visit.
* \param aPeriod Period for which to visit.
*/
void LandAllocatorPrinter::startVisitLandNode(const LandNode *aLandNode, const int aPeriod){
    if( !mCorrectRegion ){
        return;
    }

    // Print the node.
    printNode( aLandNode->getName() );

    if( !mParent.empty() ){
        // Print the parent link.
        printParentChildRelationship( aLandNode->getName() );
    }
    mParent.push( util::replaceSpaces( makeNameFromLabel( aLandNode->getName() ) ) );
    mNumNodes++;
}

/*!
* \brief End visiting a land node.
* \details Pops its own name off the parent names stack.
* \param aLandNode node to end visiting.
* \param aPeriod Period for which to end visiting.
*/
void LandAllocatorPrinter::endVisitLandNode(const LandNode *aLandNode, const int aPeriod){
    if( !mCorrectRegion ){
        return;
    }
    mParent.pop();
}

/*!
* \brief Begin visiting a landLeaf.
* \details Outputs the node, its parent-child relationship (it always has a parent)
* \param aLandNode landLeaf to visit.
* \param aPeriod Period for which to visit.
*/
void LandAllocatorPrinter::startVisitLandLeaf( const LandLeaf *aLandLeaf, const int aPeriod ){
    if( !mCorrectRegion ){
        return;
    }
    printNode( aLandLeaf->getName(), true );
    printParentChildRelationship( aLandLeaf->getName() );
    mNumNodes++;
}

/*!
* \brief Outputs a node.
* \details Outputs a node.  Creates a unique name for the node.
* \param aName name of node
*/
void LandAllocatorPrinter::printNode( const string& aName, const bool aIsLeaf ) const{
    string nameStripped = util::replaceSpaces( aName );
    mFile << "\t" << makeNameFromLabel( aName ) << "[label=" << nameStripped;
    if(aIsLeaf){
        mFile << ", shape=box";
    }
    mFile << "];" << endl;
}

/*!
* \brief Outputs the parent-child relationship between two nodes.
* \details Outputs the link from a parent node to its child node.
* \param aName name of node
*/
void LandAllocatorPrinter::printParentChildRelationship( const string& aName ) const{
    mFile << "\t" << mParent.top() << "->" << util::replaceSpaces( makeNameFromLabel( aName ) ) << ";" << endl;
}

/*!
* \brief Creates a unique name for the node.
* \details Prevents duplicate node names from causing problems.
* \param aName name to make unique.
* \return unique name for node.
*/
string LandAllocatorPrinter::makeNameFromLabel( const string& aName ) const{
    return aName + boost::lexical_cast<std::string>(mNumNodes);
}