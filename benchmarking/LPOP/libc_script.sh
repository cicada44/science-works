
../../redis-libc/src/./redis-cli flushall

for (( i=5000;i<=100000;i+=5000 ))
do
	../../redis-libc/src/./redis-benchmark -t lpop -n $i
done
