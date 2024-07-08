echo "Enter a"
read a
echo "Enter b"
read b
echo "Guess what is a*b ?"
read c
if [ $c -eq $((a * b)) ]
then
	echo "Crct"
else
	echo "Wrng"
fi
