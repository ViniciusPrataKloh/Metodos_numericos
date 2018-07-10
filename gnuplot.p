set encoding utf8
set xlabel 'Dias'
set ylabel 'Células'
set key top left
set yrange [4e+09:1.3e+10]
set term png
set grid
set output 'dt-1.000000.png'
set xrange [0:100]
set xtics (0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100)

f(x) = (4*10**9)*exp(0.01*x)
plot f(x) title 'Analítica' w l, \
'explicit-dt-1.000000.dat' title 'Euler Explícito' w p pt 8 ps 1 lc rgb "green", \
'implicit-dt-1.000000.dat' title 'Euler Implícito' w p pt 6 ps 1 lc rgb "red" \
