// https://www.codingame.com/multiplayer/bot-programming/botters-of-the-galaxy

#pragma GCC optimize("O3,inline,omit-frame-pointer,unroll-loops")
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <sstream>

#define HEALTH_GOLD_RESERVE 1000
#define DAMAGE_GOLD_RESERVE 0
#define FIREBALL_MANA_LIMIT 59

using namespace std;

class Konstante {
public:
	int health_gold_reserve = HEALTH_GOLD_RESERVE;
	int damage_gold_reserve = DAMAGE_GOLD_RESERVE;
	int fireball_mana_limit = FIREBALL_MANA_LIMIT;

};


class Point {

public:
	float x;
	float y;

	void normalize() {
		float d = sqrt(x*x + y*y);
		if (d > 0.0) {
			x = x / d;
			y = y / d;
		}
	}

	float distance2(float xx, float yy) {
		return (x - xx)*(x - xx) + (y - yy)*(y - yy);
	}

	float distance(float xx, float yy) {
		return sqrt((x - xx)*(x - xx) + (y - yy)*(y - yy));
	}

};

class Item {

public:
	string itemName; // contains keywords such as BRONZE, SILVER and BLADE, BOOTS connected by "_" to help you sort easier
	int itemCost; // BRONZE items have lowest cost, the most expensive items are LEGENDARY
	int damage; // keyword BLADE is present if the most important item stat is damage
	int health;
	int maxHealth;
	int mana;
	int maxMana;
	int moveSpeed; // keyword BOOTS is present if the most important item stat is moveSpeed
	int manaRegeneration;
	int isPotion; // 0 if it's not instantly consumed
};

class Entity { 

public:
	Konstante konst;
            int unitId;
            int team;
            string unitType; // UNIT, HERO, TOWER, can also be GROOT from wood1
			float attackTime; // heroes 0.1, units, 0.2;
			float x;
			float y;
			float attackRange;
			int health;
			float maxHealth;
            int shield; // useful in bronze
			float attackDamage;
			float movementSpeed;
            int stunDuration; // useful in bronze
            int goldValue;
            int countDown1; // all countDown and mana variables are useful starting in bronze
            int countDown2;
            int countDown3;
            int mana;
            int maxMana;
            int manaRegeneration;
            string heroType; // DEADPOOL, VALKYRIE, DOCTOR_STRANGE, HULK, IRONMAN
            int isVisible; // 0 if it isn't
            int itemsOwned; // useful from wood1 
            
            float distance2(int xx, int yy) {
                return (x-xx)*(x-xx)+(y-yy)*(y-yy);
            }
            
            float distance(int xx, int yy) {
                return sqrt((x-xx)*(x-xx)+(y-yy)*(y-yy));
            }


			float GetAttackTime(Entity e) // Ce vec kot 1 ne morem napasti
			{
				float dist = distance(e.x,e.y);
				float t = 0;
				if (dist > e.attackRange)
				{
					t = (dist - attackRange) / movementSpeed;
					dist = attackRange;
				}

				t += attackTime;
				if (attackRange > 150)
				{
					t += attackTime * (dist / attackRange);
				}

				return t;
			}
			float GetDistToAttackFromRange(Entity e) {
				float dist = attackRange; // predpostavljam, da napadam iz attackrange
				float d = 0.0;
				float t = attackTime; 
				if (attackRange > 150) { t += attackTime * (dist / attackRange); }
				// tu imamo v t cas, ki ga porabim da ustrelim iz attackrange
				// preostane mi
				t = 1.0 - t;
				if (t > 0.0) {
					d = t*movementSpeed;
				}
				else { d = 0.0; }
				return d;
			}

			Point GetAttackRangePosition(Entity e) {

				Point n; // unit normal from e to me
				Point ar; // point at attack range;

				n.x = x - e.x;
				n.y = y - e.y;
				n.normalize();

				ar.x = e.x + n.x*attackRange;
				ar.y = e.y + n.y*attackRange;
				
				return ar;

			}
            

			Entity ClosestEntity(vector<Entity> Entities) { // Najblizji meni

				Entity target;
				target.unitId = -100; // in case I dont find any
				float minD = 1.0E10;

				for (Entity e : Entities) {
					float d = e.distance(x, y);
					if (d < minD) { minD = d; target = e; }
				}
				return target;
			}

