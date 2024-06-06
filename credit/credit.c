#include <cs50.h>
#include <stdio.h>

long acquireCardNumber(void);
int determineCardSize(long cardNumber);
int determineCardTypeValidity(long cardNumber, int cardLength);
bool determineCheckSumCompliance(long cardNumber, int cardLength);

int main(void)
{
    long cardNumber = acquireCardNumber();
    int cardSize = determineCardSize(cardNumber);
    int cardType = determineCardTypeValidity(cardNumber, cardSize);

    if (cardType == 0)
    {
        printf("INVALID\n");
    }
    else
    {
        if (determineCheckSumCompliance(cardNumber, cardSize))
        {
            if (cardType == 1)
            {
                printf("MASTERCARD\n");
            }
            else if (cardType == 2)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("VISA\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
}

long acquireCardNumber(void)
{
    long cardNumber = get_long("Number: ");
    return cardNumber;
}

int determineCardSize(long cardNumber)
{
    long cardNum = cardNumber;
    int cardLength = 0;

    while (cardNum > 0)
    {
        cardNum /= 10;
        cardLength++;
    }
    return cardLength;
}

int determineCardTypeValidity(long cardNumber, int cardLength)
{
    long cardNum = cardNumber;
    int cardPrefix;

    while (cardNum > 0)
    {
        if (cardNum >= 10 && cardNum <= 99)
        {
            cardPrefix = cardNum;
        }
        cardNum /= 10;
    }

    if (cardLength != 15 && cardLength != 16 && cardLength != 13)
    {
        return 0;
    }
    else if ((!(cardPrefix <= 55 && cardPrefix >= 51)) && cardPrefix != 34 && cardPrefix != 37 && (cardPrefix / 10 != 4))
    {
        return 0;
    }
    else
    {
        if (cardPrefix <= 55 && cardPrefix >= 51)
        {
            if (cardLength != 16)
            {
                return 0;
            }
            return 1;
        }
        else if ((cardPrefix == 34 || cardPrefix == 37))
        {
            if (cardLength != 15)
            {
                return 0;
            }
            return 2;
        }
        else
        {
            if (cardLength != 13 && cardLength != 16)
            {
                return 0;
            }
            return 3;
        }
    }
}

bool determineCheckSumCompliance(long cardNumber, int cardLength)
{
    long cardNum = cardNumber;
    int counter = 0;
    int byTwoSum = 0;
    int byOneSum = 0;

    while (cardNum > 0)
    {
        int digit = ((cardNum) - ((cardNum / 10) * 10));
        cardNum /= 10;

        if (counter % 2 == 0)
        {
            byOneSum += (int) digit;
        }
        else
        {
            int product = digit * 2;
            while (product > 0)
            {
                int productDecomp = ((product) - ((product / 10) * 10));
                product /= 10;
                byTwoSum += productDecomp;
            }
        }
        counter++;
    }

    if ((byTwoSum + byOneSum) % 10 == 0)
    {
        return true;
    }
    return false;
}