extern int getMoonlightStrength(double prog){
	double phase = getMoonPhase(lyear(),lmonth(),lday());
	return round((increase(prog,0.5/24.0,9.5/24.0,phase,0)+decrease(prog,0.5/24.0,22.5/24.0,phase,0))*255);
}
extern int getSunlightStrength(double prog){
	return round((increase(prog,1.0/24.0,9.5/24.0,0,1)*decrease(prog,0.25/24.0,10/24.0,0,1)+increase(prog,0.25/24.0,21.0/24.0,0,1)*decrease(prog,1/24.0,21.5/24.0,0,1))*255);
}
double increase(double prog, double span, double time, double min, double max){
	//sin^2 from 0 to 0.5pi
	double start = time-span/2;
	double end = time+span/2;
	
	if(prog<start){
		 return min;
	} else if(prog>end){
		return max;
	} else {
		double d = (prog-start)/span;
		return min+(max-min)*pow(sin(d*HALF_PI),2);
	}
}
//berg is maal elkaar dal is optellen.
double decrease(double prog, double span, double time, double min, double max){
	//cos^2 from 0 to 0.5pi
	double start = time-span/2;
	double end = time+span/2;
	
	if(prog<start){
		 return max;
	} else if(prog>end){
		return min;
	} else {
		double d = (prog-start)/span;
		return min+(max-min)*pow(cos(d*HALF_PI),2);
	}
}
// Adapted from Stephen R. Schmitt's Lunar phase computation program.
// Originally written for the Zeno programming language.
// http://home.att.net/~srschmitt/lunarphasecalc.html
double normalize(double v) {           // normalize moon calculation between 0-1 (per unage)
    v = v - floor(v);
    if (v < 0)
        v = v + 1;
    v = fabs(v-0.5)/0.5;
    return v;
}
extern double getMoonPhase(int Y, int M, int D) {
  double  IP;  
  long YY, MM, K1, K2, K3, JD;
  YY = Y - floor((12 - M) / 10);
  MM = M + 9;
  if(MM >= 12)
    MM = MM - 12;
  
  K1 = floor(365.25 * (YY + 4712));
  K2 = floor(30.6 * MM + 0.5);
  K3 = floor(floor((YY / 100) + 49) * 0.75) - 38;

  JD = K1 + K2 + D + 59;
  if(JD > 2299160)
    JD = JD -K3;
  
  IP = normalize((JD - 2451550.1) / 29.530588853);  
  return IP;    
}

