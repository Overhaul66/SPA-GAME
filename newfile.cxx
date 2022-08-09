#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

enum Suit {SPADES , DIAMONDS, CLUBS, HEARTS};

const unsigned int JACK = 11, QUEEN = 12, KING = 13, ACE = 14;

class Card {
  private:
     unsigned int number;
     Suit suit;
     
  public:
    
     Card(unsigned int n, Suit s) : number(n), suit(s) {}
     
     Card () {}
     
     void showCard() const;
     
     Suit getSuit() const;
     
     void setCard(unsigned int n, Suit s);
     
     bool operator > (const Card &c) const;  
     
     bool operator == (const Card &c) const;
     
     bool isEqual (const Card &c) const;
      
};

void Card:: showCard() const {
   if(number >= 5 && number <= 10)
         std:: cout << number ;
       
   else
      switch (number) {
      case JACK: std:: cout << 'J'; break;
      case QUEEN: std:: cout << 'Q'; break;
      case KING: std:: cout << 'K'; break;
      case ACE: std:: cout << 'A'; break;        
     }
        
   switch (suit) {
   case SPADES: std:: cout << "♠ "; break;
   case DIAMONDS: std:: cout << "♦ "; break;
   case HEARTS: std:: cout << "♥ "; break;
   case CLUBS: std:: cout << "♣ "; break;
     }
}


bool Card:: operator > (const Card &c) const {
    if(suit == c.suit) {
     return  (number > c.number) ? true: false;
    }
    
    return false;
}  
    
Suit Card:: getSuit() const {
  return suit;
}

void Card:: setCard(unsigned int n, Suit s) {
    number = n;
    suit = s;
}

bool Card:: operator == ( const Card &c) const {
    return (suit == c.suit) ? true : false;
}

bool Card:: isEqual(const Card &c) const {
    return (number == c.number && suit == c.suit) ? true : false;
}

void showDeck(Card []); 
void shuffleCards(Card []);
void setCards(Card []);
void sortCards(std:: vector<Card> &);
//if is Cpu turn after player plays
int play(Card &, std:: vector<Card> & );

//if cpu wins
int play(std:: vector<Card> &);

//check if player has a similar card suit

bool haveSimilarSuitCard(const Card &card , std:: vector<Card> &cards) {
  for(auto c : cards) {
       if(card == c ) { 
            return true;
        }
     }
     
     return false;
}

