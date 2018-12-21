/***************************************************************************
 *   Copyright (C) 2018 by Hendrik Vennekate                               *
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

#include <cxxtest/TestSuite.h>
#include "utilities.h"
#include <sumformula.h>

using namespace Molsketch;

class SumFormulaUnitTest : public CxxTest::TestSuite {
public:
  void testCreation() {
    QS_ASSERT_EQUALS(SumFormula{"A"}.toString(), QString("A"));

    auto a2 = SumFormula{"A", 2};
    QS_ASSERT_EQUALS(a2.toString(), QString("A2"));

    auto ach = SumFormula{{"A"}, {"C"}, {"H"}};
    QS_ASSERT_EQUALS(ach.toString(), QString("CHA"));

    auto aa = SumFormula{{"A"}, {"H"}, {"A"}};
    QS_ASSERT_EQUALS(aa.toString(), QString("HA2"));
  }

  void testFormatting() {
    QS_ASSERT_EQUALS(SumFormula{"A"}.toHtml(), QString("A"));

    auto a2 = SumFormula{"A", 20};
    QS_ASSERT_EQUALS(a2.toHtml(), QString("A<sub>20</sub>"));

    auto ach = SumFormula{{"A"}, {"C"}, {"H"}};
    QS_ASSERT_EQUALS(ach.toHtml(), QString("CHA"));

    auto aa = SumFormula{{"A"}, {"H"}, {"A"}};
    QS_ASSERT_EQUALS(aa.toHtml(), QString("HA<sub>2</sub>"));

    auto withEmptyElement = SumFormula{{"A"}, {"B", 0}};
    QS_ASSERT_EQUALS(withEmptyElement, SumFormula{"A"});

    auto withNegativeElement = SumFormula{{"A"}, {"B", -1}};
    QS_ASSERT_EQUALS(withEmptyElement, SumFormula{"A"});
  }

  void testAdding() {
    QS_ASSERT_EQUALS((SumFormula{"A"} + SumFormula{"B"}).toString(), QString("AB"));
    QS_ASSERT_EQUALS((SumFormula{"B"} + SumFormula{"A"}).toString(), QString("AB"));
    QS_ASSERT_EQUALS((SumFormula{"A"} + SumFormula{"A"}).toString(), QString("A2"));
    QS_ASSERT_EQUALS((SumFormula{"Ab"} + SumFormula{"A"}).toString(), QString("AAb"));

    auto a2 = SumFormula{"A", 2};
    QS_ASSERT_EQUALS((a2 + SumFormula{"A"}).toString(), QString("A3"));

    auto a1b = SumFormula{{"A", 1}, {"B"}};
    QS_ASSERT_EQUALS((a1b + SumFormula{"B"}).toString(), QString("AB2"));

    auto a1b2c3 = SumFormula{{"A", 1}, {"B", 2}, {"C", 3}};
    auto d3c5a = SumFormula{{"D", 3}, {"C", 5}, {"A"}};
    QS_ASSERT_EQUALS((a1b2c3 + d3c5a).toString(), QString("C8A2B2D3"));
  }

  void testEquality() {
    TS_ASSERT(SumFormula{"A"} == SumFormula("A"));
    TS_ASSERT(SumFormula{"B"} != SumFormula("A"));

    auto aa = SumFormula{{"A"}, {"A"}};
    auto a2 = SumFormula{{"A", 2}};
    TS_ASSERT(aa == a2);

    auto abc = SumFormula{{"A"}, {"B"}, {"C"}};
    auto cba = SumFormula{{"C"}, {"B"}, {"A"}};
    TS_ASSERT(abc == cba);

    auto ab = SumFormula{{"A"}, {"B"}};
    auto abElement = SumFormula{{"AB"}};
    TS_ASSERT(ab != abElement);
  }

  void testParsingString() {
    QS_ASSERT_EQUALS(SumFormula::fromString("A"), SumFormula("A"));

    auto ab = SumFormula{{"A"}, {"B"}};
    QS_ASSERT_EQUALS(SumFormula::fromString("AB"), ab);
    QS_ASSERT_EQUALS(SumFormula::fromString("BA"), ab);

    QS_ASSERT_EQUALS(SumFormula::fromString("Ab"), SumFormula("Ab"));

    auto aaa = SumFormula{{"A"}, {"Aa"}};
    QS_ASSERT_EQUALS(SumFormula::fromString("AAa"), aaa);
    QS_ASSERT_EQUALS(SumFormula::fromString("AaA"), aaa);

    auto a2aa = SumFormula{{"A", 2}, {"Aa"}};
    QS_ASSERT_EQUALS(SumFormula::fromString("AAAa"), a2aa);
    QS_ASSERT_EQUALS(SumFormula::fromString("A2Aa"), a2aa);
    QS_ASSERT_EQUALS(SumFormula::fromString("AAaA"), a2aa);
    QS_ASSERT_EQUALS(SumFormula::fromString("AaAA"), a2aa);
    QS_ASSERT_EQUALS(SumFormula::fromString("AaA2"), a2aa);

    auto aa2a = SumFormula{{"A"}, {"Aa", 2}};
    QS_ASSERT_EQUALS(SumFormula::fromString("AaAaA"), aa2a);
    QS_ASSERT_EQUALS(SumFormula::fromString("Aa2A"), aa2a);
    QS_ASSERT_EQUALS(SumFormula::fromString("AaAAa"), aa2a);
    QS_ASSERT_EQUALS(SumFormula::fromString("AAaAa"), aa2a);
    QS_ASSERT_EQUALS(SumFormula::fromString("AAa2"), aa2a);

    auto a2 = SumFormula{{"A", 2}};
    QS_ASSERT_EQUALS(SumFormula::fromString("A2"), a2);
    QS_ASSERT_EQUALS(SumFormula::fromString("AA"), a2);

    auto a1b2c3 = SumFormula{{"A", 1}, {"B", 2}, {"C", 3}};
    QS_ASSERT_EQUALS(SumFormula::fromString("AB2C3"), a1b2c3);
  }

  void testValidityCheck() {
    bool valid = false;
    QString result;

    result = SumFormula::fromString("C3H5", &valid);
    auto c3h5 = SumFormula{{"C", 3}, {"H", 5}};
    TS_ASSERT(valid);
    QS_ASSERT_EQUALS(result, c3h5);

    result = SumFormula::fromString("C3", &valid);
    auto c3 = SumFormula{{"C", 3}};
    TS_ASSERT(valid);
    QS_ASSERT_EQUALS(result, c3);

    result = SumFormula::fromString("CaO", &valid);
    auto cao = SumFormula{{"Ca"}, {"O"}};
    TS_ASSERT(valid);
    QS_ASSERT_EQUALS(result, cao);

    result = SumFormula::fromString("Na2O", &valid);
    auto na2o = SumFormula{{"Na", 2}, {"O"}};
    TS_ASSERT(valid);
    QS_ASSERT_EQUALS(result, na2o);

    result = SumFormula::fromString("TosH", &valid);
    auto tosh = SumFormula{{"Tos"}, {"H"}};
    TS_ASSERT(valid);
    QS_ASSERT_EQUALS(result, tosh);

    result = SumFormula::fromString("", &valid);
    TS_ASSERT(!valid);
    QS_ASSERT_EQUALS(result, SumFormula());

    result = SumFormula::fromString("aC", &valid);
    TS_ASSERT(!valid);
    QS_ASSERT_EQUALS(result, SumFormula());

    result = SumFormula::fromString("C H 3", &valid);
    TS_ASSERT(!valid);
    QS_ASSERT_EQUALS(result, SumFormula());
  }
};
