echo "Enter string"
read s
l=${#s}

c=0
for((i=0; $i<l; ((i++))))
do
	ch=${s:$i:1}
	case $ch in 
		[aeiou])
			((c++))
	esac
done
echo "Vowel count:$c"


			
