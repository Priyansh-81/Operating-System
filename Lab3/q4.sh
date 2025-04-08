#!/bin/sh

# Gross salary calculator
echo "Enter basic salary and TA"
read bsc
read ta
echo "Basic Salary: $bsc"
echo "TA: $ta"
# Calculate gross salary
gs=$(echo "$bsc + $ta + $bsc * 0.1" | bc)
echo "Gross salary is $gs"
