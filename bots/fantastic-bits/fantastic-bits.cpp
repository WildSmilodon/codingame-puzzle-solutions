// https://www.codingame.com/multiplayer/bot-programming/fantastic-bits'

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


double DotProduct(double x1, double y1,double x2, double y2) {
    
    std::cerr << "dp " << x1*x2+y1*y2 << std::endl;
    return x1*x2+y1*y2;
}

class GoalClass
{
public:
            int xc; // position
            int yc; // position
            int ymin = 3750 - 1000;
            int ymax = 3750 + 1000; 
};

class WizardClass
{
public:
            int x; // position
            int y; // position
            int vx; // velocity
            int vy; // velocity
            int state; // 1 if the wizard is holding a Snaffle, 0 otherwise
            int id; // entity ID
	
	double dist(int a, int b) {
    	return sqrt( pow(x-a,2)+pow(y-b,2) );
	}
	
	void GetClosestSnaf(WizardClass s[], int nsnaf, double& minDist, int& minj) {
	    minDist=100000;
        minj=-1;
        for (int j = 0; j<nsnaf; j++) {
            double d = dist(s[j].x,s[j].y); //  sqrt( pow(x-s[j].x,2)+pow(x-s[j].y,2) );
            std::cerr << d << " " << j  << " xy " << x << " " << y << " xy " << s[j].x << " " << s[j].y  << std::endl;
            if (d<minDist && s[j].state==0) {
                        minDist=d;
                        minj=j;
            }
        }
	std::cerr << minj << " min " << minDist << " xy " << x << " " << y << std::endl;
	}
	
	int AmIchasing(WizardClass s, GoalClass myGoal) {
	   if (s.state == 0) {    
	       if (myGoal.xc<s.x && s.x<x) {
	           return 1;
	       }
	       if (myGoal.xc>s.x && s.x>x) {
	           return 1;
	       }
	   }
	       
	   return 0;
	}
	
	void TargetXY(GoalClass hisGoal, int& Tx, int& Ty) {
	    Tx = hisGoal.xc;
	    if (y<hisGoal.ymax && y>hisGoal.ymin) {
	        Ty = y;
	    } else if (y>hisGoal.ymax) {
	        Ty=hisGoal.ymax;
	    } else {
	        Ty=hisGoal.ymin; 
	    }
	        
	}
	
	int Flipendo(WizardClass s[], int nsnaf, GoalClass hisGoal) {
	    
	    for (int j = 0; j<nsnaf; j++) {
	        if (s[j].state==0 && DotProduct(s[j].x - x,s[j].y - y,hisGoal.xc - x,hisGoal.yc - y)>0) {
	               double alfa = ( hisGoal.xc - x ) / ( s[j].x - x + 0.00001 );
	               double ips = y + ( s[j].y - y ) * alfa;
	               if (ips<hisGoal.ymax && ips>hisGoal.ymin) {
	                   return j; //s[j].id;
	               }
	        }
	    }
	    return -1;       
	}
	
	
	int Petrificus(GoalClass myGoal) {
	 
	 //std::cerr << x+vx << "pp " << y+vy << "   " << myGoal.xc << std::endl;
	 
	 if (myGoal.xc == 0) {
	    if (x+1.75*vx<myGoal.xc && y+1.75*vy < myGoal.ymax && y+1.75*vy>myGoal.ymin) {
	        return 1;
	    } 
	 } else {
	    if (x+1.75*vx>myGoal.xc && y+1.75*vy < myGoal.ymax && y+1.75*vy>myGoal.ymin) {
	        return 1;
	    }
	 }
	 
	 return 0;
	}

};

using namespace std;

/**
 * Grab Snaffles and try to throw them through the opponent's goal!
 * Move towards a Snaffle and use your team id to determine where you need to throw it.
 **/
