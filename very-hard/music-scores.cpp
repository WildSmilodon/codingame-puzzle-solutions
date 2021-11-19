// https://www.codingame.com/training/expert/music-scores

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator> 

using namespace std;


std::vector<std::string> splitString(string text) {

    std::istringstream iss(text);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                     std::istream_iterator<std::string>());
    return results;
}

class Visina {
public:
    float y;
    string sign;
};


class Line {
public:
    int start;
    int end;

};

class Note {
public:
    int start;
    int end;
    int weight;
    float center;
    string type;
    string visina;
    float rat;

};


class Map {
public:
    int W;
    int H;
    int startCol;
    bool data[1500000];
    bool dataCopy[1500000];
    Line lines[5];
    Note notes[1000];
    Visina tipiNot[12];
    int nNotes;

    bool pixel(int row, int col) {

        int index = row * W + col;
        return data[index];
    }

    bool pixelCopy(int row, int col) {

        int index = row * W + col;
        return dataCopy[index];
    }

    void erase(int row, int col) {

        int index = row * W + col;
        data[index] = false;
    } 

    void findLines() {

        // find line with first black pixel
        bool found = false;
        int c = 0;
        while (!found) {
            for (int r = 0; r < H; r++) {
                if (pixel(r,c)) { found = true; }
            }
            if (!found) { c++; }

        }
        int startCol = c;
        cerr << "startCol=" << startCol << endl;

        // find line with last black pixel
        found = false;
        c = W - 1;
        while (!found) {
            for (int r = 0; r < H; r++) {
                if (pixel(r,c)) { found = true; }
            }
            if (!found) { c--; }

        }
        int endCol = c;
        cerr << "endCol=" << endCol << endl;


        // find the 5 lines
        int l = 0;
        int r = 0;
        while (r < H) {
                if (pixel(r,startCol)) { 
         //           cerr << "line " << l << " start " << r << endl;
                    lines[l].start = r;
                    while (pixel(r,startCol)) {
                        r++;
                    } 
           //         cerr << "line " << l << " end " << r-1 << endl;
                    lines[l].end = r - 1 ;
                    l++;
                }
            r++;
        }

        int distBetwLines = lines[1].start-lines[0].end - 1;
        int lineWidth = lines[0].end-lines[0].start + 1;
        cerr << "line width = " << lineWidth << " dist between line " << distBetwLines << endl;

        // delete lines
        for (int i = 0; i<5; i++) {
            for (int r = lines[i].start; r <= lines[i].end; r++) {
                for (int c = 0; c < W; c++) {
                    erase(r,c);
                }
            }
        }



        // delete the 6th line
        for (int r = lines[4].start + distBetwLines + lineWidth; r <= lines[4].end + lineWidth+ distBetwLines; r++) {
            for (int c = 0; c < W; c++) {
                 erase(r,c);
            }
        }        


        for (int i = 0; i<5; i++) {
            cerr << " line " << i << " s=" << lines[i].start << " e=" << lines[i].end << endl;
        }
        
        for (int i = 0; i<4; i++) {
            cerr << " dist between line " << i << " and " << i+1 << " = " << lines[i+1].start-lines[i].end-1 << endl;
        }


    
        // lokacije tezisc
        tipiNot[11].y = (lines[0].start + lines[0].end)/2.0 - distBetwLines/2.0;
        tipiNot[10].y = (lines[0].start + lines[0].end)/2.0;
        tipiNot[9].y = (lines[1].start + lines[0].end)/2.0;
        tipiNot[8].y = (lines[1].start + lines[1].end)/2.0;
        tipiNot[7].y = (lines[2].start + lines[1].end)/2.0;
        tipiNot[6].y = (lines[2].start + lines[2].end)/2.0;
        tipiNot[5].y = (lines[3].start + lines[2].end)/2.0;
        tipiNot[4].y = (lines[3].start + lines[3].end)/2.0;
        tipiNot[3].y = (lines[4].start + lines[3].end)/2.0;
        tipiNot[2].y = (lines[4].start + lines[4].end)/2.0;
        tipiNot[1].y = (lines[4].start + lines[4].end)/2.0 + distBetwLines/2.0;
        tipiNot[0].y = (lines[4].start + lines[4].end)/2.0 + distBetwLines;


        for (int i = 0; i < 12; i++) {
            cerr << " note " << tipiNot[i].sign << " " << tipiNot[i].y << endl;
        }


        // find verticals
        int nVertical[W];
        for (int c = 0; c<W; c++) {
            int nBlack = 0;
            for (int r = 0; r<H; r++) {            
                if (pixel(r,c)) { nBlack++; }
            }
            nVertical[c] = nBlack;
          //  cerr << " c = " << c << " nVert " << nVertical[c]  << endl;
        }

        c = startCol;
        nNotes = 0;
        bool prvic = true;
        while (c < endCol) {
            if (nVertical[c] == nVertical[startCol]) {
               // cerr << " start = " << c << endl;
                if (!prvic) {
                    notes[nNotes - 1].end = c;
                } else {
                    prvic = false;
                }
                
                while (nVertical[c] == nVertical[startCol]) {
                    c++;
                }
              //  cerr << " end = " << c-1 << endl;
                notes[nNotes].start = c;
                nNotes++;
            }
            c++;
        }
        nNotes--;
        cerr << "nNotes " << nNotes << endl;

       
        // delete verticals
        for (int c = 0; c<W; c++) {
            if (nVertical[c] > distBetwLines) {
             //   cerr << "erase col : " << c << " nV: " << nVertical[c] << endl;
                for (int r = 0; r<H; r++) {
                    erase(r,c);
                }
            }
        }

        // tehtaj
        for (int i = 0; i< nNotes; i++) {
            notes[i].weight = 0;
            for (int c = notes[i].start; c<=notes[i].end; c++) {            
                for (int r = 0; r<H; r++) {
                    if (pixel(r,c)) { 
                        notes[i].weight++; 
                        notes[i].center =  notes[i].center + r;
                    }
                }
            }
            notes[i].center =  notes[i].center / (float) notes[i].weight;

            int sr = (int) notes[i].center;
            int sc = (int) ((notes[i].start + notes[i].end)/2.0);

            // poisci gap size 
//            notes[i].yWeight = 0;
  //          for (int r = 0; r<H; r++) {
    //            if (pixel(r,sc)) { 
      //              notes[i].yWeight++; 
      //          }
      //      }

          //  cerr << sr << " " << sc << " ss " << pixelCopy(sr,sc) << " " << pixel(sr,sc) << endl;

            // 0 = false
            notes[i].rat = (float) notes[i].weight / (float)( distBetwLines * ( - notes[i].start + notes[i].end ));
    
           // if (notes[i].rat > 0.5) {
            //if (notes[i].weight > 200) {
            if (pixelCopy(sr,sc) == true) {
                notes[i].type = "Q";
            } else {
                notes[i].type = "H";
            }


            float minDif = 1.0E10;
            for (int j = 0; j < 12; j++) {
                float dif = abs( notes[i].center - tipiNot[j].y );
                if (dif < minDif) {
                    minDif = dif;
                    notes[i].visina = tipiNot[j].sign;
                }
            }
        }

        for (int i = 0; i< nNotes; i++) {
            cerr << "note " << i << " start " << notes[i].start << " end = " << notes[i].end << " w " << notes[i].weight << " c " << notes[i].center << " rat=" << notes[i].rat << " "  << notes[i].visina << notes[i].type  << endl;
        }



    }


