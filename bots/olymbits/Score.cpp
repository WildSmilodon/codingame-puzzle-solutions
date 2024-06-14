#include "Score.h"

Score::Score()
{
    cmdNames[0] = "RIGHT";
    cmdNames[1] = "LEFT";
    cmdNames[2] = "UP";
    cmdNames[3] = "DOWN";
    for (int i = 0; i<4; i++)
    {
        h[i] = 0;
        a[i] = 0;
        s[i] = 0;
        d[i] = 0;
    }
}

std::string Score::getCmd()
{
    int total[4];
    std::string cmd = "";
    for (int i = 0; i<4; i++)
    {
        total[i] = h[i] + a[i] + s[i] + d[i];
        std::cerr << h[i]<< " " << a[i]<< " " << s[i]<< " " << d[i]<< " " << total[i]<< " " << cmdNames[i] << std::endl;
    }
    int topScore = - 1000;
    for (int i = 0; i<4; i++)
    {
        if (total[i] > topScore) 
        {
            topScore = total[i];
            cmd = cmdNames[i];
        }
    }

    return cmd;

}