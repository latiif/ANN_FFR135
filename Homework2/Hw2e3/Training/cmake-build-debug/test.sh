for m1 in $(seq 5 30)
do
	for m2 in $(seq 5 30)
	do
		for t in $(seq 1 100)
		do
			./Training 27 9 >> result.txt
		done
	done
done
