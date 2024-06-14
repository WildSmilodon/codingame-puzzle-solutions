#include "Game.h"

Game::Game()
{
}

void Game::readInit()
{
    cin >> creature_count; cin.ignore();
    for (int i = 0; i < creature_count; i++) {
        Fish f;
        f.readInit();
        fish.push_back(f);
    }
}

void Game::readTurn()
{

    myDrones.clear();
    hisDrones.clear();

    cin >> my_score; cin.ignore();
    cin >> foe_score; cin.ignore();   
    cin >> my_scan_count; cin.ignore();

    // to so tiste ribe, ki jih prineseš na površino
    for (int i = 0; i < my_scan_count; i++) {
        int creature_id;
        cin >> creature_id; cin.ignore();
        fish[getFishI(creature_id)].scannedByMe = true;
    }
    
    cin >> foe_scan_count; cin.ignore();
    for (int i = 0; i < foe_scan_count; i++) {
        int creature_id;
        cin >> creature_id; cin.ignore();
        fish[getFishI(creature_id)].scannedByFoe = true;         
    }

    cin >> my_drone_count; cin.ignore();
    for (int i = 0; i < my_drone_count; i++) {
        Drone d;
        d.read();
        myDrones.push_back(d);
    }
    
    cin >> foe_drone_count; cin.ignore();
    for (int i = 0; i < foe_drone_count; i++) {
        Drone d;
        d.read();
        hisDrones.push_back(d);
    }
    
    // to so tiste, ki si jih poskeniral in so še v dronu
    cin >> drone_scan_count; cin.ignore();
    for (int i = 0; i < drone_scan_count; i++) {
        int drone_id;
        int creature_id;
        cin >> drone_id >> creature_id; cin.ignore();
        cerr << creature_id << endl;
        // tu so vsi droni
        int ii = getmyDroneI(drone_id);
        if (ii > -1 ) {
            fish[getFishI(creature_id)].scannedByMe = true;
            myDrones[ii].scannedFish.push_back(creature_id);
        } else {
            ii = getfoeDroneI(drone_id);
            fish[getFishI(creature_id)].scannedByFoe = true;
            hisDrones[ii].scannedFish.push_back(creature_id);            
        }
    }
        
    for (Fish &f : fish) {
        f.isVisible = false;
    }

    cin >> visible_creature_count; cin.ignore();
    for (int i = 0; i < visible_creature_count; i++) {
        int creature_id;
        int creature_x;
        int creature_y;
        int creature_vx;
        int creature_vy;
        cin >> creature_id >> creature_x >> creature_y >> creature_vx >> creature_vy; cin.ignore();
        for (Fish &f : fish) {
            if (creature_id == f.id) { 
                f.isVisible = true; 
                f.row = creature_y;
                f.col = creature_x;
                f.vCol = creature_vx;
                f.vRow = creature_vy;
            }
        }   
    
    }

    for (Drone &d : myDrones) {
        d.radarBL.clear();
        d.radarBR.clear();
        d.radarTL.clear();
        d.radarTR.clear();
    }
    
    cin >> radar_blip_count; cin.ignore();
    for (int i = 0; i < radar_blip_count; i++) {
        int drone_id;
        int creature_id;
        string radar;
        cin >> drone_id >> creature_id >> radar; cin.ignore();
        if ( !fish[getFishI(creature_id)].scannedByMe ) {
            int di = getmyDroneI(drone_id);
            if (radar == "BL") { myDrones[di].radarBL.push_back(creature_id); }
            if (radar == "BR") { myDrones[di].radarBR.push_back(creature_id); }
            if (radar == "TL") { myDrones[di].radarTL.push_back(creature_id); }
            if (radar == "TR") { myDrones[di].radarTR.push_back(creature_id); }
        }
    }

}

void Game::printTurn()
{
    for (Fish f : fish) {
        if (f.isVisible) {
            if (f.scannedByMe  ) { 
                cerr << "me : " << f << endl; 
            }
            if (f.scannedByFoe ) { 
                cerr << "foe: " << f << endl; 
            } 
          // if (!f.scannedByMe && !f.scannedByFoe ) {
                cerr << "vis: " << f << endl; 
          //  }
        } 
    }

    for (Drone d : myDrones) {
        cerr << d.id << " " << "BL: "; for (int id : d.radarBL) { cerr << id << " "; } cerr << endl;
        cerr << d.id << " " << "BR: "; for (int id : d.radarBR) { cerr << id << " "; } cerr << endl;
        cerr << d.id << " " << "TL: "; for (int id : d.radarTL) { cerr << id << " "; } cerr << endl;
        cerr << d.id << " " << "TR: "; for (int id : d.radarTR) { cerr << id << " "; } cerr << endl;
        cerr << d.id << " SF: ";
        for (int i : d.scannedFish) {
            cerr << i << " ";
        }
        cerr << endl;
    }
}

int Game::getFishI(int id)
{
    int listID = -1;

    int i = -1;
    for (Fish f : fish) {
        i++;
        if (f.id == id ) { listID = i; } 
    }
    return listID;
}

int Game::getmyDroneI(int id)
{
    int listID = -1;

    int i = -1;
    for (Drone d : myDrones) {
        i++;
        if (d.id == id ) { listID = i; } 
    }
    return listID;
}


int Game::getfoeDroneI(int id)
{
    int listID = -1;

    int i = -1;
    for (Drone d : hisDrones) {
        i++;
        if (d.id == id ) { listID = i; } 
    }
    return listID;
}
