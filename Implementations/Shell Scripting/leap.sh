echo "Enter year"
read y
f=0
if [ $((y % 4)) -eq 0 ]
then
	f=1
fi
if [ $((y % 100)) -eq 0 ]
then
	f=0
fi
if [ $f -eq 1 ]
then
	echo "Leap year"
else
	echo "Not leap year"
fi
