#include <stdio.h>
#include <math.h>

struct data
{
	int date[13][32];
}tahun[3000];

float xminusX[22],yminusY[22],x[22],y[22];

void dataSet();
int linearRegression(int year,int month,int date);
void fillGlobalArray(int currYear,int currMonth,int currDay);
void fillRemainingGlobalArray(float X,float Y);
float getSigmaY();
float getSigmaX();
float getSigmaCross();

int main(){
	dataSet();
	while(true){
		printf("Prototype Covid 19 Prediction\n");
		printf("==========================================================\n");
		int day,month;
		printf("Enter month: ");
		scanf("%d",&month);
		printf("Enter day: ");
		scanf("%d",&day);
		int prediction = linearRegression(2020,month,day);
		printf("Prediction : %d\n\n",prediction);
	}
	
	return 0;
}

float averagePastInfected(int currYear,int currMonth,int currDay){
	float pastInfected=0;
	
	for(int i=1;i<=3;i++){
				if(i>=currDay){ //jika tanggal kurang dari 10 (bakal liat data bulan lalu) -- tahun lom bikin :)
					currMonth--;
					
					if(currMonth==2){
						if(currYear%4==0){
							currDay+=29;
						}else{
							currDay += 28;	
						}	
					}
					else if(currMonth<7)
					{
						if(currMonth%2 == 1) currDay+=31;
						else currDay+=30;								
					}
					else if(currMonth>8)
					{	
						if(currMonth%2 == 1) currDay+=30;
						else currDay+=31;
					}
					else{
						currDay+=31;
					}
				}
				pastInfected += tahun[currYear].date[currMonth][currDay-i];
			}
			
	return pastInfected/3;
}

float averageLast10Date(int currYear,int currMonth,int currDay){
	
	float avg20day=0;
	
	for(int i=1;i<=3;i++){
		if(i>=currDay){ //jika tanggal kurang dari 10 (bakal liat data bulan lalu) -- tahun lom bikin :)
			currMonth--;
			
			if(currMonth==2){
				if(currYear%4==0){
					currDay+=29;
				}else{
				currDay += 28;	
				}	
			}
			else if(currMonth<7)
			{
				if(currMonth%2 == 1) currDay+=31;
				else currDay+=30;								
			}
			else if(currMonth>8)
			{	
				if(currMonth%2 == 1) currDay+=30;
				else currDay+=31;
			}
			else{
				currDay+=31;
			}
		}
		avg20day += currDay-i;
	}
	
	return avg20day/3;
}

int linearRegression(int year,int month,int date){
	
	if(tahun[year].date[month][date-1] == NULL){ // melakukan recursive jika hari yang ingin di prediksi mempunyai jarak lebih dari 1 hari 
		tahun[year].date[month][date-1] = linearRegression(year,month,date-1);
	}
	
	float sigmaCross,sigmaX,sigmaY;
	
	fillGlobalArray(year,month,date); //hanya mengisi array x dan y (sebenarnya sudah ada hanya supaya gampang dan tertata saja penamaan variable kita)
	
	float X = averageLast10Date(year,month,date);  // mencari X yaitu rata rata dari tanggal pada 10 hari terahir
	float Y = averagePastInfected(year,month,date); // mencari Y yaitu rata rata infected pada 10 hari terahir
	
	fillRemainingGlobalArray(X,Y); // mengisi array xminusX dan yminusY agar nantinya bisa mencari sigmaX,sigmaY,dan sigmaCross
	
	// menampung hasil sebuah perhitungan yang akan dibutuhkan nantinya
	sigmaX = getSigmaX();
	sigmaY = getSigmaY();
	sigmaCross = getSigmaCross(); 
	
	float r = sigmaCross/sqrt(sigmaX*sigmaY); // mencari nilai data positif covid dari variable hari dan pastInfected (variable X dan Y)
	float Sy = sqrt(sigmaY/3); // dibagi n-1 (9 jadinya)
	float Sx = sqrt(sigmaX/3); // dibagi n-1 (9 jadinya)
	
	float b = r*Sy/Sx; // slope -> ratio antara perkembangan X dan Y, it tells you how much you can expect Y to change as X increases
	float a = Y-b*X; // intercept -> expected Y value at certain X

	int y = a + b*date; // menghitung prediksi infected pada hari yang ditentukan
	
	return y;
}

