# Write a shell script to calculate the gross salary. GS=Basics + TA + 10% of Basics.
# Floating point calculations has to be performed.

#!/bin/bash

echo "Enter the basic salary "
read basic
echo "Enter the Travel allowance "
read TA
salary=$(echo "$basic+$TA+$basic * 0.1"|bc)
# use of awk is recommended for floating point calculations
echo "basic salary is $basic"
echo "travel allowance is $TA"
echo "Total salary is $salary"
