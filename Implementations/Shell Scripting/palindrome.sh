echo "Enter num"
read n
nl=$n
sum=0
while [ $nl -gt 0 ]
do
	r=$((nl % 10))
	nl=$((nl / 10))
	sum=$((sum * 10 + r))
done
if [ $n -eq $sum ]
then
	echo "Palindrome"
else
	echo "Not palindrome"
fi

