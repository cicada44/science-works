
../../redis-libc/src/./redis-cli flushall

for (( i=5000;i<=100000;i+=5000 ))
do
	../../redis-libc/src/./redis-benchmark -t lrange_300 -n $i
done
