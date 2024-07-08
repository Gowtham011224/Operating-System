echo "Enter a string:"
read inp
n=${#inp}
echo "Characters in the string: $n"
ss=${inp:0:2}
echo "Substring1 : $ss"
ss=${inp:2:4}
echo "Substring2 : $ss"


