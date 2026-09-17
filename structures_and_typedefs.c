#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> /* we are going to use the boolean type! */
#include <string.h>
#include <time.h>

#define MAXLEN 128 /* I'll make all strings a multiple of MAXLEN */
#define MAXSTR 127 /* longest possible string in this buffer */


/* we will use these later */

char *firstnames[] = {"Alex", "Sally", "Blasto", "Ceefax", "Peter", "John", "Amy", "Cassandra", "Liz", "Jennifer-Vanessa"};
char *lastnames[] = {"Mc", "Smith", "Lee", "Jones", "Garcia", "Peterson", "Frank", "Johnson", "Gorbachev", "Jingleheimer-Schmidt"};



/***************************
 * TYPEDEFS and STRUCTURES *
 * ************************/

/* there's a lot that could be said about both typedefs and structures (or
 * "structs")... this tutorial is just going to cover the basics. There's lots
 * of great info online about both topics.
 */

/************
 * typedefs *
 * *********/

/* 'typedef' is a way to give a new name to an existing type. There are
 * different reasons for why you might want to do this, but in short, if you
 * see unusual types in C source, they have probably been created through the
 * use of a typedef at some point in the code or one of its other files.
 *
 * To name a new type, do the following:
 */

typedef long long int MegaIntTM; // enterprise-grade integer

/* Now that I have typedef'ed MegaIntTM, I can use it anywhere in my code: */

void print_a_MegaIntTM(void) { // returns nothing, needs nothing

	MegaIntTM number = 5; /* boom, I just declared a MegaIntTM!!! */

	printf("My MegaIntTM is: %lld\n", number);

	/* since MegaIntTM is really a long long int, I use %lld */

}

/* for more information about typedefs, see:
 * https://www.geeksforgeeks.org/c/typedef-in-c/
 */

/***************
 * structures! *
 * ************/

/* C structures are aggregate data types with named members. In other words, a
 * structure can contain different types, and each member of a structure has
 * its own name. In this way, a structure may seem vaguely object-like.
 * However, it's more like an a kind of an array with a specific set of
 * elements that you access using a name rather than an index.
 *
 * Let's see how structs are defined:
 */

struct contact_card {
	char firstname[MAXLEN];
	char lastname[MAXLEN];
	float age;
	int birthyear;
	int birthmonth;
	int birthdaynum;
	bool likes_cilantro;
}; /* <--- notice this sneaky semi-colon! It's required */

/* Now, any contact_card I declare will have the named elements, and I can sort of access the elements the way you might access the properties of an object.
 *
 * Exactly how you access those elements depends on whether the struct variable
 * is a pointer to the structure, or whether it is the structure itself. This
 * is probably the most confusing thing about structures, but I'll demonstrate
 * it below.
 *
 * * For more information on C structures, see:
 * https://www.geeksforgeeks.org/c/structures-c/
 */

/* function to print the members of a contact_card 
 * This function has one argument, a pointer to an existing card!
 *
 * Declared here, but defined after main().
 */
void print_card(struct contact_card *card);