			Entity WillDie(vector<Entity> Entities) { // najsibkejsi, ali ga ubijem

				Entity target;
				target.unitId = -100; // in case I dont find any
				float minD = 1.0E10;

				for (Entity e : Entities) {
					float h = e.health;
					float d = e.distance(x, y);
					if ( (h < minD) & (d<attackRange) & (h-attackDamage<1) & (h>0)  ) { minD = h; target = e; }
				}
				return target;
			}

			Entity MinATimeTarget(vector<Entity> Entities) { // katerega napadem

				Entity target;
				target.unitId = -100; // in case I dont find any
				float minD = 1.0E10;

				for (Entity e : Entities) {
					float d = GetAttackTime(e);
					if (d < minD & e.health>0 ) { minD = d; target = e; } // health zato, ker ga je drugi ze unicil
				}
				return target;
			}

			int BuyStuff(string &cmd, int &gold, vector<Item> Items) {
				int done = 0;
				stringstream buf;

				// consider a health potion
				if (health < maxHealth) {
					for (Item it : Items) {
						if (it.itemCost < gold & it.isPotion == 1 & health + it.health <= maxHealth & it.health>0) {
							buf << "BUY " << it.itemName << ";Buy"; cmd = buf.str();
							gold = gold - it.itemCost;
							done = 1;
							break;
						}
					}
				}

				// health stuff
				if (done == 0 & itemsOwned<3) {
					for (Item it : Items) {
						if (it.itemCost < gold - konst.health_gold_reserve & it.health>0 & it.isPotion == 0) {
							buf << "BUY " << it.itemName << ";Buy"; cmd = buf.str();
							done = 1;
							gold = gold - it.itemCost;
							itemsOwned++;
							break;
						}
					}
				}

				// damaage stuff
				if (done == 0 & itemsOwned<3 ) {
					for (Item it : Items) {
						if (it.itemCost < gold - konst.damage_gold_reserve & it.damage>0 & it.isPotion == 0) {
							buf << "BUY " << it.itemName << ";Buy"; cmd = buf.str();
							done = 1;
							gold = gold - it.itemCost;
							itemsOwned++;
							break;
						}
					}
				}
				return done;
			}

			int CastSpell(string &cmd, vector<Entity> &hisAll) {

				int done = 0;
				stringstream buf;

				if (done == 0 & heroType == "DEADPOOL" & mana>49 & countDown2 == 0) {

					for (Entity &e : hisAll) {
						float d = distance(e.x, e.y);
						if (d < 200) {
							buf << "WIRE " << e.x << " " << e.y << ";Wire"; cmd = buf.str();
							done = 1;
							mana = mana - 40;
							break;
						}
					}
				}

				if (done == 0 & heroType == "HULK" & mana>39 & countDown3 == 0) {
					
					for (Entity &e : hisAll) {
						float d = distance(e.x, e.y);
						if (d < 150) {
							buf << "BASH " << e.unitId << ";BASH"; cmd = buf.str();
							done = 1;
							mana = mana - 40;
							break;
						}
					}
				}

				if (done == 0 & heroType == "HULK" & mana>29 & countDown2 == 0) {

					for (Entity &e : hisAll) {
						float d = distance(e.x, e.y);
						if (d < 150) {
							buf << "EXPLOSIVESHIELD"  << ";EXPLOSIVESHIELD"; cmd = buf.str();
							done = 1;
							mana = mana - 30;
							break;
						}
					}
				}

				if ((done == 0) & (heroType == "IRONMAN") & (mana>konst.fireball_mana_limit) & (countDown2 == 0)) {
					for (Entity &e : hisAll) {
						float d = distance(e.x, e.y);
						float t = GetAttackTime(e);
						float dam = mana * 0.2 + 55 * d / 1000.0;
						if (d < 900 & t > 1.0) {
							buf << "FIREBALL " << e.x << " " << e.y << ";Fireball"; cmd = buf.str();
							done = 1;
							e.health = e.health - dam;
							mana = mana - 60;
							//cerr << e.unitId << " ff " << e.health << " ee " << dam << endl;
							break;
						}
					}
				}


				if (done == 0 & heroType == "DOCTOR_STRANGE" & mana>49 & countDown1 == 0) {
					if (health<500) {
						buf << "AOEHEAL " << x << " " << y << ";AOEHEAL"; cmd = buf.str();
						done = 1;
						mana = mana - 50;
					}
				}

				if (done == 0 & heroType == "DOCTOR_STRANGE" & mana>39 & countDown2 == 0) {
					if (health<500) {
						buf << "SHIELD " << unitId << ";SHIELD"; cmd = buf.str();
						done = 1;
						mana = mana - 40;
					}
				}


				return done;
			}


};
 
 
class BushSpawnClass {

public:
            string entityType; // BUSH, from wood1 it can also be SPAWN
            int x;
            int y;
            int radius;
}; 


 

