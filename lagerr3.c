#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

//*********************************************  

struct kopia {
  int type; // NOTHING = 0, ADD = 1, REMOVE = 2, EDIT = 3
  char namn[50];
  int pris;
  char beskrivning[50];
  char hyl[5];
  int antal;
  int k_index;
}kopia[2];

struct vara {
  char namn[50];
  int pris;
  char beskrivning[50];
  char hyl[5];
  int antal;
}vara[100];
  
//*********************************************  

int i = 1;
int rtv = 0;
int sida = 0;

//*********************************************  

void add_vara();
void main_choice();
void vara_print();
void vara_print_choice();
void vara_print_visa();
void hitta_vara();
void avsluta();
void vara_redigera(int);
void add_vara_pris();
void add_vara_pris_index();
void ta_bort(int);
void angra();

int hylla_check(char[5]);
int hylla_ledig(char[5]);
int int_check();

//*********************************************  

void angra() {
  int action = kopia[0].type;

  if(action == 0) {
    printf("Kan inte ångra om inget har gjorts/Du har redan ångrat 1 steg.\n");
    main_choice();
  }

  if(action == 1) {
    kopia[0].type = 0;
    ta_bort(i-1);
  }

  if(action == 2) {
    kopia[0].type = 0;
    
    strncpy(vara[i].namn, kopia[0].namn, 50);
    vara[i].pris = kopia[0].pris;
    strncpy(vara[i].beskrivning, kopia[0].beskrivning, 50);
    strncpy(vara[i].hyl, kopia[0].hyl, 5);
    vara[i].antal = kopia[0].antal;

    i++; //Går vidare till nästa element i vara-listan

    main_choice();
  }

  if(action == 3) {
    kopia[0].type = 0;
    
    int index = kopia[0].k_index;

    strncpy(vara[index].namn, kopia[0].namn, 50);
    vara[index].pris = kopia[0].pris;
    strncpy(vara[index].beskrivning, kopia[0].beskrivning, 50);
    strncpy(vara[index].hyl, kopia[0].hyl, 5);
    vara[index].antal = kopia[0].antal;

    main_choice();
  }

}

void ta_bort(int e) {

  kopia[0].type = 2;

  strncpy(kopia[0].namn, vara[e].namn, 50);
  kopia[0].pris = vara[e].pris;
  strncpy(kopia[0].beskrivning, vara[e].beskrivning, 50);
  strncpy(kopia[0].hyl, vara[e].hyl, 5);
  kopia[0].antal = vara[e].antal;

  strncpy(vara[e].namn, "", 50);
  vara[e].pris = 0;
  strncpy(vara[e].beskrivning, "", 50);
  strncpy(vara[e].hyl, "", 5);
  vara[e].antal = 0;

  
  while(strcmp(vara[e+1].namn, vara[0].namn) != 0) {
    vara[e] = vara[e+1];
    e++;
  }

  if(strcmp(vara[e+1].namn, vara[0].namn) == 0) {
    strncpy(vara[e].namn, "", 50);
    vara[e].pris = 0;
    strncpy(vara[e].beskrivning, "", 50);
    strncpy(vara[e].hyl, "", 5);
    vara[e].antal = 0;
  }

  i--;
  main_choice();
}

int hylla_ledig(char hylla[5]) {

  int i = 1;
  int status = 1;

  while(strcmp(vara[i].hyl, vara[0].hyl) != 0) {
    if(strcmp(hylla, vara[i].hyl) == 0) {
      printf("\nHyllan är upptagen, försök med en ny.\n"
	     ":");
      status = 0;
      break;
    };
    i++;
  };
  return status;
}

int hylla_check(char hylla[5]) {
	int state = 0;
	
	int e_1 = hylla[0]; //Första elementet, kollas om bokstav & om det är stor bokstav
	int e_2 = hylla[1]; //Andra elementet, kollas om det är en siffra
	int e_3 = hylla[2]; //Sista elementet, kollas om det är en siffra
	
	if(e_1 < 91 && isalpha(e_1) && isdigit(e_2) && isdigit(e_3)) {
		state = 1;
	}
	
	else {
		printf("\nHyllan finns inte, första tecknet ska vara en stor bokstav och de två efter nummer.\n"
			"Exempel : A23\n"
			"Var god försök igen    : ");
	}
	
	return state;
};

