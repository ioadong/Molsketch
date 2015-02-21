/***************************************************************************
 *   Copyright (C) 2014 by Hendrik Vennekate                               *
 *   HVennekate@gmx.de                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifndef OBABELIFACE_H
#define OBABELIFACE_H

#include <QString>
#include <vector>

class QGraphicsScene ;

namespace Molsketch
{
  class Molecule ;
  class Atom ;
  class Bond ;
}

extern "C"
{
  namespace Molsketch
  {
/**
 * Generate SMILES string from molecule
 */
    QString smiles(const Molecule*) ;
    typedef QString (*smilesFunctionPointer)(const Molecule*) ;
    /**
 * Load and save routines
 *
 * @author Harm van Eersel (modified by H. Vennekate)
 */

/** 
 * Loads file with @p fileName and returns it as pointer to a new Molecule 
 * object. 
 */
    Molecule* loadFile(const QString &fileName);
    typedef Molecule* (*loadFileFunctionPointer)(const QString&) ;
/** 
 * Saves the current document under @p fileName and returns @c false if the
 * save failed.
 */
    bool saveFile(const QString &fileName, QGraphicsScene * scene, unsigned short int dim = 2);
    typedef bool (*saveFileFunctionPointer)(const QString&, QGraphicsScene*, unsigned short int) ;
/**
 * Get symmetry numbers for atoms
 */
    void getSymmetryClasses(const Molecule* molecule, std::vector<unsigned int>& symmetry_classes) ;
    typedef void (*getSymmetryClassesFunctionPointer)(const Molecule*, std::vector<unsigned int>&) ;
/**
 * Get chiral atoms for molecule @p molecule
 */
    QList<Atom*> chiralAtoms(const Molecule* molecule) ;
    typedef QList<Atom*> (*chiralAtomsFunctionPointer)(const Molecule*) ;
/**
 * Load Molecule from image (OSRA)
 */
    Molecule*  call_osra(QString fileName);
    typedef Molecule* (*callOsraFunctionPointer)(QString) ;
  } // namespace
} // extern "C"

#endif //OBABELIFACE_H