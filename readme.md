Compilación:
    ->  gcc -o bn bn.c -lgmp -lm
Uso:
    1)  Algortimo multiplicacion;
        ->  ./bn 1 a b
        Ejemplo:
        ->  ./bn 1 5563 15151
        ->   a*b=84285013

    2)  Algortimo gcd;
        ->  ./bn 2 a b
        Ejemplo:
        ->  ./bn 2 4568 62458
        ->    gcd(a, b)=2

    3)  Algortimo Exponenciacion modular binaria;
        ->  ./bn 3 a k
        Ejemplo:
        ->  ./bn 3 37 8
        ->   a^k=3512479453921

    4)  Algortimo factorizacion;
        ->  ./bn 4 n
        Ejemplo:
        ->  ./bn 4 2566325136
        ->   {2^4} {3^1} {19^1} {41^1} {68633^1}