class Game {

public:
    int myTeam;
    int bushAndSpawnPointCount; // usefrul from wood1, represents the number of bushes and the number of places where neutral units can spawn
    int itemCount; // useful from wood2
	int Rush = 1;

    int gold;
    int enemyGold;
    int roundType; // a positive value will show the number of heroes that await a command
    int entityCount;

	vector<BushSpawnClass> BushSpawn;
	vector<Item> Items;
	
	vector<Entity> myUnits;
	vector<Entity> myHeroes;
	Entity myTower;

	vector<Entity> hisUnits;
	vector<Entity> hisHeroes;
	Entity hisTower;
	vector<Entity> hisAll;
	vector<Entity> groot;


	void ReadMyTeam() {
	    cin >> myTeam; cin.ignore();
	}


	void ReadBushSpawn() {
	    cin >> bushAndSpawnPointCount; cin.ignore();
        for (int i = 0; i < bushAndSpawnPointCount; i++) {
            BushSpawnClass bs;
            cin >> bs.entityType >>  bs.x >>  bs.y >>  bs.radius; cin.ignore();
            BushSpawn.push_back(bs);  
        }
	}

	void ReadItems() {
        cin >> itemCount; cin.ignore();
        for (int i = 0; i < itemCount; i++) {
            Item it;
            cin >> it.itemName >> it.itemCost >> it.damage >> it.health >> it.maxHealth >> it.mana >> it.maxMana >> it.moveSpeed >> it.manaRegeneration >> it.isPotion; cin.ignore();
            Items.push_back(it);
            cerr << it.itemName << " " << it.itemCost << " " << it.damage << " " << it.health << " " << it.maxHealth << " " << it.mana << " " << it.maxMana << " " << it.moveSpeed << " " << it.manaRegeneration << " " << it.isPotion << endl;
        }    
	}


	void ReadLoop() {

        cin >> gold; cin.ignore();
        cin >> enemyGold; cin.ignore();
        cin >> roundType; cin.ignore();
        cin >> entityCount; cin.ignore();
        myHeroes.clear();
        myUnits.clear();
        hisHeroes.clear();
        hisUnits.clear();
        hisAll.clear();
        
        for (int i = 0; i < entityCount; i++) {
            Entity e;
            cin >> e.unitId >>e.team >>e.unitType >> e.x >> e.y >> e.attackRange >> e.health >> e.maxHealth >> e.shield >> e.attackDamage >> e.movementSpeed >> e.stunDuration >> e.goldValue >> e.countDown1 >> e.countDown2 >> e.countDown3 >> e.mana >> e.maxMana >> e.manaRegeneration >> e.heroType >> e.isVisible >> e.itemsOwned; cin.ignore();
            
            if (e.team==myTeam) {
                if (e.unitType=="TOWER") { myTower = e; }
                if (e.unitType=="HERO") { e.attackTime = 0.1;  myHeroes.push_back(e); }
				if (e.unitType == "UNIT") { e.attackTime = 0.2; myUnits.push_back(e); }
            } else {
                if (e.unitType=="TOWER") { hisTower = e; }
                if (e.unitType=="HERO") { e.attackTime = 0.1; hisHeroes.push_back(e); }
                if (e.unitType=="UNIT") { e.attackTime = 0.2; hisUnits.push_back(e); }
                if (e.unitType=="GROOT") { e.attackTime = 0.2;  groot.push_back(e); } else { hisAll.push_back(e); }
            }          
        }
	}



	Entity FindLastUnit() {
	    
	        Entity MyLastUnit;
	        MyLastUnit.unitId = -100;
	        if (myTeam==0) {
                float minD = 1.0E10;
                for (Entity e : myUnits) {
                    float d = e.x;
                    if (d<minD) {minD=d; MyLastUnit = e;}
                }                    
            } else {        
                float minD = 0.0;
                for (Entity e : myUnits) {
                    float d = e.x;
                    if (d>minD) {minD=d; MyLastUnit = e;}
                }
            }
            return MyLastUnit;
	}
	
