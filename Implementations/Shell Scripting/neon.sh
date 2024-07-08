echo "Enter number"
read n
sq=$((n * n))
sum=0
while [ $sq -gt 0 ]
do
	r=$((sq % 10))
	sum=$((sum + r))
	sq=$((sq / 10))
done
if [ $sum -eq $n ]
then
	echo "Neon number"
else
	echo "Not neon"
fi
