#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

FILE *pFile = NULL;

int checkConvergence(const double error, const double tol){
  if(error <= tol){
    FILE *pFile = NULL;
    pFile = fopen("convegence.dat", "a");
    if(pFile == NULL)
      return 0;
    fprintf(pFile, "Error: %lf and tolerance: %lf", error, tol);
  }
  return 1;
}

int concatName(char* file, const double dt){
  char aux[20];
  sprintf(aux, "%f", dt);
  strcat(file, aux);
  strcat(file, ".dat");
}

int explicitEuler(double* explicit, const int* t, const double n0, const double r, const double dt, const int steps){
  int count;
  char file[40] = "explicit-dt-";
  concatName(file, dt);
  double cal_aux = r * dt;

  explicit[0] = n0;
  for(count = 1; count <= (steps); count++){
    explicit[count] = (1 + (cal_aux)) * explicit[count-1];
  }

  pFile = fopen(file, "w");
  if(pFile == NULL)
    return 0;
  fprintf(pFile, "#Dias \t Celulas\n");
  for(count = 0; count < (steps) + 1; count++){
  	fprintf(pFile, "%d \t   %lf \n", t[count], explicit[count]);
  }
  fclose(pFile);
  return 1;
}

int implicitEuler(double* implicit, const int* t, const double n0, const double r, const double dt, const int steps){
  int count;
  char file[40] = "implicit-dt-";
  concatName(file, dt);
  double cal_aux = r * dt;

  implicit[0] = n0;
  for(count = 1; count <= (steps) + 1; count++){
    implicit[count] = (1 / (1 - (cal_aux))) * implicit[count-1];
  }

  pFile = fopen(file, "w");
  if(pFile == NULL)
    return 0;
  fprintf(pFile, "#Dias \t Celulas\n");
  for(count = 0; count < (steps) + 1; count++){
  	fprintf(pFile, "%d \t   %lf \n", t[count], implicit[count]);
  }
  fclose(pFile);
  return 1;
}

int explicitError(double expError, double logTime, const double* explicit, const double* analytic, const int sample, const double dt, double const tol){
  int cal_aux = sample/dt;
  char file[40] = "log_explicit.dat";
  expError = fabs(explicit[cal_aux] - analytic[cal_aux]);
  double logExpError = log(expError);
  logTime = log(dt);

  pFile = fopen(file, "a");
  if(pFile == NULL)
    return 0;
  fprintf(pFile, "%lf \t %lf \t %lf \n", logTime, logExpError, expError);
  fclose(pFile);

  return 1;
}

int implicitError(double impError, double logTime, const double* implicit, const double* analytic, const int sample, const double dt, double const tol){
  int cal_aux = sample/dt;
  char file[40] = "log_implicit.dat";
  impError = fabs(implicit[cal_aux] - analytic[cal_aux]);
  double logImpError = log(impError);
  logTime = log(dt);

  pFile = fopen(file, "a");
  if(pFile == NULL)
    return 0;
  fprintf(pFile, "%lf \t %lf \t %lf \n", logTime, logImpError, impError);
  fclose(pFile);

  return 1;
}

int discretTimes(int* t, const int dt, const int steps){
  int count;
  t[0] = 0;
  for(count = 1; count <= (steps) + 1; count++){
  	t[count] = dt + t[count-1];
  }
  return 1;
}

int analyticFunc(double* analytic, const double n0, const int* t, const double r, const double steps){
  int count;
  for(count = 0; count <= steps+1; count++){
    analytic[count] = n0 * exp(r * t[count]);
  }
  pFile = fopen("analytic.dat", "w");
  if(pFile == NULL)
    return 0;
  fprintf(pFile, "#Dias \t Celulas \n");
  for(count = 0; count <= steps; count++){
  	fprintf(pFile, "%d \t   %lf \n", t[count], analytic[count]);
  }
  fclose(pFile);
  return 1;
}

int main(int argc, char *argv[]){
  double r = 0.01;
  double n0 = 4000000000;
  double dt = atof(argv[1]);
  int tmax = atof(argv[2]);
  double tol = 0.5;
  int steps = (int) tmax/dt;
  double t[steps];
  int sample = 50;

  long double logTime;
  double expError;
  double impError;
  double explicit[steps];
  double implicit[steps];
  double analytic[steps];

  discretTimes(t, dt, steps);
  analyticFunc(analytic, n0, t, r, steps);
  explicitEuler(explicit, t, n0, r, dt, steps);
  implicitEuler(implicit, t, n0, r, dt, steps);
  explicitError(expError, logTime, explicit, analytic, sample, dt, tol);
  implicitError(impError, logTime, implicit, analytic, sample, dt, tol);

  return 0;
}
