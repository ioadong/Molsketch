/***************************************************************************
 *   Copyright (C) 2017 by Hendrik Vennekate                               *
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
#ifndef MOLSKETCH_LONEPAIR_H
#define MOLSKETCH_LONEPAIR_H

#include "boundingboxlinker.h"
#include <QGraphicsItem>
#include <QtGlobal>

namespace Molsketch {

class LonePairPrivate;

class LonePair : public QGraphicsItem, public abstractXmlObject {
  Q_DECLARE_PRIVATE (LonePair)
  QScopedPointer<LonePairPrivate> d_ptr;

public:
  // TODO use static methods/offer methods to change properties
  explicit LonePair (qreal angle, qreal lineWidth, qreal length, BoundingBoxLinker linker = BoundingBoxLinker (Anchor::Top), const QColor& color = QColor ());
  LonePair (const LonePair& other);
  ~LonePair ();
  BoundingBoxLinker linker () const;
  friend QDebug operator<< (QDebug debug, const LonePair& lonePair);
  QRectF boundingRect () const override;
  void paint (QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
  QString xmlName () const override;

protected:
  XmlObjectInterface* produceChild (const QString& name, const QString& type) override;
  void readAttributes (const QXmlStreamAttributes& attributes) override;
  QList<const XmlObjectInterface*> children () const override;
  QXmlStreamAttributes xmlAttributes () const override;
};

} // namespace Molsketch

#endif // MOLSKETCH_LONEPAIR_H
