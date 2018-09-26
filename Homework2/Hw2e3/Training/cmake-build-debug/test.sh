for m1 in $(seq 10 30)
do
	for m2 in $(seq 20 30)
	do
		for t in $(seq 1 1000)
		do
			./Training 10 20 >> result.txt
		done
	done
done
