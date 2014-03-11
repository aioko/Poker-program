/*Program that generates hands and checks for poker hands*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*generate card type*/
struct card{
	char suit;
	int face;
};
typedef struct card Card;
/*lookups*/
char *faces[] = {"", "", "deuce", "three", "four", "five", "six",
	"seven", "eight", "nine", "ten", "jack", "queen", "king", "ace"};
char *suit(char s) {
	if (s == 'C') return "Clubs";
	if (s == 'D') return "Diamonds";
	if (s == 'H') return "Hearts";
	return "Spades";
}
/*function prototypes*/
void printCard(Card c);
void printDeck(struct card x[], int n);
void shuffle(Card x[]);
void swap(Card *a, Card *b);
/*----------------------------------------*/
int main(void){
	Card deck[52];
	Card hand[5];
	int i;
	/*generate deck of 52 cards*/
	for(i=0;i<52;i++){
		if(i<13){
			deck[i].face = i+2;
			deck[i].suit = 'S';	
		}
		if(i>=13 && i<26){
			deck[i].face = (i-13)+2;
			deck[i].suit = 'D';
		}
		if(i>=26 && i<39){
			deck[i].face = (i-26)+2;
			deck[i].suit = 'H';
		}
		if(i>=39 && i<52){
			deck[i].face = (i-39)+2;
			deck[i].suit = 'C';
		}
	}
	/*generate random number based off of system time*/
	shuffle(deck);
	/*generate own hand*/
	for(i=0;i<5;i++){
		hand[i].face = deck[i].face;
		hand[i].suit = deck[i].suit;
	}

	printDeck(hand,5);
	printf("----------------\n");
	/*create hand values*/
	playHand(hand);
	return 0;
}

/*shuffle functions and print functions and utility functions*/
void printCard(Card c){
	printf("%s of %s\n", faces[c.face], suit(c.suit));
}

void shuffle(Card x[]){
	srand(time(NULL));
	int r_index;
	
	int i;
	for(i=0;i<52;i++){
		r_index = rand() % (52-i);
		swap(&x[r_index],&x[51-i]);
	}
}

void swap(Card *a, Card *b){
	Card temp;
	temp = *a;
	*a = *b;
	*b = temp; 
}

int maxCard(Card x[]){
	int i, max;
	max = x[0].face;
	for(i=1;i<5;i++){
		if(x[i].face > max)
			max=x[i].face;
	}
	return max;
}

void swapInt(int *a, int *b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void sort(Card x[]){
	int i,m,j;
	int temp;
	for(i=0;i<4;i++){
		m=i;
		for(j=i+1;j<5;j++){
			if(x[m].face>x[j].face)
				m=j;
		}
		temp = x[m].face;
		x[m].face = x[i].face;
		x[i].face = temp;
	}
	return;
}

void printDeck(Card x[], int n){
	int i;
	for(i=0;i<n;i++)
		printCard(x[i]);
}

void playHand(Card x[]){
	if(isFullHouse(x))
		printf("You have a full House!\n");
	else{
		if(hasTwoPair(x))
			printf("You have two pairs!\n");
		else{
			if(hasPair(x))
				printf("You have a pair!\n");
		}	
		if(hasThree(x))
			printf("You have three of a kind!\n");
	}
	if(hasFour(x))
		printf("You have four of a kind!\n");
	if(isStraightFlush(x))
		printf("You have a straight flush!\n");
	else{
	if(isFlush(x))
		printf("You have a flush!\n");
	if(isStraight(x))
		printf("You have a straight!\n");
	}
	return;
}

/*HAND VALUE FUNCTIONS*/
int hasPair(Card x[]){
	sort(x);
	int i, check=0;
	if(hasFour(x))
		return 0;
	else{
		for(i=0;i<3;i++){
			if((x[i].face == x[i+1].face) && (x[i].face != x[i+2].face)){
				if(x[i].face != x[i-1].face)
					check+= 1;
				break;
			}
		}
		if(x[3].face == x[4].face && x[3].face != x[2].face){
			check+= 1;
		}
	}

	if(check == 1){
		return 1;
	}
	return 0;
}

int hasTwoPair(Card x[]){
	sort(x);
	int i, check=0;
	if(hasFour(x))
		return 0;
	else{
		for(i=0;i<3;i++){
			if((x[i].face == x[i+1].face) && (x[i].face != x[i+2].face)){
				if(x[i].face != x[i-1].face)
					check+= 1;
			}
		}
		if(x[3].face == x[4].face && x[3].face != x[2].face){
			check+= 1;
		}
	}

	if(check == 2){
		return 1;
	}
	return 0;
}

int hasThree(Card x[]){
	sort(x);
	int i, count=0;
	if(hasFour(x)!=1){
		for(i=0;i<3;i++){
			if(x[i].face == x[i+1].face && x[i].face == x[i+2].face)
			{
				return 1;
				break;
			}
		}
	}
	return 0;	
}

int hasFour(Card x[]){
	sort(x);
	int i;
	for(i=0;i<2;i++){
		if(x[i].face==x[i+1].face && x[i].face==x[i+2].face && x[i].face==x[i+3].face){
			return 1;
			break;
		}
	}
	return 0;
}

int isFullHouse(Card x[]){
	if(hasPair(x) && hasThree(x))
		return 1;
	return 0;
}

int isFlush(Card x[]){
	int i;
	int s_c = 0, c_c = 0, h_c = 0, d_c =0;
	for(i=0;i<5;i++){
		if(x[i].suit == 'S')
			s_c+=1;
		if(x[i].suit == 'C')
			c_c+=1;
		if(x[i].suit == 'D')
			d_c+=1;
		if(x[i].suit == 'H')
			h_c+=1;
	}	
	if(s_c==5 || c_c==5 || d_c==5 || h_c==5){
		return 1;
	}
	return 0;
}

int isStraight(Card x[]){
	int i;
	if(x[0].face == x[1].face-1 && x[0].face == x[2].face-2 && x[0].face == x[3].face-3
			&& x[0].face == x[4].face-4){
		return 1;
	}
	return 0;
}

int isStraightFlush(Card x[]){
	if(isStraight(x) && isFlush(x)){
		return 1;
	}
	return 0;
}