	Entity FindFirstUnit(int &dx) {
	    
	        Entity MyLastUnit;
	        dx=0;
	        MyLastUnit.unitId = -100;
	        if (myTeam==1) {
                float minD = 1.0E10;
                for (Entity e : myUnits) {
                    float d = e.x;
                    if (d<minD) {minD=d; MyLastUnit = e; dx=+10;}
                }                    
            } else {        
                float minD = 0.0;
                for (Entity e : myUnits) {
                    float d = e.x;
                    if (d>minD) {minD=d; MyLastUnit = e; dx=-10;}
                }
            }
            return MyLastUnit;
	}


	Entity FindHisFirstUnit(int &dx) {
	    
	        Entity unit;
	        unit.unitId = -100;
	        if (myTeam==0) {
                float minD = 1.0E10;
                for (Entity e : hisAll) {
                    float d = e.x-e.attackRange;
                    if (d<minD) {minD=d; unit = e; dx=-20-e.attackRange;}
                }                    
            } else {        
                float minD = -1.0E10;
                for (Entity e : hisAll) {
                    float d = e.x+e.attackRange;
                    if (d>minD) {minD=d; unit = e; dx=+20+e.attackRange;}
                }
            }
            return unit;
	}


    int GetBehind(string &cmd, Entity e, Entity me, int dx, int TUID) {
        int done = 0;
		stringstream buf;
        if (e.unitId>0) {
            if (myTeam==0) {
                cerr << me.x << " ss " << e.x+dx << endl;
                if (me.x>e.x+dx) {
						buf << "MOVE_ATTACK " << e.x + dx << " " << e.y << " " << TUID << ";GetBehind"; cmd = buf.str();
                        done = 1; }
            } else {
                            
                if (me.x<e.x+dx) {
					buf << "MOVE_ATTACK " << e.x + dx << " " << e.y << " " << TUID << ";GetBehind"; cmd = buf.str();
                    done = 1; }                        
            }
        }
        return done;
    }

    int AttackBehind(string &cmd, Entity e, Entity me, int dx, int tuid) {
        int done = 0;
		stringstream buf;
        if (e.unitId>0) {
			buf << "MOVE_ATTACK " << e.x + dx << " " << e.y << " " << tuid << ";AttackBehind"; cmd = buf.str();
            done = 1; 

        }
        return done;
    }
    

    int CastSpell(string &cmd, Entity me, Entity ClosestHero) {
        int done = 0;
		stringstream buf;
        if ( (done == 0) & (me.heroType=="IRONMAN") & (me.mana>59) & (me.countDown2==0) ) {
            float d=me.distance(ClosestHero.x,ClosestHero.y);
            if (d<900) {
				buf  << "FIREBALL " << ClosestHero.x << " " << ClosestHero.y << ";Fireball"; cmd = buf.str();
                done = 1; 
            }
        }

        if (done == 0 & me.heroType=="DOCTOR_STRANGE" & me.mana>19 & me.countDown1==0 ) {
            if (me.health<500) {
				buf << "AOEHEAL " << me.x << " " << me.y << ";AOEHEAL"; cmd = buf.str();
                done = 1; 
            }
        }

        if (done == 0 & me.heroType=="DOCTOR_STRANGE" & me.mana>59 & me.countDown2==0 ) {
            if (me.health<500) {
				buf << "SHIELD " << me.unitId << ";SHIELD"; cmd = buf.str();
                done = 1; 
            }
        }
        
        return done;
    }

    int RunToTower(string &cmd, Entity me) {
        int done = 0;
		stringstream buf;
        
        if (myUnits.size() == 0 || me.health < 200) {
            done = 1;
			buf << "MOVE " << myTower.x << " " << myTower.y << " " << ";RunToTower"; cmd = buf.str();
        }
        
        return done;
            
    }
    