void vara_redigera(int index) {

  kopia[0].type = 3;

  strncpy(kopia[0].namn, vara[index].namn, 50);
  kopia[0].pris = vara[index].pris;
  strncpy(kopia[0].beskrivning, vara[index].beskrivning, 50);
  strncpy(kopia[0].hyl, vara[index].hyl, 5);
  kopia[0].antal = vara[index].antal;
  kopia[0].k_index = index;
	
	unsigned char opt;
	printf("\n[N]amn\n"
		"[B]eskrivning\n"
		"[P]ris\n"
		"[L]agerhylla\n"
		"An[t]al\n");
	
	printf("\nVälj rad eller [a]vbryt: ");
	
	opt = getchar();
	while(getchar() != '\n');
	
	switch(toupper(opt)) {
	case 'N':
		printf("\nNuvarandra namn:	");
		printf("%s\n", vara[index].namn);
		
		printf("\nNytt namn: ");
		scanf("%s",vara[index].namn);
		while(getchar()!='\n');
		break;
	case 'B':
		printf("\nNuvarandra beskrivning:	");
		printf("%s\n", vara[index].beskrivning);
		
		printf("\nNytt beskrivning: ");
		fgets(vara[index].beskrivning, 50, stdin );
		break;
	case 'P':
	  printf("\nNuvarande pris:     ");
	  printf("%d", vara[index].pris);

	  printf("\nNytt pris:    ");
	  int pris_ny = int_check();
	  vara[index].pris = pris_ny;
	  break;
	case 'L':
	  printf("\nNuvarande lagerhylla:     ");
	  printf("%s", vara[index].hyl);

	  printf("\nNy lagerhylla:     ");
	  char hyl_ny[5];
	  int hyl_state = 0;
	  int hyl_led = 0;

	  while(hyl_state == 0 || hyl_led == 0) {
		fgets(hyl_ny, 5, stdin);
		*strchr(hyl_ny, '\n') = '\0';
		hyl_state = hylla_check(hyl_ny);
		hyl_led = hylla_ledig(hyl_ny);
	  }
	  strncpy(vara[index].hyl, hyl_ny, 5);
	  
	  break;
	case 'T':
	  printf("\nNuvarande antal:     ");
	  printf("%d", vara[index].antal);

	  printf("\nNytt antal:    ");
	  int antal_ny = int_check();
	  vara[index].antal = antal_ny;
	  break;
	  
		
	}
	
}

void avsluta(){
  
  printf("\nVill du avsluta programet y/n?");
  unsigned char option;
  option = getchar();
  while( getchar() !='\n');

 
  switch(toupper(option)){
  case 'Y':
    exit(0);
    break;
  case 'N':
    main_choice();
    break;
  default:
    printf("Felaktig inmatning, försök igen.\n");
    avsluta();
  }
}

void vara_print_visa() {
	printf("Välj en vara genom index\n");

	char choice;
	choice = getchar();
	while(getchar() != '\n');
	int ichoice;
	ichoice = choice - '0';
	ichoice = ichoice + (20*sida);
	sida = 0;

	printf("Namn: ");
	printf("%s\n", vara[ichoice].namn);

	printf("Pris: ");
	printf("%d\n", vara[ichoice].pris);
		
	printf("Beskrivning: ");
	printf("%s\n", vara[ichoice].beskrivning);
	
	printf("Hylla: ");
	printf("%s\n", vara[ichoice].hyl);
	
	printf("Antal: ");
	printf("%d\n", vara[ichoice].antal);
			  
	printf("=================================\n");

	if(rtv==1) {
	  vara_redigera(ichoice);
	}

	if(rtv==2) {
	  ta_bort(ichoice);
	}

  main_choice();
}  

void vara_print_choice() {

  char nextChoice;

  printf("\n=================================\n");
  printf("Nästa sida= 'n'\n"
		"Eller välj en vara genom index.\n"
		"[A]vbryt.\n");
  printf("=================================\n");

  int loop = 1;

  while(loop == 1) {
    nextChoice = getchar();
    while(getchar() != '\n');
	
    if(nextChoice == 'a' || nextChoice == 'A') {
		main_choice();
    }

    if(nextChoice == 'n' || nextChoice == 'N') {
      sida++;
      loop = 0;
    }

    else {
      vara_print_visa();
    } 
  }
}

