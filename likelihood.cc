#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


long double poisson(long double mu, int k) {
    return ((pow(mu,k)*exp(-1*mu))/(tgamma(k+1)));
}
long double prob(std::vector<int> daten, long double mu) {
  long double L = 1;
  for(int k:daten) {
    L*=poisson(mu,k);
  }
  //std::cout << L << std::endl;
    return L;

}
long double probk(std::vector<int> daten) {
  long double A = 1;
  for(int k:daten) {
    A*=poisson(k,k);
  }
  //std::cout << L << std::endl;
    return A;
}
long double Lambda(std::vector<int> daten,double mu){
  return prob(daten,mu)/probk(daten);
}
int main() {
    using namespace std;
    
    vector<int> daten;

    ifstream fin("datensumme.txt");
    int zahl;
    for(int i = 0 ; i < 234 ; ++i) {
        fin >> zahl;
        daten.push_back(zahl);
    }
    fin.close();

    std::cout << prob(daten,3.11538) << std::endl;
    ofstream fout("likelihood.txt");
    for(double mu = 0; mu <=6; mu+=0.01) {
      fout << mu << " " << prob(daten,mu) << std::endl;
    }
    fout.close();
    ofstream fout2("nll.txt");
    for(double mu=0;mu<=6;mu+=0.01){
      fout2 << mu << " " << (-2)*log(prob(daten,mu)) << std::endl;
    }
    fout2.close();
    ofstream fout3("deltanll.txt");
    for(double mu=0;mu<=6;mu+=0.001){
      fout3 << mu << " " << (-2)*log(prob(daten,mu))-(-2)*log(prob(daten,3.115)) << std::endl;
    }
    fout3.close();
  ofstream fout4("test2.txt");
  fout4 << -2*log(Lambda(daten,3.11538))<< std::endl;
  std::cout<<-2*log(Lambda(daten,3.11538))<< std::endl;
  fout4.close();
  ofstream fout5("reldiv.txt");
  fout5<<(-2*log(Lambda(daten,3.11538))-233)/(sqrt(2*233))<<std::endl;
  std:cout<<(-2*log(Lambda(daten,3.11538))-233)/(sqrt(2*233))<<std::endl;
  fout4.close();

}