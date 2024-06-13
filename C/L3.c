// 3. Write a program to compute CRC code for the polynomials CRC-12, CRC-16 and CRCCCIP
// Include headers
#include <stdio.h>
#include <string.h>
#define N strlen(gen_poly) // length of the generator polynomial

char data[28]; // data to be transmitted and received

char check_value[28]; // CRC value

char gen_poly[10]; // generator polynomial

int data_length, i, j; // variables

void XOR() // function that performs XOR operation
{
    // if both bits are the same, the output is 0
    // if the bits are different the output is 1
    for (j = 1; j < N; j++)
        check_value[j] = ((check_value[j] == gen_poly[j]) ? '0' : '1');
}
void crc()
{
    for (i = 0; i < N; i++) // initializing check_value
        check_value[i] = data[i];
    do
    {
        if (check_value[0] == '1') // check if the first bit is 1 and calls XOR function
            XOR();
        for (j = 0; j < N - 1; j++) // Move the bits by 1 position for the next computation
            check_value[j] = check_value[j + 1];
        check_value[j] = data[i++]; // appending a bit from data
    } while (i <= data_length + N - 1);
    // loop until the data ends
}
// Function to check for errors on the receiver side
void receiver()
{
    // get the received data
    printf("Enter the received data: ");
    scanf("%s", data);
    printf("\n \n");
    printf("Data received: %s", data);
    crc(); // Cyclic Redundancy Check

    // Check if the remainder is zero to find the error
    for (i = 0; (i < N - 1) && (check_value[i] != '1'); i++)
        ;
    if (i < N - 1)
        printf("\nError detected\n\n");
    else
        printf("\nNo error detected\n\n");
}
int main()
{
    printf("\nEnter data to be transmitted: "); // get the data to be transmitted

    scanf("%s", data);
    printf("\n Enter the Generating polynomial: ");
    scanf("%s", gen_poly); // get the generator polynomial

    data_length = strlen(data); // find the length of data

    for (i = data_length; i < data_length + N - 1; i++) // appending n-1 zeros to the data

        data[i] = '0';
    printf("\n ");
    printf("\n Data padded with n-1 zeros : %s", data); // print the data with padded zeros

    printf("\n ");
    crc(); // Cyclic Redundancy Check

    printf("\nCRC or Check value is : %s", check_value); // print the computed check value

    for (i = data_length; i < data_length + N - 1; i++) // Append data with check_value(CRC)

        data[i] = check_value[i - data_length];
    printf("\n ");
    printf("\n Final data to be sent : %s", data); // printing the final data to be sent

    printf("\n \n");
    receiver(); // Calling the receiver function to check errors

    return 0;
}
