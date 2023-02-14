#include <stdio.h>
#include <stdlib.h>
#include "module.h"
#include "string.h"

void app_main(void){
    printf("Result: %d\n", moduleFunction(3,5));
}