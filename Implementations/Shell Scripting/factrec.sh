fact() {
    n=$1
    if [ $n -eq 0 ]; then
        echo 1
    else
        m=$((n - 1))
        f=$(fact $m)
        r=$((n * f))
        echo $r
    fi
}

echo "Enter number"
read n
result=$(fact $n)
echo "The factorial value is $result"

