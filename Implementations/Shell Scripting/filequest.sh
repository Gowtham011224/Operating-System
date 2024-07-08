echo "Enter file name"
read fname

if [ ! -f $fname ]
then
	echo "File not found"
	exit
else
	echo "File found,
Content of file:"
	cat $fname
fi
st=$(<$fname)
sum=0
len=${#st}
for((i=0;i<len;i++))
do
	ch=${st:$i:1}
	case $ch in 
		[0123456789])
			sum=$((sum+ch))
	esac
done
echo "Sum of digits:$sum"
if [ $((sum % 5)) -eq 0 ]
then
	echo "Divisible by 5"
else
	echo "Not divisible by 5"
fi
