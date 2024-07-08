echo "Enter n"
read n
if [ $n -eq 1 ]
then
	echo "Neither prime nor composite"
else
	c=0
	for((i=2; i<$n; i++))
	do
		if [ $((n % i)) -eq 0 ]
		then 
			c=$((c + 1))
		fi
	done
	if [ $c -eq 0 ]
	then
		echo "Prime"
	else
		echo "Composite"
	fi
fi


