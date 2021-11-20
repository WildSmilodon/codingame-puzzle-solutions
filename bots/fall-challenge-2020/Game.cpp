#include "Game.h"

	Game::Game() {} // default constructor


    int Game::eval(Player p, int startRupees) {

        int score = p.inv.total();

        score = score + 10000 * (p.rupees - startRupees);        

        int minNegTot = 0;
        for (Action r : recipes) {
            Quad newInv = p.inv + r.delta;
            int val = 100 * newInv.negTotal();
            if ( val < minNegTot) { minNegTot = val; }
        }
        score = score + minNegTot;

        return score;
    }


    void Game::play(Player& p, Action a) {
        if (a.type == "BREW") {
            p.rupees = p.rupees + a.price;
            p.inv = p.inv + a.delta;
            // must dissapear from recipes
            for (Action& r : recipes) {
                if (r.id == r.id) {
                    r.delta.val[0]=1000; // not possible to achieve
                }
            }
        }
        if (a.type == "CAST") {
            p.inv = p.inv + a.delta;
            for (Action& s : spells) {
                if (s.id == a.id) {
                    s.castable = false;
                }                
            }
        }
        if (a.type == "LEARN") {
            // Pay to learn
            p.inv.val[0] = p.inv.val[0] - a.placeInTome;
            // Collect tax
            int toAdd = a.taxCount;
            if (10-p.inv.total() < a.taxCount) {toAdd = 10 - p.inv.total(); }
            p.inv.val[0] = p.inv.val[0] + toAdd;
            // Add spell
            Action aa = a;
            aa.type = "SPELL";
            aa.castable = true;
            spells.push_back(aa);
            // must dissapear from tome
            for (Action& t : tome) {
                if (t.id == a.id) {
                    t.placeInTome = 1000;
                } else {
                    t.placeInTome--;
                }                
            }

        }
        if (a.type == "REST") {
            for (Action& s : spells) {
                s.castable = true;
            }
        }
        if (a.type == "WAIT") {
        }


    }


    std::vector<Action> Game::listAvailableActions(Player p) {

        std::vector<Action> actions;

        // Consider brewing
        for (Action t : tome) {
            if (t.can(p.inv)) {
                actions.push_back(t);
            }
        }

        // Add rest action
        bool canIrest = false;
        for (Action s : spells) {
            if (s.castable == false) { canIrest = true;}
        }
        if (canIrest) {
            Action rest;
            actions.push_back(rest);
        }

        // Consider brewing
        for (Action r : recipes) {
            if (r.can(p.inv)) {
                actions.push_back(r);
            }
        }

        // Consider casting
        for (Action s : spells) {
            if (s.can(p.inv)) {
                actions.push_back(s);

                if (s.repeatable) {                    
                    for (int i = 2; i<5; i++) {
                        Action ss = s;
                        ss.times = i;
                        ss.delta = ss.delta * i;
                        if (ss.can(p.inv)) { actions.push_back(ss); }
                    }
                }
            }
        }



        return actions;


    }


	void Game::read() {

        int actionCount; // the number of spells and recipes in play
        std::cin >> actionCount; std::cin.ignore();
        recipes.clear();
        spells.clear();
        tome.clear();
        int placeInTome = 0;
        for (int i = 0; i < actionCount; i++) {
            Action a;
            a.Read();
            if (a.type=="BREW") { recipes.push_back(a); }
            if (a.type=="CAST") { spells.push_back(a); }
            if (a.type=="LEARN") { a.placeInTome = placeInTome; placeInTome++; tome.push_back(a); }
        }
        me.Read();
        he.Read();
        std::cerr << me << std::endl;
        std::cerr << he << std::endl;
//        for (Action r : recipes) {std::cerr << r << std::endl;}
//        for (Action s : spells) {std::cerr << s << std::endl;}
//        for (Action t : tome) {std::cerr << t << std::endl;}
        
    }

