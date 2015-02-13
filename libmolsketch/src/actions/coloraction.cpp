/***************************************************************************
 *   Copyright (C) 2007-2008 by Harm van Eersel                            *
 *   Copyright (C) 2009 Tim Vandermeersch                                  *
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

#include <QColorDialog>
#include "coloraction.h"
#include "commands.h"

namespace Molsketch {

  colorAction::colorAction(MolScene *parent) :
    abstractItemAction(parent)
  {
    setText(tr("Color...")) ;
    setToolTip(tr("Set color")) ;
    setWhatsThis(tr("Displays the color chooser dialog")) ;
  }

  void colorAction::execute()
  {
    QColor newColor = QColorDialog::getColor(items().size() == 1
                                             ? items().first()->getColor()
                                             : QColor()) ;
    if (!newColor.isValid()) return ;

    ITERATEOVERITEMSMACRO("Change color", changeColor, newColor)
  }

}// namespace