for m1 in $(seq 10 30)
do
	for m2 in $(seq 10 30)
	do
		for t in $(seq 1 100)
		do
			./Training 20 20 >> result.txt
		done
	done
done