    int BuyStuff(string &cmd, Entity me) {
        int done = 0;
		stringstream buf;
        
       // consider a health potion
        if (me.health < me.maxHealth) {
            for (Item it : Items) {
               if (it.itemCost < gold & it.isPotion==1 & me.health + it.health <= me.maxHealth & it.health>0 ) {
					buf  << "BUY " << it.itemName << ";Buy"; cmd = buf.str();
                    gold = gold - it.itemCost;
                    done = 1;
                    break;
               }
            }            
        }
       
        // health stuff
        if (me.itemsOwned<2 & done==0 ) {
            for (Item it : Items) {
               if (it.itemCost < gold & it.health>0 & it.isPotion==0 ) {
					buf  << "BUY " << it.itemName << ";Buy"; cmd = buf.str();
                    done = 1;
                    gold = gold - it.itemCost;
                    break;
               }
            } 
        }

        // other  stuff
        if (me.itemsOwned<2  & done==0 ) {
            for (Item it : Items) {
               if (it.itemCost < gold & it.isPotion==0 ) {
					buf  << "BUY " << it.itemName << ";Buy"; cmd = buf.str();
                    done = 1;
                    gold = gold - it.itemCost;
                    break;
               }
            } 
        }       
        
        return done;
    }    
    

    Entity FindClosestEnemyHero(Entity me) {

        Entity target;
        float minD = 1.0E10;
        
        for (Entity e : hisHeroes) {
            float d = e.distance(me.x,me.y);
            if (d<minD) {target = e; minD=d; }
        }
        return target;
    }

    Entity FindTarget(Entity me) {

        Entity target;
        int done = 0;
        
        for (Entity e : hisHeroes) {
            float d = e.distance(me.x,me.y);
            if (d<me.attackRange) {target = e; return target;}
        }        
        
        
        // find weakest unit
        float minD = 1.0E10;
        for (Entity e : hisAll) {
            float d = e.distance(me.x,me.y);
            if (d<me.attackRange & e.health<minD ) {minD=e.health; target = e; done=1;}
        }
        if (done==1) {return target;}
        
        // find closest unit
        minD = 1.0E10;
        for (Entity e : hisAll) {
            float d = e.distance(me.x,me.y);
            if (d<minD) {minD=d; target = e;}
        }
        
        return target;
    }

};


string SimpleStrategy(Entity me, Game game) {

	int done = 0;
	string cmd = "WAIT";
	int dx1;
	int dx2;
	Entity MyLastUnit = game.FindLastUnit();
	Entity MyFirstUnit = game.FindFirstUnit(dx1);
	Entity HisFirstUnit = game.FindHisFirstUnit(dx2);
	Entity target = game.FindTarget(me);
	Entity ClosestEnemyHero = game.FindClosestEnemyHero(me);
	Entity ClosestEnemyHeroNew = me.ClosestEntity(game.hisHeroes);
	Entity UnitWillDie = me.WillDie(game.hisAll);

	cerr << "CEH " << ClosestEnemyHero.unitId << " " << ClosestEnemyHeroNew.unitId << endl;
	cerr << "WillDIE " << UnitWillDie.unitId << endl;

	cerr << "myU x=" << MyFirstUnit.x << " " << MyFirstUnit.unitId << " " << dx1 << endl;
	cerr << "his x=" << HisFirstUnit.x << " " << HisFirstUnit.unitId << " " << dx2 << endl;
	cerr << "me  x=" << me.x << endl;
	cerr << "tar x=" << target.x << " " << target.unitId << endl;
	
	if (done == 0) { done = game.RunToTower(cmd, me); }

	if (done == 0) { done = game.BuyStuff(cmd, me); }

	if (done == 0) { done = game.CastSpell(cmd, me, ClosestEnemyHero); }

	if (done == 0) { done = game.GetBehind(cmd, MyFirstUnit, me, dx1, target.unitId); }
	cerr << "done2=" << done << " " << MyFirstUnit.unitId << endl;

	if (done == 0) { done = game.AttackBehind(cmd, HisFirstUnit, me, dx2, target.unitId); }
	cerr << "done3=" << done << endl;
	
	if (done == 0) { done = game.GetBehind(cmd, HisFirstUnit, me, dx2, target.unitId); }
	cerr << "done1=" << done << endl;

	return cmd;


}