void vara_print() {
  int e = 1;
  int index = 1;
  int first = 1;

  printf("\n=================================\n");
  while(1==1) {
    if(strcmp(vara[e].namn, vara[0].namn) == 0) {
      
      if(first == 1) {
	printf("Finns inga varor att visa.\n");
	printf("=================================\n");
	main_choice();
      }
      printf("=================================\n");
      vara_print_visa();
    }

    if(index==21) {
      index = 1;
      vara_print_choice();
    }
    
    else {
      printf("%d", index);
      printf(").   ");
      printf("%s\n", vara[e].namn);
      e++;
      index++;
    }
    
    first = 0;
  }
}

void main_choice() {

 printf("Välkommen till lagerhantering 1.0\n"
	 "=================================\n\n"
	 "[L]ägga till en vara\n"
	 "[T]a bort en vara\n"
	 "[R]redigera en vara\n"
	 "Ån[g]ra senaste ändringen\n"
	 "Lista [h]ela varukatalogen\n"
	 "[A]vsluta\n\n"
	 "Vad vill du göra idag? ");

  unsigned char option;
  option = getchar();
  while(getchar() != '\n');

  switch(toupper(option)){
  case 'L':
    printf("Lägga till");
    add_vara();
    break;
  case 'T':
    printf("Ta bort");
    rtv = 2;
    vara_print();
    break;
  case 'R':
    printf("Redigera");
    rtv = 1;
	vara_print();
    break;
  case 'G':
    printf("Ångra\n");
    angra();
    break;
  case 'H':
	printf("Visa");
	rtv = 0;
    vara_print();
    break;
  case 'A':
    printf("Avsluta");
    avsluta();
    break;
  default:
    printf("Felaktig inmatning, försök igen.\n");
    main_choice();
  }
}



int int_check() {
	int num;
	char term;

	while(scanf(" %d%c", &num, &term) != 2 || term != '\n') {
	  printf("Felaktig inmatning, inte en sifferkombination.\n"
			"Var god försök igen    : ");
	  while(getchar()!='\n');
	}
	return num;
}


void add_vara() {
  
  char opt[2];
  char nam[50];
  int pri;
  char bes[50];
  char hyl[5];
  int antal;
  int hyl_state = 0;
  int hyl_ledig = 0;  

  kopia[0].type = 1;

    printf("\nSkriv varans namn    : ");
    scanf("%s", nam);
    // scanf("%s",vara[i].namn);
	  
        
    printf("\nSkriv varans pris    : ");
    pri = int_check();
	
    printf("\nBeskrvning av varan   : ");
    fgets(bes, 50, stdin);
    *strchr(bes, '\n') = '\0';
    //fgets(vara[i].beskrivning, 50, stdin );

	printf("\nSkriv in lagerhylla    : ");
	while(hyl_state == 0 || hyl_ledig == 0) {
		fgets(hyl, 5, stdin);
		*strchr(hyl, '\n') = '\0';
		hyl_state = hylla_check(hyl);
		hyl_ledig = hylla_ledig(hyl);
	}
	//*strchr(hyl, '\n') = '\0';

    printf("\nSkriv in antal varor   : ");
    antal = int_check();

    printf("\nVad vill du göra (S)para, (A)vbryta, (R)edigera   : ");
    scanf("%s", opt);
    while(getchar() != '\n');
    
    if(strcmp(opt,"s") == 0 || strcmp(opt,"S") == 0 || strcmp(opt,"r") == 0 || strcmp(opt,"R") == 0){
      strncpy(vara[i].namn, nam, 50);
      vara[i].pris = pri;
      strncpy(vara[i].beskrivning, bes, 50);
      strncpy(vara[i].hyl, hyl, 5);
      vara[i].antal = antal;

    if(strcmp(opt,"r") == 0 || strcmp(opt,"R") == 0) {
	vara_redigera(i);
	  }
    }
   
    if(strcmp(opt,"a") == 0 || strcmp(opt,"A") == 0){
      main_choice();
    }


    i = i + 1;
    main_choice();
      
}

int main() {

  struct vara vara[100];
  strcpy(vara[0].namn, "");
  kopia[0].type = 0;

  main_choice();

  return 0;
}
