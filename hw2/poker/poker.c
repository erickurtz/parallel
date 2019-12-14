#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h> 


typedef enum suit_s {DIAMONDS, CLUBS, HEARTS, SPADES} Suit;

typedef struct card_s{
  int rank;
  Suit suit;
} * Card;


typedef struct hand_s{

  Card *cards;
} * Hand; 

void reroll_card(Card card){
  int rank = rand()%13 + 1;
  int suit = rand()%4;
  card->rank = rank;
  card->suit = suit;  
}

Card create_random_card(){
  Card result = (Card)malloc(sizeof(Card));

  reroll_card(result);
  reroll_card(result); 
  return result; 

}

void print_card(Card card){

  switch(card->rank){
  case 13 :
    printf("King");
    break;
  case 12 :
    printf("Queen");
    break;
  case 11 :
    printf("Jack");
    break;
  case 1 :
    printf("Ace");
    break;
  default:
    printf("%d", card->rank);
    break;
  }
  printf(" of ");
  switch(card->suit){
  case DIAMONDS:
    printf("Diamonds");
    break;
  case CLUBS:
    printf("Clubs");
    break;
  case HEARTS:
    printf("Hearts");
    break;
  case SPADES:
    printf("Spades");
    break;
  default:
    printf("Error!");
    break; 
  }
  printf("\n"); 
}

_Bool card_equal (Card a_card, Card b_card){
  return a_card->rank == b_card->rank && a_card->suit == b_card->suit; 
}

void destroy_card(Card card){
  free(card);
}

Hand generate_random_hand(){

  Hand result = (Hand)malloc(sizeof(Hand));
  result->cards = (Card*)malloc(5*sizeof(Card));
  for (int i = 0; i<5; i++){
    result->cards[i] = create_random_card();
    int j = 0; 
    for(; j<i; j++){
      if(card_equal(result->cards[j], result->cards[i])){
	reroll_card(result->cards[i]);
	j=-1; //restart loop. 
	}
    }
  }

  
  return result; 

} 


void print_hand(Hand hand){

  if(hand->cards == NULL){
    printf("Hand is empty\n");
    return; 
  }
  
  for(int i = 0; i<5; i++){
    print_card(hand->cards[i]);
  }

}

void destroy_hand(Hand hand){
  for(int i = 0; i<5; i++){
    destroy_card(hand->cards[i]);
  } 
  free(hand->cards);
  free(hand); 
}

void sort_hand_by_rank(Hand h){
  
  for(int i = 0; i<5; i++){
    int min_index = i;
    for(int j = i+1; j<5; j++){
      Card other = h->cards[j];
      if(other->rank < h->cards[min_index]->rank){
	min_index = j; 
      }
    }
    Card temp = h->cards[i];
    h->cards[i] = h->cards[min_index];
    h->cards[min_index] = temp; 
 
  }
} 

_Bool is_flush(Hand hand){
  sort_hand_by_rank(hand);

  for(int i =0; i<4; i++){
    if(hand->cards[i+1]->suit != hand->cards[i]->suit) return false; 
  } 

  //handles case where Ace counts as highest card. 
  if(hand->cards[4]->rank == 13){
    return(hand->cards[0]->rank==1 && hand->cards[1]->rank == 10
	   && hand->cards[2]->rank == 11 && hand->cards[3]->rank == 12); 
  }

  for(int i = 0; i<4; i++){
    if(hand->cards[i+1]->rank - hand->cards[i]->rank != 1) return false; 

  }

  return true; 
  
}


int main(int argc, char* argv[]){

  srand(time(NULL));
  int reps = atoi(argv[1]);
  int num_flush = 0;
  for(int i = 0; i<reps; i++){
    Hand h = generate_random_hand(); 
    if(is_flush(h)){
      printf("Flush!"); 
      num_flush++;
    }
    destroy_hand(h);
  }

  double ratio = (double)num_flush/reps;

  printf("%d straight flushes out of %d hands.\n", num_flush, reps); 
  printf("Ratio: %lf\n", ratio); 
}