void dataSet(){
	
	//december
	tahun[2020].date[12][1] = 137919;
	tahun[2020].date[12][2] = 139085;
	tahun[2020].date[12][3] = 140238;
	tahun[2020].date[12][4] = 141270;
	tahun[2020].date[12][5] = 142630;
	tahun[2020].date[12][6] = 143961;
	tahun[2020].date[12][7] = 145427;
	tahun[2020].date[12][8] = 146601;
	tahun[2020].date[12][9] = 147838;
	tahun[2020].date[12][10] = 149018; 
	tahun[2020].date[12][11] = 150250;
	tahun[2020].date[12][12] = 151201;
	tahun[2020].date[12][13] = 152499;
	tahun[2020].date[12][14] = 154065;
	tahun[2020].date[12][15] = 155122;
	tahun[2020].date[12][16] = 156343;
	tahun[2020].date[12][17] = 158033;
	
	//november 2020
	tahun[2020].date[11][1] = 106205;
	tahun[2020].date[11][2] = 107229;
	tahun[2020].date[11][3] = 107846;
	tahun[2020].date[11][4] = 108620;
	tahun[2020].date[11][5] = 109411;
	tahun[2020].date[11][6] = 110083;
	tahun[2020].date[11][7] = 111201;
	tahun[2020].date[11][8] = 112027;
	tahun[2020].date[11][9] = 112743;
	tahun[2020].date[11][10] = 113756; 
	tahun[2020].date[11][11] = 114343;
	tahun[2020].date[11][12] = 115174;
	tahun[2020].date[11][13] = 116207;
	tahun[2020].date[11][14] = 117462;
	tahun[2020].date[11][15] = 118627;
	tahun[2020].date[11][16] = 119633;
	tahun[2020].date[11][17] = 120671;
	tahun[2020].date[11][18] = 121818;
	tahun[2020].date[11][19] = 123003;
	tahun[2020].date[11][20] = 124243;
	tahun[2020].date[11][21] = 125822;
	tahun[2020].date[11][22] = 127164;
	tahun[2020].date[11][23] = 128173;
	tahun[2020].date[11][24] = 129188;
	tahun[2020].date[11][25] = 130461;
	tahun[2020].date[11][26] = 131522;
	tahun[2020].date[11][27] = 132961;
	tahun[2020].date[11][28] = 134331;
	tahun[2020].date[11][29] = 135762;
	tahun[2020].date[11][30] = 136861;
	
	//oktober 2020
	tahun[2020].date[10][1] = 75521;
	tahun[2020].date[10][2] = 76619;
	tahun[2020].date[10][3] = 77784;
	tahun[2020].date[10][4] = 79214;
	tahun[2020].date[10][5] = 80036;
	tahun[2020].date[10][6] = 81043;
	tahun[2020].date[10][7] = 82383;
	tahun[2020].date[10][8] = 83392;
	tahun[2020].date[10][9] = 84364;
	tahun[2020].date[10][10] = 85617; 
	tahun[2020].date[10][11] = 87006;
	tahun[2020].date[10][12] = 88174;
	tahun[2020].date[10][13] = 89228;
	tahun[2020].date[10][14] = 90266;
	tahun[2020].date[10][15] = 91337;
	tahun[2020].date[10][16] = 92382;
	tahun[2020].date[10][17] = 93356;
	tahun[2020].date[10][18] = 94327;
	tahun[2020].date[10][19] = 95253;
	tahun[2020].date[10][20] = 96217;
	tahun[2020].date[10][21] = 97217;
	tahun[2020].date[10][22] = 98206;
	tahun[2020].date[10][23] = 99158;
	tahun[2020].date[10][24] = 100220;
	tahun[2020].date[10][25] = 100991;
	tahun[2020].date[10][26] = 101897;
	tahun[2020].date[10][27] = 102678;
	tahun[2020].date[10][28] = 103522;
	tahun[2020].date[10][29] = 104235;
	tahun[2020].date[10][30] = 104847;
	tahun[2020].date[10][31] = 105597;
	
	
	//September
	
	tahun[2020].date[9][1] = 41250;
	tahun[2020].date[9][2] = 42303;
	tahun[2020].date[9][3] = 43709;
	tahun[2020].date[9][4] = 44604;
	tahun[2020].date[9][5] = 45446;
	tahun[2020].date[9][6] = 46691;
	tahun[2020].date[9][7] = 47796;
	tahun[2020].date[9][8] = 48811;
	tahun[2020].date[9][9] = 49837;
	tahun[2020].date[9][10] = 51287;
	tahun[2020].date[9][11] = 52321;
	tahun[2020].date[9][12] = 53761;
	tahun[2020].date[9][13] = 54864;
	tahun[2020].date[9][14] = 55926;
	tahun[2020].date[9][15] = 56953;
	tahun[2020].date[9][16] = 58458;
	tahun[2020].date[9][17] = 59472;
	tahun[2020].date[9][18] = 60875;
	tahun[2020].date[9][19] = 61807;
	tahun[2020].date[9][20] = 62886;
	tahun[2020].date[9][21] = 64196;
	tahun[2020].date[9][22] = 65318;
	tahun[2020].date[9][23] = 66505;
	tahun[2020].date[9][24] = 67638;
	tahun[2020].date[9][25] = 68927;
	tahun[2020].date[9][26] = 70184;
	tahun[2020].date[9][27] = 71370;
	tahun[2020].date[9][28] = 72177;
	tahun[2020].date[9][29] = 73309;
	tahun[2020].date[9][30] = 74368;
	
		//Agustus
	
	tahun[2020].date[8][1] = 21575;
	tahun[2020].date[8][2] = 21954;
	tahun[2020].date[8][3] = 22443;
	tahun[2020].date[8][4] = 22909;
	tahun[2020].date[8][5] = 23266;
	tahun[2020].date[8][6] = 23863;
	tahun[2020].date[8][7] = 24521;
	tahun[2020].date[8][8] = 25242;
	tahun[2020].date[8][9] = 25714;
	tahun[2020].date[8][10] = 26193;
	tahun[2020].date[8][11] = 26664;
	tahun[2020].date[8][12] = 27242;
	tahun[2020].date[8][13] = 27863;
	tahun[2020].date[8][14] = 28438;
	tahun[2020].date[8][15] = 29036;
	tahun[2020].date[8][16] = 29554;
	tahun[2020].date[8][17] = 30092;
	tahun[2020].date[8][18] = 30597;
	tahun[2020].date[8][19] = 31162;
	tahun[2020].date[8][20] = 31757;
	tahun[2020].date[8][21] = 32398;
	tahun[2020].date[8][22] = 32999;
	tahun[2020].date[8][23] = 33636;
	tahun[2020].date[8][24] = 34295;
	tahun[2020].date[8][25] = 34931;
	tahun[2020].date[8][26] = 35642;
	tahun[2020].date[8][27] = 36462;
	tahun[2020].date[8][28] = 37278;
	tahun[2020].date[8][29] = 38166;
	tahun[2020].date[8][30] = 39280;
	tahun[2020].date[8][31] = 40309;

	//juli 2020
	tahun[2020].date[7][1] = 11482;
	tahun[2020].date[7][2] = 11677;
	tahun[2020].date[7][3] = 11824;
	tahun[2020].date[7][4] = 12039;
	tahun[2020].date[7][5] = 12295;
	tahun[2020].date[7][6] = 12526;
	tahun[2020].date[7][7] = 12725;
	tahun[2020].date[7][8] = 13069;
	tahun[2020].date[7][9] = 13359;
	tahun[2020].date[7][10] = 13598;
	tahun[2020].date[7][11] = 13957;
	tahun[2020].date[7][12] = 14361;
	tahun[2020].date[7][13] = 14639;
	tahun[2020].date[7][14] = 14914;
	tahun[2020].date[7][15] = 15173;
	tahun[2020].date[7][16] = 15466;
	tahun[2020].date[7][17] = 15707;
	tahun[2020].date[7][18] = 16038;
	tahun[2020].date[7][19] = 16351;
	tahun[2020].date[7][20] = 16712;
	tahun[2020].date[7][21] = 17153;
	tahun[2020].date[7][22] = 17529;
	tahun[2020].date[7][23] = 17945;
	tahun[2020].date[7][24] = 18230;
	tahun[2020].date[7][25] = 18623;
	tahun[2020].date[7][26] = 19001;
	tahun[2020].date[7][27] = 19473;
	tahun[2020].date[7][28] = 19885;
	tahun[2020].date[7][29] = 20470;
	tahun[2020].date[7][30] = 20769;
	tahun[2020].date[7][31] = 21201;
	
}

