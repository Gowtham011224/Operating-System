echo "Enter string"
read s
st=""
for((i=0;i<${#s};i++))
do
	ch=${s:$i:1}
	st=$ch$st
done
echo "Reversed string is $st"
