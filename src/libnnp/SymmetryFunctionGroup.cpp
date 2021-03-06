// n2p2 - A neural network potential package
// Copyright (C) 2018 Andreas Singraber (University of Vienna)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "SymmetryFunctionGroup.h"
#include "utility.h"

using namespace std;
using namespace nnp;

SymmetryFunctionGroup::PrintFormat const
SymmetryFunctionGroup::printFormat = initializePrintFormat();

SymmetryFunctionGroup::PrintOrder const
SymmetryFunctionGroup::printOrder = initializePrintOrder();

SymmetryFunctionGroup::
SymmetryFunctionGroup(size_t type, ElementMap const& elementMap) :
    type       (type                   ),
    elementMap (elementMap             ),
    index      (0                      ),
    ec         (0                      ),
    rc         (0.0                    ),
    cutoffAlpha(0.0                    ),
    convLength (1.0                    ),
    cutoffType (CutoffFunction::CT_HARD)
{
    // Add standard common parameter IDs to set.
    parametersCommon.insert("index");
    parametersCommon.insert("type");
    parametersCommon.insert("ec");
    parametersCommon.insert("rc");
    parametersCommon.insert("cutoffType");
    parametersCommon.insert("cutoffAlpha");

    // Add standard member parameter IDs to set.
    parametersMember.insert("lineNumber");
}

SymmetryFunctionGroup::PrintFormat const
SymmetryFunctionGroup::initializePrintFormat()
{
    PrintFormat pf;

    pf["index"]       = make_pair("%4zu" , string(4, ' '));
    pf["ec"]          = make_pair("%2s"  , string(2, ' '));
    pf["type"]        = make_pair("%2zu" , string(2, ' '));
    pf["e1"]          = make_pair("%2s"  , string(2, ' '));
    pf["e2"]          = make_pair("%2s"  , string(2, ' '));
    pf["eta"]         = make_pair("%9.3E", string(9, ' '));
    pf["rs"]          = make_pair("%9.3E", string(9, ' '));
    pf["lambda"]      = make_pair("%2.0f", string(2, ' '));
    pf["zeta"]        = make_pair("%4.1f", string(4, ' '));
    pf["rc"]          = make_pair("%9.3E", string(9, ' '));
    pf["cutoffType"]  = make_pair("%2d"  , string(2, ' '));
    pf["cutoffAlpha"] = make_pair("%4.2f", string(4, ' '));
    pf["lineNumber"]  = make_pair("%5zu" , string(5, ' '));
    pf["mindex"]      = make_pair("%4zu" , string(4, ' '));
    pf["sfindex"]     = make_pair("%4zu" , string(4, ' '));
    pf["calcexp"]     = make_pair("%1d"  , string(1, ' '));

    return pf;
}

SymmetryFunctionGroup::PrintOrder const
SymmetryFunctionGroup::initializePrintOrder()
{
    vector<string> po;

    po.push_back("index"      );
    po.push_back("ec"         );
    po.push_back("type"       );
    po.push_back("e1"         );
    po.push_back("e2"         );
    po.push_back("eta"        );
    po.push_back("rs"         );
    po.push_back("lambda"     );
    po.push_back("zeta"       );
    po.push_back("rc"         );
    po.push_back("cutoffType" );
    po.push_back("cutoffAlpha");
    po.push_back("lineNumber" );
    po.push_back("mindex"     );
    po.push_back("sfindex"    );
    po.push_back("calcexp"    );

    return po;
}

string SymmetryFunctionGroup::getPrintFormatCommon() const
{
    string s;

    for (PrintOrder::const_iterator it = printOrder.begin();
         it != printOrder.end(); ++it)
    {
        // If common parameter is present add format string.
        if (parametersCommon.find(*it) != parametersCommon.end())
        {
            s += safeFind(printFormat, (*it)).first + ' ';
        }
        // Else if member parameter is present add star marker.
        else if (parametersMember.find(*it) != parametersMember.end())
        {
            string t = safeFind(printFormat, (*it)).second;
            if (t.size () > 0)  t.resize (t.size () - 1);
            t += '*';
            s += t + ' ';
        }
        // Else add just enough empty spaces.
        else 
        {
            s += safeFind(printFormat, (*it)).second + ' ';
        }
    }
    // Remove extra space at the end.
    if (s.size () > 0)  s.resize (s.size () - 1);
    s += '\n';

    return s;
}

string SymmetryFunctionGroup::getPrintFormatMember() const
{
    string s;

    for (PrintOrder::const_iterator it = printOrder.begin();
         it != printOrder.end(); ++it)
    {
        // If common parameter is present add format string.
        if (parametersMember.find(*it) != parametersMember.end())
        {
            s += safeFind(printFormat, (*it)).first + ' ';
        }
        // Else if member parameter is present add star marker.
        else if (parametersCommon.find(*it) != parametersCommon.end())
        {
            string t = safeFind(printFormat, (*it)).second;
            if (t.size () > 0)  t.resize (t.size () - 1);
            t += '-';
            s += t + ' ';
        }
        // Else add just enough empty spaces.
        else 
        {
            s += safeFind(printFormat, (*it)).second + ' ';
        }
    }
    // Remove extra space at the end.
    if (s.size () > 0)  s.resize (s.size () - 1);
    s += '\n';

    return s;
}
