echo "Enter a number to be checked: "
read num
len=${#num}
sum=0
for (( i=0; i<$len; i++ ))
do
  digit=${num:i:1}
  powered=$(( digit ** len ))
  sum=$(( sum + powered ))
done

if [ $sum -eq $num ]
then
    echo "$num is an Armstrong number."
else
    echo "$num is not an Armstrong number."
fi
