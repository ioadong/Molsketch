/***************************************************************************
 *   Copyright (C) 2018 by Hendrik Vennekate, HVennekate@gmx.de            *
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
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/

#ifndef UTILITIES_H
#define UTILITIES_H

#include <QDebug>
#include <QString>
#include <cxxtest/TestSuite.h>
#include <QTest>
#include <functional>

class QTableView;
class QLineEdit;
class QCheckBox;
class QXmlStreamReader;
class QXmlStreamAttributes;

#define QS_ASSERT_EQUALS(VAL1,VAL2) {QString __comparison("\n    "); QDebug __out(&__comparison); __out << VAL1; __comparison += "\n != "; __out << VAL2; TSM_ASSERT_EQUALS(__comparison.toStdString().data(), VAL1, VAL2)}

#define QSM_ASSERT_EQUALS(MESSAGE, VAL1, VAL2) {QString __comparison("\n    "); QDebug __out(&__comparison); __out << VAL1; __comparison += "\n != "; __out << VAL2; TSM_ASSERT_EQUALS((MESSAGE + __comparison).toStdString().data(), VAL1, VAL2)}

#define QSO_ASSERT(ASSERTION, ...) {TSM_ASSERT(joinToString(__VA_ARGS__), ASSERTION)}
#define QSO_ASSERT_EQUALS(VAL1, VAL2, ...) {TSM_ASSERT_EQUALS(joinToString(__VA_ARGS__), VAL1, VAL2)}

template<typename T>
QString joinToString(T t) {
  QString result;
  QDebug(&result) << t;
  return result;
}

template<typename FirstType, typename... InputTypes>
QString joinToString(FirstType firstInput, InputTypes... inputs) {
  return joinToString(firstInput) + joinToString(inputs...);
}

#define QS_ASSERT_ON_POINTER(CAST_TYPE, POINTER, METHOD, VALUE) {\
  TSM_ASSERT(#POINTER " is null", POINTER);\
  if (POINTER) {\
    TSM_ASSERT(#POINTER " is not of type " #CAST_TYPE, dynamic_cast<CAST_TYPE*>(POINTER));\
    CAST_TYPE *p = dynamic_cast<CAST_TYPE*>(POINTER);\
    if (p) QS_ASSERT_EQUALS(p->METHOD, VALUE)\
  }\
  }

void mouseMoveEvent(QWidget *widget, Qt::MouseButton button, Qt::KeyboardModifiers stateKey, QPoint pos, int delay=-1);

void enterDataIntoCell(QTableView *table, const QString& data, int row, int column);

void enterTextIntoInputWidget(QLineEdit *editor, const QString& text, int position = 0);

void clickCheckBox(QCheckBox* checkBox);

template<class T>
class ForTesting {
public:
  static int instanceCounter;
  ForTesting<T>() { ++ instanceCounter; }
  ~ForTesting<T>() { -- instanceCounter; }
};

// Don't forget to add instanceCounter to instanceCounter.cpp
#define CLASS_FOR_TESTING_WITH_FUNCTIONS(CLASSNAME, CONTENT) \
  class CLASSNAME##ForTesting : public CLASSNAME, public ForTesting<CLASSNAME>{ CONTENT };

#define CLASS_FOR_TESTING(CLASSNAME) CLASS_FOR_TESTING_WITH_FUNCTIONS(CLASSNAME,)

template<class T>
T* assertNotNull(T* pointer, QString message = "Should not be null") {
  TSM_ASSERT_DIFFERS(message.toStdString().data(), pointer, nullptr);
  if (!pointer) throw nullptr;
  return pointer;
}
void assertTrue(bool input, QString message = "Assertion not fulfilled!");

bool findNextElement(QXmlStreamReader& reader, const QString& element);

int xmlElementCount(const QString& xml, const QString& element);

QPolygonF getPointsFromXml(const QXmlStreamReader& reader, const QString& attribute);

QXmlStreamAttributes getAttributesOfParentElement(QXmlStreamReader& reader, const QString &element);

#endif // UTILITIES_H
