#include <iostream>
#include <cmath>

using namespace std;
double effective_depth(int rebar,int rebar_cover,int overall_d)
{
	int d;
	d= overall_d-rebar*1.5-rebar_cover;
	return d;
}
double Tension(double Fc,int L, int d, double num_pile)
{ 
	double T;
	if (num_pile == 2)
	{
		T=Fc*d/(4*d);
	}
	if (num_pile == 3)
	{
		T=Fc*d/(9*d);
	}
	if (num_pile == 4)
	{
		T=Fc*d/(8*d);
	}
	return T;

}
int main()
{
	double c, Fc, Fcu, Fy;
	cout << "input column's width in mm" << endl;
	cin >> c;//input column width, assumed squred column
	cout << "input column's design load in kN" << endl;
	cin >> Fc;//input load from column
	cout << "grade of concrete?" << endl;
	cin >> Fcu;
	cout << "grade of steel?" << endl;
	cin >> Fy;
	int rebar,rebar_cover;
	cout << "prefered size of rebar ?" << endl;
	cin >> rebar;// input prefered size of reinforcement bar
	cout << "rebar cover in mm" << endl;
	cin >> rebar_cover;//input rebar cover
	int overall_d;
	cout << "Design overall depth in mm" << endl;
	cin >> overall_d;
	double d=effective_depth(rebar,rebar_cover,overall_d);
	double pile_d;
	cout << "Design pile diameter" << endl;
	cin >>pile_d;
	int c2c;
	cout << "Design pile distance, it should be within "<< 3*pile_d <<" to distribute rebar uniformly"<< endl;
	cin >> c2c;
	int num_pile;
	cout << "number of pile?" << endl;
	cin >> num_pile;
	if (num_pile !=2 & num_pile !=3 & num_pile !=4)
	{ 
		cout << "Please input vaild number of pile. (2 , 3 or 4)" << endl;
		cin >> num_pile;
	}
	double b=c2c+pile_d+rebar_cover*2;//Take covering from side to be double of rebar cover
	cout << " Take pile cap length be: " << b << " mm"<<endl;
	double T;
	T= Tension(Fc,c2c,d,num_pile);
	double As_req;
	As_req= T*1000/(0.87*Fy)*2;
	cout << "Required area of rebar is "<< As_req << " mm^2"<< endl;
	cout << "Suggested number of rebar: " << As_req/(rebar*2*3.1415) << endl;
	int rebar_no;
	cout << "Design number of rebars: "<<endl;
	cin >> rebar_no;
	double As_pro=rebar_no*(rebar*2*3.1415);
	cout << "As provided=: " << As_pro << " mm^2" << endl;
	cout << endl;
	cout << "Steel ratio=  " << 100*As_pro/((c2c+pile_d+rebar_cover*2)*overall_d) <<endl; //Take covering from side to be double of rebar cover
	cout << " It should be within 0.13 to 4"<<endl;
	cout << endl;
	cout << "Check maximum shear at perimeter of the column face:" << endl;
	cout << "Perimeter of the column= " << 4*c << " mm"<< endl;
	cout << "Design shear=" << Fc << "KN" << endl;
	cout << "Vmax=" << Fc*1000/(4*c*d)<<"MPa"<< endl;
	cout << "It should be smaller than  "<< 0.8*sqrt(Fcu)<<" or 7 MPa" << endl;
	cout << endl;
	cout << "Check Shear at Section av from from Column Face" << endl;
	cout << "100As/bd=  " << 100*As_pro/(b*d) << endl;
	cout << "(400/d)^1/4= " << sqrt(sqrt(400 / d)) << "     has to be greater then 0.67"<< endl;//checking
	double vc = 0.79 * pow(100*As_pro/b*d,1/3)*sqrt(sqrt(400 / d))/1.25*pow(Fcu/25,1/3);//maximum allowable shear of concretee
	cout << "vc= " <<vc << " MPa" << endl;
	double av= (c2c-pile_d-c)/2+0.2*pile_d;
	cout << "critical section for shear check av=" << av <<"mm"<< endl;
	cout << "Enhanced Vc=" << vc*(1.5*d/av) <<"   check if smaller than"<< 0.8*sqrt(Fcu)<<"or 7 MPa"<< endl;
	cout << "Design shear V = " << Fc/2 <<endl;
	cout << "shear stress= " << (Fc/2)*1000/(b*d)<< "   It should be smaller than Enhanced Vc," << vc*(1.5*d/av)<<endl;
	cout << "type anything to end the program" << endl;
	char answer;
	cin >> answer;

	return 0;
}





