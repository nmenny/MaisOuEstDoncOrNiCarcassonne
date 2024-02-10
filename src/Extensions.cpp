/*
    Copyright: (c) 2022, Bigotte Adrien, Lemkhali Bilal, Maistre Elise, Menny Nathan
    GNU General Public License v3.0+ (see COPYING or https://www.gnu.org/licenses/gpl-3.0.txt)
*/

#include "Extensions.h"

namespace Carcassonne {

vector<string> getMeeples(vector<extensions> ext) {
       vector<string> res;

       set<string> s;

       for(extensions e : ext) {
           switch(e) {
           case extensions::Base:
               s.insert("Meeple");
               break;
           case extensions::Abbe:
               s.insert("Abbe");
               break;
           case extensions::Auberge:
               s.insert("Gd Meeple");
               break;
           default:
                break;
           }
       }

       for(string ch : s) {
           res.push_back(ch);
       }

       return res;
   }

    std::string toString(extensions e) {
        switch(e) {
        case extensions::Base:
            return "Base";
            break;
        case extensions::Paysans:
            return "Paysans";
            break;
        case extensions::Abbe:
            return "Abbe";
            break;
        case extensions::Riviere:
            return "Riviere";
            break;
        case extensions::Auberge:
            return "Auberge";
            break;
        default:
            return "";
        }
    }
}
