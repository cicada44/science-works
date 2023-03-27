
../../redis-je/src/./redis-cli flushall

for (( i=5000;i<=100000;i+=5000 ))
do
	../../redis-je/src/./redis-benchmark -n $i copy -r 10000
done
