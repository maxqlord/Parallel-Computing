#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

int valueinarray(int val, char arr[], int size){
    int i;
    for (i=0; i < size; i++) {
        if (arr[i] == val)
            return i;
    }
    return -1;
}

int main(int arr,char* array[])
{
    FILE* fin;
    char code[10000];
    char message[10000];
    char freq[10000];
    char all_chars[10000];
    char ch, key;


    fin =  fopen( "decodeME.txt" , "r" ); //open txt file
    //NULL THE ARRAY
    for(int i = 0; i <10000 ; i++)
    {
        code[i] = message[i] = freq[i] = all_chars[i] = '\0';
    }


    int n = 29; //num of lines

    //read in # of lines value
    while(1) {
        fread(&ch, sizeof(char), 1, fin);
        //
        if (ch == '\n')
            break;
    }

    //create key
    for(int k = 0; k < n; k++) //for each line of key
    {
        fread(&key, sizeof(char), 1, fin); //read in letter
        int index = 1;
        while(1)
        {
            fread(&ch, sizeof(char), 1, fin); //read in next binary
            if(ch == '\n') //if endline char
                break;

            index *=2;  //find final index (if 0 then 2k if 1 then 2k+1)
            if(ch == '1') {
                index += 1;
            }

        }
        //%d = int %c = interpret as char
        //printf("index=%d\t", index);
        //printf("key=%c\n", key);
        code[index] = key;
    }


    //DECODE MESSAGE

    int index = 1; //starting value of eventual message index
    int decoded_index = 0; //current free message index
    int encoded_counter = 0; //count number of bits in encoded message
    int message_counter = 0; //count number of characters in decoded message
    int next_arr_index = 0;
    //all_chars
    //freq



    while(!(feof(fin))) //while file is not empty
    {
        fread(&ch, sizeof(char), 1, fin);
        if (ch == '\n') {
            //printf("found\n");
            break;
        }
        //find index with 2k or 2k +1
        encoded_counter += 1;
        index *= 2;
        if(ch == '1')
            index++;
        //check if index holds a value
        if(code[index] != '\0')
        {

            if(valueinarray(code[index], all_chars, 10000) == -1) {   //creating freq data
                all_chars[next_arr_index] = code[index];
                freq[next_arr_index] = 1;
                next_arr_index+=1;
            } else {
                freq[valueinarray(code[index], all_chars, 10000)] += 1;
            }
            message[decoded_index] = code[index]; //fill message
            message_counter += 1; //increment message counter
            decoded_index +=1; //move to next message index
            index = 1; //reset index
        }
    }
    printf("Message: %s\n", message );
    fclose(fin);	//close file
    printf("Message length: %d\n", message_counter);
    printf("Encoded length: %d\n", encoded_counter);


    float ratio = (float)100* ((8 * message_counter) - (encoded_counter))/(8*message_counter) ;
    printf("Compression ratio: %f", ratio);
    printf("%%\n");



    //find frequency for each char
    //probability = frequency/total
    float min_bits = 0;
    for(int i = 0; i < next_arr_index; i++) {
        //printf("char=%c\t", all_chars[i]);
        //printf("value=%d\n", freq[i]);
        min_bits += freq[i] * -log2f((float) freq[i]/message_counter);
    }

    printf("Min Bits: %f\n", min_bits);




    //minimum number of bits = SUM(frequency * -log2(probability))
}