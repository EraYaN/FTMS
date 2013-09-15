#include <U8glib.h>
#include <string.h>
//U8GLIB_ST7920_128X64 u8g(3, 9, 8, U8G_PIN_NONE);
// SPI Com: SCK = en = 3, MOSI = rw = 9, CS = di = 8
U8GLIB_ST7920_128X64 u8g(SCREEN_SCK, SCREEN_MOSI, SCREEN_SS, U8G_PIN_NONE);
// HW SPI: http://arduino.cc/en/Reference/SPI MOSI = ICSP-4, MISO = ICSP-1, SCK = ICSP-3, SS = D53 = CS
//U8GLIB_ST7920_128X64 u8g(d0, d1, d2, d3, d4, d5, d6, d7, en, cs1, cs2, di, rw [, reset])
//8Bit
const u8g_fntpgm_uint8_t *font_l = u8g_font_helvR10r;
const u8g_fntpgm_uint8_t *font_m = u8g_font_helvR08;
const u8g_fntpgm_uint8_t *font_s = u8g_font_04b_03r;
const u8g_fntpgm_uint8_t *font_xs = u8g_font_u8glib_4r;

int K = 0;
int lastbytevalue=0;
void fr(const char* text){
	Serial.print("\t---- ");
	int tmp = freeMemory();
	Serial.print(tmp-lastbytevalue);
	lastbytevalue=tmp;
	Serial.print(" mutation, ");
	Serial.print(lastbytevalue);
	Serial.print(" bytes free RAM ->");
	Serial.println(text);
	Serial.flush();

}
void initScreen(){


}
char* substr(const char* str, int start, int number){
	int n = min(number,strlen(str)-start);
	char* to = (char*) safeMalloc(n+1);
	strncpy(to,str+start,n);
	to[n]='\0';
	return to;
}
unsigned int getStrWidth(const char *s){
	return u8g.getStrWidth(s);
}
int unsigned splitInLines(const char* msg, char* lines[], size_t maxlines, bool &leftover, unsigned int (*gPW)(const char*)){
	int screenwidth = u8g.getWidth();
	int width = gPW(msg);
	int unsigned numlines = 0;
	//Serial.println("splitter");
	bool done = false;
	leftover = false;
	int unsigned a = 0, b = 0;
	int I = 0;
	if(width>=screenwidth){
		//Serial.println("splitter-if");
		//Serial.flush();
		char* workstr;
		//Serial.println(strlen(msg)+1);
		//Serial.flush();
		//fr("malloc");
		workstr = (char*)safeMalloc(strlen(msg)+1);
		//Serial.println("splitter-strcpy-1");
		strcpy(workstr, msg);
		//Serial.println("splitter-if-2");
		while(!done&&I<100000){
			//Serial.println("splitter-while-line");
			while(width>=screenwidth){
				//Serial.println("splitter-while-word");
				a=0;
				char* tmp = workstr;
				char* space = strrchr(workstr,' ');
				//Serial.println("splitter-while-word-2");
				if(!space) { /*Serial.println("splitter-while-word-error");*/ done = true; leftover = true; break;}
				a = (int)space-(int)workstr;
				//Serial.println("splitter-while-word-3");
				workstr = substr(tmp,0,a);       
				safeFree( tmp); 
				//Serial.println("splitter-while-word-4");
				width = gPW(workstr);
				if(a>strlen(msg)||I>10000) { /*Serial.println("splitter-while-word-error-2");*/ break; };  
				I++;  

			}
			b += a;
			if(numlines>0) b++;
			lines[numlines] = (char*)safeMalloc(strlen(workstr)+1);
			strcpy(lines[numlines],workstr);
			numlines++;
			safeFree(workstr);
			workstr = substr(msg,b+1,strlen(msg)-b-1);
			width = gPW(workstr);
			if(width<=screenwidth){
				lines[numlines] = (char*)safeMalloc(strlen(workstr)+1);
				strcpy(lines[numlines],workstr);
				numlines++;
				done = true;
				safeFree(workstr);
			}
			if(numlines>=maxlines){
				leftover = true;
				break;
			}
		}
	} 
	else {
		//Serial.println("splitter-if-short");
		lines[numlines] = (char*)safeMalloc(strlen(msg)+1);		
		strcpy(lines[numlines],msg);
		numlines++;
	}
	return numlines;
}
void draw(){
	char* buff = (char*)safeMalloc(100);
	u8g.setColorIndex(1);	
	u8g.setFont(font_s);
	time_t t = lnow();	
	snprintf(buff,100,"%04d-%02d-%02d",year(t),month(t),day(t));
	u8g.drawStr( u8g.getWidth()-u8g.getStrPixelWidth(buff)-1,7, buff);
	snprintf(buff,100,"%02d:%02d",hour(t),minute(t));
	u8g.drawStr( u8g.getWidth()-u8g.getStrPixelWidth(buff)-1,14, buff);
	u8g.setFont(font_m);
	snprintf(buff,100,"W-PH: %0.2lf",drctr.s_pHProbe.getpH());
	u8g.drawStr( 1,10, buff);
	snprintf(buff,100,"W-T: %0.1lf %cC",drctr.s_DS18B20.getTemperature(),'\xb0');
	u8g.drawStr( 1,20, buff);
	snprintf(buff,100,"K-T: %0.lf %cC",drctr.s_DHT11.getTemperature(),'\xb0');
	u8g.drawStr( 1,30, buff);
	snprintf(buff,100,"K-H: %0.lf %%",drctr.s_DHT11.getHumidity());
	u8g.drawStr( 1,40, buff);	
	u8g.setFont(font_xs);	
	snprintf(buff,100,"fM: %0.1f%%",(double)freeMemory()/(8*1024)*100);	
	u8g.drawStr( u8g.getWidth()-u8g.getStrPixelWidth(buff)-1,u8g.getHeight()-1, buff);	
	safeFree(buff);
	//seconds indicator
	u8g.drawLine(0, 0, second(t)/60.0*u8g.getWidth(), 0);
}
int drawStatusMessage(const char* msg){
	u8g.setColorIndex(1);	
	u8g.setFont(font_l);	
	const int m = (u8g.getHeight())/u8g.getFontLineSpacing();
	//Serial.println(++K);
	char *output[m];
	int lines;
	int width;
	int offsetX;
	int offsetY;
	bool leftover = false;   
	//Serial.println("draw-init");
	lines = splitInLines(msg,output,m,leftover,getStrWidth);
	u8g.setColorIndex(1);	
	u8g.setFont(font_l);
	int textHeigth = lines*u8g.getFontLineSpacing();
	//Serial.println("draw-drawing-for");
	for(int j = 0; j<lines; j++){
		width = getStrWidth(output[j]);
		offsetX = max(0,((int)u8g.getWidth() - width)/2);
		offsetY = max(0,(((int)(u8g.getHeight())-textHeigth)/2))+u8g.getFontLineSpacing()*(j+1);
		u8g.drawStr( offsetX,offsetY, output[j]);
		safeFree(output[j]);
	}
}
void frameStatusMessage(const char* msg){	
	//Serial.println("frame");
	u8g.firstPage();
	do{
		//Serial.println("next-page");
		drawStatusMessage(msg);
	} while(u8g.nextPage());
}
void frame(){
	u8g.firstPage();
	do{
		draw();
	} while(u8g.nextPage());
}