int main(int argc, char *argv[]) {

	/* first, let's use our new MegaIntTM type! */
	print_a_MegaIntTM();

	/* declare a struct_contact card and give it a name */
	struct contact_card card1;

	/* let's fill in that contact card with made-up nonsense */

	strncpy(card1.firstname, "Jarnathan", MAXSTR);
	strncpy(card1.lastname, "Kleeckson", MAXSTR);
	card1.age = 47.265; /* note the familiar dot notation of the struct member! */
	card1.birthyear = 1077;
	card1.birthmonth = 19;
	card1.birthdaynum = 37;
	card1.likes_cilantro = true; /* did you know cilantro's taste is genetic? */

	/* DOT ACCESSING is possible ONLY when you are directly operating on the
	 * structure, like we were, because the structure itself is in scope (in
	 * this case, because we declared it in this function.
	 *
	 * Remember that character arrays are really *pointers to space* used as a
	 * character array. This is why I can directly hand card1.firstname to
	 * strncpy() as a pointer... because it *is* already a pointer. (The struct
	 * card1 is not a pointer, but two of the members of card1 are pointers.)
	 */

	/* Now, let's print out a card! 
	 *
	 * Recall that print_card takes a pointer *to* a contact card, but we only
	 * have the actual contact card variable. Don't fret! Remember that we can
	 * always use the & symbol to get a pointer to a variable. I think of & as
	 * meaning "the address of" or "a pointer to" -- so, &card1 can be read as
	 * "a pointer to card1". Let's try it:
	 */

	print_card(&card1);

	/* *******************************************
	 * struct typedefs and arrays of structures! *
	 * ******************************************/

	/* Once a structure has been defined, the compiler knows how much space each structure of that type will require, and that's all that the compiler needs to be able to make an array of structures.
	 *
	 * Additionally, you can typedef a particular structure, to give it a more
	 * friendly name, if you like. (Note: defining a type for the struct isn't
	 * necessary for making arrays, but I'm combining the two steps here.)
	 *
	 * Let's typedef our struct contact_card, and then let's make an array of them:
	 */

	typedef struct contact_card ccard;

	/* now we can make an array of ccards */

	ccard rolodex[128];

	/* let's set all that memory to \0 */
	memset(rolodex, '\0', sizeof(ccard) * 128);


	/* let's randomly fill all 128 cards */

	int i = 0;
	int name_index;

	/* The C RNG rand() is not cryptographically secure! It's also not
	 * cryptographically secure to use the time of execution as the seed for
	 * the RNG. But we don't care about that in this case. */
	srand(time(NULL)); // seed RNG with current UNIX time in seconds

	for (i = 0; i < 128; i++) {

		name_index = (rand() % 10); // rand() is NOT cryptographically secure!
		strncpy(rolodex[i].firstname, firstnames[name_index], MAXSTR);
		
		name_index = (rand() % 10);
		strncpy(rolodex[i].lastname, lastnames[name_index], MAXSTR);
	
		/* lastname "Mc" is a special case, let's have some fun */	
		if (name_index == 0) {
			strncat(rolodex[i].lastname, rolodex[i].firstname, (MAXSTR - strlen(rolodex[i].lastname)));
			strncat(rolodex[i].lastname, "erson", (MAXSTR - strlen(rolodex[i].lastname)));
		}

		rolodex[i].age = (rand() % 100) * 1.0 + (rand() % 100) / 1000.0;
		/* age is obviously not calculated based on the birthdate and current
		 * date... but if you're feeling ambitious, it could be... */

		rolodex[i].birthyear = (rand() % 150) + 1900;
		rolodex[i].birthmonth = (rand() % 12) + 1;
		rolodex[i].birthdaynum = (rand() % 30) + 1; /* waves hands */

		rolodex[i].likes_cilantro = false; /* false is the default */
		if ((rand() % 2) == 0) {
			rolodex[i].likes_cilantro = true;
		}

		print_card(&rolodex[i]);

	}



	return 0;

}

void print_card(struct contact_card *card) {

	/* When calling this function, you provide it a pointer to an existing
	 * card. Inside this function, that card is accessed through the pointer
	 * *card.
	 *
	 * When working with pointers to structures, you access members using an arrow (->)
	 * instead of a dot, e.g., struct->member -- Otherwise, it's basically the same.
	 */

	printf("\n");
	printf("CONTACT CARD PRINTER 2000 v0.57a:\n");
	printf("---------------------------------\n");

	printf("Firstname: %s\n", card->firstname);
	printf("Lastname: %s\n", card->lastname);
	printf("Age: %f\n", card->age);
	printf("Birthday: %d-%d-%d\n", card->birthyear, card->birthmonth, card->birthdaynum);
	if (card->likes_cilantro) {
		printf("Likes cilantro.\n");
	} else {
		printf("Dislikes cilantro.\n");
	}
	printf("\n");

	/* void functions don't return anything */
}


