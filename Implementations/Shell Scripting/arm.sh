echo "Enter n:"
read n
s=${#n}
nl=$n
sum=0

while [ $n -gt 0 ]
do
    d=$((n % 10))
    p=$((d ** s))
    sum=$((sum + p))
    n=$((n / 10))
done
if [ $sum -eq $nl ]
then
    echo "$nl is an Armstrong number"
else
    echo "$nl is not an Armstrong number"
fi

