#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <iomanip>
#define PI 3.14159265359
#define c 418.9829

using namespace std;

double numeroAleatorio(double menor, double maior) {
       return maior + menor*((double)(rand())/RAND_MAX);
}

double Entradas(int d, double * aux){           /// FUNCAO SCHWEFEL
    double soma = 0;                            /// DEPOSITA EM *AUX O VALOR QUE FOI GERADO PELA FUNCAO EM CADA PARTICULA
    for(int i = 0; i < d; i++){
        double x = aux[i];                      /// OU DA UM RETURN DE ((c * d) - soma) DEPENDENDO DO CASO
        soma = soma + x * sin(sqrt(fabs(x)));   /// CASO SEJA NECESSARIO MUDAR A FUNCAO PSO E NAO USAR MAIS OS ARRAYS AUX1 E AUX2
    }
    double resul = ((c * d) - soma);
    return resul;
}

double Easom (int d, double * aux){
        double resul, x1 = aux[0], x2 = aux[1];
            double fator1 = -cos(x1) * cos(x2);
            double fator2 = exp(-((x1 - PI)*(x1 - PI)) - ((x2-PI)*(x2-PI)));
            resul = fator1 * fator2;
        return resul;
}
void EncontrarGbest(double ** pbest, double * gbest, int nP, int d){
    for(int i = 0 ; i < nP; i++){
        if(Entradas(d,pbest[i]) < Entradas(d,gbest)){
            for(int j = 0; j < d; j++){
                gbest[j] = pbest[i][j];
            }
        }
    }
}
void PreencherPbest (double ** pbest, double ** matrixP, int nP, int d){
    for(int i = 0 ; i < nP; i++){
        for(int j = 0; j < d; j++){
            pbest[i][j] = matrixP[i][j];
        }
    }
}
void PSO(double ** vP,double ** matrixP, double ** pbest, int nP, int d,int n, double * gbest){ ///CALCULO DO PSO
    int CriterioDParada = 0;
    do{
        int w = 0.9 - (CriterioDParada *((0.9 - 0.4)/n));     /// FATOR DE INERCIA

        for(int i = 0; i < nP; i++){
            if(Easom(d,matrixP[i]) < Easom(d,pbest[i])){  /// SE O RESULTADO DA PARTICULA FOR MENOR QUE O MELHOR RESULTADO JA FEITO POR ELA, TROCASSE OS VALORES
                for(int j = 0; j < d; j++){
                    pbest[i][j] = matrixP[i][j];

                    if(Easom(d,matrixP[i]) < Easom(d,gbest)){   /// SE O VALOR DA PARTICULA FOR MENOR QUE O GBEST, O GEST RECEBE ESSE VALOR
                        gbest[j] = pbest[i][j];
                    }
                }
            }

            for(int j = 0; j < d; j++){
                double r1 = numeroAleatorio(0,1); /// NUMERO ALEATORIO QUALQUER
                double r2 = numeroAleatorio(0,1);
                int con = 2; /// CONSTANTE INDICADA NO SLIDE

                double part1 = (w*vP[i][j]); ///PRIMEIRA PARTE

                double part2 = (con * r1 * (pbest[i][j] - matrixP[i][j])); ///SEGUNDA PARTE

                double part3 = (con * r2 *(gbest[j] - matrixP[i][j])); ///TERCEIRA PARTE

                vP[i][j] = (part1+part2+part3); ///SOMA AS TRES PARTES E DA O VALOR DA VELOCIDADE DA PARTICULA

                if(vP[i][j]> 20)
                    vP[i][j]  = 20;
                if(vP[i][j] < -20)
                    vP[i][j] = -20;

                matrixP[i][j] += vP[i][j];

                if(matrixP[i][j] > 100)
                    matrixP[i][j] = 100;
                else if(matrixP[i][j] < -100)
                    matrixP[i][j] = -100;
            }
        }

        cout << "Iteraçao : " << CriterioDParada << "\n" << Easom(d,gbest)  << "\n";
        CriterioDParada++;
    }while(CriterioDParada != n);
}

void imprimirM (double ** matrix, int nP, int d){ ///IMPRIMIR A MATRIZ PARA TESTES
    for(int i = 0 ; i <nP; i++){
        for(int j = 0; j < d; j++){
            cout <<matrix[i][j] << " ";
        }
        cout<<endl;
    }
}
void imprimirV (double * matrix, int d){ ///IMPRIMIR A VETORES PARA TESTES
    for(int i = 0 ; i < d; i++){
        cout << matrix[i] << " ";
    }
}
void preencher(double ** arr, int nP,int d){
    for(int i = 0; i < nP; i++){
        for(int j = 0; j < d; j++){
            arr[i][j] = numeroAleatorio(-100,100);
        }
    }
}
void preencherNulo(double ** arr, int nP,int d){
    for(int i = 0; i < nP; i++){
        for(int j = 0; j< d; j++){
            arr[i][j] = 0;
        }
    }
}

