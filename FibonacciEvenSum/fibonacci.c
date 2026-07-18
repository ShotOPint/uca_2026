#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int fiboSumOptimized(int limit){
    
    long sum=0;
    int a=2;
    int b=8;
    while(a<=limit){
        sum+=a;
        int c=4*b+a;
        a=b;
        b=c;
    }

    return sum;
}
int fiboSumBruteForce(int limit){
    long sum=0;
    int a=0;
    int b=1;
    while(a<=limit){
        if(a%2==0){
            sum+=a;
        }
        int c=a+b;
        a=b;
        b=c;
    }

    return sum;
}
int main(){
    int limit;
    printf("Enter the limit: ");
    scanf("%d",&limit);

    int sumOptimized=fiboSumOptimized(limit);
    int sumBruteForce=fiboSumBruteForce(limit);

    printf("Sum of even Fibonacci numbers (Optimized): %ld\n", sumOptimized);
    printf("Sum of even Fibonacci numbers (Brute Force): %ld\n", sumBruteForce);

}