int main()
{
    int myTeamId; // if 0 you need to score on the right of the map, if 1 you need to score on the left
    cin >> myTeamId; cin.ignore();

    WizardClass myWizard[2];
    WizardClass bludger[2];
    WizardClass hisWizard[2];
    WizardClass snaffle[12];
    GoalClass myGoal,hisGoal;
    

    if (myTeamId==0) {
        myGoal.xc=0;
        myGoal.yc=3750;
        
        hisGoal.xc=16000;
        hisGoal.yc=3750;
    } else {
        myGoal.xc=16000;
        myGoal.yc=3750;
        
        hisGoal.xc=0;
        hisGoal.yc=3750;
    }
 //  cerr << myTeamId << " " << hisGoal.xc << endl;    

    // game loop
    while (1) {
        int myScore;
        int myMagic;
        cin >> myScore >> myMagic; cin.ignore();
        int opponentScore;
        int opponentMagic;
        cin >> opponentScore >> opponentMagic; cin.ignore();
        int entities; // number of entities still in game
        cin >> entities; cin.ignore();
        
        int nmy = 0;
        int nhis = 0;
        int nsnaf = 0;
        int nblu = 0;
        
        for (int i = 0; i < entities; i++) {
            int entityId; // entity identifier
            string entityType; // "WIZARD", "OPPONENT_WIZARD" or "SNAFFLE" (or "BLUDGER" after first league)
            int x; // position
            int y; // position
            int vx; // velocity
            int vy; // velocity
            int state; // 1 if the wizard is holding a Snaffle, 0 otherwise
            cin >> entityId >> entityType >> x >> y >> vx >> vy >> state; cin.ignore();
        
            if (entityType=="WIZARD") {
                myWizard[nmy].x=x;
                myWizard[nmy].y=y;
                myWizard[nmy].vx=vx;
                myWizard[nmy].vy=vy;
                myWizard[nmy].state=state;
                myWizard[nmy].id=entityId;
                cerr << "me="<< myWizard[nmy].x<<","<<myWizard[nmy].y <<","<<myWizard[nmy].state << " "<< nmy << endl;
                nmy=nmy+1;
            }

            if (entityType=="OPPONENT_WIZARD") {
                hisWizard[nhis].x=x;
                hisWizard[nhis].y=y;
                hisWizard[nhis].vx=vx;
                hisWizard[nhis].vy=vy;
                hisWizard[nhis].state=state;
                hisWizard[nhis].id=entityId;
                nhis=nhis+1;
            } 

            if (entityType=="BLUDGER") {
                bludger[nblu].x=x;
                bludger[nblu].y=y;
                bludger[nblu].vx=vx;
                bludger[nblu].vy=vy;
                bludger[nblu].state=state;
                bludger[nblu].id=entityId;
                nblu=nblu+1;
            } 

            if (entityType=="SNAFFLE") {
                snaffle[nsnaf].x=x;
                snaffle[nsnaf].y=y;
                snaffle[nsnaf].vx=vx;
                snaffle[nsnaf].vy=vy;
                snaffle[nsnaf].state=state;
                snaffle[nsnaf].id=entityId;
                cerr << nsnaf << " " << snaffle[nsnaf].x << " " << snaffle[nsnaf].y << " " << snaffle[nsnaf].state << " " << snaffle[nsnaf].id << endl;
                nsnaf=nsnaf+1;
            }      
                        
            
            
        }
            
        double minDist[2];
        int cSnaf[2];
        for (int i = 0; i < 2; i++) {
            myWizard[i].GetClosestSnaf(snaffle,nsnaf,minDist[i],cSnaf[i]);
            cerr << i << " " << minDist[i] << " " << cSnaf[i] << " " << snaffle[cSnaf[i]].x<<" " << snaffle[cSnaf[i]].y << endl; 
        }
        if (nsnaf>1 && myWizard[0].state==0 && myWizard[1].state==0) {
             if (minDist[0]<minDist[1]) {
                 snaffle[cSnaf[0]].state=3;
                  myWizard[1].GetClosestSnaf(snaffle,nsnaf,minDist[1],cSnaf[1]);
             } else {
                 snaffle[cSnaf[1]].state=3;
                 myWizard[0].GetClosestSnaf(snaffle,nsnaf,minDist[0],cSnaf[0]);
             }
        }

        int ipet = -1;
        for (int j = 0; j<nsnaf; j++) {
            if (snaffle[j].state == 0) {
                if (snaffle[j].Petrificus(myGoal)==1) {
                    ipet=j;
                }
            }
        }
        
        if (ipet>-1) {
            cerr << snaffle[ipet].x+snaffle[ipet].vx << "pp " << snaffle[ipet].y+snaffle[ipet].vy << "   " << myGoal.xc << std::endl;
        }

        
        for (int i = 0; i < 2; i++) {
            
            
            int fid = myWizard[i].Flipendo(snaffle,nsnaf,hisGoal);
            cerr << i << " " << fid << endl;
            
            if (myMagic > 10 && ipet>-1) {
                snaffle[ipet].state=3;
                cout << "PETRIFICUS "<< snaffle[ipet].id << endl;
                myMagic = myMagic - 10;
            } else if (myMagic > 20 && fid > -1) {
                 cout << "FLIPENDO "<< snaffle[fid].id << endl;
                 snaffle[fid].state=3;
                 myMagic = myMagic - 20;
            } else if (myMagic > 15 && myWizard[i].AmIchasing(snaffle[cSnaf[i]],myGoal)==1 && cSnaf[i]>-1) {
                 cerr << cSnaf[i] << " " << snaffle[cSnaf[i]].id << endl;
                 cout << "ACCIO "<< snaffle[cSnaf[i]].id << endl;
                 myMagic = myMagic - 15;
            } else if (myWizard[i].state == 0) {
            
//                double minDist=100000;
//                int minj=-1;
//                myWizard[i].GetClosestSnaf(snaffle,nsnaf,minDist,minj);
//                 cerr << i << " " << minDist << " " << minj << endl; 
                
//                for (int j = 0; j<nsnaf; j++) {
//                    double d = myWizard[i].dist(snaffle[j].x,snaffle[j].y);
//                    if (d<minDist && snaffle[j].state==0) {
//                        minDist=d;
//                        minj=j;
//                    }
//                    cerr << j << " " << myWizard[i].dist(snaffle[j].x,snaffle[j].y) << " " << minj << endl;
//                }
                cout << "MOVE "<< snaffle[cSnaf[i]].x+snaffle[cSnaf[i]].vx<<" " << snaffle[cSnaf[i]].y+snaffle[cSnaf[i]].vy << " 150" << endl;
//                snaffle[minj].state=3;
            } else {
                int Tx,Ty;
                myWizard[i].TargetXY(hisGoal,Tx,Ty);
               // cout << "THROW " << hisGoal.xc << " " << hisGoal.yc << " 500" << endl;
                cout << "THROW " << Tx << " " << Ty << " 500" << endl;       
            }
            // Write an action using cout. DON'T FORGET THE "<< endl"
            // To debug: cerr << "Debug messages..." << endl;


            // Edit this line to indicate the action for each wizard (0 ≤ thrust ≤ 150, 0 ≤ power ≤ 500)
            // i.e.: "MOVE x y thrust" or "THROW x y power"
          //  cout << "MOVE 8000 3750 100" << endl;
        }
    }
}
