# Write a shell script to find the factorial of number.

#!/bin/bash

echo "Enter the number to calculate its factorial "
read num

factorial(){
    local n=$1
    fact=1
    if [ $n -le 1 ]; then
        echo "Factorial of $n is 1"
    fi

    for((i = n; i >= 2; i--)); do
        fact=$((fact * i))
    done
    echo "factorial is $fact"
}

factorial "$num"
