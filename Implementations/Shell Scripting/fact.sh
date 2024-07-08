echo "Enter number to find factorial"
read n
p=1
for((i=1;i<=n;i++))
do
         p=$((p * i))
done
echo "Factorial value: $p"