void fillGlobalArray(int currYear,int currMonth,int currDay){
	int hari = 3;
	for(int i=1;i<=3;i++){
		if(i>=currDay){ //jika tanggal kurang dari 10 (bakal liat data bulan lalu) -- tahun lom bikin :)
			currMonth--;

			if(currMonth==2){
				if(currYear%4==0){
					currDay+=29;
				}else{
				currDay += 28;	
				}	
			}
			else if(currMonth<7)
			{
				if(currMonth%2 == 1) currDay+=31;
				else currDay+=30;								
			}
			else if(currMonth>8)
			{	
				if(currMonth%2 == 1) currDay+=30;
				else currDay+=31;
			}
			else{
				currDay+=31;
			}
		}

		x[hari] = currDay-i;
		y[hari] = tahun[2020].date[currMonth][currDay-i];
	hari--;	
	}
	
}

void fillRemainingGlobalArray(float X,float Y){
	
	for(int i=1;i<=3;i++){
		xminusX[i] = x[i] - X;
		yminusY[i] = y[i] - Y;
	}
	
}

float getSigmaX(){
	
	float sigmaX=0;
	
	for(int i=1;i<=3;i++){
		sigmaX += (xminusX[i]*xminusX[i]); 
	}
	
	return sigmaX;
}

float getSigmaY(){
	
	float sigmaY=0;
	
	for(int i=1;i<=3;i++){
		sigmaY += (yminusY[i]*yminusY[i]); 
	}
	
	return sigmaY;
}

float getSigmaCross(){
	
	float sigmaCross=0;
	
	for(int i=1;i<=3;i++){
		sigmaCross += (xminusX[i]*yminusY[i]); 
	}
	
	return sigmaCross;
}




