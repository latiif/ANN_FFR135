for m1 in $(seq 30 130)
do
	for m2 in $(seq 30 130)
	do
		./Training $m1 $m2 >> result.txt
	done
done