string NewStrategy(Entity me, Game &game) {

	int done = 0;
	string cmd = "WAIT";

	me.konst.damage_gold_reserve = 100;
	me.konst.health_gold_reserve = 100;
	me.konst.fireball_mana_limit = 59;

	int dx1 = 0;
	int dx2 = 0;
	Entity MyLastUnit = game.FindLastUnit();
	Entity MyFirstUnit = game.FindFirstUnit(dx1);
	Entity HisFirstUnit = game.FindHisFirstUnit(dx2);
	Entity target = game.FindTarget(me);
	Entity ClosestEnemyHero = game.FindClosestEnemyHero(me);
	Entity ClosestEnemyHeroNew = me.ClosestEntity(game.hisHeroes);
	Entity UnitWillDie = me.WillDie(game.hisAll);


	if (done == 0) { done = me.BuyStuff(cmd, game.gold, game.Items); }

	if (done == 0) { done = me.CastSpell(cmd, game.hisAll); }

	if (done == 0) { done = game.GetBehind(cmd, MyLastUnit, me, dx1, target.unitId); }

	if (done == 0) {

		Entity ClosestEnemyHeroNew = me.ClosestEntity(game.hisHeroes);
		Entity UnitWillDie = me.WillDie(game.hisAll);
		Entity MinATimeTarget = me.MinATimeTarget(game.hisAll);

		float t = me.GetAttackTime(MinATimeTarget);
		stringstream buf;
		if (t < 1.0) {
			// move, so I attack with time 1.0
			Point AR = me.GetAttackRangePosition(MinATimeTarget);
			float d = me.GetDistToAttackFromRange(MinATimeTarget);
			float dist = AR.distance(me.x, me.y);

			if (d > dist) {
				buf << "MOVE_ATTACK " << AR.x << " " << AR.y << " " << MinATimeTarget.unitId << ";MA"; cmd = buf.str();
				MinATimeTarget.health = MinATimeTarget.health - me.attackDamage;
			}
			else {
				buf << "ATTACK " << MinATimeTarget.unitId << ";Attack t<1"; cmd = buf.str();
			}
		}
		else {
			buf << "ATTACK " << MinATimeTarget.unitId << ";Attack"; cmd = buf.str();
		}

	}

	return cmd;

}

string RushStrategy(Entity me, Game &game) {

	int done = 0;
	string cmd = "WAIT";
	stringstream buf;

	me.konst.damage_gold_reserve = 0;
	me.konst.health_gold_reserve = 1000;
	me.konst.fireball_mana_limit = 59;




	if (done == 0) { done = me.BuyStuff(cmd, game.gold, game.Items); }

	if (done == 0) { done = me.CastSpell(cmd, game.hisHeroes); }

	if (done == 0) {
		// cmd = "ATTACK_NEAREST HERO"; done = 1;
		float minD = 1.0E10;
		Entity target;
		for (Entity e : game.hisHeroes) {
			float d = e.distance(game.myTower.x, game.myTower.y);
			if (d < minD) { minD = d; target = e; }
		}

		float t2t = game.myTower.distance(game.hisTower.x, game.hisTower.y);

		if (minD > t2t - game.hisTower.attackRange) {
			cerr << "t2t " << t2t << " " << game.hisTower.attackRange << " " << minD << " " << target.unitId << endl;
			cmd = NewStrategy(me, game);
		}
		else {
			buf << "ATTACK " << target.unitId << ";A1"; cmd = buf.str();
		}
		
	}

	return cmd;
}



int main()
{
	string cmd;
    Game game;
    game.ReadMyTeam();
    game.ReadBushSpawn();
    game.ReadItems();
    
    // game loop
    while (1) {
       
        game.ReadLoop();
        
        // If roundType has a negative value then you need to output a Hero name, such as "DEADPOOL" or "VALKYRIE".
        if (game.roundType<0) {
            if (game.myHeroes.size() == 0) { cout << "IRONMAN" << endl; } else { cout << "DOCTOR_STRANGE" << endl; }
		//	if (game.myHeroes.size() == 0) { cout << "HULK" << endl; } else { cout << "DEADPOOL" << endl; }
        } else {
        // Else you need to output roundType number of any valid action, such as "WAIT" or "ATTACK unitId"
            
            for (Entity me : game.myHeroes) {
				
			//	cmd = SimpleStrategy(me, game);
			//	cmd = NewStrategy(me, game);
				if ( (game.Rush==1) & ( (game.myHeroes.size() == 2) || (game.hisHeroes.size() == 1))) {
					cmd = RushStrategy(me, game);
				//	cmd = NewStrategy(me, game);
				}
				else {
				//	cmd = RushStrategy(me, game);
					cmd = NewStrategy(me, game);
				}
				
              
				// Send command to hero!
				cout << cmd << endl;
            }
        }
    }
}
