/*****************************************************
								Desafio#1 - Platzi
	Semáforo para dos Avenidas (Principal y Secundaria)
	ambas tienen una luz azul para indicar el giro a la
	izquierda y un pulsador peatonal para cambiar el 
	estado de la luz verde y darle paso a los peatones.

	Configuración:
		Entradas: botones peatonales {13(P),2(S)} 
		Salidas: 
			luces verde, amarilla, roja y azul 
						{11,10,9,8}Princial ; {7,6,5,4}Secundaria

	Autor: Pablo Cardozo

*****************************************************/
// Avenida Principal
const int vp = 11;
const int ap = 10;
const int rp = 9;
const int zp = 8;
const int butP = 13;	//Pulsador Peatonal
const int semP[4] = {vp, ap, rp, zp};	// arreglo para semáforo Principal
// Avenida Secundaria
const int vs = 7;
const int as = 6;
const int rs = 5;
const int zs = 4;
const int butS = 2;	//Pulsador Peatonal
const int semS[4] = {vs, as, rs, zs}; // arreglo para semáforo Secundario
// Tiempos para cada luz en milisegundos (tr = tz)
int ta = 2000;
int tv = 6000;
int tz = 3000;
// Variables Globales
unsigned long tiempoActual;
int tiempo;
int estadoSem;	// el semáforo tiene 6 estados
bool flagButton = false;


void setup()
{
	// Configuración de Salidas para los semáforos
	for(int i=0; i<4; i++){
		pinMode(semP[i], OUTPUT);    
		pinMode(semS[i], OUTPUT);    
	}
	// Configuración de Entradas para los pulsadores
	pinMode(butP, INPUT_PULLUP);
	pinMode(butS, INPUT_PULLUP);

	iniciar();
}

void loop()
{
	if((millis() - tiempoActual) > tiempo) {
		cambio();
		tiempoActual = millis();
	}
	if((digitalRead(butP) == LOW) || (digitalRead(butS) == LOW)) {		
		delay(200);
		//esperamos hasta que los botones no esten pulsados
		while((digitalRead(butP) == LOW) && (digitalRead(butS) == LOW));		
		flagButton = true;
		estadoSem--;	// el estado actual apunta al siguiente
		if(estadoSem <= 0)	estadoSem = 6;
		if((estadoSem == 1) || (estadoSem == 4))	estadoSem++, cambio();
		else flagButton = false;
		tiempoActual = millis();		
	}
}

void iniciar() {	
	estadoSem = 1;
	cambio();
}

void cambio() {
	for(int i=0; i<4; i++) {
		digitalWrite(semP[i], LOW);    
		digitalWrite(semS[i], LOW);    
	}
	switch (estadoSem) {
	    case 1:
	      digitalWrite(vp, HIGH);
	      digitalWrite(rs, HIGH);
	      tiempo = tv;
	      break;
	    case 2:
	      digitalWrite(ap, HIGH);
	      digitalWrite(rs, HIGH);
	      tiempo = ta;
	      break;
	    case 3:
	      digitalWrite(rp, HIGH);
	      digitalWrite(zp, HIGH);
	      digitalWrite(rs, HIGH);
	      tiempo = tz;
	      break;
	    case 4:
	      digitalWrite(rp, HIGH);
	      digitalWrite(vs, HIGH);
	      tiempo = tv;
	      break;
	    case 5:
	      digitalWrite(rp, HIGH);
	      digitalWrite(as, HIGH);
	      tiempo = ta;
	      break;
	    case 6:
	      digitalWrite(rp, HIGH);
	      digitalWrite(rs, HIGH);
	      digitalWrite(zs, HIGH);
	      tiempo = tz;
	      break;
	    default:
	      break;
	}
	if(flagButton)	estadoSem += 2, flagButton = false;
	else estadoSem++;
	if(estadoSem > 6)	estadoSem = 1;
}
