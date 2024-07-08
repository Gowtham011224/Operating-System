echo "Enter n"
read n
for((i=0; $i<13; ((i++))))
do
	p=$((n * i))
	echo "$n * $i = $p"
done

