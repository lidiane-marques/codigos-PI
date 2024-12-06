set datafile separator ","
set title "Bubble Sort vs Merge Sort (C e Python)"
set xlabel "Tamanho da entrada"
set ylabel "Tempo médio (s)"
set logscale 
set format x "10^{%L}"
set xrange [10:1000000]
set ytics 100
set xtics rotate by -45  
set grid
set key outside
set term png size 1280,960  
set output "grafico_resultados.png"
plot "bubble_c_resultado.csv" using 1:2 with linespoints title "Bubble Sort (C)", \
     "bubble_python_resultado.csv" using 1:2 with linespoints title "Bubble Sort (Python)", \
     "merge_c_resultado.csv" using 1:2 with linespoints title "Merge Sort (C)", \
     "merge_python_resultado.csv" using 1:2 with linespoints title "Merge Sort (Python)"
