#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    string name = get_string("What is your name? ");
    printf("Hello, %s, how you doing today?\n", name);
    // string response = get_string("Good or Bad?: ");

    // if((strcmp(response,"Good")==0) || (strcmp(response,"good")==0)){
    //     printf("I'm so glad you to hear that you doing %s.", response);
    // }
    // if(strcmp(response,"Bad")==0 || strcmp(response,"bad")==0){
    //     printf("I'm sorry to hear that, lets code a bit I'm sure it will make you feel better.");
    // }
    // printf("\nLets get started :)\n");
}
