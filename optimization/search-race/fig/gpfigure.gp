POLNA = 1; CRTKANA = 2; PIKE=4; RDECA =1; ZELENA =2; MODRA=3;CRNA=7;PLUS=1;KRIZEC=2;ZVEZDA=3;PRAZENKVADRAT=4;POLNKVADRAT=5;PRAZENKROG=6;POLNKROG=7
ilw=2; ips=1; iss=0.75; 


# set term wxt enhanced dashed "arial,16"
# za barvni: color
# za velikost slike size 9cm,7cm
set terminal epslatex  color font ',8.5pt'; set output 'gpfigure.tex';ilw=4;ips=2
set border linewidth 1
#set format y "%2.0t \cdot 10^{%L}"
#set format y "$10^{%L}$"

MODRIKVADRATI = 1; set style line MODRIKVADRATI   lc MODRA  lt POLNA lw ilw pt POLNKVADRAT    ps iss  
RDECIKVADRATI = 2; set style line RDECIKVADRATI lc RDECA  lt POLNA lw ilw pt POLNKVADRAT ps iss  
ZELENAZVEZDA =  3; set style line ZELENAZVEZDA  lc ZELENA lt POLNA lw ilw pt ZVEZDA      ps iss  
MODRIKROGCI = 4; set style line MODRIKROGCI lc MODRA  lt POLNA lw ilw pt POLNKROG    ps iss  
RDECIKROGCI = 5; set style line RDECIKROGCI lc RDECA  lt POLNA lw ilw pt POLNKROG ps iss  
MODRIPKROG = 6; set style line MODRIPKROG lc MODRA  lt POLNA lw ilw pt PRAZENKROG    ps iss  
RDECIPKROG = 7; set style line RDECIPKROG lc RDECA  lt POLNA lw ilw pt PRAZENKROG ps iss  
MODRIPLUS = 8; set style line MODRIPLUS lc MODRA  lt POLNA lw ilw pt PLUS    ps iss  
RDECIPLUS = 9; set style line RDECIPLUS lc RDECA  lt POLNA lw ilw pt PLUS ps iss  
MODRIKRIZEC = 10; set style line MODRIKRIZEC lc MODRA  lt POLNA lw ilw pt KRIZEC    ps iss  
RDECIKRIZEC = 11; set style line RDECIKRIZEC lc RDECA  lt POLNA lw ilw pt KRIZEC ps iss  
CRNACRTA = 12; set style line CRNACRTA lc CRNA lt POLNA lw ilw

#set label 1 '{\footnotesize model development data set}' at graph 0.22,1.03 center rotate by 0.0 tc ls CRNACRTA
#set key spacing 1.5

#Set the X axis label
set xlabel "x" 
#Set the Y axis label
set ylabel "y" offset -3,0,0
#set xrange [-15:35]

set size ratio -1

plot \
"../src/track.dat" index 0 using 1:2:6 title '\footnotesize{track}'  with points lc  variable lw 2,\
"../src/circles.dat" using 1:2:3:4 with circles lc variable notitle 


