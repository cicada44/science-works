
../../redis-tc/src/./redis-cli flushall

for (( i=5000;i<=100000;i+=5000 ))
do
	../../redis-tc/src/./redis-benchmark -t lpop -n $i
done
