# Write a shell script to check whether the user entered number is prime or not.

#!/bin/bash

echo "Enter the number to check for prime:"
read num

checkprime() {
    local n=$1
    if [ $n -le 1 ]; then
        echo "$n is not a prime number."
        return
    fi

    for ((i = 2; i * i <= n; i++)); do
        if [ $((n % i)) -eq 0 ]; then
            echo "$n is not a prime number."
            return
        fi
    done

    echo "$n is a prime number."
}

checkprime "$num"
