#!/bin/bash

# Function to finding the largest of three numbers
find_largest() {
    echo "Thread 1: Finding largest of $1, $2, $3"
    sleep 1
    if [ $1 -gt $2 ] && [ $1 -gt $3 ]; then
        largest=$1
    elif [ $2 -gt $1 ] && [ $2 -gt $3 ]; then
        largest=$2
    else
        largest=$3
    fi
    echo "Thread 1: Largest number is $largest"
    pthread_exit "$largest"
}

# Function to reversing a number
reverse_number() {
    echo "Thread 2: Reversing number $1"
    sleep 1
    num=$1
    rev=0
    while [ $num -gt 0 ]; do
        digit=$((num % 10))
        rev=$((rev * 10 + digit))
        num=$((num / 10))
    done
    echo "Thread 2: Reversed number is $rev"
    pthread_exit "$rev"
}

# Function to calculate sum of digits
sum_digits() {
    echo "Thread 3: Calculating sum of digits of $1"
    sleep 1
    num=$1
    sum=0
    while [ $num -gt 0 ]; do
        digit=$((num % 10))
        sum=$((sum + digit))
        num=$((num / 10))
    done
    echo "Thread 3: Sum of digits is $sum"
    pthread_exit "$sum"
}

# Main program
echo "Enter three 4-digit numbers:"
read -p "Number 1: " num1
read -p "Number 2: " num2
read -p "Number 3: " num3

# Validate input
for num in $num1 $num2 $num3; do
    if [ ${#num} -lt 4 ]; then
        echo "Error: All numbers must be at least 4 digits!"
        exit 1
    fi
done

echo -e "\nStarting all the threads sequentially..."

# Thread 1: Find largest number
largest=$(find_largest $num1 $num2 $num3)

# Thread 2: Reverse the largest number
reversed=$(reverse_number $largest)

# Thread 3: Sum digits of the original largest number
sum=$(sum_digits $largest)

echo -e "\nFinal Results:"
echo "original Largest Number: $largest"
echo "reversed Largest Number: $reversed"
echo "sum of digits of Largest Number: $sum"
