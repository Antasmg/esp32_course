#include <stdio.h>
#include "string.h"

typedef struct Person_struct{
    char firstName[20];
    char lastName[20];
    int age;
}Person; //name of this structure which can be used later

void updatePerson(Person *person){
    strcpy(person->firstName, "Mike");
    strcpy(person->lastName, "Wazowski");
    person->age = 23;
}

void exclamIt(char * word){
    strcat(word, "!");

}

void app_main(void){
    Person person;
    char word[20] = {"Hello, World"};
    exclamIt(word); //It will work also with &
    printf("Function output: %s \n", word);
    updatePerson(&person); //address of the structure is passed
    printf("Person %s %s is %d years old \n", person.firstName, person.lastName, person.age);
}