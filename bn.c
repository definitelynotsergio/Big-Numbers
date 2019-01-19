/* 
Fundamentos de la Computación 2
Exponenciación modular, multiplicación de numeros grandes, y factorización de numeros enteros
por fuerza bruta.
Integrantes:
    - Sergio Muñoz Campos    -   sergio.munoz.ca@usach.cl
    - Belén Lagos Bahamondes -   blagosb@gmail.com
Compilación:
    ->  gcc -o bfnp bfnp.c -lgmp -lm
Uso:
    1)  Algortimo multiplicacion;
        ->  ./bfnp 1 a b
        Ejemplo:
        ->  ./bfnp 1 5563 15151
        ->   a*b=84285013

    2)  Algortimo gcd;
        ->  ./bfnp 2 a b
        Ejemplo:
        ->  ./bfnp 2 4568 62458
        ->    gcd(a, b)=2

    3)  Algortimo Exponenciacion modular binaria;
        ->  ./bfnp 3 a k
        Ejemplo:
        ->  ./bfnp 3 37 8
        ->   a^k=3512479453921

    4)  Algortimo factorizacion;
        ->  ./bfnp 4 n
        Ejemplo:
        ->  ./bfnp 4 2566325136
        ->   {2^4} {3^1} {19^1} {41^1} {68633^1}

*/          

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <math.h>
#include <time.h>

void multiplicacion(char* input[]);
void gcd(char* input[]);
void expmodbin(char* input[]);
void factorizacion(char* input[]);

int main(int argc, char *argv[]){
    switch(strtol(argv[1], NULL, 10)){
        case 1:
            multiplicacion(argv);
            break;

        case 2:
            gcd(argv);
            break;

        case 3:
            expmodbin(argv);
            break;
        
        case 4: 
            factorizacion(argv);
            break;

        default:
            printf("Error en el primer argumento (1, 2, 3, 4)");            
    }
    return 0;
}

void multiplicacion(char* input[]){
    clock_t start_t, end_t; 
    mpz_t a, b, a_times_b;
    mpz_init(a);
    mpz_init(b);
    mpz_init(a_times_b);
    mpz_set_str(a, input[2], 10); 
    mpz_set_str(b, input[3], 10); 

    start_t = clock();
    mpz_mul(a_times_b, a, b);
    end_t = clock();
    gmp_printf("a*b=%Zd\n", a_times_b);
    printf("Tiempo: %f\n",  (double)(end_t - start_t) / CLOCKS_PER_SEC);
    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(a_times_b); 
}

void gcd(char* input[]){
    clock_t start_t, end_t; 
    mpz_t a, b, r;
    mpz_init(a);
    mpz_init(b);
    mpz_init(r);
    mpz_set_str(a, input[2], 10); 
    mpz_set_str(b, input[3], 10); 

    start_t = clock();
    while(mpz_cmp_ui(b, 0)!=0){        
        mpz_mod(r, a, b);
        mpz_init_set(a,b);
        mpz_init_set(b,r); 
    }
    end_t = clock();
    gmp_printf("gcd(a, b)=%Zd\n", a);
    printf("Tiempo: %f\n",  (double)(end_t - start_t) / CLOCKS_PER_SEC);
    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(r);
}

void expmodbin(char* input[]){
    clock_t start_t, end_t; 
    mpz_t a, k, r_0;
    char *bin;
    int n, i;
    mpz_init(a);
    mpz_init(k);
    mpz_init(r_0);
    mpz_set_str(a, input[2], 10); 
    mpz_set_str(k, input[3], 10);
    n = mpz_sizeinbase(k,2);
    bin = malloc(n*sizeof(char));
    mpz_get_str(bin, 2, k);

    start_t = clock();
    mpz_set(r_0, a);
    for(i=1; i<n; i++){
        mpz_mul(r_0, r_0, r_0);
        if(bin[i] == '1'){
            mpz_mul(r_0, r_0, a);
        }            
    }
    end_t = clock();
    gmp_printf("a^k=%Zd\n", r_0);   
    printf("Tiempo: %f\n",  (double)(end_t - start_t) / CLOCKS_PER_SEC); 

    mpz_clear(a);
    mpz_clear(k);
    mpz_init(r_0);
    free(bin);
}

