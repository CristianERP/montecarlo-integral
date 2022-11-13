#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string.h>

using namespace std;

double flagCommandLine(int argc, char *argv[], char flag[]);
double integrationFuction(double x);
double integrationReal(double x);
double monteCarloEstimate(double lowerLimit, double upperLimit, int iterations);
double errorFuction(double calculatedValue, double realValue);

int main(int argc, char *argv[])
{

  char lower[] = "--lower";
  char upper[] = "--upper";
  char iter[] = "--iter";

  double lowerLimit = flagCommandLine(argc, argv, lower);
  double upperLimit = flagCommandLine(argc, argv, upper);
  int iterations = flagCommandLine(argc, argv, iter);

  double estimate = monteCarloEstimate(lowerLimit, upperLimit, iterations);

  double real = integrationReal(upperLimit) - integrationReal(lowerLimit);

  double error = errorFuction(estimate, real);

  printf("\tLimite Inferior -> %.1f\n \tLimite Superior -> %.1f\n \tIteraciones -> %.i\n \tValor Estimado = %.1f\n \tValor Real = %.1f\n \tError = %.8f",
         lowerLimit, upperLimit, iterations, estimate, real, error);

  return 0;
}

// Funcion a integrar
double integrationFuction(double x)
{
  return pow(x, 2);
}

// Solucion de integral
double integrationReal(double x)
{
  return pow(x, 3) / 3;
}

// Funcion para estimar la integral con el metodo Monte Carlo
double monteCarloEstimate(double lowerLimit, double upperLimit, int iterations)
{

  double totalSum = 0;
  double randNum;
  double integrationVal;

  int iter = 0;

  for (iter; iter < iterations; iter++)
  {

    // Numero random entre los limites definidos
    randNum = lowerLimit + (float(rand()) / RAND_MAX) * (upperLimit - lowerLimit);

    // Resultado de evaluar la funcion con numero random
    integrationVal = integrationFuction(randNum);

    // Acumular los resultados de las interacion
    totalSum += integrationVal;
  }

  double result = (upperLimit - lowerLimit) * totalSum / iterations;

  return result;
}

double errorFuction(double calculatedValue, double realValue)
{
  return fabs((calculatedValue - realValue) / realValue);
}

double flagCommandLine(int argc, char *argv[], char flag[])
{

  if (argc != 7)
  {
    throw std::invalid_argument("Error de argumentos linea de comandos\n Ejemplo de uso: monteCarlo --lower 0 --upper 1 --iter 100");
    return -1;
  }

  for (int index = 1; index < argc; index = index + 2)
  {
    if (strcmp(flag, argv[index]) == 0)
    {
      return atof(argv[index + 1]);
    }
  }

  throw std::invalid_argument("Error de argumentos linea de comandos\n Ejemplo de uso: monteCarlo --lower 0 --upper 1 --iter 100");
}
