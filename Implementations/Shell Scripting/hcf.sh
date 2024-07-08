echo "Enter a:"
read a 
echo "Enter b:"
read b
if [ $a -gt $b ]
then
	i=$a
else
	i=$b
fi
for((;i>0;i--))
do
	if [[ $((a % i)) -eq 0 && $((b % i)) -eq 0 ]]
	then
		echo "HCF of $a and $b is $i"
		break
	fi
done
