arr=(9 4 5 1 2 7)
echo "Enter element to search"
read s
l=${#arr[@]}
f=0
for((i=0; i<l; i++))
do
	if [ ${arr[$i]} -eq $s ]
	then
		f=1
	fi
done
if [ $f -eq 1 ]
then
	echo "Found"
else
	echo "Not found"
fi
