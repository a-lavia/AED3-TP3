rm -f ej1.out
touch ej1.out

for i in {3..14..1} 
do
    paradas=$((($i*2+3-1)/3))
    gimnasios=$(($i/3))
    mochila=$(($paradas*3/$gimnasios+1))
    for dificultad in {10..100..10}
    do
        # echo $i"   "$paradas", "$gimnasios", "$mochila
        ./gen.out 20 20 $gimnasios $paradas $mochila $dificultad 10
        ./ej1Exp.out < mapa.out
    done
done