void factorizacion(char* input[]){
    clock_t start_t, end_t;
    unsigned long int i, j;
    mpz_t number, max, aux, aux2;
    mpz_init(number);
    mpz_init(max);
    mpz_init(aux);
    mpz_init(aux2);
    mpz_set_str(number, input[2], 10); 
    mpz_sqrt(max,number);

    start_t = clock();

    mpz_t *primes;
    primes = (mpz_t *) malloc( (mpz_get_ui(max)+1) * sizeof(mpz_t)); //primes[max+1];        

    mpz_add_ui(aux, max,1);
    
    for(i = 2; mpz_cmp_ui(aux, i)>0; i++){ // i<=max+1 Crea los elementos hasta sqrt(number); 
        mpz_init(primes[i]); //primes[i] = i;         
        mpz_set_ui(primes[i], i);
        
    }  

    /* Generar la criba */
    i = 2;
    mpz_t multi;
    mpz_init(multi);
    mpz_set_ui(aux, i*i); //aux=i*i
    mpz_add_ui(aux2, max,1);
    while (mpz_cmp(aux, aux2)<0){ //(i*i) < max+1
        if ( mpz_cmp_ui(primes[i], 0) != 0){ //primes[i] != 0)
            for(j=2; mpz_cmp_ui(max, j)>0; j++){ //mpz_cmp_ui(max, i)>0 j<max
                mpz_mul_ui(multi, primes[i], j); //multi = primes[i]*j
                if (mpz_cmp(multi, max)>0) // if (multi > max)
                    break;
                else{
                    mpz_set_ui(primes[mpz_get_ui(primes[i])*j], 0); // primes[primes[i]*j]=0
                }
                    
            }
        }
        i++;
        mpz_set_ui(aux, i*i);
    }
    int potencia=0;
        int fact_disc=0; //cantidad de factores distintos
        for(i=2; mpz_cmp_ui(aux2, i)>0; i++){ //i<max+1 Recorro la criba
            if(mpz_cmp_ui(primes[i], 0)!= 0){ //pertenezca a la criba
                mpz_mod(aux, number, primes[i]); //obtengo el mod
                if(mpz_cmp_ui(aux, 0)==0){ //number%primes[i]==0
                    //printf("{%d, ", primes[i]);
                    fact_disc++;
                    printf("{");
                    mpz_out_str(stdout, 10, primes[i]);
                    printf("^");
                    while(mpz_cmp_ui(aux, 0)==0){ //genera las potencias del factor primo
                        potencia++;
                        mpz_div(number, number, primes[i]); //number=number/primes[i];
                        mpz_mod(aux, number, primes[i]);  //recalculo el resto
                    }
                    printf("%d} ", potencia);
                }                
            }
            potencia=0;
        }

        
        if(mpz_cmp_ui(number, 1) != 0){ //muestra el ultimo numero primo que esta fuera de la criba y es divisor
            printf("{");
            mpz_out_str(stdout, 10, number);
            printf("^1}");
        }
        printf("\n");
    

        end_t = clock();
	    printf("\ntime: %f",  (double)(end_t - start_t) / CLOCKS_PER_SEC);

        /*Libera el espacio de las variables tipo mpz_t o punteros creados*/
        mpz_add_ui(aux, max,1);
        for(i = 2; mpz_cmp_ui(aux , i)>0; i++){ 
            mpz_clear(primes[i]); 
        }
        free(primes);
        mpz_clear(number);
        mpz_clear(max);
        mpz_clear(aux);
        mpz_clear(aux2);
        mpz_clear(multi);

}