void showPlayerCards(std:: vector<Card> & cards) {
  for(auto c : cards)
      c.showCard();
  std:: cout << '\n';
}
    
    
int main() {

///////////////////////////////////////////
    Card deck[40]; 
    
    setCards(deck);
    
   // showDeck(deck);
///////////////////////////////////////////
    //std:: cout << "\nShuffled Cards\n\n";
    shuffleCards(deck);
    
   // showDeck(deck);

///////////////////////////////////////////
/* Share cards */
    std:: vector<Card> player1 (std:: begin(deck), std:: begin(deck) + 5);
    /*first 5 cards go to player 1*/
    std:: vector<Card> player2 (std:: begin(deck)+5, std:: begin(deck) + 10);
    /*second 5 cards go to player 2*/
    
   std:: cout << "\n";
  // std:: cout << "Player 1 cards : ";
 //  showPlayerCards(player1);
  // std:: cout << "Player 2 cards : ";
   //showPlayerCards(player2);
   
   std:: cout << "S P A\n";
 
 std:: cout << "\n----------------------------------------------------\n";
   
     std:: cout << "The game is simple...\nEach player is dealt with 5 cards\nthe player who presents the card with higher suit\nand already leading in the last round wins\nIt doesn't matter if you are winning the last round is all that matters....\nAlso if a player plays a card you have to play\n a card with similar suit otherwise 'Way3 Ogba!!!'\n in my local language means you have violated a crucial rule\n but don''t worry the system does not allow you to make such mistakes...\n";
     
     std:: cout << "------------------------------------------------------\n";
     
     std:: cout << "\nNOTE: after you choose a card\n that card is popped out of sight\nso entering same number on different occasions\nwill choose another card :)\n\nNOTE :.//Count the position of your\n cards and enter it position.\n";
    
    PlayersTurn:
    do {
      int choose;
     std:: cout << "\nYour cards : ";
      showPlayerCards(player1);
      std:: cout << "Enter number to choose card : ";
      std:: cin >> choose;
      if(choose < 1 || choose > player1.size()){
        std:: cerr << "Number out of bounds\n";
        continue;
      }
      //user enters correct number
      else  {
          Card card1 = player1[choose - 1];
        std:: cout << "\nPlayer 1 card : ";  card1.showCard(); std:: cout << '\n';
          player1.erase(player1.begin() + (choose-1));
          int p = play(card1, player2);
          Card card2 = player2[p];
         std:: cout << "Player 2 card : "; card2.showCard();
          player2.erase(player2.begin() + p);
          std:: cout << '\n';
          
          if(card2 > card1) {
               if(player2.size() == 0) {
                 //then ;game is over
                 std:: cout << "\nPlayer 2 in last round\n  GAME OVER!";
                 return EXIT_SUCCESS;
               }
                goto player2Leads;       
          }
      }
   }
  
   while(player1.size() != 0);
   
   std:: cout << "\nPlayer 1 wins... GAME OVER\n";
   return EXIT_SUCCESS;
    
   player2Leads: 
       std:: cout << "\n\nPlayer 2 wins\n this round by presenting a more stronger card suit,\nbut this game is not over :) yet\nyou now have 5% chance of winning unless\nmaybe you want to prove me wrong ðŸ˜‚ðŸ˜‚\n\n\n";
      
   do {
      std:: cout << "Player 2 plays : ";
          int p = play(player2);
          Card card2 = player2[p];
          card2.showCard(); 
          player2.erase(player2.begin() + p);
   player1Turn:
          int choose;
          std:: cout << "\n\nYour cards : ";
          showPlayerCards(player1);
          std:: cout << "Enter number to choose card : ";
          std:: cin >> choose;
          
          if(choose < 1 || choose > player1.size()) {
          std:: cerr << "Number out of bounds\n";
            goto player1Turn;
          }
          
        else {
          Card card1 = player1[choose - 1];
          
          if(!(card1 == card2)) {
            if(haveSimilarSuitCard(card2, player1)) {
              std:: cout << "\nYou have a card with similar suit, sorry! You have to bring it out";
              
              goto player1Turn;
            }
          }
         
         std:: cout << "\nPlayer 2 card : "; card2.showCard();
       std:: cout << "\nPlayer 1 card : "; card1.showCard(); std:: cout << "\n";
     
          
       player1.erase(player1.begin() + (choose-1));
          std:: cout << '\n';
     if(card1 > card2)  {
               if(player1.size() == 0){
              
    std:: cout << "Phew! very lucky\nyou won in the last round\nPlayer 1 wins... GAME OVER!";
                return EXIT_SUCCESS;
             }
                 else { std:: cout << "\nCongratulations on winning this round\n you are on your road to victory\n keep maintaning your victory\nby making good choices or should i say guessess!ðŸ˜‚ðŸ˜‚\n\n";
                  goto PlayersTurn;
                }  
             }
          }          
      }
      
      while(player1.size() != 0);   
     
      std:: cout << "\nPlayer 2 wins... GAME OVER\n";
   return EXIT_SUCCESS;
       
}

void showDeck(Card deck[]) {
  for(size_t j = 0; j < 40; ++j) {
        deck[j].showCard();
        if(((j+1)%10) == 0) std:: cout << '\n'; 
    }
}

void shuffleCards(Card deck[]) {
    std:: srand(time(NULL));
    
    for(size_t j = 0; j < 40; ++j) {
        int r = rand() % 40;
        std:: swap(deck[j],deck[r]);
    }
}

void sortCards(std:: vector<Card> &cards) {
  for(int x = 1; x < cards.size(); ++x) {
    for(int y = 0; y <= x; ++y) {
       if(cards[y] > cards[x]) {
         std:: swap(cards[y], cards[x]);
       }
    }
  }
}

void setCards(Card deck[]) {
    for(size_t j = 0; j < 40; ++j) {
     deck[j].setCard((j%10)+5, Suit((j/10)));
    }
}
 
int play(Card &card, std:: vector<Card> &player2) {
     bool containsSuit = false;
     std:: vector<Card> possibleCards;

    for(auto c : player2) {
       //if player2 has cards with common suit store in possible cards
        if(c == card) {
          possibleCards.push_back(c); 
          
          if(containsSuit) 
               continue;
          containsSuit = true;
       }           
    }
    

    if(containsSuit) {
      
    sortCards(possibleCards);
     
     for(size_t j = 0; j < possibleCards.size(); ++j ) {
     if(possibleCards[j] > card) {
    auto f = std:: find(player2.begin(), player2.end(), possibleCards[j]);
    
      return (f - player2.begin());
    }
 }


 std:: srand(time(NULL));
 
  
      //if no better card was found
     
        int size = possibleCards.size();
        
      
        int randomCard = std:: rand() % size;
         
        auto f = std:: find(player2.begin(), player2.end(), possibleCards[randomCard]);
        
        return (f - player2.begin());
               
      }
  
        
  //if no such card of the same suit is found
    int size = player2.size();
   
   int randomCard = std:: rand() % size;
        
     auto f = std:: find(player2.begin(), player2.end(), player2[randomCard]);
        
       return (f - player2.begin());     
}

int play(std:: vector<Card> &player2) {
    std:: srand(time(NULL));
    size_t size = player2.size();
    int r = std:: rand() % size;
    
    return (r);
}

