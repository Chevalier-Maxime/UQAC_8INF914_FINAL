#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>
#define QTOT 500
#define NOM_FICHIER "param_bb.txt"
using namespace std;

double p1(double hChute, double debit);
double p2(double hChute, double debit);
double p3(double hChute, double debit);
double p4(double hChute, double debit);
double p5(double hChute, double debit);
double hauteurChute(double elevationAmont, double qtot, double debit);
double calculElevation(double qtot);

int main ( int argc , char ** argv ) {
  double res = 0;
  double elevAmont; // = 172.6;
	double x[5];
	double Qtot = 0; // = QTOT;
	double QtotInitial = 0;
  bool depassement = false;
  if ( argc >= 2 ) {
		if(true){
			ifstream in (NOM_FICHIER);
			in >> Qtot;
			in >> elevAmont;
			in.close();
		}

		QtotInitial = Qtot;

    ifstream in ( argv[1] );
		double tmp;
		
    for ( int i = 0 ; i < 5 ; i++ ) {
      in >> tmp;
			if(Qtot - tmp >= 0){
				x[i] = tmp;
				Qtot-= tmp;
			}else{
				if(!depassement){
					depassement = true;
					x[i] = Qtot;
					Qtot -= tmp;
				}else{
					x[i] = 0;
					Qtot-= tmp;
				}
			}
    }
    in.close();

		//TODO ajouter lecture dans une fichier pour QTOT et hChute
		//TODO Peut-être remplacer le QTOT ici, par le QTOT donné par nomad ?...
		
		res = p1(hauteurChute(elevAmont,QtotInitial,x[0]), x[0]) +
						p2(hauteurChute(elevAmont,QtotInitial,x[1]), x[1]) +
						p3(hauteurChute(elevAmont,QtotInitial,x[2]), x[2]) +
						p4(hauteurChute(elevAmont,QtotInitial,x[3]), x[3]) +
						p5(hauteurChute(elevAmont,QtotInitial,x[4]), x[4]);
			
		/*cout << "P1 : " << p1(hauteurChute(elevAmont,QTOT,x[0]), x[0]) << endl;
		cout << "P2 : " << p1(hauteurChute(elevAmont,QTOT,x[1]), x[1]) << endl;
		cout << "P3 : " << p1(hauteurChute(elevAmont,QTOT,x[2]), x[2]) << endl;
		cout << "P4 : " << p1(hauteurChute(elevAmont,QTOT,x[3]), x[3]) << endl;
		cout << "P5 : " << p1(hauteurChute(elevAmont,QTOT,x[4]), x[4]) << endl;*/

		res *= -1; //Because Nomad minimize
  }

	if(depassement)
		Qtot *= -1;
  cout << res << " " << Qtot << endl;
  return 0;
}

double p1(double hChute, double debit){
    hChute = (hChute - 31.97) / 1.589;
		debit = (debit - 118.5) / 55.03;
		
		double res = 0;
		
		double t2 = 1.659 * hChute;
		double t3 = 15.17 * debit;
		double t4 = 6.038e-3 * pow(hChute, 2);
		double t5 = 0.8589 * hChute * debit;
		double t6 = 2.71 * pow(debit, 2);
		double t7 = 2.805e-3 * pow(hChute, 2) * debit;
		double t8 = 0.04096 * hChute * pow(debit, 2);
		double t9 = 1.309 * pow(debit, 3);
		
		res = 32.15 + t2 + t3 - t4 + t5 - t6 - t7 + t8 - t9;
		
		return res;
}

double p2(double hChute, double debit){
  //Normalisation des donn�es :
		//TODO absolument pas sur qu'on doivent faire un truc dans le genre
		hChute = (hChute - 31.98) / 1.589;
		debit = (debit - 114.6) / 57.24;
		
		double res = 0;
		
		double t2 = 1.68 * hChute;
		double t3 = 13.65 * debit;
		double t4 = 6.624 * pow(10, -14) * pow(hChute, 2);
		double t5 = 0.8393 * hChute * debit;
		double t6 = 1.25 * pow(debit, 2);
		
		
		res = 32.35 + t2 + t3 + t4 + t5 - t6;
		
		return res;
}

double p3(double hChute, double debit){
  //Normalisation des donn�es :
		//TODO absolument pas sur qu'on doivent faire un truc dans le genre
		hChute = (hChute - 31.97) / 1.588;
		debit = (debit - 123.5) / 51.05;
		
		double res = 0;
		
		double t2 = 1.77 * hChute;
		double t3 = 14.88* debit;
		double t4 = 0.9327 * hChute * debit;
		double t5 = 3.237 * pow(debit, 2);
		double t6 = 0.08316 * hChute * pow(debit, 2);
		double t7 = 1.478 * pow(debit, 3);
		
		res = 34.02 + t2 + t3 + t4 - t5 + t6 - t7;
		
		return res;
}

double p4(double hChute, double debit){
	hChute = (hChute - 31.97) / 1.588;
		debit = (debit - 121.9) / 55;
		
		double res = 0;
		
		double t2 = 1.799 * hChute;
		double t3 = 18.65 * debit;
		double t4 = 1.139 * hChute * debit;
		double t5 = 4.391 * pow(debit, 2);
		double t6 = 0.1478 * hChute * pow(debit, 2);
		double t7 = 2.582 * pow(debit, 3);
		
		res = 34.8 + t2 + t3 + t4 - t5 + t6 - t7;
		
		return res;
}

double p5(double hChute, double debit){
	hChute = (hChute - 31.98) / 1.588;
		debit = (debit - 113.4) / 53.7;
		
		double res = 0;
		
		double t2 = 1.866 * hChute;
		double t3 = 15.75 * debit;
		double t4 = 1.01 * hChute * debit;
		double t5 = 2.666 * pow(debit, 2);
		double t6 = 0.05991 * hChute * pow(debit, 2);
		double t7 = 1.335 * pow(debit, 3);
		
		res = 32.57 + t2 + t3 + t4 - t5 + t6 - t7;
		
		return res;
}

/**
	 * Approximation de la fonction d'elevation
	 * @param qtot	Le debit total turbin� � la centrale
	 * @return Elevation aval
	 */
	double calculElevation(double qtot) {
		double res = 0;
		
		double t1 = 8.639e-13 * pow(qtot, 4);
		double t2 = 3.189e-9 * pow(qtot, 3);
		double t3 = 3.257e-6 * pow(qtot, 2);
		double t4 = 2.168e-3 * qtot;
		
		res = t1 - t2 + t3 + t4 + 137.5;
		
		return res;
	}
	
	/**
	 * Calcul de la hauteur de chute
	 * @param elevationAmont	Elevation Amont
	 * @param qtot				D�bit total turbin� � la centrale
	 * @param debit				D�bit turbin� par la turbine
	 * @return					La hauteur de chute
	 */
	double hauteurChute(double elevationAmont, double qtot, double debit) {
		double res = 0;
		
		res = elevationAmont - calculElevation(qtot) - (0.5e-5 * pow(debit, 2));
		
		return res;
	}