    void init(int HH, int WW, string IMAGE) {
        H = HH;
        W = WW;

        vector<string> Image = splitString(IMAGE);

        int index  = 0;

        for (int i = 0; i<Image.size()/2; i++) {
            string color = Image[2*i];
            int length = stoi(Image[2*i+1]); 

            // set pixels
            for (int i = 0; i < length; i++) {
                if (color == "W") {
                    data[index] = false;
                    dataCopy[index] = false;
                } else {
                    data[index] = true;
                    dataCopy[index] = true;
                }
                index++;
            }
        }

        tipiNot[0].sign = "C";
        tipiNot[1].sign = "D";
        tipiNot[2].sign = "E";
        tipiNot[3].sign = "F";
        tipiNot[4].sign = "G";
        tipiNot[5].sign = "A";
        tipiNot[6].sign = "B";
        tipiNot[7].sign = "C";
        tipiNot[8].sign = "D";
        tipiNot[9].sign = "E";
        tipiNot[10].sign = "F";
        tipiNot[11].sign = "G";



    }

};

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    Map map;
    int W;
    int H;
    cin >> W >> H; cin.ignore();    
    string IMAGE;
    getline(cin, IMAGE);

    //W = 10; H = 10; IMAGE="W 66 B 1 W 33"; 

    map.init(H,W,IMAGE);
    map.findLines();

    for (int i = 0; i < map.nNotes; i++) {
        if (i>0) { cout << " ";}
        cout << map.notes[i].visina << map.notes[i].type;
    }
    cout << endl;
 
    // Write an answer using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    //cout << "AQ DH" << endl;
}
